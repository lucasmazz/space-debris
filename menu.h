#ifndef MENU_H
#define MENU_H

#include <functional>
#include <memory>

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
         const char confirm_text[]="START", const char cancel_text[]="EXIT",
         std::function<void()> start_callback=NULL, std::function<void()> exit_callback=NULL);

public:
    static std::string font_family;

private:
    std::unique_ptr<QPixmap> image_;
    std::unique_ptr<QGraphicsPixmapItem> background_;
    std::unique_ptr<QGraphicsTextItem> title_;
    std::unique_ptr<Button> confirm_button_;
    std::unique_ptr<Button> cancel_button_;

};

#endif // MENU_H
