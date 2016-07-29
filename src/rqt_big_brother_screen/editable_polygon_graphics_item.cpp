#include <rqt_big_brother_screen/editable_polygon_graphics_item.h>

#include <QDebug>

EditablePolygonGraphicsItem::EditablePolygonGraphicsItem(QGraphicsItem *parent) :
    QGraphicsItemGroup(parent)
{
    polygon_item_ = 0;
    is_editable_ = false;
    setDefaultParameters();
}

EditablePolygonGraphicsItem::EditablePolygonGraphicsItem(const QPolygonF &polygon,
                                                         QGraphicsItem *parent) :
    QGraphicsItemGroup(parent)
{
    polygon_item_ = 0;
    is_editable_ = false;
    setDefaultParameters();

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

    //create polygon item
    polygon_item_ = new PolygonGraphicsItem(polygon, this);
    polygon_item_->setPen(main_pen_);

    //create nodes
    int id = 0;
    foreach(QPointF point, polygon){
        NodePolygonGraphicsItem* node = new NodePolygonGraphicsItem(
                    id, point, node_size_, polygon_item_, this);
        ++id;
        node->setPen(node_pen_);
        node->setBrush(node_brush_);

        nodes_.push_back(node);
    }

    setEditable(is_editable_);
}

QPolygonF EditablePolygonGraphicsItem::polygon() const
{
    return polygon_item_->polygon();
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

void EditablePolygonGraphicsItem::setNodeSize(const QSize& size)
{
    node_size_ = size;

    foreach(NodePolygonGraphicsItem* node, nodes_){
        node->setSize(size);
    }
}

QSize EditablePolygonGraphicsItem::nodeSize() const
{
    return node_size_;
}

void EditablePolygonGraphicsItem::setMidNodeSize(const QSize& size)
{
    mid_node_size_ = size;

    if(polygon_item_ != 0)
        polygon_item_->setMidNodeSize(size);
}

QSize EditablePolygonGraphicsItem::midNodeSize() const
{
    return mid_node_size_;
}

void EditablePolygonGraphicsItem::setMainPen(const QPen& pen)
{
    main_pen_ = pen;

    if(polygon_item_ != 0)
        polygon_item_->setPen(pen);
}

QPen EditablePolygonGraphicsItem::mainPen() const
{
    return main_pen_;
}

void EditablePolygonGraphicsItem::setMainBrush(const QBrush& brush)
{
    main_brush_ = brush;

    if(polygon_item_ != 0)
        polygon_item_->setBrush(brush);
}

QBrush EditablePolygonGraphicsItem::mainBrush()
{
    return main_brush_;
}

void EditablePolygonGraphicsItem::setNodePen(const QPen& pen)
{
    node_pen_ = pen;

    foreach(NodePolygonGraphicsItem* node, nodes_){
        node->setPen(pen);
    }
}

QPen EditablePolygonGraphicsItem::nodePen() const
{
    return node_pen_;
}

void EditablePolygonGraphicsItem::setNodeBrush(const QBrush& brush)
{
    node_brush_ = brush;

    foreach(NodePolygonGraphicsItem* node, nodes_){
        node->setBrush(brush);
    }
}

QBrush EditablePolygonGraphicsItem::nodeBrush() const
{
    return node_brush_;
}

void EditablePolygonGraphicsItem::setDefaultParameters()
{
    setNodeSize(QSize(10, 10));
    setMidNodeSize(QSize(8, 8));

    QPen main_pen;
    main_pen.setColor(qRgb(0, 255, 0));
    main_pen.setWidth(2);
    setMainPen(main_pen);

    QBrush main_brush;
    setMainBrush(main_brush);

    QPen node_pen;
    node_pen.setColor(Qt::black);
    node_pen.setWidth(1);
    setNodePen(node_pen);

    QBrush node_brush(Qt::white);
    setNodeBrush(node_brush);
}
