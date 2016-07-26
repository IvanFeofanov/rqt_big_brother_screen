#include <rqt_big_brother_screen/area_edit_mode.h>
#include <iostream>
AreaEditMode::AreaEditMode(QObject* parent) :
    EditMode(parent)
{
    polygon_item_ = 0;
    /*TODO ros::topic*/

}

AreaEditMode::AreaEditMode(EditablePolygonGraphicsItem* polygon_item,
        /*TODO ros::topic,*/QObject* parent) :
    EditMode(parent)
{
    polygon_item_ = polygon_item;
    /*TODO ros::topic*/

    polygon_item_->setEditable(true);
}

void AreaEditMode::cancel()
{
    endEdit();
}

void AreaEditMode::save()
{
    endEdit();
}

void AreaEditMode::endEdit()
{
    polygon_item_->setEditable(false);
}
