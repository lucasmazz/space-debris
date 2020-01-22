#ifndef WINDOW_H
#define WINDOW_H

#include <memory>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMainWindow>

#include "game.h"
#include "menu.h"


class Window : QMainWindow
{

private:
    Window();

public:
    static std::unique_ptr<QGraphicsView> view;
    static std::unique_ptr<QGraphicsScene> scene;

};

#endif // WINDOW_H
