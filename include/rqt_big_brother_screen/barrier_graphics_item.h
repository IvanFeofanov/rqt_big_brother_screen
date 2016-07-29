#ifndef BARRIER_GRAPHICS_ITEM_H
#define BARRIER_GRAPHICS_ITEM_H

#include <rqt_big_brother_screen/editable_polygon_graphics_item.h>

class BarrierGraphicsItem : public EditablePolygonGraphicsItem
{
public:
    explicit BarrierGraphicsItem(QGraphicsItem* parent = 0);
    BarrierGraphicsItem(const QPolygonF& polygon, QGraphicsItem* parent = 0);

private:
    void setDefaultParameters();

};

#endif
