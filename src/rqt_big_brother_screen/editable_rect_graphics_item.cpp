#include <rqt_big_brother_screen/editable_rect_graphics_item.h>

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

EditableRectGraphicsItem::EditableRectGraphicsItem(QGraphicsItem *parent):
    QGraphicsRectItem(parent)
{

    setDefaultParameters();
    createHingeItem();
    setFlags(QGraphicsItem::ItemIsMovable);
}

EditableRectGraphicsItem::EditableRectGraphicsItem(const QRect &rect,
        QGraphicsItem *parent) :
    QGraphicsRectItem(parent)
{

    setRect(rect);
    setDefaultParameters();
    createHingeItem();
    setFlags(QGraphicsItem::ItemIsMovable);
}

EditableRectGraphicsItem::~EditableRectGraphicsItem()
{
    delete hinge_item_;
}

void EditableRectGraphicsItem::update(const QPoint &hinge_pos)
{
    QPointF center = rect().center();
    QSize size(abs(hinge_pos.x() - center.x()) * 2,
               abs(hinge_pos.y() - center.y()) * 2);
    QPointF pos(center.x() - size.width() / 2,
                center.y() - size.height() / 2);

    setRect(QRect(pos.toPoint(), size));
}

void EditableRectGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF prev_center = rect().center();

    QGraphicsRectItem::mouseMoveEvent(event);

    QPointF hinge_center = hinge_item_->centerPoint();
    QPointF delta(prev_center.x() - rect().center().x(),
                  prev_center.y() - rect().center().y());
    hinge_center.setX(hinge_center.x() + delta.x());
    hinge_center.setY(hinge_center.y() + delta.y());

    hinge_item_->setCenterPoint(hinge_center);

}

void EditableRectGraphicsItem::setDefaultParameters()
{
    hinge_size_ = QSize(10, 10);
    hinge_pen_.setColor(Qt::black);
    hinge_brush_ = QBrush(Qt::white);

    QPen pen(QColor("gray"));
    pen.setWidth(2);
    setPen(pen);

    QBrush brush(QColor(152, 152, 152, 50));
    setBrush(brush);
}

void EditableRectGraphicsItem::createHingeItem()
{
    hinge_item_ = new HingeRectGraphicsItem(rect().bottomRight().toPoint(),
            hinge_size_, this, this);

    hinge_item_->setPen(hinge_pen_);
    hinge_item_->setBrush(hinge_brush_);
}
