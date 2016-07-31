#ifndef SELECT_ROBOT_EDIT_MODE_H
#define SELECT_ROBOT_EDIT_MODE_H

#include <rqt_big_brother_screen/edit_mode.h>
#include <rqt_big_brother_screen/editable_rect_graphics_item.h>

class SelectRobotEditMode : public EditMode
{
    Q_OBJECT

public:
    explicit SelectRobotEditMode(QObject* parent = 0);
    SelectRobotEditMode(EditableRectGraphicsItem* select_tool_item,
            /*TODO ros::topic*/QObject* parent);

    void cancel();
    void save();

private:
    /*TODO ros::topics*/

    EditableRectGraphicsItem* select_tool_item_;
};


#endif
