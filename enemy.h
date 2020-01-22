#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"


class Enemy : public Entity
{

public:
    Enemy(std::unordered_map<std::string, std::vector<std::shared_ptr<Sprite>>> sprites);

    void move(const float elapsed_time);
    void die(std::function<void()> callback=NULL);
    void rotate(const unsigned int angle);

    unsigned int rotation() const;
    void rotation(const unsigned int value);


private:
    unsigned int rotation_ = 0;


};


#endif // ENEMY_H
