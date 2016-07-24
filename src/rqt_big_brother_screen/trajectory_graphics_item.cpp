#include <rqt_big_brother_screen/trajectory_graphics_item.h>

TrajectoryGraphicsItem::TrajectoryGraphicsItem(QGraphicsItem *parent) :
    QGraphicsItemGroup(parent)
{
}

TrajectoryGraphicsItem::TrajectoryGraphicsItem(const QList<QPointF> &trajectory,
        QGraphicsItem *parent) :
    QGraphicsItemGroup(parent)
{
    //default style
    pen_.setColor(QColor(0, 0, 255, 55));
    pen_.setWidth(5);

    setTrajectory(trajectory);

}

void TrajectoryGraphicsItem::setTrajectory(const QList<QPointF> &trajectory)
{
    //remove old lines
    clear();

    //create new line
    foreach(QPointF point, trajectory){
        addPoint(point);
    }
}

QList<QPointF> TrajectoryGraphicsItem::trajectory() const
{
    return trajectory_;
}

bool TrajectoryGraphicsItem::addPoint(const QPointF &point)
{
    trajectory_.push_back(point);

    if(trajectory_.size() > 1){
        QPointF begin = *(trajectory_.end() - 1);
        QPointF end = *(trajectory_.end() - 2);
        QGraphicsLineItem* line_item =  new QGraphicsLineItem(
                    QLineF(begin, end), this);
        line_item->setPen(pen_);
        lines_.push_back(line_item);
    }
}

void TrajectoryGraphicsItem::clear()
{
    //remove all lines
    foreach(QGraphicsItem* item, lines_)
        delete item;
    lines_.clear();
    trajectory_.clear();
}

void TrajectoryGraphicsItem::setPen(const QPen &pen)
{
    pen_ = pen;

    foreach(QGraphicsItem* item, lines_)
        ((QGraphicsLineItem*)item)->setPen(pen_);
}

QPen TrajectoryGraphicsItem::pen() const
{
    return pen_;
}
