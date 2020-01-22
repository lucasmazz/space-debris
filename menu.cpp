#include "menu.h"


std::string Menu::font_family;

Menu::Menu(const char background_path[], const char title_text[],
           const char confirm_text[], const char cancel_text[],
           function<void()> confirm_callback, function<void()> cancel_callback)
{
    setSceneRect(0,0, 800, 600);
    setFocus();

    image_ = std::make_unique<QPixmap>(background_path);
    background_ = std::make_unique<QGraphicsPixmapItem>();
    background_->setPixmap(*image_);

    background_->setPos(0, 0);
    background_->setZValue(0);
    addItem(background_.get());

    title_ = std::make_unique<QGraphicsTextItem>();
    title_->setPlainText(title_text);
    title_->setDefaultTextColor(Qt::white);
    auto font = QFont(QString::fromUtf8(font_family.c_str()), 48);
    title_->setFont(font);
    auto title_rect = title_->sceneBoundingRect();
    title_->setPos(width()/2 - title_rect.width()/2, 100);
    addItem(title_.get());

    confirm_button_ = std::make_unique<Button>(confirm_text, confirm_callback);
    addItem(confirm_button_.get());
    confirm_button_->setPos(width()/2 - confirm_button_->rect().width()/2, 300);

    cancel_button_ = std::make_unique<Button>(cancel_text, cancel_callback);
    addItem(cancel_button_.get());
    cancel_button_->setPos(width()/2 - cancel_button_->rect().width()/2, 400);
}
