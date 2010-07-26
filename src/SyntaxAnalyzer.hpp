#include <iostream>
#include <list>
#include <string>
#include "tokens.hpp"
#include "blocks.hpp"

using namespace std;

class SyntaxAnalyzer{
public:
    SyntaxAnalyzer(){}
    ~SyntaxAnalyzer(){}

    string minify(list<BaseToken *> tokens);
    GlobalScope parse(list<BaseToken *> tokens);

private:
    list<BaseToken *> minifyToken(list<BaseToken *> tokens);
};
