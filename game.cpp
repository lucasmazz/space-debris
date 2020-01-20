#include "game.h"

std::unordered_map<std::string, std::unordered_map<std::string, std::vector<Sprite*>>> Game::sprites;
QGraphicsView* Game::view;


Game::Game(std::function<void()> callback) : callback_(callback)
{
    music_ = new QMediaPlayer();
    player_ = new Player(Game::sprites.at("player"));
    score_ = new Score();
    health_ = new Health();
    playlist_ = new QMediaPlaylist();
    timer_ = new QTimer();

    QTimer teste;

    // Just configurating the game scene.
    setSceneRect(0,0, 800, 600);
    setFocus();

    // Is required 2 backgrounds in the scene to do the infinity background scroll.
    backgrounds_.push_back(new Background(Game::sprites.at("background")));
    backgrounds_.push_back(new Background(Game::sprites.at("background")));

    // Setting backgrounds position.
    backgrounds_[0]->setPos(0, 0);
    backgrounds_[1]->setPos(0, -backgrounds_[1]->pixmap().height());

    // Positioning objects.
    player_->setPos(width()/2 - player_->pixmap().width()/2, height() - player_->pixmap().height() - 32);
    player_->setZValue(1);
    health_->setPos(width() - health_->boundingRect().width() - 10, 10);
    health_->setZValue(2);
    score_->setPos(10, 10);
    score_->setZValue(2);

    // Adding objects to the game scene.
    addItem(backgrounds_[0]);
    addItem(backgrounds_[1]);
    addItem(player_);
    addItem(score_);
    addItem(health_);

    playlist_->addMedia(QUrl("qrc:/assets/sounds/bgm.mp3"));
    playlist_->setPlaybackMode(QMediaPlaylist::Loop);
    music_->setPlaylist(playlist_);
}


Game::~Game()
{
    music_->stop();
    timer_->stop();

    delete music_;
    delete playlist_;
    delete timer_;
    delete player_;
    delete score_;
    delete health_;

    for (unsigned int i=0; i < backgrounds_.size(); i++) {
        removeItem(backgrounds_[i]);
        delete backgrounds_[i];
    }

    for (auto i = enemies_.cbegin(), next_i = i; i != enemies_.cend(); i = next_i) {
        ++next_i;
        removeItem(i->second);
        delete i->second;
    }

    for (auto i = bullets_.cbegin(), next_i = i; i != bullets_.cend(); i = next_i) {
        ++next_i;
        removeItem(i->second);
        delete i->second;
    }

    backgrounds_.clear();
    enemies_.clear();
    bullets_.clear();
}


/**
 * Plays background music and starts the game loop.
 * Should be called after game instantiation to completely start it.
 */
void Game::start()
{    

    if (music_->state() == QMediaPlayer::PlayingState)
        music_->setPosition(0);

    music_->play();

    start_time_ = std::chrono::high_resolution_clock::now();

    // Starting the game loop.
    QObject::connect(timer_, SIGNAL(timeout()), this, SLOT(loop()));
    timer_->start(20);
}


void Game::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Left) {

        player_->accelerate(-200);

    } else if (event->key() == Qt::Key_Right) {

        player_->accelerate(200);

    } else if (event->key() == Qt::Key_Space && !event->isAutoRepeat()) {

        Bullet* bullet = new Bullet(Game::sprites.at("bullet"));
        *this << bullet;

    }
}


void Game::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Left or event->key() == Qt::Key_Right)
        player_->brake();
}


/**
 * It's called from every timer cycle and updates all objects existent in the game.
 *
 * Furthermore, when the player dies the "running" flag is set to false then the game over (callback) is called.
 */
void Game::loop()
{
    if (running_) {
        stop_time_ = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> time_time_elapsed = stop_time_ - start_time_;
        float time_elapsed = time_time_elapsed.count();

        update(time_elapsed); // move objects

        start_time_ = stop_time_;
    } else {
        callback_();
    }
}


/**
 * Adds an enemy to the game.
 *
 * @param enemy
 */
void Game::operator<<(Enemy* enemy)
{
    add(enemy);
}


/**
 * Removes an enemy from the game.
 *
 * @param enemy
 */
void Game::operator>>(Enemy* enemy)
{
    remove(enemy);
}


/**
 * Adds a bullet to the game.
 *
 * @param bullet
 */
void Game::operator<<(Bullet* bullet)
{
    add(bullet);
}


/**
 * Removes a bullet from the game.
 *
 * @param bullet
 */
void Game::operator>>(Bullet* bullet)
{
    remove(bullet);
}


/**
 * Adds an enemy to the game.
 *
 * @param enemy
 */
void Game::add(Enemy* enemy)
{
    enemies_.insert({ enemy->id(), enemy });
    enemy->setPos(rand() % int(this->width() - enemy->pixmap().width()), -2*enemy->pixmap().height());
    enemy->setZValue(1);
    addItem(enemy);
}


/**
 * Removes an enemy from the game.
 *
 * @param enemy
 */
