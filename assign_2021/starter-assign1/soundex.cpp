// 本文件主要功能: 根据输入姓氏,匹配数据库中的相同姓氏
// 核心函数 1: soundex() → 接受字符串姓氏输入,返回soundex编码
// 核心函数 2: soundexSearch() → 调用 soundex(), 同时查询 /res/surnames.txt 数据库, 匹配相同编码的姓氏
#include "filelib.h"
#include "map.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "testing/SimpleTest.h"
#include "vector.h"
#include <cctype>
#include <fstream>
#include <string>
using namespace std;

/* This function is intended to return a string which
 * contains only the letter characters from the original
 * (all non-letter characters are removed)
 *
 * Use unit tests to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */
string removeNonLetters(string s) {
    string result;
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

// 功能: 接受 全英文字符串 转换为soundex数字编码
// 示例输入: Curie
// 示例输出: C600
string encode(string& s) {
    // cout << endl;
    // cout << "encode() calls with:   " << s << endl;
    s = toUpperCase(s);
    // cout << "toUpperCase: " << s << endl;

    Set<char> Set0 = { 'A', 'E', 'I', 'O', 'U', 'H', 'W', 'Y' };
    Set<char> Set1 = { 'B', 'F', 'P', 'V' };
    Set<char> Set2 = { 'C', 'G', 'J', 'K', 'Q', 'S', 'X', 'Z' };
    Set<char> Set3 = { 'D', 'T' };
    Set<char> Set4 = { 'L' };
    Set<char> Set5 = { 'M', 'N' };
    Set<char> Set6 = { 'R' };
    Map<int, Set<char>> soundexTable { { 0, Set0 }, { 1, Set1 }, { 2, Set2 }, { 3, Set3 }, { 4, Set4 }, { 5, Set5 }, { 6, Set6 } };

    string result;
    // result += s[0];
    // cout << "result:    " << s << endl;
    for (int i = 0; i < s.length(); i++) {
        // s[i] 弹出一个字母
        for (int k = 0; k < soundexTable.size(); k++) {
            if (soundexTable.get(k).contains(s[i])) {
                result += integerToString(k);
                // cout << "char:    " << s[i] << "      soundex:    " << k << endl;
                // cout << "result:    " << result << endl;
                break;
            }
        }
    }
    return result;
}

// 功能: 移除相邻且重复的字符
// 输入: 222025
// 输出: 2025
string coalesce(string& s) {
    string result;
    for (char i : s) {
        if (result == "" || result[result.length() - 1] != i) {
            result += i;
        }
    }

    return result;
}

// removeZero( 输入字符串 , 关键字)
// 功能: 移除输入字符串中的所有关键字
// 输入: ( 2025 , 0 )
// 输出: 225
string removeKeyChar(string& s, char k) {
    string result;
    for (char ch : s) {
        if (ch != k) {
            result += ch;
        }
    }

    return result;
}

// 功能: 将字符串转换为 soundex 形式
// 输入: 任意字符串
// 输出: soundex 编码形式
string soundex(string s) {

    char firstLetter = s[0];
    string result;

    result = removeNonLetters(s);
    // cout << "removeNonLetters result: " << result << endl;

    result = encode(result);
    // cout << "encode result: " << result << endl;

    result = coalesce(result);
    // cout << "coalesce result: " << result << endl;

    result[0] = toUpperCase(firstLetter);
    // cout << "first letter to upper case result: " << result << endl;

    result = removeKeyChar(result, '0');
    // cout << "removeKeyChat result: " << result << endl;

    // cout << "before make to 3 result: " << result << endl;
    while (result.length() < 4) {
        result += '0';
    }
    if (result.length() > 4) {
        result = result.substr(0, 4);
    }

    return result;
}

// 核心函数 2: soundexSearch() → 调用 soundex(), 同时查询 /res/surnames.txt 数据库, 匹配相同编码的姓氏
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    // The names in the database are now stored in the provided
    // vector named databaseNames
    Vector<string> databaseSoundex;
    cout << "build empty databaseSoundex, size: " << databaseSoundex.size() << endl;
    for (int i = 0; i < databaseNames.size(); i++) {
        databaseSoundex.add(soundex(databaseNames.get(i)));
    }
    cout << "databaseSoundex after soundex(), size: " << databaseSoundex.size() << endl;

    while (true) {
        string line = getLine("Enter a surname (RETURN to quit): ");
        string lineSoundex = soundex(line);
        cout << "Soundex code is " << lineSoundex << endl;
        Vector<string> matchString;
        for (int i = 0; i < databaseSoundex.size(); i++) {
            if (databaseSoundex.get(i) == lineSoundex) {
                matchString.add(databaseNames.get(i));
            }
        }

        cout << "Matches from database: " << matchString << endl
             << endl;
    }
}

/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}

STUDENT_TEST("Test removing puntuation, digits, and spaces") {
    string s, result;
    s = "yue";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "yue");
    s = "Yue";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Yue");
    s = "--yue";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "yue");
    s = " yue";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "yue");
    s = "   yue";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "yue");
}

STUDENT_TEST("encode() Test") {
    // EXPECT_EQUAL(encode("Curie"), "C600");
    string s;
    s = "bowman";
    EXPECT_EQUAL(encode(s), "100505");
    s = "BOWMAN";
    EXPECT_EQUAL(encode(s), "100505");
    s = "curie";
    EXPECT_EQUAL(encode(s), "20600");
    s = "CURIE";
    EXPECT_EQUAL(encode(s), "20600");
    s = "master";
    EXPECT_EQUAL(encode(s), "502306");
    s = "MASTER";
    EXPECT_EQUAL(encode(s), "502306");
    s = "oconner";
    EXPECT_EQUAL(encode(s), "0205506");
    s = "Oconner";
    EXPECT_EQUAL(encode(s), "0205506");
}

STUDENT_TEST("coalesce() Test") {
    string s;
    s = "222025";
    EXPECT_EQUAL(coalesce(s), "2025");
    s = "22202555";
    EXPECT_EQUAL(coalesce(s), "2025");
    s = "2222";
    EXPECT_EQUAL(coalesce(s), "2");
    s = "1";
    EXPECT_EQUAL(coalesce(s), "1");
    s = "222025";
    EXPECT_EQUAL(coalesce(s), "2025");
    s = "123456";
    EXPECT_EQUAL(coalesce(s), "123456");
    s = "5";
    EXPECT_EQUAL(coalesce(s), "5");
}

STUDENT_TEST("removeKeyChar() Test") {
    string s;
    s = "2000";
    EXPECT_EQUAL(removeKeyChar(s, '0'), "2");
    s = "1230400056";
    EXPECT_EQUAL(removeKeyChar(s, '0'), "123456");
    s = "12345";
    EXPECT_EQUAL(removeKeyChar(s, '0'), "12345");
    s = "00000000";
    EXPECT_EQUAL(removeKeyChar(s, '0'), "");
}

PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

STUDENT_TEST("soundex() Test") {
    EXPECT_EQUAL(soundex("Jue"), "J000");
    EXPECT_EQUAL(soundex("Master"), "M236");
}