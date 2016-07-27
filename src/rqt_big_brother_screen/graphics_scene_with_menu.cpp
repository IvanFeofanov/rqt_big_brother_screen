#include <rqt_big_brother_screen/graphics_scene_with_menu.h>

#include <QGraphicsSceneContextMenuEvent>
#include <QPoint>
#include <QDebug>

GraphicsSceneWithMenu::GraphicsSceneWithMenu(QObject* parent) :
    QGraphicsScene(parent)
{
    menu_ = 0;
}

GraphicsSceneWithMenu::GraphicsSceneWithMenu(QMenu* menu, QObject* parent) :
    QGraphicsScene(parent)
{
    menu_ = menu;
}

GraphicsSceneWithMenu::GraphicsSceneWithMenu(const QRect &rect, QMenu* menu,
        QObject* parent):
    QGraphicsScene(rect, parent)
{
    menu_ = menu;
}

GraphicsSceneWithMenu::GraphicsSceneWithMenu(const QRect &rect, QObject* parent) :
    QGraphicsScene(rect, parent)
{
    menu_ = 0;
}

void GraphicsSceneWithMenu::setMenu(QMenu *menu)
{
    menu_ = menu;
}

QMenu *GraphicsSceneWithMenu::menu() const
{
    return menu_;
}

void GraphicsSceneWithMenu::enableMenu(bool is_enable)
{
    is_menu_enable_ = is_enable;
}

bool GraphicsSceneWithMenu::isMenuEnable()
{
    return is_menu_enable_;
}

void GraphicsSceneWithMenu::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if(menu_ != 0 && is_menu_enable_)
        menu_->exec(event->screenPos());
}
