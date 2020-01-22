#ifndef ENTITY_H
#define ENTITY_H

#include <functional>
#include <vector>
#include <unordered_map>
#include <memory>
#include <QGraphicsPixmapItem>

#include "sound.h"
#include "sprite.h"


class Entity : public QGraphicsPixmapItem
{

public:
    Entity(std::unordered_map<std::string, std::vector<std::shared_ptr<Sprite>>> sprites);

    void playSound(const char path[]);

    unsigned int id() const;
    unsigned int alive() const;

    float speedX() const;
    float speedY() const;
    void speed(const float x, const float y);

    float accelerationX() const;
    float accelerationY() const;
    void acceleration(const float x, const float y);

    float maxSpeedX() const;
    float maxSpeedY() const;
    void maxSpeed(const float x, const float y);

    float maxAccelerationX() const;
    float maxAccelerationY() const;
    void maxAcceleration(const float x, const float y);

    void animation(std::string animation, const unsigned int index=0, std::function<void()> callback=NULL);

    void animate(const float elapsed_time);
    void move(const float elapsed_time);

    void die();

protected:
    void updateSprite(std::shared_ptr<Sprite> sprite);

protected:
    unsigned int id_;
    bool alive_ = true;

    float acceleration_[2] {0,0}; // x, y
    float speed_[2] {0,0}; // x, y
    float max_speed_[2] {999, 999}; // x, y
    float max_acceleration_[2] {999, 999}; // x, y

    std::unordered_map<std::string, std::vector<std::shared_ptr<Sprite>>> sprites_;
    std::vector<std::shared_ptr<Sprite>> current_animation_;
    unsigned int current_sprite_index_;

    std::function<void()> callback_ = NULL;

private:
    static unsigned int current_id_;

};



#endif // ENTITY_H
