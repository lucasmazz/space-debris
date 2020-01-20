#include "health.h"


Health::Health()
{
    setDefaultTextColor(Qt::red);
    setFont(QFont("Sans", 32));
    points(3);
    show();
}

/**
 * Updates the health points on the screen.
 */
void Health::update()
{
    QString string_points = "";

    for (unsigned int i=3; i > 0; i--) {
        if (i <= points())
            string_points += "♥";
        else
            string_points += "♡";
    }

    setPlainText(string_points);
}



