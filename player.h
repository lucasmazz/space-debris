#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include "entity.h"
#include "sprite.h"


class Player : public Entity
{

public:
    Player(std::unordered_map<std::string, std::vector<std::shared_ptr<Sprite>>> sprites);

    void crash();
    void brake();
    void accelerate(const float a);
    void move(const float elapsed);
    void die(std::function<void ()> callback=NULL);

private:
    bool insideBoundaries() const;

private:
    bool braked_ = false;

};


#endif // PLAYER_H
