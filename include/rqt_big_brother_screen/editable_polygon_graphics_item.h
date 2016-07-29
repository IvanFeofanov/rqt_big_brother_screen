#ifndef EDITABLE_POLYGON_GRAPHICS_ITEM_H
#define EDITABLE_POLYGON_GRAPHICS_ITEM_H

#include <rqt_big_brother_screen/polygon_graphics_item.h>
#include <rqt_big_brother_screen/node_polygon_graphics_item.h>

#include <QGraphicsItemGroup>
#include <QPolygonF>
#include <QList>
#include <QPen>


class EditablePolygonGraphicsItem : public QGraphicsItemGroup
{
public:
    explicit EditablePolygonGraphicsItem(QGraphicsItem* parent = 0);
    EditablePolygonGraphicsItem(const QPolygonF &polygon,
            QGraphicsItem* parent = 0);

    void setPolygon(const QPolygonF &polygon);
    QPolygonF polygon() const;

    void removeNode(int node_id);
    void addNode(int node_id, const QPointF &point);

    void setEditable(bool is_editable);
    bool isEditable() const;

    void setNodeSize(const QSize& size);
    QSize nodeSize() const;

    void setMidNodeSize(const QSize& size);
    QSize midNodeSize() const;

    void setMainPen(const QPen& pen);
    QPen mainPen() const;

    void setMainBrush(const QBrush& brush);
    QBrush mainBrush();

    void setNodePen(const QPen& pen);
    QPen nodePen() const;

    void setNodeBrush(const QBrush& brush);
    QBrush nodeBrush() const;

private:
    void setDefaultParameters();

private:
    QList<NodePolygonGraphicsItem*> nodes_;
    PolygonGraphicsItem* polygon_item_;

    bool is_editable_;

    QSize node_size_;
    QSize mid_node_size_;

    QPen main_pen_;
    QBrush main_brush_;

    QPen node_pen_;
    QBrush node_brush_;
};

#endif // EDITABLE_POLYGON_GRAPHICS_ITEM_H
