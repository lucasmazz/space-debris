#ifndef WINDOW_H
#define WINDOW_H

#include <memory>

#include <QGraphicsView>
#include <QGraphicsScene>

#include "game.h"
#include "menu.h"


class Window
{

public:
    static void show(std::shared_ptr<QGraphicsScene> scene);

private:
    Window();

public:
    static std::unique_ptr<QGraphicsView> view;

private:
    static std::shared_ptr<QGraphicsScene> scene_;

};

#endif // WINDOW_H
