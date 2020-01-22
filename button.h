#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include <memory>

#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QPen>
#include <QFont>


using std::function;

class Button : public QGraphicsRectItem
{

public:
    Button(const char text[], function<void()> callback=NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

private:
    function<void()> callback_;
    std::unique_ptr<QGraphicsTextItem> button_text_;

};

#endif // BUTTON_H
