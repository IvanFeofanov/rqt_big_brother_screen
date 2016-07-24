#ifndef TRAJECTORY_GRAPHICS_ITEM_H
#define TRAJECTORY_GRAPHICS_ITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsLineItem>

#include <QPointF>
#include <QPen>

#include <QList>

class TrajectoryGraphicsItem : public QGraphicsItemGroup
{
public:
    explicit TrajectoryGraphicsItem(QGraphicsItem* parent = 0);
    TrajectoryGraphicsItem(const QList<QPointF> &trajectory,
                           QGraphicsItem *parent = 0);

    void setTrajectory(const QList<QPointF> &trajectory);
    QList<QPointF> trajectory() const;

    bool addPoint(const QPointF &point);
    void clear();

    void setPen(const QPen &pen);
    QPen pen() const;

private:
    QList<QPointF> trajectory_;
    QList<QGraphicsLineItem*> lines_;

    QPen pen_;
};

#endif // TRAJECTORY_GRAPHICS_ITEM_H
