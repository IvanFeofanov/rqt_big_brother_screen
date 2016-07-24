#include <rqt_big_brother_screen/mid_node_polygon_graphics_item.h>
#include <rqt_big_brother_screen/editable_polygon_graphics_item.h>

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

MidNodePolygonGraphicsItem::MidNodePolygonGraphicsItem(QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent)
{
    id_ = -1;
    hide();
}

MidNodePolygonGraphicsItem::MidNodePolygonGraphicsItem(int id,
        const QPointF &point, const QSize &size, QGraphicsItem *parent):
    QGraphicsEllipseItem(parent)
{
    id_ = id;
    createNode(point, size);
}

void MidNodePolygonGraphicsItem::setPos(const QPointF &pos)
{
    QGraphicsEllipseItem::setPos(pos.x() - rect().width() / 2,
                                 pos.y() - rect().height() / 2);
}

void MidNodePolygonGraphicsItem::setPos(qreal x, qreal y)
{
    setPos(QPointF(x, y));
}

QPointF MidNodePolygonGraphicsItem::pos() const
{
    QPointF point(QGraphicsEllipseItem::pos().x() + rect().width() / 2,
                  QGraphicsEllipseItem::pos().y() + rect().height() / 2);

    return point;
}

void MidNodePolygonGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
           ((EditablePolygonGraphicsItem*)parentItem())->addNode(id_, pos());
    }
}

void MidNodePolygonGraphicsItem::createNode(const QPointF &point, const QSize &size)
{
    setRect(QRect(QPoint(0, 0), size));
    setPos(point);
}
