/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "backtracking.h"
#include "grid.h"
#include "gridlocation.h"
#include "lexicon.h"
#include "queue.h"
#include "set.h"
#include "testing/SimpleTest.h"
#include <iostream> // for cout, endl
#include <string> // for string class
using namespace std;

/*
TODO:

Extension
    Further board explorations.The standard Boggle game comes with sixteen letter cubes,
    each with particular letters on each of their six faces.The letters on each cube are
    not random; they were chosen in such a way that common letters come up more often and
    it is easier to get a good mix of vowels and consonants. Here are the letters on all
    six faces of the standard cubes:

AAEEGN, ABBJOO, ACHOPS, AFFKPS,
AOOTTW, CIMOTU, DEILRX, DELRVY,
DISTTY, EEGHNW, EEINSU, EHRTVW,
EIOSST, ELRTTY, HIMNQU, HLNNRZ

    To configure a random board from the standard cubes, shuffle the cubes into grid
    locations and randomly select the face-up letter for each cube. Some Boggle boards
    constructed from the standard cubes are a lot more fruitful that others. Exploring
    in code can tell you more about this. Is there an arrangement of the standard cubes
    that produces a board containing no words? What about an arrangement that produces
    a longest word, maybe even a word that uses all the cubes? What is the highest-scoring
    board you can construct? Recursion will be handy in trying out all the possible
    arrangements, but there are a lot of options (do the math on all the permutations
    . . .), so you may need to come up with some heuristics to direct your explorations.
*/

// 辅助函数: 输入正确英文单词返回该英文单词分数
int points(const string& str) {
    return str.length() < 4 ? 0 : str.length() - 3;
}

// 辅助函数: 根据当前格子获得可以进入的所有格子
Set<GridLocation> currAccessible(Grid<char>& board, Set<GridLocation>& visitedCube, GridLocation& curr) {
    Set<GridLocation> result;
    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
            GridLocation possible(curr.row + r, curr.col + c);
            if (
                possible.row >= board.numRows()
                || possible.row < 0
                || possible.col >= board.numCols()
                || possible.col < 0
                || visitedCube.contains(possible)) {
                continue;
            }
            result.add(possible);
        }
    }
    return result;
}

// 递归函数
void scoreBoardHelp(Grid<char>& board, Lexicon& lex, Set<GridLocation>& visitedCube, GridLocation& curr, Set<string>& collectStr, string& pathStr) {
    // Prune
    if (!lex.containsPrefix(pathStr)) {
        return;
    }
    // base case
    if (lex.contains(pathStr) && pathStr.length() >= 4) {
        collectStr.add(pathStr);
    }

    Set<GridLocation> possibles = currAccessible(board, visitedCube, curr);

    // recursive case
    // visitedCube.add(curr);
    for (GridLocation possible : possibles) {
        char currChar = board.get(possible);
        visitedCube.add(possible);
        pathStr += currChar;
        scoreBoardHelp(board, lex, visitedCube, possible, collectStr, pathStr);
        visitedCube.remove(possible);
        pathStr.pop_back();
    }
    // visitedCube.remove(curr);
    return;
}

// 主函数: 调用递归函数
int scoreBoard(Grid<char>& board, Lexicon& lex) {
    Set<string> result = { };
    Set<string> collectStr = { };
    for (int r = 0; r < board.numRows(); r++) {
        for (int c = 0; c < board.numCols(); c++) {
            // start cube
            GridLocation startCube(r, c);
            // 已经经过的位置
            Set<GridLocation> visitedCube { startCube };
            string pathStr = string(1, board.get(startCube));
            scoreBoardHelp(board, lex, visitedCube, startCube, collectStr, pathStr);
            result += collectStr;
        }
    }

    int score = 0;
    for (string str : result) {
        score += points(str);
    }
    return score;
}

/* * * * * * Test Cases * * * * * */

/* Test helper function to return shared copy of Lexicon. Use to
 * avoid (expensive) re-load of word list on each test case. */
static Lexicon& sharedLexicon() {
    static Lexicon lex("res/EnglishWords.txt");
    return lex;
}

