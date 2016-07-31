#ifndef HINGE_RECT_GRAPHICS_ITEM_H
#define HINGE_RECT_GRAPHICS_ITEM_H

#include <QGraphicsEllipseItem>
#include <QPoint>

#include <rqt_big_brother_screen/editable_rect_graphics_item.h>

class EditableRectGraphicsItem;

class HingeRectGraphicsItem : public QGraphicsEllipseItem
{
public:
    explicit HingeRectGraphicsItem(QGraphicsItem* parent);
    HingeRectGraphicsItem(const QPoint& pos, const QSize &size,
            EditableRectGraphicsItem* rect_item, QGraphicsItem* parent);

    QPoint centerPoint() const;
    void setCenterPoint(const QPointF& point);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    void createHinge(const QPoint &pos, const QSize &size);

private:
    EditableRectGraphicsItem* rect_item_;

};

#endif // HINGE_RECT_GRAPHICS_ITEM_H
