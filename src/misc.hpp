#ifndef HEADER_JS_MISC
#define HEADER_JS_MISC

#include <iostream>
#include <list>
#include <string>
#include "tokens.hpp"

using namespace std;

int isAlphanum(int c);
bool isWhiteSpace(string s);
bool isWhiteSpace(char c);
bool isAssign(string s);
bool isOperator(char c);

void outputTokens(list<BaseToken> tokens);
void outputWord(list<string> tokens);

string convert(int n);

#endif
