#include <rqt_big_brother_screen/area_edit_mode.h>

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

    saved_polygon_ = polygon_item_->polygon();
    polygon_item_->setEditable(true);
}

void AreaEditMode::cancel()
{
    polygon_item_->setPolygon(saved_polygon_);
    polygon_item_->setEditable(false);
}

void AreaEditMode::save()
{
    polygon_item_->setEditable(false);
    /*TODO ros::send*/
}
