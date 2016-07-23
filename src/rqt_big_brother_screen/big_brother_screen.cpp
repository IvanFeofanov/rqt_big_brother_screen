#include <rqt_big_brother_screen/big_brother_screen.h>
#include <rqt_big_brother_screen/settings_dialog.h>

#include <pluginlib/class_list_macros.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <highgui.h>

#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>
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
    QGraphicsScene* scene = new QGraphicsScene(this);
    image_item_ =  new ImageGraphicsItem(QImage());
    scene->addItem(image_item_);
    ui_.graphicsView->setScene(scene);
    ui_.graphicsView->setRenderHint(QPainter::Antialiasing);

    //edit settings
    connect(ui_.pushButtonSettings, SIGNAL(pressed()),
            this, SLOT(editSettings()));
    connect(ui_.pushButtonZoomOne, SIGNAL(pressed()),
            this, SLOT(setZoomOne()));

    //image transport subscriber
    setTopicImage("");
}

void BigBrotherScreen::shutdownPlugin()
{
    image_subscriber_.shutdown();
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

void BigBrotherScreen::setArea()
{

}

}//namespace

PLUGINLIB_DECLARE_CLASS(rqt_big_brother_screen, BigBrotherScreen,
        rqt_big_brother_screen::BigBrotherScreen, rqt_gui_cpp::Plugin)
