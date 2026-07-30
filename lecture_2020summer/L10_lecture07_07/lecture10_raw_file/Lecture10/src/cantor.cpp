/*
 * FILE: CANTOR FRACTALS
 * ---------------------
 * This program draws a Cantor Fractal of a constant depth on the screen.
 * A Cantor fractal of depth N is a thick horizontal line on top, with
 * a depth N-1 Cantor fractal below the left third, and a depth N-1 Cantor
 * fractal below the right third, of the drawn line.
 */

#include <math.h>
#include "gwindow.h"
#include "gobjects.h"
#include "point.h"
#include "simpio.h"
#include "fractals.h"

using namespace std;

/* Function: Draw Cantor
 * ---------------------
 * A recursive function that draws a Cantor Fractal between points
 * "left" and "right." The fractal will have "level" numbers of levels.
 */
void drawCantor(GWindow & w, int order, GPoint left, GPoint right) {
    /* TODO: Implement the Cantor Set drawing function. */
    pause(30);
    drawThickLine(w, left, right);
    if (order > 1) {
        {
            GPoint midLeft = pointBetween(left, right, 1.0 / 3);
            drawCantor(w, order - 1, getLoweredPoint(left), getLoweredPoint(midLeft));
            GPoint midRight = pointBetween(left, right, 2.0 / 3);
            drawCantor(w, order - 1, getLoweredPoint(midRight), getLoweredPoint(right));
        }
    }
}

/* PROVIDED HELPER FUNCTIONS */

/* Function: pointBetween
 * ---------------------
 * Given two points and a franction (assumed to be in the range
 * [0, 1], the function returns the point "fraction" amount of the
 * way between p1 and p2.
 */
GPoint pointBetween(GPoint p1, GPoint p2, double fraction) {
    double deltaX = p2.getX() - p1.getX();
    double deltaY = p2.getY() - p1.getY();
    double x = p1.getX() + fraction * deltaX;
    double y = p1.getY() + fraction * deltaY;
    GPoint newPoint(x, y);
    return newPoint;
}


/* Function: Draw Thick Line
 * ---------------------
 * Because sometimes thin lines just don't look good enough in
 * a lecture demo. Actually draws a rectangle instead of a line :)
 */
void drawThickLine(GWindow & w, GPoint left, GPoint right) {
    double width = right.getX() - left.getX();
    // this is called a pointer. We will learn about them later.
    GRect * rect = new GRect(0, 0, width, RECT_HEIGHT);
    rect->setFilled(true);
    cout << left.getX() << "," << left.getY() << endl;
    w.add(rect, left.getX(), left.getY());
}

/* Function: Get Lowered Point
 * ---------------------
 * Returns a GPoint which is LEVEL_HEIGHT pixels lower than the one
 * passed in (has a larger Y value).
 */
GPoint getLoweredPoint(GPoint point) {
    GPoint next(point.getX(), point.getY() + LEVEL_HEIGHT);
    return next;
}

void runCantorDemo() {
    GWindow w(SCREEN_WIDTH, SCREEN_HEIGHT);
    GPoint left(INSET, INSET);
    GPoint right(SCREEN_WIDTH - INSET, INSET);
    drawCantor(w, FRACTAL_DEPTH, left, right);
}

