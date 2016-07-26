#include <rqt_big_brother_screen/big_brother_screen.h>

#include <rqt_big_brother_screen/settings_dialog.h>
#include <rqt_big_brother_screen/graphics_scene_with_menu.h>

#include <pluginlib/class_list_macros.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <highgui.h>

#include <QImage>
#include <QPixmap>
#include <QPolygonF>

#include <QMenu>
#include <QGraphicsScene>
#include <QAction>

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

    edit_mode_ = 0;

    //graphics view
    createScene();
    createActions();
    createButtons();
    createContextMenu();
    createImageItem();
    createAreaItem();
    createTraversedPathItem();

    setEditView(false);

    //set zoom one
    connect(action_set_zoom1_, SIGNAL(triggered()),
            this, SLOT(setZoomOne()));
    //save edit
    connect(ui_.pushButtonSaveEdit, SIGNAL(pressed()),
            this, SLOT(saveEdit()));
    connect(ui_.pushButtonSaveEdit, SIGNAL(pressed()),
            this, SLOT(setEditView()));
    //cancel edit
    connect(ui_.pushButtonCancelEdit, SIGNAL(pressed()),
            this, SLOT(cancelEdit()));
    connect(ui_.pushButtonCancelEdit, SIGNAL(pressed()),
            this, SLOT(setEditView()));
    //edit settings
    connect(action_edit_settings_, SIGNAL(triggered()),
            this, SLOT(editSettings()));
    //edit area
    connect(action_edit_area_, SIGNAL(triggered()),
            this, SLOT(editArea()));
    //clear path
    connect(action_clear_path_, SIGNAL(triggered()),
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
    GraphicsSceneWithMenu* scene =
        new GraphicsSceneWithMenu(default_scene_size, this);
    ui_.graphicsView->setScene(scene);
    ui_.graphicsView->setRenderHint(QPainter::Antialiasing);
}

void BigBrotherScreen::createActions()
{
    action_set_zoom1_ = new QAction("Zoom 1", this);
    action_edit_settings_ = new QAction("Edit Settings...", this);

    action_edit_area_ = new QAction("Edit Area", this);

    action_add_barrier_ = new QAction("Add Barrier", this);
    action_edit_barriers_ = new QAction("Edit Barriers", this);
    action_remove_barriers_ = new QAction("Remove Barriers", this);

    action_show_path_ = new QAction("Show Path", this);
    action_show_path_->setCheckable(true);
    action_show_trajectory_ = new QAction("Show Trajectory", this);
    action_show_trajectory_->setCheckable(true);
    action_clear_path_ = new QAction("Clear Path", this);

    action_select_robot_ = new QAction("Select The Robot", this);
}

void BigBrotherScreen::createButtons()
{
    //zoom 1 button
    ui_.toolButtonZoomOne->setDefaultAction(action_set_zoom1_);
    ui_.toolButtonZoomOne->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

void BigBrotherScreen::createContextMenu()
{
    GraphicsSceneWithMenu* scene =
        (GraphicsSceneWithMenu*)ui_.graphicsView->scene();

    QMenu* menu = new QMenu("file", ui_.graphicsView);
    menu->addAction(action_edit_settings_);

    menu->addSeparator();

    menu->addAction(action_edit_area_);

    menu->addSeparator();

    menu->addAction(action_add_barrier_);
    menu->addAction(action_edit_barriers_);
    menu->addAction(action_remove_barriers_);

    menu->addSeparator();

    menu->addAction(action_show_path_);
    menu->addAction(action_show_trajectory_);
    menu->addAction(action_clear_path_);
    menu->addAction(action_select_robot_);

    scene->setMenu(menu);
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
    traversed_path_item_ = new TrajectoryGraphicsItem();
}

bool BigBrotherScreen::isEditView()
{
    return ui_.pushButtonSaveEdit->isVisible();
}

void BigBrotherScreen::setEditView(bool is_edit_view)
{
    if(is_edit_view){
        ui_.pushButtonSaveEdit->show();
        ui_.pushButtonCancelEdit->show();
    }else{
        ui_.pushButtonSaveEdit->hide();
        ui_.pushButtonCancelEdit->hide();
    }
}

void BigBrotherScreen::saveEdit()
{
    if(edit_mode_ != 0)
        edit_mode_->save();

    delete edit_mode_; //edit end
    edit_mode_ = 0;
}

void BigBrotherScreen::cancelEdit()
{
    if(edit_mode_ != 0)
        edit_mode_->cancel();

    delete edit_mode_; //edit end
    edit_mode_ = 0;
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

void BigBrotherScreen::editArea()
{
    delete edit_mode_;
    edit_mode_ = new AreaEditMode(area_item_, this);
    setEditView(true);
}

void BigBrotherScreen::clearTraversedPath()
{
    traversed_path_item_->clear();
    //TODO
}

}//namespace

PLUGINLIB_DECLARE_CLASS(rqt_big_brother_screen, BigBrotherScreen,
        rqt_big_brother_screen::BigBrotherScreen, rqt_gui_cpp::Plugin)
