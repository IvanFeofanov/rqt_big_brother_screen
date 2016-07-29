#include <rqt_big_brother_screen/node_polygon_graphics_item.h>
#include <rqt_big_brother_screen/editable_polygon_graphics_item.h>

#include <QGraphicsSceneMouseEvent>

#include <QDebug>

NodePolygonGraphicsItem::NodePolygonGraphicsItem(QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent)
{
    id_ = -1;
    polygon_item_ = 0;
    hide();
}

NodePolygonGraphicsItem::NodePolygonGraphicsItem(int id,
         const QPointF &point, const QSize &size,
         PolygonGraphicsItem *polygon_item, QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent)
{
    id_ = id;
    polygon_item_ = polygon_item;

    createNode(point, size);
    setFlags(QGraphicsItem::ItemIsMovable);
}

QPointF NodePolygonGraphicsItem::centerPoint() const 
{
    QPointF centerP(pos().x() + rect().width() / 2,
                    pos().y() + rect().height() / 2);
    return centerP;
}

void NodePolygonGraphicsItem::setSize(const QSize& size)
{
    createNode(rect().topLeft(), size);
}

void NodePolygonGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    polygon_item_->updateNode(id_, centerPoint());
    QGraphicsEllipseItem::mouseMoveEvent(event);
}

void NodePolygonGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        ((EditablePolygonGraphicsItem*)parentItem())->removeNode(id_);
    }
}

void NodePolygonGraphicsItem::createNode(const QPointF &point, const QSize &size)
{
    setRect(QRect(QPoint(0, 0), size));

    setPos(point.x() - rect().width() / 2,
           point.y() - rect().height() / 2);
}
