#include <rqt_big_brother_screen/polygon_graphics_item.h>

#include <QPointF>
#include <iostream>
PolygonGraphicsItem::PolygonGraphicsItem(QGraphicsItem *parent):
    QGraphicsPolygonItem(parent)
{
    setDefaultParameters();
    current_polygon_size_ = 0;
}

PolygonGraphicsItem::PolygonGraphicsItem(const QPolygonF &polygon,
                                         QGraphicsItem *parent) :
    QGraphicsPolygonItem(parent)
{
    setDefaultParameters();
    setPolygon(polygon);
    current_polygon_size_ = 0;
}

void PolygonGraphicsItem::updateNode(int id,
                                     const QPointF &new_point)
{
    QPolygonF points = polygon();
    points[id] = new_point;
    setPolygon(points);
}

void PolygonGraphicsItem::setPolygon(const QPolygonF &polygon)
{
    QGraphicsPolygonItem::setPolygon(polygon);

    //create or update middle nodes
    if(current_polygon_size_ != polygon.size()){
        createMidNodes(polygon.size());
        current_polygon_size_ = polygon.size();
    }else{
        updateMidNodes();
    }
}

void PolygonGraphicsItem::setPen(const QPen& pen)
{
    QGraphicsPolygonItem::setPen(pen);

    foreach(MidNodePolygonGraphicsItem* mid_node, mid_nodes_){
        mid_node->setPen(pen);
    }
}

void PolygonGraphicsItem::setBrush(const QBrush& brush)
{
    QGraphicsPolygonItem::setBrush(brush);

    foreach(MidNodePolygonGraphicsItem* mid_node, mid_nodes_){
        mid_node->setBrush(brush);
    }
}

void PolygonGraphicsItem::setMidNodeSize(const QSize& size)
{
    mid_node_size_ = size;

    foreach(MidNodePolygonGraphicsItem* mid_node, mid_nodes_){
        mid_node->setSize(size);
    }
}

QSize PolygonGraphicsItem::midNodeSize() const
{
    return mid_node_size_;
}

void PolygonGraphicsItem::setDefaultParameters()
{
    mid_node_size_ = QSize(8, 8);

    QPen pen;
    pen.setColor(qRgb(0, 255, 0));
    pen.setWidth(2);
    setPen(pen);

    QBrush brush;
    setBrush(brush);
}

void PolygonGraphicsItem::createMidNodes(int n)
{
    //remove old middle nodes
    foreach(QGraphicsItem* item, mid_nodes_)
        delete item;
    mid_nodes_.clear();

    //create new middle nodes
    for(int i = 0; i < n; ++i){
        MidNodePolygonGraphicsItem* mid_node = new MidNodePolygonGraphicsItem(
                   i, getMiddlePoint(i), mid_node_size_, parentItem());
        mid_node->setPen(pen());
        mid_node->setBrush(brush());

        mid_nodes_.push_back(mid_node);
    }
}

void PolygonGraphicsItem::updateMidNodes()
{
    for(int i = 0; i < mid_nodes_.size(); ++i)
        mid_nodes_[i]->setPos(getMiddlePoint(i));
}

QPoint PolygonGraphicsItem::getMiddlePoint(int node_id)
{
    QPolygonF polygon = this->polygon();
    QPointF begin(polygon[node_id]);
    QPointF end(polygon[node_id != (polygon.size()-1) ? node_id+1 : 0]);
    QPoint point((begin.x() + end.x()) / 2,
                 (begin.y() + end.y()) / 2);

    return point;
}

