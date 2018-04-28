#include <QMouseEvent>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>

#include <iostream>
#include <math.h>
#include <float.h>

#include "viewcontrolwidget.h"

static double vertexData[114][3] = {
{0.00000000000000000,0.00000000000000000,1.00000000000000000},
{0.38268343236508978,0.00000000000000000,0.92387953251128674},
{0.70710678118654746,0.00000000000000000,0.70710678118654757},
{0.92387953251128674,0.00000000000000000,0.38268343236508984},
{1.00000000000000000,0.00000000000000000,0.00000000000000006},
{0.92387953251128674,0.00000000000000000,-0.38268343236508973},
{0.70710678118654757,0.00000000000000000,-0.70710678118654746},
{0.38268343236508989,0.00000000000000000,-0.92387953251128674},
{0.00000000000000012,0.00000000000000000,-1.00000000000000000},
{0.35355339059327379,0.14644660940672624,0.92387953251128674},
{0.65328148243818818,0.27059805007309845,0.70710678118654757},
{0.85355339059327373,0.35355339059327379,0.38268343236508984},
{0.92387953251128674,0.38268343236508978,0.00000000000000006},
{0.85355339059327373,0.35355339059327379,-0.38268343236508973},
{0.65328148243818829,0.27059805007309851,-0.70710678118654746},
{0.35355339059327384,0.14644660940672630,-0.92387953251128674},
{0.27059805007309851,0.27059805007309845,0.92387953251128674},
{0.50000000000000000,0.49999999999999989,0.70710678118654757},
{0.65328148243818829,0.65328148243818818,0.38268343236508984},
{0.70710678118654757,0.70710678118654746,0.00000000000000006},
{0.65328148243818829,0.65328148243818818,-0.38268343236508973},
{0.50000000000000011,0.50000000000000000,-0.70710678118654746},
{0.27059805007309862,0.27059805007309856,-0.92387953251128674},
{0.14644660940672627,0.35355339059327379,0.92387953251128674},
{0.27059805007309851,0.65328148243818818,0.70710678118654757},
{0.35355339059327384,0.85355339059327373,0.38268343236508984},
{0.38268343236508984,0.92387953251128674,0.00000000000000006},
{0.35355339059327384,0.85355339059327373,-0.38268343236508973},
{0.27059805007309856,0.65328148243818829,-0.70710678118654746},
{0.14644660940672630,0.35355339059327384,-0.92387953251128674},
{0.00000000000000002,0.38268343236508978,0.92387953251128674},
{0.00000000000000004,0.70710678118654746,0.70710678118654757},
{0.00000000000000006,0.92387953251128674,0.38268343236508984},
{0.00000000000000006,1.00000000000000000,0.00000000000000006},
{0.00000000000000006,0.92387953251128674,-0.38268343236508973},
{0.00000000000000004,0.70710678118654757,-0.70710678118654746},
{0.00000000000000002,0.38268343236508989,-0.92387953251128674},
{-0.14644660940672621,0.35355339059327379,0.92387953251128674},
{-0.27059805007309845,0.65328148243818818,0.70710678118654757},
{-0.35355339059327373,0.85355339059327373,0.38268343236508984},
{-0.38268343236508973,0.92387953251128674,0.00000000000000006},
{-0.35355339059327373,0.85355339059327373,-0.38268343236508973},
{-0.27059805007309851,0.65328148243818829,-0.70710678118654746},
{-0.14644660940672627,0.35355339059327384,-0.92387953251128674},
{-0.27059805007309845,0.27059805007309851,0.92387953251128674},
{-0.49999999999999989,0.50000000000000000,0.70710678118654757},
{-0.65328148243818818,0.65328148243818829,0.38268343236508984},
{-0.70710678118654746,0.70710678118654757,0.00000000000000006},
{-0.65328148243818818,0.65328148243818829,-0.38268343236508973},
{-0.50000000000000000,0.50000000000000011,-0.70710678118654746},
{-0.27059805007309856,0.27059805007309862,-0.92387953251128674},
{-0.35355339059327379,0.14644660940672630,0.92387953251128674},
{-0.65328148243818818,0.27059805007309856,0.70710678118654757},
{-0.85355339059327373,0.35355339059327384,0.38268343236508984},
{-0.92387953251128674,0.38268343236508989,0.00000000000000006},
{-0.85355339059327373,0.35355339059327384,-0.38268343236508973},
{-0.65328148243818829,0.27059805007309862,-0.70710678118654746},
{-0.35355339059327384,0.14644660940672632,-0.92387953251128674},
{-0.38268343236508978,0.00000000000000005,0.92387953251128674},
{-0.70710678118654746,0.00000000000000009,0.70710678118654757},
{-0.92387953251128674,0.00000000000000011,0.38268343236508984},
{-1.00000000000000000,0.00000000000000012,0.00000000000000006},
{-0.92387953251128674,0.00000000000000011,-0.38268343236508973},
{-0.70710678118654757,0.00000000000000009,-0.70710678118654746},
{-0.38268343236508989,0.00000000000000005,-0.92387953251128674},
{-0.35355339059327379,-0.14644660940672621,0.92387953251128674},
{-0.65328148243818829,-0.27059805007309840,0.70710678118654757},
{-0.85355339059327384,-0.35355339059327368,0.38268343236508984},
{-0.92387953251128685,-0.38268343236508967,0.00000000000000006},
{-0.85355339059327384,-0.35355339059327368,-0.38268343236508973},
{-0.65328148243818840,-0.27059805007309845,-0.70710678118654746},
{-0.35355339059327390,-0.14644660940672624,-0.92387953251128674},
{-0.27059805007309856,-0.27059805007309845,0.92387953251128674},
{-0.50000000000000011,-0.49999999999999989,0.70710678118654757},
{-0.65328148243818840,-0.65328148243818818,0.38268343236508984},
{-0.70710678118654768,-0.70710678118654746,0.00000000000000006},
{-0.65328148243818840,-0.65328148243818818,-0.38268343236508973},
{-0.50000000000000011,-0.50000000000000000,-0.70710678118654746},
{-0.27059805007309862,-0.27059805007309856,-0.92387953251128674},
{-0.14644660940672646,-0.35355339059327368,0.92387953251128674},
{-0.27059805007309889,-0.65328148243818807,0.70710678118654757},
{-0.35355339059327429,-0.85355339059327351,0.38268343236508984},
{-0.38268343236509034,-0.92387953251128652,0.00000000000000006},
{-0.35355339059327429,-0.85355339059327351,-0.38268343236508973},
{-0.27059805007309889,-0.65328148243818818,-0.70710678118654746},
{-0.14644660940672649,-0.35355339059327379,-0.92387953251128674},
{-0.00000000000000007,-0.38268343236508978,0.92387953251128674},
{-0.00000000000000013,-0.70710678118654746,0.70710678118654757},
{-0.00000000000000017,-0.92387953251128674,0.38268343236508984},
{-0.00000000000000018,-1.00000000000000000,0.00000000000000006},
{-0.00000000000000017,-0.92387953251128674,-0.38268343236508973},
{-0.00000000000000013,-0.70710678118654757,-0.70710678118654746},
{-0.00000000000000007,-0.38268343236508989,-0.92387953251128674},
{0.14644660940672632,-0.35355339059327373,0.92387953251128674},
{0.27059805007309862,-0.65328148243818807,0.70710678118654757},
{0.35355339059327395,-0.85355339059327362,0.38268343236508984},
{0.38268343236509000,-0.92387953251128663,0.00000000000000006},
{0.35355339059327395,-0.85355339059327362,-0.38268343236508973},
{0.27059805007309867,-0.65328148243818818,-0.70710678118654746},
{0.14644660940672638,-0.35355339059327384,-0.92387953251128674},
{0.27059805007309845,-0.27059805007309856,0.92387953251128674},
{0.49999999999999983,-0.50000000000000011,0.70710678118654757},
{0.65328148243818807,-0.65328148243818840,0.38268343236508984},
{0.70710678118654735,-0.70710678118654768,0.00000000000000006},
{0.65328148243818807,-0.65328148243818840,-0.38268343236508973},
{0.49999999999999989,-0.50000000000000011,-0.70710678118654746},
{0.27059805007309851,-0.27059805007309862,-0.92387953251128674},
{0.35355339059327368,-0.14644660940672649,0.92387953251128674},
{0.65328148243818807,-0.27059805007309889,0.70710678118654757},
{0.85355339059327351,-0.35355339059327434,0.38268343236508984},
{0.92387953251128652,-0.38268343236509039,0.00000000000000006},
{0.85355339059327351,-0.35355339059327434,-0.38268343236508973},
{0.65328148243818818,-0.27059805007309895,-0.70710678118654746},
{0.35355339059327379,-0.14644660940672652,-0.92387953251128674}
};


