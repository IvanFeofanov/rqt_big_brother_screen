#ifndef POLYGON_GRAPHICS_ITEM_H
#define POLYGON_GRAPHICS_ITEM_H

#include <rqt_big_brother_screen/mid_node_polygon_graphics_item.h>

#include <QGraphicsPolygonItem>
#include <QList>

class PolygonGraphicsItem : public QGraphicsPolygonItem
{
public:
    explicit PolygonGraphicsItem(QGraphicsItem* parent = 0);
    PolygonGraphicsItem(const QPolygonF &polygon,
                        QGraphicsItem* parent = 0);

    void updateNode(int id, const QPointF &new_point);

    void setPolygon(const QPolygonF &polygon);

private:
    void createMidNodes(int n);
    void updateMidNodes();
    QPoint getMiddlePoint(int node_id);

private:
    QList<MidNodePolygonGraphicsItem*> mid_nodes_;
    int current_polygon_size_;
};

#endif // POLYGON_GRAPHICS_ITEM_H