void Game::remove(Enemy* enemy)
{

    std::function<void()> lambda = [this, enemy]()
    {
        enemies_.erase(enemy->id());
        removeItem(enemy);
        delete enemy;
    };

    enemy->die(lambda);
}


/**
 * Adds a bullet to the game.
 *
 * @param bullet
 */
void Game::add(Bullet* bullet)
{
    bullets_.insert({ bullet->id(), bullet });
    bullet->setPos(player_->x() + int(player_->pixmap().width())/2 - bullet->pixmap().width()/2,
                   player_->y() - bullet->pixmap().height());

    bullet->setZValue(1);
    addItem(bullet);
}


/**
 * Removes a bullet from the game.
 *
 * @param bullet
 */
void Game::remove(Bullet* bullet)
{
    bullet->die();
    removeItem(bullet);
    bullets_.erase(bullet->id());
    delete bullet;
}


/**
 * Spawns a number of enemies based on the total time that the game is running.
 *
 * @param time_elapsed Current time elapsed in the game loop.
 */
void Game::spawnEnemies(const float time_elapsed)
{
    int amount = int(total_time_/100) + 1;

    if (amount > 9)
        amount = 9;

    if (enemies_.size() < amount) {
        Enemy* enemy = new Enemy(Game::sprites.at("asteroid"));
        *this << enemy;
    }
}


/**
 * Moves the background based on the total time that the game is running.
 *
 * Next, always removes the background that isn't visible to the player and creates a new one
 * to generate an infinity scroll effect.
 *
 * @param time_elapsed Current time elapsed in the game loop.
 */
void Game::moveBackground(const float time_elapsed)
{
    float speed = 100 + total_time_;

    if (speed > 999)
        speed = 999;

    for (unsigned int i=0; i < backgrounds_.size(); i++) {
        backgrounds_[i]->speed(0, speed);
        backgrounds_[i]->move(time_elapsed);
    }

    if (backgrounds_[0]->pos().y() > height()) {
        removeItem(backgrounds_[0]);
        delete backgrounds_[0];
        backgrounds_.pop_front();

        Background* new_background = new Background(Game::sprites.at("background"));
        new_background->setPos(0, -new_background->pixmap().height());
        new_background->setZValue(0);
        addItem(new_background);
        backgrounds_.push_back(new_background);
    }
}


/**
 * Moves all enemy entities in the game and tests if they are out of reach,
 * if they are colliding with the player or was hit by a bullet.
 *
 * @param time_elapsed Current time elapsed in the game loop.
 */
void Game::moveEnemies(const float time_elapsed)
{
    for (auto i = enemies_.cbegin(), next_i = i; i != enemies_.cend(); i = next_i) {
        ++next_i;

        Enemy* enemy = i->second;
        QList<QGraphicsItem*> colliding_items = collidingItems(enemy);


        if (enemy->alive()) {

            enemy->move(time_elapsed);

            // Enemy is out of reach or enemy is colliding with player_.
            if (enemy->pos().y() > height() || enemy->collidesWithItem(player_)) {
                --(*health_);
                *this >> enemy; // remove the enemy from game

                // If the player_ dies, then stop the game loop.
                if (health_->points() <= 0) {

                    std::function<void()> lambda = [this]()
                    {
                        removeItem(player_);
                        running_ = false;
                    };

                    player_->die(lambda);

                } else {
                    player_->crash();
                }

            // Enemy was hitted by a bullet.
            } else {

                for (auto j = bullets_.cbegin(), next_j = j; j != bullets_.cend(); j = next_j) {
                    ++next_j;
                    Bullet* bullet = j->second;

                    if (enemy->collidesWithItem(bullet)) {
                        ++(*score_);
                        *this >> bullet; // remove the bullet from game
                        *this >> enemy; // remove the enemy from game
                    }
                }
            }
        }

        enemy->animate(time_elapsed);
    }
}


/**
 * Moves all bullet entities in the game and tests if they are out of reach.
 *
 * @param time_elapsed Current time elapsed in the game loop.
 */
void Game::moveBullets(const float time_elapsed)
{
    for (auto i = bullets_.cbegin(), next_i = i; i != bullets_.cend(); i = next_i) {
        ++next_i;

        Bullet* bullet = i->second;

        bullet->move(time_elapsed);

        // Bullet is out of range.
        if (bullet->pos().y() + bullet->pixmap().height() < 0) {
            *this >> bullet; // remove the bullet
        }
    }
}


/**
 * Does a completely update to the game entities.
 *
 * Basically spawn enemies, moves the background, the player, the enemies and the bullets.
 *
 * It's also responsible for testing the collision between the entities and then increase
 * score and decrease health stats.
 *
 * Moreover, calls the objects animations and callbacks.
 *
 * @param time_elapsed Current time elapsed in the game loop.
 */
void Game::update(const float time_elapsed)
{

    total_time_ += time_elapsed;

    moveBackground(time_elapsed);
    spawnEnemies(time_elapsed);

    player_->move(time_elapsed);
    moveEnemies(time_elapsed);
    moveBullets(time_elapsed);

    player_->animate(time_elapsed);
}

