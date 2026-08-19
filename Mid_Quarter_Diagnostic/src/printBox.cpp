#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
#include "console.h"
#include "error.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include <cctype>

using namespace std;

// 测试函数
void tryLearn_1() {
    cerr << "---------" << endl;
    string k = "#";
    cout << k << endl;
    k += "good";
    cout << k << endl;
    int kLength = k.length();
    k[kLength - 1] = '!';
    cout << k << endl;
    cerr << "---------" << endl;
}

// 辅助函数:返回指定数量的重复字符组成的字符串
string multiCharacter(string input, int times) {
    string result;
    for (int i = 0; i < times; i++) {
        result += input;
    }
    return result;
}

// 辅助函数:将字符串转换为首字母大写
void caseChange(string& input) {
    // 先将字母全部转换为小写
    input = toLowerCase(input);
    // 字符串首字符大写(如果是字母的话,不是字母不处理)
    if (isalpha(input[0])) {
        input[0] = toupper(input[0]);
    }
}

void printBox(Vector<string> lines, int width) {
    cout << multiCharacter("#", width) << endl;

    for (string line : lines) {
        // 移除前后空白
        line = trim(line);
        // 字母大小写变换
        caseChange(line);

        // 添加 '#' 相关格式
        string currLine = "#";
        currLine += line;
        int diff = width - currLine.length();
        currLine += multiCharacter(" ", diff);
        currLine[currLine.length() - 1] = '#';

        // print
        cout << currLine << endl;
    }

    cout << multiCharacter("#", width) << endl;
}

STUDENT_TEST("test multiCharacter: ") {
    EXPECT_EQUAL(multiCharacter("aa", 1), "aa");
    EXPECT_EQUAL(multiCharacter("ab", 3), "ababab");
    EXPECT_EQUAL(multiCharacter("aa", 0), "");
    EXPECT_EQUAL(multiCharacter("*", 3), "***");
}

STUDENT_TEST("test caseChange: ") {
    string a = "aaa";
    caseChange(a);
    EXPECT_EQUAL(a, "Aaa");
    string b = "Baa";
    caseChange(b);
    EXPECT_EQUAL(b, "Baa");
    string c = "aaA";
    caseChange(c);
    EXPECT_EQUAL(c, "Aaa");
}

STUDENT_TEST("test printBox: ") {
    Vector<string> lines = { "Your skin like dawn", "Mine like musk", "", "One paints the beginning", "of a certain end", "", "The other, the end of a", "sure beginning.", "", "-Maya Angelou" };

    cerr << endl;
    cerr << lines.toString() << endl;

    cerr << endl;
    printBox(lines, 26);

    cerr << endl;
    printBox(lines, 35);
}
