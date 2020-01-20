#include <string>
#include <vector>
#include <unordered_map>
#include <stdlib.h>

#include <QApplication>
#include <QGraphicsView>
#include <QCloseEvent>

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
    std::unordered_map<std::string, std::vector<Sprite*>> background_sprites;
    std::unordered_map<std::string, std::vector<Sprite*>> player_sprites;
    std::unordered_map<std::string, std::vector<Sprite*>> asteroid_sprites;
    std::unordered_map<std::string, std::vector<Sprite*>> bullet_sprites;

    background_sprites["default"] = {
        (new Sprite(":/assets/images/background.png", 0)),
    };

    player_sprites["default"] = {
        (new Sprite(":/assets/images/player.png", 0))
    };

    asteroid_sprites["default"] = {
        (new Sprite(":/assets/images/asteroid.png", 0)),
    };

    player_sprites["die"] = asteroid_sprites["die"] = {
        (new Sprite(":/assets/images/explosion00.png", 0.01)),
        (new Sprite(":/assets/images/explosion01.png", 0.01)),
        (new Sprite(":/assets/images/explosion02.png", 0.02)),
        (new Sprite(":/assets/images/explosion03.png", 0.02)),
        (new Sprite(":/assets/images/explosion04.png", 0.03)),
        (new Sprite(":/assets/images/explosion05.png", 0.03)),
        (new Sprite(":/assets/images/explosion06.png", 0.03)),
        (new Sprite(":/assets/images/explosion07.png", 0.02)),
        (new Sprite(":/assets/images/explosion08.png", 0.02)),
        (new Sprite(":/assets/images/explosion09.png", 0.01)),
        (new Sprite(":/assets/images/explosion10.png", 0.01)),
    };

    bullet_sprites["default"] = {
        (new Sprite(":/assets/images/bullet.png", 0))
    };

    Game::sprites.insert({"background", background_sprites});
    Game::sprites.insert({"player", player_sprites});
    Game::sprites.insert({"asteroid", asteroid_sprites});
    Game::sprites.insert({"bullet", bullet_sprites});

    // Configuring the view.
    Game::view = new QGraphicsView();
    Game::view->setBackgroundBrush(QBrush(QColor(Qt::black)));
    Game::view->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    Game::view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Game::view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Game::view->setMouseTracking(true);
    Game::view->setFixedSize(800, 600);

    // Configuring sound.
    Sound::channels(3);

    // Configuring menu.
    int font_id = QFontDatabase::addApplicationFont(":/assets/fonts/starjedi.ttf");
    Menu::font_family = QFontDatabase::applicationFontFamilies(font_id).at(0).toStdString();

    Menu* start_game_menu = new Menu(":/assets/images/start.png",
                                     "space debris", "START", "EXIT",
                                     startGame, exitGame);

    Game::view->setScene(start_game_menu);
    Game::view->show();


    return app.exec();
}


/**
 * Starts the game.
 *
 * Removes the start game menu and effectively starts the game
 */
void startGame()
{
    Game* game = new Game(gameOver);

    delete Game::view->scene();
    Game::view->setMouseTracking(false);
    Game::view->setScene(game);
    Game::view->show();

    game->start();
}


/**
 * Game over.
 *
 * It's called when the game ends.
 * Indeed, removes the game and creates a game over menu.
 */
void gameOver()
{
    Menu* game_over_menu = new Menu(":/assets/images/gameover.png",
                                    "game over", "RESTART", "EXIT",
                                    startGame, exitGame);
    delete Game::view->scene();
    Game::view->setMouseTracking(true);
    Game::view->setScene(game_over_menu);
    Game::view->show();
}


/**
 * Exit game.
 *
 * Clears objects and destroy the window.
 */
void exitGame()
{
    delete Game::view->scene();
    QApplication::quit();
}


