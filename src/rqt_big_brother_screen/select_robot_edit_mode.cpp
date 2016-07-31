#include <rqt_big_brother_screen/select_robot_edit_mode.h>

SelectRobotEditMode::SelectRobotEditMode(QObject* parent) :
    EditMode(parent)
{
    select_tool_item_ = 0;
}

SelectRobotEditMode::SelectRobotEditMode(
        EditableRectGraphicsItem* select_tool_item,
        /*TODO ros::topic*/
        QObject* parent) :
    EditMode(parent)
{
    select_tool_item_ = select_tool_item;

    select_tool_item_->show();
}

void SelectRobotEditMode::cancel()
{
    select_tool_item_->hide();
}

void SelectRobotEditMode::save()
{
    select_tool_item_->hide();
    //TODO ros::send
}