// This widget implements a nifty 3D view controller
// It allows the user to select from a precise set of view directions
// which is very suitable for slow to redraw objects

ViewControlWidget::ViewControlWidget(QWidget *parent)
        : QWidget(parent)
{
    backgroundImage = new QPixmap(":/new/prefix1/ViewControlWidget Images/SideBySide.png");
    blob = new QPixmap(":/new/prefix1/ViewControlWidget Images/Blob.png");

    setCursor(Qt::CrossCursor);

    lastX = 0;
    lastY = -1;
    lastZ = 0;
}

ViewControlWidget::~ViewControlWidget()
{
    delete backgroundImage;
}

void ViewControlWidget::mousePressEvent(QMouseEvent *event)
{
    double x, y, z, t;
    double radius = 73;
    int centreY = 80;
    int centre1X = 79;
    int centre2X = 239;
    int index;

    //std::cerr << event->pos().x() << " " << event->pos().y() << "\n";

    if (event->buttons() & Qt::LeftButton)
    {
        if (event->pos().x() < (centre1X + centre2X) / 2) // left hand image
        {
            // convert to target coordinates
            x = static_cast<double>((event->pos().x() - centre1X)) / radius;
            z = static_cast<double>(centreY - event->pos().y()) / radius;
            t = 1 - (x * x + z * z);
            if (t > 0) y = sqrt(t);
            else y = 0;
            if (lastY < 0) y = -y;
            index = FindClosestVertex(vertexData, 114, x, y, z);
            lastX = vertexData[index][0];
            lastY = vertexData[index][1];
            lastZ = vertexData[index][2];
        }
        else
        {
            // convert to target coordinates
            x = static_cast<double>(event->pos().x() - centre2X) / radius;
            y = static_cast<double>(centreY - event->pos().y()) / radius;
            t = 1 - (x * x + y * y);
            if (t > 0) z = sqrt(t);
            else z = 0;
            if (lastZ < 0) z = -z;
            index = FindClosestVertex(vertexData, 114, x, y, z);
            lastX = vertexData[index][0];
            lastY = vertexData[index][1];
            lastZ = vertexData[index][2];
        }
        // send out the new vector from the point to the centre
        emit EmitCameraVec(-lastX, -lastY, -lastZ);
        update();
    }
}