PROVIDED_TEST("Load shared Lexicon, confirm number of words") {
    Lexicon lex = sharedLexicon();
    EXPECT_EQUAL(lex.size(), 127145);
}
PROVIDED_TEST("Test point scoring") {
    EXPECT_EQUAL(points("and"), 0);
    EXPECT_EQUAL(points("quad"), 1);
    EXPECT_EQUAL(points("quint"), 2);
    EXPECT_EQUAL(points("sextet"), 3);
    EXPECT_EQUAL(points("seventh"), 4);
    EXPECT_EQUAL(points("supercomputer"), 10);
}
STUDENT_TEST("currAccessible() test start cube ") {
    Grid<char> board = {
        { 'B', 'C', 'D' },
        { 'G', 'H', 'J' },
        { 'L', 'M', 'N' },
        { 'Q', 'R', 'S' }
    };

    EXPECT_EQUAL(board.numRows(), 4);
    EXPECT_EQUAL(board.numCols(), 3);
    GridLocation curr(0, 0);
    Set<GridLocation> passed { curr };
    Set<GridLocation> expectation {
        GridLocation(0, 1),
        GridLocation(1, 0),
        GridLocation(1, 1)
    };
    Set<GridLocation> result = currAccessible(board, passed, curr);
    cerr << endl;
    cerr << result.toString() << endl;
    EXPECT(result == expectation);
}
STUDENT_TEST("currAccessible() test middle cube ") {
    Grid<char> board = {
        { 'B', 'C', 'D' },
        { 'G', 'H', 'J' },
        { 'L', 'M', 'N' },
        { 'Q', 'R', 'S' }
    };

    EXPECT_EQUAL(board.numRows(), 4);
    EXPECT_EQUAL(board.numCols(), 3);
    GridLocation curr(1, 1);
    Set<GridLocation> passed { curr, GridLocation(0, 0), GridLocation(0, 1) };
    Set<GridLocation> expectation {
        // GridLocation(0, 0),
        // GridLocation(0, 1),
        GridLocation(0, 2),
        GridLocation(1, 0),
        GridLocation(1, 2),
        GridLocation(2, 0),
        GridLocation(2, 1),
        GridLocation(2, 2)
    };
    Set<GridLocation> result = currAccessible(board, passed, curr);
    cerr << endl;
    cerr << result.toString() << endl;
    EXPECT(result == expectation);
}
STUDENT_TEST("currAccessible() test end cube ") {
    Grid<char> board = {
        { 'B', 'C', 'D' },
        { 'G', 'H', 'J' },
        { 'L', 'M', 'N' },
        { 'Q', 'R', 'S' }
    };

    EXPECT_EQUAL(board.numRows(), 4);
    EXPECT_EQUAL(board.numCols(), 3);
    GridLocation curr(board.numRows() - 1, board.numCols() - 1);
    Set<GridLocation> passed { curr };
    Set<GridLocation> expectation {
        GridLocation(3, 1),
        GridLocation(2, 1),
        GridLocation(2, 2)
    };
    Set<GridLocation> result = currAccessible(board, passed, curr);
    cerr << endl;
    cerr << result.toString() << endl;
    EXPECT(result == expectation);
}

PROVIDED_TEST("Test scoreBoard, board contains no words, score of zero") {
    Grid<char> board = {{'B','C','D','F'}, //no vowels, no words
                        {'G','H','J','K'},
                        {'L','M','N','P'},
                        {'Q','R','S','T'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 0);
}

PROVIDED_TEST("Test scoreBoard, board contains one word, score of 1") {
    Grid<char> board = {{'C','_','_','_'},
                        {'Z','_','_','_'},
                        {'_','A','_','_'},
                        {'_','_','R','_'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
}

PROVIDED_TEST("Test scoreBoard, alternate paths for same word, still score of 1") {
    Grid<char> board = {{'C','C','_','_'},
                        {'C','Z','C','_'},
                        {'_','A','_','_'},
                        {'R','_','R','_'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
}

PROVIDED_TEST("Test scoreBoard, small number of words in corner of board") {
    Grid<char> board = {{'L','I','_','_'},
                        {'M','E','_','_'},
                        {'_','S','_','_'},
                        {'_','_','_','_'}};
    Set<string> words = {"SMILE", "LIMES", "MILES", "MILE", "MIES", "LIME", "LIES", "ELMS", "SEMI"};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()),  2 + 2 + 2 + 1 + 1 + 1 + 1 + 1 + 1);
}

PROVIDED_TEST("Test scoreBoard, full board, small number of words") {
    Grid<char> board = {{'E','Z','R','R'},
                        {'O','H','I','O'},
                        {'N','J','I','H'},
                        {'Y','A','H','O'}};
    Set<string> words = { "HORIZON", "OHIA", "ORZO", "JOHN", "HAJI"};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 4 + 1 + 1 + 1 + 1);
}

PROVIDED_TEST("Test scoreBoard, full board, medium number of words") {
    Grid<char> board = {{'O','T','H','X'},
                        {'T','H','T','P'},
                        {'S','S','F','E'},
                        {'N','A','L','T'}};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 76);
}

PROVIDED_TEST("Test scoreBoard, full board, large number of words") {
    Grid<char> board = {{'E','A','A','R'},
                        {'L','V','T','S'},
                        {'R','A','A','N'},
                        {'O','I','S','E'}};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 234);
}