#include "labyrinth.h"
#include "demo/MazeGenerator.h"
#include "testing/SimpleTest.h"
using namespace std;

/* Change kYourName constant to your full name.
 *
 * WARNING: Once you've set set this constant and started exploring your labyrinth,
 * do NOT edit the value of kYourName. Changing kYourName will change which
 * maze you get back, which might invalidate all your hard work!
 */
const string kYourName = "Yue Daiyan";

/* Change this constant to the path out of your labyrinth. */
const string kPathOutOfNormalMaze = "SENEEWSSENSWWSW";

void checkCellContents(MazeCell*& curr, Set<string>& needs) {
    if (needs.contains(curr->contents)) {
        needs -= curr->contents;
        // if() means I only pick items what I need…
        // curr->contents = "";
    }
}

void MazeMove(MazeCell*& curr, char move) {
    if (move == 'S') {
        curr = curr->south;
    }
    if (move == 'N') {
        curr = curr->north;
    }
    if (move == 'E') {
        curr = curr->east;
    }
    if (move == 'W') {
        curr = curr->west;
    }
}

bool checkValidMove(MazeCell* curr, char move) {
    if (move == 'S') {
        if (curr->south == nullptr) {
            // error("invalid move");
            return false;
        }
    }
    if (move == 'N') {
        if (curr->north == nullptr) {
            // error("invalid move");
            return false;
        }
    }
    if (move == 'E') {
        if (curr->east == nullptr) {
            // error("invalid move");
            return false;
        }
    }
    if (move == 'W') {
        if (curr->west == nullptr) {
            // error("invalid move");
            return false;
        }
    }
    return true;
}

/**
 * Given a location in a maze, returns whether the given sequence of
 * steps will let you escape the maze.
 *
 * To escape the maze, you need to collect all items in the `needs` set.
 * You can only take steps in the four cardinal directions,
 * and you can't move in directions that don't exist in the maze.
 */
bool isPathToFreedom(MazeCell* start, string moves, Set<string> needs) {
    cout << "" << endl;
    cout << " ---- " << endl;
    if (moves.find_first_not_of("NSEW") != string::npos) {
        error("input path contains invalid character.");
    }

    cout << "path valid" << endl;
    cout << "" << endl;

    // cout << "check first cell" << endl;
    // check first cell
    checkCellContents(start, needs);
    cerr << needs.toString() << endl;

    // other cells

    MazeCell* curr = start;

    for (char move : moves) {
        if (checkValidMove(curr, move)) {

            MazeMove(curr, move);

            checkCellContents(curr, needs);
            if (needs.isEmpty()) {
                return true;
            }
            cerr << needs.toString() << endl;
        }
    }
    cerr << needs.toString() << endl;
    cout << " ---- " << endl;
    cout << "" << endl;
    return false;
}


/* * * * * * Test Cases Below This Point * * * * * */
bool labyrinth_learn_1(string str) {
    return str.find_first_not_of("NSEW") == string::npos;
}

STUDENT_TEST("Learn: labyrinth") {
    EXPECT(labyrinth_learn_1("NNSSEW"));
}

STUDENT_TEST("Learn: labyrinth") {
    EXPECT(!labyrinth_learn_1("AASEW"));
}

PROVIDED_TEST("Check paths in the sample from writeup") {
    Set<string> allThree = {"Spellbook", "Potion", "Wand"};
    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    cout << "-1" << endl;
    /* These paths are the ones in the handout. They all work. */
    EXPECT(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWN", allThree));
    EXPECT(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES", allThree));
    EXPECT(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES", allThree));

    cout << "-2" << endl;

    /* This path works to pick up just potion */
    EXPECT(isPathToFreedom(maze[2][2], "ESNW", { "Potion" }));

    cout << "-3" << endl;

    /* This path doesn't work, since doesn't pick up all items. */
    EXPECT(!isPathToFreedom(maze[2][2], "ESNW", allThree));

    cout << "-4" << endl;

    /* This path doesn't work, cannot walk through walls. */
    EXPECT(!isPathToFreedom(maze[2][2], "NNWWSSSEEE", allThree));
}

PROVIDED_TEST("Works when start on an item") {
    auto maze = toMaze({"P-S-W"});

    EXPECT(isPathToFreedom(maze[0][0], "E", {"Potion"}));
    EXPECT(isPathToFreedom(maze[0][1], "W", {"Potion", "Spellbook"}));
}

PROVIDED_TEST("Reports errors if given illegal characters") {
    auto maze = toMaze({"P-S-W"});

    EXPECT_ERROR(isPathToFreedom(maze[0][0], "Q", {"Wand"}));
    EXPECT_ERROR(isPathToFreedom(maze[0][0], "Ee", {"Wand"}));
}

PROVIDED_TEST("Escape from your personal labyrinth!") {
    Set<string> allThree = {"Spellbook", "Potion", "Wand"};
    /* A maze for you to escape from. This maze will be personalized
     * based on the constant kYourName.
     */
    EXPECT(kYourName != "TODO");
    MazeCell* startLocation = mazeFor(kYourName);

    /* Set a breakpoint here. As a reminder, the labyrinth you
     * get will be personalized to you, so don't start exploring the labyrinth
     * unless you've edited the constant kYourName to include your name(s)!
     * Otherwise, you'll be escaping the wrong labyrinth.
     */
    EXPECT(kPathOutOfNormalMaze != "TODO");
    EXPECT(isPathToFreedom(startLocation, kPathOutOfNormalMaze, allThree));
}

