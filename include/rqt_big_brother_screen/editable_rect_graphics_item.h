#ifndef EDITABLE_RECT_GRAPHICS_ITEM_H
#define EDITABLE_RECT_GRAPHICS_ITEM_H

#include <rqt_big_brother_screen/hinge_rect_graphics_item.h>

#include <QGraphicsRectItem>
#include <QPoint>

#include <QPen>
#include <QBrush>

class HingeRectGraphicsItem;

class EditableRectGraphicsItem : public QGraphicsRectItem
{
public:
    explicit EditableRectGraphicsItem(QGraphicsItem* parent = 0);
    EditableRectGraphicsItem(const QRect& rect, QGraphicsItem *parent = 0);
    ~EditableRectGraphicsItem();

    void update(const QPoint& hinge_pos);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    void setDefaultParameters();
    void createHingeItem();

private:
    HingeRectGraphicsItem* hinge_item_;

    QSize hinge_size_;
    QPen hinge_pen_;
    QBrush hinge_brush_;
};

#endif // EDITABLE_RECT_GRAPHICS_ITEM_H
