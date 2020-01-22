#ifndef GAME_H
#define GAME_H

#include <deque>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <functional>
#include <memory>

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
    void stop();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

public slots:
    void loop();

public:
    void operator<<(std::shared_ptr<Enemy> enemy);
    void operator>>(std::shared_ptr<Enemy> enemy);

    void operator<<(std::shared_ptr<Bullet> bullet);
    void operator>>(std::shared_ptr<Bullet> bullet);

private:
    void add(std::shared_ptr<Enemy> enemy);
    void remove(std::shared_ptr<Enemy> enemy);

    void add(std::shared_ptr<Bullet> bullet);
    void remove(std::shared_ptr<Bullet> bullet);

    void spawnEnemies(const float time_elapsed);
    void moveBackground(const float time_elapsed);
    void moveEnemies(const float time_elapsed);
    void moveBullets(const float time_elapsed);
    void update(const float time_elapsed);

public:
    static std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::shared_ptr<Sprite>>>> sprites;

private:
    bool running_ = true;

    std::deque<std::unique_ptr<Background>> backgrounds_;
    std::unordered_map<unsigned int, std::shared_ptr<Enemy>> enemies_;
    std::unordered_map<unsigned int, std::shared_ptr<Bullet>> bullets_;

    std::unique_ptr<QMediaPlayer> music_;
    std::unique_ptr<QMediaPlaylist> playlist_;
    std::unique_ptr<Player> player_;
    std::unique_ptr<Score> score_;
    std::unique_ptr<Health> health_;
    std::unique_ptr<QTimer> timer_;

    std::chrono::high_resolution_clock::time_point start_time_;
    std::chrono::high_resolution_clock::time_point stop_time_;
    float total_time_ = 0;

    std::function<void()> callback_;

};


#endif // GAME_H
