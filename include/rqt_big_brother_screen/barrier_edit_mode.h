#ifndef BARRIER_EDIT_MODE_H
#define BARRIER_EDIT_MODE_H

#include <rqt_big_brother_screen/edit_mode.h>
#include <rqt_big_brother_screen/barrier_graphics_item.h>

#include <QObject>
#include <QSet>
#include <QList>
#include <QPolygonF>
#include <QGraphicsScene>

class BarrierEditMode : public EditMode
{
    Q_OBJECT

public:
    explicit BarrierEditMode(QObject* parent);
    BarrierEditMode(QList<BarrierGraphicsItem*>* barrier_items,
            /*TODO ros::topic*/QObject* parent);

    void cancel();
    void save();

private:
    void setEditable(bool is_editable);

private:
    QList<BarrierGraphicsItem*>* barrier_items_;
    QList<QPolygonF> saved_polygon_barriers_;
    //TODO ros::topic
};

#endif
