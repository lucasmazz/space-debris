#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "entity.h"

class Background : public Entity
{

public:
    Background(std::unordered_map<std::string, std::vector<Sprite*>> sprites);

};


#endif // BACKGROUND_H
