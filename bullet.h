#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsScene>
#include "entity.h"


class Bullet : public Entity
{

public:
    Bullet(Sprite::Set& sprites);
};

#endif // BULLET_H
