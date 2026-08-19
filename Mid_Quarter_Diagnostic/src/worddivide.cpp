#include "cs106lib.h"
void STUDENT_TEST_Help();

Vector<string> divideHelp(int depth, Lexicon& dict, string& s1, string& s2, int index) {
    // cout << string(depth * 4, ' ') << depth << " -- " << s1 << " , " << s2 << " --" << endl;
    // cout << " -- " << s1 << " , " << s2 << " --" << endl;
    // cerr << string(depth * 4, ' ') << depth << " call divideHelp( dict , " << s1 << " , " << s2 << " , " << index << " )" << endl;

    Vector<string> result;
    int s2Length = s2.length();
    if (dict.contains(s1) && dict.contains(s2)) {
        cerr << string(20, '=') << " find s1, s2 " << string(20, '=') << endl;
        return Vector { s1, s2 };
    } else if (index == s2Length) {
        return { };
    }

    else {
        for (int i = index; i < s2Length; i++) {
            s1 += s2[i];
            s2.erase(i, 1);
            result = divideHelp(depth + 1, dict, s1, s2, i);
            if (!result.isEmpty()) {
                return result;
            }
            s2.insert(i, 1, s1[s1.length() - 1]);
            s1.erase(s1.length() - 1, 1);
        }
    }
    return result;
}

Vector<string> divide(Lexicon& dict, string word) {
    string s1 = "";
    string s2 = word;
    Vector<string> result = divideHelp(0, dict, s1, s2, 0);
    cerr << "find s1,s2: " << result.toString() << endl;
    return result;
}

void learn_1() {
    Lexicon dict("res/EnglishWords.txt");
    cout << dict.size() << endl;
}
void learn_2() {

    Vector<string> result = { "" };
    if (!result.isEmpty()) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
}
void learn_3() {
    string s1 = "";
    string s2 = "word";
    int s2Length = s2.length();
    for (int i = 0; i < s2Length; i++) {
        string curr1 = s1;
        string curr2 = s2;
        cerr << string(5, '-') << endl;
        curr1 += curr2[i];
        curr2.erase(i, 1);
        Vector<string> result = { curr1, curr2 };
        cout << result.toString() << endl;
        cerr << string(5, '-') << endl;
    }
}
void learn_4() {
    Lexicon dict("res/EnglishWords.txt");
    Vector<string> result;
    result = divide(dict, "12345678");
}

STUDENT_TEST("LEARN: ") {
    cout << endl;
    // cerr << string(20, '-') << endl;
    // learn_1();
    // cerr << string(20, '-') << endl;
    // learn_2();
    // cerr << string(20, '-') << endl;
    // learn_3();
    // cerr << string(20, '-') << endl;
    // learn_4();
    // cerr << string(20, '-') << endl;
}

STUDENT_TEST("divide() test: ") {
    STUDENT_TEST_Help();
}

void STUDENT_TEST_Help() {
    Lexicon dict("res/EnglishWords.txt");
    Vector<string> result;
    cout << endl;

    result = divide(dict, "friendly");
    cerr << result.toString() << endl;

    EXPECT(!result.isEmpty());
    if (!result.isEmpty()) {
        EXPECT(dict.contains(result.get(0)) && dict.contains(result.get(1)));
    }

    result = divide(dict, "standing");
    EXPECT(!result.isEmpty());
    if (!result.isEmpty()) {
        EXPECT(dict.contains(result.get(0)) && dict.contains(result.get(1)));
    }

    result = divide(dict, "midterm");
    EXPECT(!result.isEmpty());
    if (!result.isEmpty()) {
        EXPECT(dict.contains(result.get(0)) && dict.contains(result.get(1)));
    }

    result = divide(dict, "recuperate");
    EXPECT(!result.isEmpty());
    if (!result.isEmpty()) {
        EXPECT(dict.contains(result.get(0)) && dict.contains(result.get(1)));
    }

    result = divide(dict, "stream");
    EXPECT(result.isEmpty());
    result = divide(dict, "atomic");
    EXPECT(result.isEmpty());
    result = divide(dict, "czar");
    EXPECT(result.isEmpty());
    result = divide(dict, "xyz");
    EXPECT(result.isEmpty());
}