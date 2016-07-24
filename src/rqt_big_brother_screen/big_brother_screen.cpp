#include <rqt_big_brother_screen/big_brother_screen.h>
#include <rqt_big_brother_screen/settings_dialog.h>

#include <pluginlib/class_list_macros.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <highgui.h>

#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>
#include <QPolygonF>

#include <iostream>
namespace rqt_big_brother_screen
{

BigBrotherScreen::BigBrotherScreen() :
    rqt_gui_cpp::Plugin(),
    widget_(0)
{
    setObjectName("bigBrotherScreen");
}

void BigBrotherScreen::initPlugin(qt_gui_cpp::PluginContext& context)
{
    //setup ui
    widget_ = new QWidget();
    ui_.setupUi(widget_);
    context.addWidget(widget_);

    //graphics view
    createScene();
    createImageItem();
    createAreaItem();
    createTraversedPathItem();

    //edit settings
    connect(ui_.pushButtonSettings, SIGNAL(pressed()),
            this, SLOT(editSettings()));
    //set zoom
    connect(ui_.pushButtonZoomOne, SIGNAL(pressed()),
            this, SLOT(setZoomOne()));
    //edit area
    connect(ui_.pushButtonArea, SIGNAL(toggled(bool)),
            this, SLOT(editArea(bool)));
    //clear traversed path
    connect(ui_.pushButtonClearPath, SIGNAL(pressed()),
            this, SLOT(clearTraversedPath()));

    //image transport subscriber
    setTopicImage("");
}

void BigBrotherScreen::shutdownPlugin()
{
    image_subscriber_.shutdown();

    delete image_item_;
    delete area_item_;
    delete traversed_path_item_;
}

void BigBrotherScreen::saveSettings(qt_gui_cpp::Settings& plugin_settings,
        qt_gui_cpp::Settings& instance_settings) const
{
}

void BigBrotherScreen::restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
        const qt_gui_cpp::Settings& instance_settings)
{
}

void BigBrotherScreen::callbackImage(const sensor_msgs::ImageConstPtr &msg)
{
    cv_bridge::CvImageConstPtr cv_ptr;
    cv::Mat cv_image;

    try{
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
        cv_image = cv_ptr->image;
    }catch(cv_bridge::Exception &e){
        ROS_ERROR("cv_bridge: %s", e.what());
    }

    //cv::Mat to QImage
    QImage image(cv_image.data, cv_image.cols,
            cv_image.rows, cv_image.step[0], QImage::Format_RGB888);

    image_item_->setImage(image);
}

void BigBrotherScreen::setTopicImage(const QString &topic)
{
    const int QUEUE_SIZE = 1;

    image_subscriber_.shutdown();

    //reset image
    //TODO

    //new topic
    if(!topic.isEmpty()){
        image_transport::ImageTransport image_transport(getNodeHandle());

        try{
            image_subscriber_ = image_transport.subscribe(topic.toStdString(),
                    QUEUE_SIZE, &BigBrotherScreen::callbackImage, this);
        }catch(image_transport::TransportLoadException& e){
            ROS_ERROR("Load image transport plugin faled %s", e.what());
        }
    }
}

void BigBrotherScreen::createScene()
{
    QRect default_scene_size(0, 0, 640, 480);
    QGraphicsScene* scene = new QGraphicsScene(default_scene_size, this);
    ui_.graphicsView->setScene(scene);
    ui_.graphicsView->setRenderHint(QPainter::Antialiasing);
}

void BigBrotherScreen::createImageItem()
{
    image_item_ =  new ImageGraphicsItem(QImage());
    ui_.graphicsView->scene()->addItem(image_item_);
}

void BigBrotherScreen::createAreaItem()
{
    QPolygonF polygon;
    QRectF scene_rect = ui_.graphicsView->scene()->sceneRect();
    QPointF center_point(scene_rect.width() / 2, scene_rect.height() / 2);
    polygon << QPointF( center_point.x() - scene_rect.width() / 4,
                        center_point.y() - scene_rect.height() / 4)
            << QPointF( center_point.x() + scene_rect.width() / 4,
                        center_point.y() - scene_rect.height() / 4)
            << QPointF( center_point.x() + scene_rect.width() / 4,
                        center_point.y() + scene_rect.height() / 4)
            << QPointF( center_point.x() - scene_rect.width() / 4,
                        center_point.y() + scene_rect.height() / 4);

    area_item_ = new EditablePolygonGraphicsItem(polygon);
    ui_.graphicsView->scene()->addItem(area_item_);
}

void BigBrotherScreen::createTraversedPathItem()
{
    QList<QPointF> points;
    points  << QPointF(0, 0)
            << QPointF(50, 50)
            << QPointF(50, 100);
    traversed_path_item_ = new TrajectoryGraphicsItem(points);
    ui_.graphicsView->scene()->addItem(traversed_path_item_);
}

void BigBrotherScreen::editSettings()
{
    SettingsDialog* sd = new SettingsDialog();

    //set current settings
    QString current_topic = QString::fromStdString(image_subscriber_.getTopic());
    sd->selectTopicImage(current_topic);

    int status = sd->exec();

    if(status == QDialog::Accepted){
        setTopicImage(sd->topicImage());
    }

    delete sd;
}

void BigBrotherScreen::setZoomOne()
{
    ui_.graphicsView->fitInView(image_item_, Qt::KeepAspectRatio);
}

void BigBrotherScreen::editArea(bool is_editable)
{
    area_item_->setEditable(is_editable);

    // if(!is_editable)
        // TODO send current area
}

void BigBrotherScreen::clearTraversedPath()
{
    traversed_path_item_->clear();
    //TODO
}

}//namespace

PLUGINLIB_DECLARE_CLASS(rqt_big_brother_screen, BigBrotherScreen,
        rqt_big_brother_screen::BigBrotherScreen, rqt_gui_cpp::Plugin)
