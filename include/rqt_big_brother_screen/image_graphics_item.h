#ifndef IMAGE_GRAPHICS_ITEM_H
#define IMAGE_GRAPHICS_ITEM_H

#include <QGraphicsItem>
#include <QImage>

namespace rqt_big_brother_screen
{

class ImageGraphicsItem : public QGraphicsItem
{
public:
    explicit ImageGraphicsItem(QGraphicsItem* parent = 0);
    ImageGraphicsItem(const QImage &image, QGraphicsItem* parent = 0);

    void setImage(const QImage &image);
    QImage image();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
            QWidget *widget);

private:
    QImage image_;
};

}
#endif
