#ifndef SOUND_H
#define SOUND_H

#include <vector>

#include <QMediaPlayer>


class Sound
{

public:
    static void play(const char path[]);
    static void channels(const unsigned int number);

private:
    Sound();

private:
    static std::vector<QMediaPlayer*> channels_;
    static unsigned int index_;

};

#endif // SOUND_H
