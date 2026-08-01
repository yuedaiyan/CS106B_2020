#include <string>
#include "lexicon.h"
#include "testing/SimpleTest.h"

using namespace std;

bool isShrinkable(Lexicon& lex, string word) {
    if (word.length() == 1 && lex.contains(word)) {
        // basic case
        return true;
    } else {
        // recursive case
        for (int i = 0; i < word.length(); i++) {
            string subWord = word.substr(0, i) + word.substr(i + 1);
            if (lex.contains(subWord)) {
                if (isShrinkable(lex, subWord)) {
                    return true;
                }
            }
        }
    }
    return false;
}

PROVIDED_TEST("Example cases of isShrinkable function from slides"){
    Lexicon lex("res/EnglishWords.txt");
    EXPECT(isShrinkable(lex, "startling"));
    EXPECT(isShrinkable(lex, "cart"));
    EXPECT(!isShrinkable(lex, "cusp"));
}
