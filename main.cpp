#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <QApplication>
#include <QGraphicsView>
#include <QCloseEvent>

#include "window.h"
#include "game.h"
#include "menu.h"
#include "sprite.h"


void startGame();
void gameOver();
void exitGame();

int main(int argc, char* argv[])
{
    srand(unsigned(int(time(nullptr))));

    QApplication app(argc, argv);

    // Loading sprites.
    std::unordered_map<std::string, std::vector<std::shared_ptr<Sprite>>> background_sprites;
    std::unordered_map<std::string, std::vector<std::shared_ptr<Sprite>>> player_sprites;
    std::unordered_map<std::string, std::vector<std::shared_ptr<Sprite>>> asteroid_sprites;
    std::unordered_map<std::string, std::vector<std::shared_ptr<Sprite>>> bullet_sprites;

    background_sprites["default"] = {
        std::make_shared<Sprite>(":/assets/images/background.png", 0),
    };

    player_sprites["default"] = {
        std::make_shared<Sprite>(":/assets/images/player.png", 0)
    };

    asteroid_sprites["default"] = {
        std::make_shared<Sprite>(":/assets/images/asteroid.png", 0)
    };

    player_sprites["die"] = asteroid_sprites["die"] = {
        std::make_shared<Sprite>(":/assets/images/explosion00.png", 0.01),
        std::make_shared<Sprite>(":/assets/images/explosion01.png", 0.01),
        std::make_shared<Sprite>(":/assets/images/explosion02.png", 0.02),
        std::make_shared<Sprite>(":/assets/images/explosion03.png", 0.02),
        std::make_shared<Sprite>(":/assets/images/explosion04.png", 0.03),
        std::make_shared<Sprite>(":/assets/images/explosion05.png", 0.03),
        std::make_shared<Sprite>(":/assets/images/explosion06.png", 0.03),
        std::make_shared<Sprite>(":/assets/images/explosion07.png", 0.02),
        std::make_shared<Sprite>(":/assets/images/explosion08.png", 0.02),
        std::make_shared<Sprite>(":/assets/images/explosion09.png", 0.01),
        std::make_shared<Sprite>(":/assets/images/explosion10.png", 0.01)
    };

    bullet_sprites["default"] = {
        std::make_shared<Sprite>(":/assets/images/bullet.png", 0)
    };

    Game::sprites.insert({"background", background_sprites});
    Game::sprites.insert({"player", player_sprites});
    Game::sprites.insert({"asteroid", asteroid_sprites});
    Game::sprites.insert({"bullet", bullet_sprites});

    // Configuring the view.
    Window::view = std::make_unique<QGraphicsView>();
    Window::view->setBackgroundBrush(QBrush(QColor(Qt::black)));
    Window::view->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    Window::view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Window::view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Window::view->setMouseTracking(true);
    Window::view->setFixedSize(800, 600);

    // Configuring sound.
    Sound::channels(5);

    // Configuring menu.
    int font_id = QFontDatabase::addApplicationFont(":/assets/fonts/starjedi.ttf");
    Menu::font_family = QFontDatabase::applicationFontFamilies(font_id).at(0).toStdString();



    Window::scene = std::make_unique<Menu>(":/assets/images/start.png",
                                           "space debris", "START", "EXIT",
                                           startGame, exitGame);


    Window::view->setScene(Window::scene.get());

    Window::view->show();

    return app.exec();
}


/**
 * Starts the game.
 *
 * Removes the start game menu and effectively starts the game
 */
void startGame()
{
    Window::scene.reset();

    Window::scene = std::make_unique<Game>(gameOver);
    Window::view->setScene(Window::scene.get());
    Window::view->show();

    dynamic_cast<Game*>(Window::scene.get())->start();
}


/**
 * Game over.
 *
 * It's called when the game ends.
 * Indeed, removes the game and creates a game over menu.
 */
void gameOver()
{
    Window::scene.reset();
    Window::scene = std::make_unique<Menu>(":/assets/images/gameover.png",
                                           "game over",  "RESTART", "EXIT",
                                           startGame, exitGame);

    Window::view->setScene(Window::scene.get());
    Window::view->show();
}


/**
 * Exit game.
 *
 * Clears objects and destroy the window.
 */
void exitGame()
{
    QApplication::quit();
}


