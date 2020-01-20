#ifndef HEALTH_H
#define HEALTH_H

#include "score.h"


class Health : public Score
{

public:
    Health();

private:
    void update() override;

};


#endif // HEALTH_H
