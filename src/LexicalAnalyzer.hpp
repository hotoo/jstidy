#ifndef HEADER_LEXICAL_ANALYZER
#define HEADER_LEXICAL_ANALYZER

using namespace std;

#include <string>
#include <list>
#include "misc.hpp"
#include "file_functions.hpp"
#include "tokens.hpp"
#include "exceptions.hpp"

enum PARSE_STATUS {
    ST_NONE,
    ST_WHITE_SPACE,
    ST_SINGLE_LINE_COMMENT,
    ST_MULTI_LINE_COMMENT,
    ST_LINE_TERMINATOR,
    ST_OPERATOR,
    ST_PUNCTUATION,
    ST_STRING,
    ST_REGEXP,
    ST_REGEXP_BRACKET,
    ST_REGEXP_FLAG,
    ST_NUMERAL,
    ST_IDENTIFIER
};

class LexicalAnalyzer{
public:
    LexicalAnalyzer();
    ~LexicalAnalyzer();

    list<BaseToken *> parse(string src);
    list<BaseToken *> parseFile(string filename);
    list<BaseToken *> getTokens(){return tokens;}
    void clear();

    int getLine(){return line;}
    int getCols(){return cols;}
private:
    string curr;
    // lastToken is the last valid token.
    BaseToken * lastToken;
    char lastChar, stringQuote;
    int escapeLen;
    int line, cols; // current line number.
    // lastStatus is the Last Valid Status.
    PARSE_STATUS status, lastStatus;
    // Last Valid Status List.
    list<PARSE_STATUS> stateList;
    list<BaseToken *> tokens;

    void parseChar(char c);
};

#endif
