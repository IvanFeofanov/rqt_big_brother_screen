#ifndef NODE_POLYGON_GRAPHICS_ITEM_H
#define NODE_POLYGON_GRAPHICS_ITEM_H

#include <rqt_big_brother_screen/polygon_graphics_item.h>

#include <QGraphicsEllipseItem>

class NodePolygonGraphicsItem : public QGraphicsEllipseItem
{
public:
    explicit NodePolygonGraphicsItem(QGraphicsItem* parent = 0);
    NodePolygonGraphicsItem(int id, const QPointF &point,
            const QSize &size, PolygonGraphicsItem* polygon_item,
            QGraphicsItem* parent = 0);

    QPointF centerPoint();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    void createNode(const QPointF &point, const QSize &size);

private:
    int id_;
    PolygonGraphicsItem* polygon_item_;
};

#endif // NODE_POLYGON_GRAPHICS_ITEM_H
