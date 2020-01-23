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
    Sprite::Set background_sprites;
    Sprite::Set player_sprites;
    Sprite::Set asteroid_sprites;
    Sprite::Set bullet_sprites;

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

    auto start_game = std::make_shared<Menu>(":/assets/images/start.png",
                                             "space debris", "START", "EXIT",
                                             startGame, exitGame);

    Window::show(start_game);
    /*
    Window::view->setScene(start_game.get());
    Window::view->show();

    Window::scene.reset();
    Window::scene = move(start_game);
    */
    return app.exec();
}


/**
 * Starts the game.
 *
 * Removes the start game menu and effectively starts the game
 */
void startGame()
{
    auto game = std::make_shared<Game>(gameOver);

    Window::show(game);
    game->start();
    /*
    Window::view->setScene(game.get());
    Window::view->show();

    game->start();

    // Holds the scene reference.
    Window::scene.reset();
    Window::scene = std::move(game);
    */
}


/**
 * Game over.
 *
 * It's called when the game ends.
 * Indeed, removes the game and creates a game over menu.
 */
void gameOver()
{
    auto game_over = std::make_shared<Menu>(":/assets/images/gameover.png",
                                            "game over",  "RESTART", "EXIT",
                                            startGame, exitGame);
    Window::show(game_over);
    /*
    Window::view->setScene(game_over.get());
    Window::view->show();

    // Holds the scene reference.
    Window::scene.reset();
    Window::scene = std::move(game_over);
    */
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