void ViewControlWidget::paintEvent (QPaintEvent *)
{
    double radius = 73;
    double centreY = 80;
    double centre1X = 79;
    double centre2X = 239;
    QPainter qpainter(this);

    int x = static_cast<int>((radius * lastX) + centre1X + 0.5);
    int y = static_cast<int>(centreY - (radius * lastZ) + 0.5);

    qpainter.drawPixmap(5, 5, *backgroundImage);
    qpainter.drawPixmap(x - blob->width() / 2 + 1, y - blob->height() / 2, *blob);

    x = static_cast<int>((radius * lastX) + centre2X + 0.5);
    y = static_cast<int>(centreY - (radius * lastY) + 0.5);

    qpainter.drawPixmap(x - blob->width() / 2 + 1, y - blob->height() / 2, *blob);
}

int ViewControlWidget::FindClosestVertex(double data[][3], int count, double x, double y, double z)
{
    double minSqDist = DBL_MAX;
    double sqDist, dx, dy, dz;
    int index, i;
    for (i = 0; i < count; i++)
    {
        dx = data[i][0] - x;
        dy = data[i][1] - y;
        dz = data[i][2] - z;
        sqDist = dx * dx + dy * dy + dz * dz;
        if (sqDist < minSqDist)
        {
            index = i;
            minSqDist = sqDist;
        }
    }
    return index;
}
