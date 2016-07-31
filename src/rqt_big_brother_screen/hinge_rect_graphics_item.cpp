#include <rqt_big_brother_screen/hinge_rect_graphics_item.h>

HingeRectGraphicsItem::HingeRectGraphicsItem(QGraphicsItem* parent) :
    QGraphicsEllipseItem(parent)
{
    rect_item_ = 0;
    hide();
}

HingeRectGraphicsItem::HingeRectGraphicsItem(const QPoint &pos, const QSize &size,
        EditableRectGraphicsItem *rect_item, QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent)
{
    rect_item_ = rect_item;
    createHinge(pos, size);
    setFlags(QGraphicsItem::ItemIsMovable);
}

QPoint HingeRectGraphicsItem::centerPoint() const
{
    QPoint center_point(pos().x() + rect().width() / 2,
                        pos().y() + rect().height() / 2);
    return center_point;
}

void HingeRectGraphicsItem::setCenterPoint(const QPointF &point)
{
    setPos(point.x() - rect().width() / 2,
           point.y() - rect().height() / 2);
}

void HingeRectGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsEllipseItem::mouseMoveEvent(event);
    rect_item_->update(centerPoint());
}

void HingeRectGraphicsItem::createHinge(const QPoint &pos, const QSize &size)
{
    setRect(QRect(QPoint(0, 0), size));

    setCenterPoint(pos);
}
