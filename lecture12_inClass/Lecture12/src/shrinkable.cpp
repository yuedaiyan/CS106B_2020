#include <string>
#include "lexicon.h"
#include "testing/SimpleTest.h"

using namespace std;

bool isShrinkable(Lexicon& lex, string word) {
    /* TODO: Fill in isShrinkable function! */
    return false;
}

PROVIDED_TEST("Example cases of isShrinkable function from slides"){
    Lexicon lex("res/EnglishWords.txt");
    EXPECT(isShrinkable(lex, "startling"));
    EXPECT(isShrinkable(lex, "cart"));
    EXPECT(!isShrinkable(lex, "cusp"));
}
