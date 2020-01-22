#include "bullet.h"


Bullet::Bullet(Sprite::Set& sprites) : Entity(sprites)
{
    playSound("qrc:/assets/sounds/shot.wav");
    speed(0, -999);
}
