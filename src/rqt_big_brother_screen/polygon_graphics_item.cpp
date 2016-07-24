#include <rqt_big_brother_screen/polygon_graphics_item.h>

#include <QPen>
#include <QPointF>

PolygonGraphicsItem::PolygonGraphicsItem(QGraphicsItem *parent):
    QGraphicsPolygonItem(parent)
{
    current_polygon_size_ = 0;
}

PolygonGraphicsItem::PolygonGraphicsItem(const QPolygonF &polygon,
                                         QGraphicsItem *parent) :
    QGraphicsPolygonItem(parent)
{
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

void PolygonGraphicsItem::createMidNodes(int n)
{
    //remove old middle nodes
    foreach(QGraphicsItem* item, mid_nodes_)
        delete item;
    mid_nodes_.clear();

    //default parameters
    QPen default_pen;
    default_pen.setColor(qRgb(0, 255, 0));
    default_pen.setWidth(1);
    QBrush default_brush(Qt::white);
    QSize default_size = QSize(8, 8);

    //create new middle nodes
    for(int i = 0; i < n; ++i){
        MidNodePolygonGraphicsItem* mid_node = new MidNodePolygonGraphicsItem(
                   i, getMiddlePoint(i), default_size, parentItem());
        mid_node->setPen(default_pen);
        mid_node->setBrush(default_brush);

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

