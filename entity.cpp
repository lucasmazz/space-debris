#include "entity.h"


unsigned int Entity::Entity::current_id_ = 0;

Entity::Entity(Sprite::Set sprites) : sprites_(sprites)
{
    if (current_id_ == 1000)
        current_id_ = 0;

    id_ = current_id_++;

    animation("default");
    updateSprite(current_animation_[0]);
}


/**
 * Plays a sound.
 *
 * @param path
 */
void Entity::playSound(const char path[])
{
    Sound::play(path);
}


/**
 * "id" accessor.
 *
 * @return id_ Entity unique id.
 */
unsigned int Entity::id() const
{
    return id_;
}


/**
 * "alive" accessor.
 *
 * @return alive_
 */
unsigned int Entity::alive() const
{
    return alive_;
}


/**
 * "speed[0]" accessor.
 *
 * @return speed_[0] The x coordinates speed.
 */
float Entity::speedX() const
{
    return speed_[0];
}


/**
 * "speed[1]" accessor.
 *
 * @return speed_[1] The y coordinates speed.
 */
float Entity::speedY() const
{
    return speed_[1];
}


/**
 * "speed" mutator.
 *
 * @param x Speed in x coordinates.
 * @param y Speed in y coordinates.
 */
void Entity::speed(const float x, const float y)
{
    if (abs(x) <= max_speed_[0])
        speed_[0] = x;
    else
        speed_[0] = x/abs(x) * max_speed_[0];

    if (abs(y) <= max_speed_[0])
        speed_[1] = y;
    else
        speed_[1] = y/abs(y) * max_speed_[1];
}


/**
 * "acceleration[0]" accessor.
 *
 * @return acceleration_[0] The x coordinates acceleration.
 */
float Entity::accelerationX() const
{
    return acceleration_[0];
}


/**
 * "acceleration[1]" accessor.
 *
 * @return acceleration_[1] The y coordinates acceleration.
 */
float Entity::accelerationY() const
{
    return acceleration_[1];
}


/**
 * "acceleration" mutator.
 *
 * @param x Acceleration in x coordinates.
 * @param y Acceleration in y coordinates.
 */
void Entity::acceleration(const float x, const float y)
{
    if (abs(x) <= max_acceleration_[0])
        acceleration_[0] = x;
    else
        acceleration_[0] = x/abs(x) * max_acceleration_[0];

    if (abs(y) <= max_acceleration_[1])
        acceleration_[1] = y;
    else
        acceleration_[1] = y/abs(y) * max_acceleration_[1];
}


/**
 * "max_speed[0]" accessor.
 *
 * @return max_speed_[0] The x coordinates max speed.
 */
float Entity::maxSpeedX() const
{
    return max_speed_[0];
}


/**
 *  "max_speed[1]" accessor.
 *
 * @return max_speed_[1] The y coordinates max speed.
 */
float Entity::maxSpeedY() const
{
    return max_speed_[1];
}


/**
 *  "max_speed" mutator.
 *
 * @param x Max speed in x coordinates.
 * @param y Max speed in y coordinates.
 */
void Entity::maxSpeed(const float x, const float y)
{
    max_speed_[0] = x;
    max_speed_[1] = y;
}


/**
 * "max_acceleration[0]" accessor.
 *
 * @return max_acceleration_[0] The x coordinates max acceleration.
 */
float Entity::maxAccelerationX() const
{
    return max_acceleration_[0];
}


/**
 * "max_acceleration[1]" accessor.
 *
 * @return max_acceleration_[1] The y coordinates max acceleration.
 */
float Entity::maxAccelerationY() const
{
    return max_acceleration_[1];
}


/**
 * "max_acceleration" mutator.
 *
 * @param x Max acceleration in x coordinates.
 * @param y Max acceleration in y coordinates.
 */
void Entity::maxAcceleration(const float x, const float y)
{
    max_acceleration_[0] = x;
    max_acceleration_[1] = y;
}

/**
 * Sets the animation.
 *
 * @param animation Name of the animation.
 * @param index Animation will start from that index.
 * @param callback Function that is called after animation ends.
 */
void Entity::animation(std::string animation, const unsigned int index, std::function<void ()> callback)
{
    current_animation_ = sprites_[animation];
    current_sprite_index_ = index;
    callback_ = callback;
}


/**
 * Handles the animation.
 *
 * Basically updates the entity sprite if the last sprite time is over.
 * Further, when animation is finished calls the callback function.
 *
 * @param elapsed_time Time elapsed from the last animate call.
 */
void Entity::animate(const float elapsed_time)
{

    updateSprite(current_animation_[current_sprite_index_]);

    float t = current_animation_[current_sprite_index_]->elapsed_time() + elapsed_time;

    current_animation_[current_sprite_index_]->elapsed_time(t);

    if (current_animation_[current_sprite_index_]->finished()) {
        current_animation_[current_sprite_index_]->clear();
        current_sprite_index_++;
    }

    if (current_sprite_index_ > current_animation_.size()-1) {
        current_sprite_index_ = 0;

        if (callback_ != NULL)
            callback_();
    }
}


/**
 * Handles the movement using the speed and acceleration.
 *
 * @param elapsed_time Time elapsed from the last move call.
 */
void Entity::move(const float elapsed_time)
{
    if (acceleration_[0] != 0) {
        speed(speed_[0] + acceleration_[0]*elapsed_time, speed_[1]);
    }

    if (acceleration_[1] != 0) {
        speed(speed_[0],  speed_[1] + acceleration_[1]*elapsed_time);
    }

    float distance_x = x() + speed_[0]*elapsed_time;
    float distance_y = y() + speed_[1]*elapsed_time;

    setPos(distance_x, distance_y);
}


/**
 * Sets "alive" flag to false.
 */
void Entity::die()
{
    alive_ = false;
}

/**
 * Updates the entity pixmap sprite.
 *
 * @param sprite
 */
void Entity::updateSprite(std::shared_ptr<Sprite> sprite)
{
    setPixmap(*sprite);
}


