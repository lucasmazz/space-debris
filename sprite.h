#ifndef SPRITE_H
#define SPRITE_H

#include <QPixmap>


class Sprite : public QPixmap
{

public:
    Sprite(const char path[], float time=0);

    float time() const;
    void time(const float value);

    float elapsed_time() const;
    void elapsed_time(const float value);

    bool finished() const;
    void clear();

private:
    float time_;
    float elapsed_time_ = 0;

};


#endif // SPRITE_H
