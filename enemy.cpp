#include "enemy.h"


Enemy::Enemy(Sprite::Set& sprites) : Entity(sprites)
{
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);
    rotation(rand() % 360);
    speed(0, 100);
}

/**
 * Handles the movement and rotation
 *
 * @param elapsed_time Time elapsed from the last move call.
 */
void Enemy::move(const float elapsed_time)
{
    rotate(int(100*elapsed_time));
    Entity::move(elapsed_time);
}


/**
 * Kills the enemy.
 *
 * @param callback Function that will be called after the die animation ends.
 */
void Enemy::die(std::function<void ()> callback)
{
    animation("die", 0, callback);
    playSound("qrc:/assets/sounds/explosion.wav");
    Entity::die();
}

/**
 * Rotates the enemy.
 *
 * @param angle
 */
void Enemy::rotate(const unsigned int angle)
{
    rotation(rotation_ + angle);
}


/**
 * "rotation" accessor.
 *
 * @return rotation_
 */
unsigned int Enemy::rotation() const
{
    return rotation_;
}


/**
 * "rotation" mutator.
 *
 * @param value
 */
void Enemy::rotation(const unsigned int value)
{
    rotation_ = value;
    setRotation(rotation_);
}
