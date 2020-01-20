#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QString>
#include <QFont>


class Score : public QGraphicsTextItem
{

public:
    Score();

    unsigned int points() const;
    void points(const unsigned int value);

    void increase();
    void decrease();

public:
    Score &operator++();
    Score &operator--();

protected:
    virtual void update();

protected:
    unsigned int points_;

};


#endif // SCORE_H
