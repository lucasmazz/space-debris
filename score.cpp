#include "score.h"


Score::Score()
{
    setDefaultTextColor(Qt::cyan);
    setFont(QFont("times", 24));
    points(0);
}


/**
 * "points" accessor.
 *
 * @return points_
 */
unsigned int Score::points() const
{
    return points_;
}

/**
 * "points" mutator.
 *
 * @param value
 */
void Score::points(const unsigned int value)
{
    points_ = value;
    update();
}

/**
 * Increase points and update.
 */
void Score::increase()
{
    points_++;
    update();
}

/**
 * Decrease points and update.
 */
void Score::decrease()
{
    points_--;
    update();
}

/**
 * increase points.
 */
Score &Score::operator++()
{
    increase();
    return *this;
}

/**
 * Decrease points.
 */
Score &Score::operator--()
{
    decrease();
    return *this;
}

/**
 * Update points on the screen.
 */
void Score::update()
{
    setPlainText(QString("★ ") + QString::number(points()));
}



