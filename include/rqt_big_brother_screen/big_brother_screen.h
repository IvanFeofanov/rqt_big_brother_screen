#ifndef RQT_BIG_BROTHER_SCREEN_H
#define RQT_BIG_BROTHER_SCREEN_H

#include <rqt_big_brother_screen/ui_big_brother_screen.h>

#include <rqt_big_brother_screen/image_graphics_item.h>
#include <rqt_big_brother_screen/editable_polygon_graphics_item.h>
#include <rqt_big_brother_screen/barrier_graphics_item.h>
#include <rqt_big_brother_screen/trajectory_graphics_item.h>
#include <rqt_big_brother_screen/editable_rect_graphics_item.h>

#include <rqt_big_brother_screen/edit_mode.h>
#include <rqt_big_brother_screen/area_edit_mode.h>
#include <rqt_big_brother_screen/barrier_edit_mode.h>
#include <rqt_big_brother_screen/select_robot_edit_mode.h>

#include <rqt_gui_cpp/plugin.h>
#include <image_transport/image_transport.h>

#include <QWidget>
#include <QSet>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>

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
    // void callbackRobotPos();

    void setTopicImage(const QString &topic); //set topic name

    void createScene();
    void createActions();
    void createButtons();
    void createContextMenu();
    void createImageItem();
    void createAreaItem();
    void createTraversedPathItem();
    void createTrajectoryItem();
    void createSelectToolItem();
    void createRobotItem();

    void setEditView(bool is_edit_view = false);
    void setEditMode(EditMode* edit_mode = 0);

private slots:
    void saveEdit();
    void cancelEdit();

    void editSettings();
    void setZoomOne();
    void editArea();

    void addBarrier();
    void editBarriers();

    void showTraversedPath(bool is_visible);
    void showTrajectory(bool is_visible);
    void clearTraversedPath();

    void selectRobot();
    void showRobot(bool is_visible);

private:
    Ui::Window ui_;
    QWidget* widget_;

    EditMode* edit_mode_;

    QAction* action_set_zoom1_;
    QAction* action_edit_settings_;
    QAction* action_edit_area_;
    QAction* action_add_barrier_;
    QAction* action_edit_barriers_;
    QAction* action_show_path_;
    QAction* action_show_trajectory_;
    QAction* action_clear_path_;
    QAction* action_select_robot_;
    QAction* action_show_robot_;

    image_transport::Subscriber image_subscriber_;

    ImageGraphicsItem* image_item_;
    EditablePolygonGraphicsItem* area_item_;
    TrajectoryGraphicsItem* traversed_path_item_;
    TrajectoryGraphicsItem* trajectory_item_;
    EditableRectGraphicsItem* select_tool_item_;
    QGraphicsRectItem* marker_robot_item_;

    QList<BarrierGraphicsItem*> barriers_;
};

}

#endif
