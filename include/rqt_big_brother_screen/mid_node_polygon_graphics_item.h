#ifndef MID_NODE_POLYGON_GRAPHICS_ITEM_H
#define MID_NODE_POLYGON_GRAPHICS_ITEM_H

#include <QGraphicsEllipseItem>

class MidNodePolygonGraphicsItem : public QGraphicsEllipseItem
{
public:
    explicit MidNodePolygonGraphicsItem(QGraphicsItem* parent = 0);
    MidNodePolygonGraphicsItem(int id, const QPointF &point,
           const QSize &size, QGraphicsItem* parent = 0);

    void setPos(const QPointF &pos);
    void setPos(qreal x, qreal y);

    void setSize(const QSize &size);

    QPointF pos() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    void createNode(const QPointF &point, const QSize &size);

private:
    int id_;
};

#endif // MID_NODE_POLYGON_GRAPHICS_ITEM_H
