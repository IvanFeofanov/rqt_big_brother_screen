#include <rqt_big_brother_screen/image_graphics_item.h>

#include <QPainter>
#include <iostream>

namespace rqt_big_brother_screen
{

ImageGraphicsItem::ImageGraphicsItem(QGraphicsItem* parent) :
    QGraphicsItem(parent)
{
}

ImageGraphicsItem::ImageGraphicsItem(const QImage &image,
        QGraphicsItem* parent) :
    QGraphicsItem(parent)
{
    setImage(image);
}

void ImageGraphicsItem::setImage(const QImage& image)
{
    image_ = image;
    update();
}

QImage ImageGraphicsItem::image()
{
    return image_;
}

QRectF ImageGraphicsItem::boundingRect() const
{
    return QRectF(QPointF(0, 0), image_.size());
}

void ImageGraphicsItem::paint(QPainter *painter,
        const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(0, 0, image_);
}

}
