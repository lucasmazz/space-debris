#include "player.h"


Player::Player(std::unordered_map<std::string, std::vector<std::shared_ptr<Sprite>>> sprites) : Entity(sprites)
{
    maxSpeed(500, 500);
    maxAcceleration(500, 500);
}

/**
 * Plays the crash sound.
 */
void Player::crash()
{
    playSound("qrc:/assets/sounds/crash.wav");
}

/**
 * Sets the "braked" flag to true.
 */
void Player::brake()
{
    braked_ = true;
}


/**
 * If the player is inside the game boundaries then accelerates in the x coordinates.
 *
 * @param a Acceleration.
 */
void Player::accelerate(const float a)
{
    braked_ = false;

    if (insideBoundaries())
        acceleration(a, 0);
}


/**
 * Handles the movement.
 *
 * If braked then creates an opposite acceleration to the movement until stop.
 *
 * Also, this move does not let it overcome the boundaries of the game.
 *
 * @param elapsed_time Time elapsed from the last move call.
 */
void Player::move(const float elapsed)
{
    if (braked_ && speed_[0] != 0)
        acceleration( 100*abs(speed_[0])/speed_[0]*(-1), 0);

    if (insideBoundaries()) {

        Entity::move(elapsed);

    } else if (pos().x() < 0) {

        braked_ = false;
        acceleration(0, 0);
        speed(0, 0);
        setPos(0, y());

    } else if (pos().x() > scene()->width() - pixmap().width()) {

        braked_ = false;
        acceleration(0, 0);
        speed(0, 0);
        setPos(scene()->width() - pixmap().width(), y());

    }

}


/**
 * Kills player.
 *
 * @param callback Function that will be called after the die animation ends.
 */
void Player::die(std::function<void ()> callback)
{
    playSound("qrc:/sounds/explosion.wav");
    animation("die", 0, callback);
    Entity::die();
}


/**
 * Verifies if the player is inside the boundaries of the game.
 */
bool Player::insideBoundaries() const
{
    return (pos().x() >= 0) && (pos().x() <= (scene()->width() - pixmap().width()));
}





