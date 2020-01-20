#include "sound.h"


std::vector<QMediaPlayer*> Sound::channels_;
unsigned int Sound::index_ = 0;

/**
 * Plays a sound.
 *
 * Switch between sound channels for more than one sound can be played at the same time.
 *
 * @param path Path of a sound
 */
void Sound::play(const char path[])
{
    channels_[index_]->setMedia(QUrl(path));
    channels_[index_]->setPosition(0);
    channels_[index_]->play();

    if (++index_ == channels_.size())
        index_ = 0;
}

/**
 * Creates a number of sound channels used to play different sounds at same time.
 *
 * @param number Number of sound channels
 */
void Sound::channels(const unsigned int number)
{
    for(unsigned int i=0; i < number; i++)
        channels_.push_back(new QMediaPlayer());
}
