#include <rqt_big_brother_screen/barrier_edit_mode.h>
#include <rqt_big_brother_screen/barrier_graphics_item.h>
#include <iostream>

BarrierEditMode::BarrierEditMode(QObject* parent) :
    EditMode(parent)
{
    barrier_items_ = 0;
}

BarrierEditMode::BarrierEditMode(QList<BarrierGraphicsItem*>* barrier_items,
        /*TODO ros::topic*/QObject* parent) :
    EditMode(parent)
{
    barrier_items_ = barrier_items;

    setEditable(true);

    //save polygon barriers
    foreach(BarrierGraphicsItem* barrier_item, *barrier_items_){
        saved_polygon_barriers_.push_back(barrier_item->polygon());
    }
}

void BarrierEditMode::cancel()
{
    setEditable(false);

    //set previous barriers
    for(int i = 0; i < barrier_items_->size(); ++i){
        (*barrier_items_)[i]->setPolygon(saved_polygon_barriers_[i]);
    }
    saved_polygon_barriers_.clear();
}

void BarrierEditMode::save()
{
    setEditable(false);

    //remove null polygons
    for(QList<BarrierGraphicsItem*>::iterator it = barrier_items_->begin();
            it != barrier_items_->end(); it++){
        if((*it)->polygon().size() == 0){
            delete (*it);
            QList<BarrierGraphicsItem*>::iterator next =
                barrier_items_->erase(it);
            if(next == barrier_items_->end()){
                break;
            }
        }
    }

    //TODO ros::send
}

void BarrierEditMode::setEditable(bool is_editable)
{
    if(barrier_items_ == 0)
        return;

    foreach(BarrierGraphicsItem* polygon_item, *barrier_items_){
        polygon_item->setEditable(is_editable);
    }

}
