#include "sprite.h"


Sprite::Sprite(const char path[], float time) : QPixmap(path), time_(time) {}


/**
 * "time" accessor.
 *
 * @return time_
 */
float Sprite::time() const
{
    return time_;
}

/**
 * "time" mutator.
 *
 * @param value
 */
void Sprite::time(const float value)
{
    time_ = value;
}


/**
 * "elapsed_time" accessor.
 *
 * @return elapsed_time_
 */
float Sprite::elapsed_time() const
{
    return elapsed_time_;
}


/**
 * "elapsed_time" mutator.
 *
 * @param value
 */
void Sprite::elapsed_time(const float value)
{
    elapsed_time_ = value;
}


/**
 * Returns if the sprite time is finished.
 */
bool Sprite::finished() const
{
    return elapsed_time() >= time();
}


/**
 * Clears the elapsed time from sprite.
 */
void Sprite::clear()
{
    elapsed_time(0);
}
