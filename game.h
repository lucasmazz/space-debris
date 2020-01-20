#ifndef GAME_H
#define GAME_H

#include <deque>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <functional>
#include <stdlib.h>

#include <QTimer>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QKeyEvent>

#include "background.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "score.h"
#include "health.h"
#include "sprite.h"


class Game : public QGraphicsScene
{
    Q_OBJECT

public:
    Game(std::function<void()> callback=NULL);
    ~Game();

    void start();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

public slots:
    void loop();

public:
    void operator<<(Enemy* enemy);
    void operator>>(Enemy* enemy);

    void operator<<(Bullet* bullet);
    void operator>>(Bullet* bullet);

private:
    void add(Enemy* enemy);
    void remove(Enemy* enemy);

    void add(Bullet* bullet);
    void remove(Bullet* bullet);

    void spawnEnemies(const float time_elapsed);
    void moveBackground(const float time_elapsed);
    void moveEnemies(const float time_elapsed);
    void moveBullets(const float time_elapsed);
    void update(const float time_elapsed);

public:
    static std::unordered_map<std::string, std::unordered_map<std::string, std::vector<Sprite*>>> sprites;
    static QGraphicsView* view;


private:
    bool running_ = true;

    std::deque<Background*> backgrounds_;
    std::unordered_map<unsigned int, Enemy*> enemies_;
    std::unordered_map<unsigned int, Bullet*> bullets_;

    QMediaPlayer* music_;
    QMediaPlaylist* playlist_;
    Player* player_;
    Score* score_;
    Health* health_;
    QTimer* timer_;

    std::chrono::high_resolution_clock::time_point start_time_;
    std::chrono::high_resolution_clock::time_point stop_time_;
    float total_time_;

    std::function<void()> callback_;

};


#endif // GAME_H
