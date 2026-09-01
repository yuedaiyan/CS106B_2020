#include "cs106lib.h"
using namespace std;

// 字母分发程序：
Vector<string> divide2Help(int index, Lexicon& dict, string& word, string& left, string& right) {
    // cerr << " left : " << left << " right : " << right << endl;
    cerr << "index=" << index
         << " left=" << left
         << " right=" << right
         << " remaining=" << word.substr(index)
         << endl;
    /* 检查案例：
     *      检查当前的 s1 和 s2 是不是包含在字典中，如果不是，直接剪枝
     */
    if (!dict.containsPrefix(left) || !dict.containsPrefix(right)) {
        return { };
    }

    /* 基础情况：
     *      传入单词没有剩余字母，检查终末两个单词是不是包含在字典中
     *      如果是，返回是
     *      如果否，返回否
     */
    if (word.size() == index) {
        if (dict.contains(left) && dict.contains(right)) {
            return { left, right };
        } else {
            return { };
        }
    }

    /* 递归情况：
     *      提取一个字母，分发给第一个字符串
     *      取消分发给第二个字符串
     *      提取一个字符，分发给第二个字符串
     */
    Vector<string> result;
    char c = word[index];

    left += c;
    result = divide2Help(index + 1, dict, word, left, right);
    left.pop_back();
    if (!result.isEmpty()) {
        return result;
    }

    right += c;
    result = divide2Help(index + 1, dict, word, left, right);
    right.pop_back();
    if (!result.isEmpty()) {
        return result;
    }

    return { };
}

Vector<string> divide2(Lexicon& dict, string word) {
    string s1 = "";
    string s2 = "";
    return divide2Help(0, dict, word, s1, s2);
}

STUDENT_TEST("LEARN : ") {
    cout << endl;

    string str = "hello";
    str.pop_back();

    cerr << str << endl;

    EXPECT(true);
}

STUDENT_TEST("divide() test : friendly") {
    Lexicon dict("res/EnglishWords.txt");
    Vector<string> result;

    result = divide2(dict, "friendly");

    EXPECT(!result.isEmpty());

    if (!result.isEmpty()) {
        EXPECT(dict.contains(result.get(0)) && dict.contains(result.get(1)));
    }
}

STUDENT_TEST("divide() test : standing") {
    Lexicon dict("res/EnglishWords.txt");
    Vector<string> result;

    result = divide2(dict, "standing");

    EXPECT(!result.isEmpty());

    if (!result.isEmpty()) {
        EXPECT(dict.contains(result.get(0)) && dict.contains(result.get(1)));
    }
}

STUDENT_TEST("divide() test : midterm") {
    Lexicon dict("res/EnglishWords.txt");
    Vector<string> result;

    result = divide2(dict, "midterm");

    EXPECT(!result.isEmpty());

    if (!result.isEmpty()) {
        EXPECT(dict.contains(result.get(0)) && dict.contains(result.get(1)));
    }
}

STUDENT_TEST("divide() test : recuperate") {
    Lexicon dict("res/EnglishWords.txt");
    Vector<string> result;

    result = divide2(dict, "recuperate");

    EXPECT(!result.isEmpty());

    if (!result.isEmpty()) {
        EXPECT(dict.contains(result.get(0)) && dict.contains(result.get(1)));
    }
}

STUDENT_TEST("divide() empty test") {
    Lexicon dict("res/EnglishWords.txt");
    Vector<string> result;

    result = divide2(dict, "stream");
    EXPECT(result.isEmpty());

    result = divide2(dict, "atomic");
    EXPECT(result.isEmpty());

    result = divide2(dict, "czar");
    EXPECT(result.isEmpty());

    result = divide2(dict, "xyz");
    EXPECT(result.isEmpty());
}