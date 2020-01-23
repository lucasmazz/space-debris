#include "window.h"

std::unique_ptr<QGraphicsView> Window::view;
std::shared_ptr<QGraphicsScene> Window::scene_;

void Window::show(std::shared_ptr<QGraphicsScene> scene)
{
    Window::view->setScene(scene.get());
    Window::view->show();

    // Holds the scene.
    Window::scene_.reset();
    Window::scene_ = scene;
}
