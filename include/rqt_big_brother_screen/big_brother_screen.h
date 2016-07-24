#ifndef RQT_BIG_BROTHER_SCREEN_H
#define RQT_BIG_BROTHER_SCREEN_H

#include <rqt_big_brother_screen/ui_big_brother_screen.h>
#include <rqt_big_brother_screen/image_graphics_item.h>

#include <rqt_big_brother_screen/editable_polygon_graphics_item.h>

#include <rqt_gui_cpp/plugin.h>
#include <image_transport/image_transport.h>

#include <QWidget>
#include <QGraphicsPixmapItem>

namespace rqt_big_brother_screen
{

class BigBrotherScreen : public rqt_gui_cpp::Plugin
{
    Q_OBJECT

public:
    BigBrotherScreen();
    virtual void initPlugin(qt_gui_cpp::PluginContext& context);
    virtual void shutdownPlugin();
    virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings,
            qt_gui_cpp::Settings& instance_settings) const;
    virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
            const qt_gui_cpp::Settings& instance_settings);
private:
    void callbackImage(const sensor_msgs::ImageConstPtr &msg);
    void setTopicImage(const QString &topic);
    
    void createScene();
    void createImageItem();
    void createAreaItem();

private slots:
    void editSettings();
    void setZoomOne();
    void editArea(bool is_editable);

private:
    Ui::Window ui_;
    QWidget* widget_;

    image_transport::Subscriber image_subscriber_;

    ImageGraphicsItem* image_item_;
    EditablePolygonGraphicsItem* area_item_;
};

}

#endif
