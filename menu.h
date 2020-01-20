#ifndef MENU_H
#define MENU_H

#include <functional>

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QRectF>
#include <QFontDatabase>
#include <QString>

#include "button.h"


class Menu : public QGraphicsScene
{

public:
    Menu(const char background_path[], const char title_text[]="",
         const char start_text[]="START", const char exit_text[]="EXIT",
         std::function<void()> start_callback=NULL, std::function<void()> exit_callback=NULL);

    ~Menu();

public:
    static std::string font_family;

private:
    QPixmap* image_;
    QGraphicsPixmapItem* background_;
    QGraphicsTextItem* title_;
    Button* confirm_button_;
    Button* cancel_button_;

};

#endif // MENU_H
