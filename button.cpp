#include "button.h"


Button::Button(const char text[], function<void()> callback) : callback_(callback)
{
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::gray);
    setPen(pen);

    setRect(0,0,200,50);

    button_text_ = std::make_unique<QGraphicsTextItem>(text, this);
    button_text_->setFont(QFont ("Sans", 14));
    button_text_->setPos(rect().width()/2 - button_text_->boundingRect().width()/2,
                         rect().height()/2 - button_text_->boundingRect().height()/2);

    setAcceptHoverEvents(true);
}


void Button::mousePressEvent(QGraphicsSceneMouseEvent* event){
    callback_();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent* event){
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::white);
    setPen(pen);

    QApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* event){
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::gray);
    setPen(pen);

    QApplication::restoreOverrideCursor();
}
