#ifndef AREA_EDIT_MODE_H
#define AREA_EDIT_MODE_H

#include <rqt_big_brother_screen/edit_mode.h>
#include <rqt_big_brother_screen/editable_polygon_graphics_item.h>

#include <QPolygon>

class AreaEditMode : public EditMode
{
    Q_OBJECT

public:
    explicit AreaEditMode(QObject* parent = 0);
    AreaEditMode(EditablePolygonGraphicsItem* polygon_item,
            /*TODO ros::topic*/QObject* parent = 0);

    void cancel();
    void save();

private:
    EditablePolygonGraphicsItem* polygon_item_;
    QPolygonF saved_polygon_;
    /*TODO ros::topic*/
};

#endif
