/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "gtypes.h"
#include "recursion.h"
#include "testing/SimpleTest.h"
#include <iostream> // for cout, endl
using namespace std;

/*
 * This function draws a filled, black triangle on the provided GWindow
 * that is defined by the corner GPoints one, two, and three. This
 * function has been provided for you and does not need to be modified.
 */
void fillBlackTriangle(GWindow& window, GPoint one, GPoint two, GPoint three) {
    window.setColor("black");
    window.fillPolygon( {one, two, three} );
}

// 绘制递归图形,根据 order 自动调整递归层级
int drawSierpinskiTriangle(GWindow& window, GPoint one, GPoint two, GPoint three, int order) {
    if (order == 0) {
        fillBlackTriangle(window, one, two, three);
        return 1;
    } else {
        GPoint one_two((one.x + two.x) / 2, (one.y + two.y) / 2);
        GPoint two_three((two.x + three.x) / 2, (two.y + three.y) / 2);
        GPoint one_three((three.x + one.x) / 2, (three.y + one.y) / 2);
        int a = drawSierpinskiTriangle(window, one, one_two, one_three, order - 1);
        int b = drawSierpinskiTriangle(window, one_two, two, two_three, order - 1);
        int c = drawSierpinskiTriangle(window, one_three, two_three, three, order - 1);
        return a + b + c;
    }
    return 0;
}


/* * * * * * Test Cases * * * * * */

/*
 * Do not modify the code beyond this line! There are no
 * unit tests for this problem. You should do all testing
 * via the interactive demo.
 */
PROVIDED_TEST("Test fractal drawing interactively using graphical demo") {
    runInteractiveDemo();
}

