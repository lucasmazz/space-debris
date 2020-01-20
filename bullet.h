#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsScene>
#include "entity.h"


class Bullet : public Entity
{

public:
    Bullet(std::unordered_map<std::string, std::vector<Sprite*>> sprites);
};

#endif // BULLET_H
