#ifndef GRAPHICS_SCENE_WITH_MENU_H
#define GRAPHICS_SCENE_WITH_MENU_H

#include <QGraphicsScene>
#include <QMenu>
#include <QRect>

class GraphicsSceneWithMenu : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsSceneWithMenu(QObject* parent = 0);
    GraphicsSceneWithMenu(QMenu* menu, QObject* parent = 0);
    GraphicsSceneWithMenu(const QRect &rect, QObject* parent = 0);
    GraphicsSceneWithMenu(const QRect &rect, QMenu* menu = 0, QObject* parent = 0);

    void setMenu(QMenu* menu);
    QMenu* menu() const;

    void enableMenu(bool is_enable);
    bool isMenuEnable();
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    QMenu* menu_;
    bool is_menu_enable_;
};

#endif // GRAPHICS_SCENE_WITH_MENU_H
