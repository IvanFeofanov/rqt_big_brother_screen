#include <rqt_big_brother_screen/editable_polygon_graphics_item.h>

#include <QDebug>

EditablePolygonGraphicsItem::EditablePolygonGraphicsItem(QGraphicsItem *parent) :
    QGraphicsItemGroup(parent)
{
    polygon_item_ = 0;
    is_editable_ = false;
}

EditablePolygonGraphicsItem::EditablePolygonGraphicsItem(const QPolygonF &polygon,
                                                         QGraphicsItem *parent) :
    QGraphicsItemGroup(parent)
{
    polygon_item_ = 0;
    is_editable_ = false;

    setPolygon(polygon);
    setHandlesChildEvents(false);
}

void EditablePolygonGraphicsItem::setPolygon(const QPolygonF &polygon)
{
    //erase old polygon
    foreach(QGraphicsItem* item, childItems()){
        delete item;
    }
    childItems().clear();
    nodes_.clear();

    //default parameters
    //TODO
    QPen default_polygon_pen;
    default_polygon_pen.setColor(qRgb(0, 255, 0));
    default_polygon_pen.setWidth(2);

    QPen default_node_pen;
    default_node_pen.setColor(Qt::black);
    default_node_pen.setWidth(1);

    QBrush default_node_brush(Qt::white);

    QSize default_node_size = QSize(10, 10);

    //create polygon item
    polygon_item_ = new PolygonGraphicsItem(polygon, this);
    polygon_item_->setPen(default_polygon_pen);

    //create nodes
    int id = 0;
    foreach(QPointF point, polygon){
        NodePolygonGraphicsItem* node = new NodePolygonGraphicsItem(
                    id, point, default_node_size, polygon_item_, this);
        ++id;
        node->setPen(default_node_pen);
        node->setBrush(default_node_brush);

        nodes_.push_back(node);
    }

    setEditable(is_editable_);
}

void EditablePolygonGraphicsItem::removeNode(int node_id)
{
    QPolygonF new_polygon = polygon();
    QPolygonF::Iterator it = new_polygon.begin() + node_id;
    new_polygon.erase(it);
    setPolygon(new_polygon);
}

void EditablePolygonGraphicsItem::addNode(int node_id, const QPointF &point)
{
    QPolygonF new_polygon = polygon();
    QPolygonF::Iterator it = new_polygon.begin() + node_id + 1;
    new_polygon.insert(it, point);
    setPolygon(new_polygon);
}

void EditablePolygonGraphicsItem::setEditable(bool is_editable)
{
    is_editable_ = is_editable;

    foreach(QGraphicsItem* item, childItems()){
        if(is_editable_)
            item->show();
        else
            item->hide();
    }

    polygon_item_->show(); //always visible
}

bool EditablePolygonGraphicsItem::isEditable() const
{
    return is_editable_;
}

QPolygonF EditablePolygonGraphicsItem::polygon() const
{
    return polygon_item_->polygon();
}
