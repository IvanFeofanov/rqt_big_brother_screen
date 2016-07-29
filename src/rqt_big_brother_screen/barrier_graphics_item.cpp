#include <rqt_big_brother_screen/barrier_graphics_item.h>

BarrierGraphicsItem::BarrierGraphicsItem(QGraphicsItem* parent) :
    EditablePolygonGraphicsItem(parent)
{
    setDefaultParameters();
}

BarrierGraphicsItem::BarrierGraphicsItem(const QPolygonF& polygon,
        QGraphicsItem* parent):
    EditablePolygonGraphicsItem(polygon, parent)
{
    setDefaultParameters();
}

void BarrierGraphicsItem::setDefaultParameters()
{
    QPen main_pen = mainPen();
    main_pen.setColor(qRgb(0, 0, 255));
    setMainPen(main_pen);
}

