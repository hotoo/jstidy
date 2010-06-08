/**
 * @see http://www.cplusplus.com/reference/stl/list/insert/
 *
 */
#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

class LexicalAnalyzer {
    list<BaseToken> tokens;
    list<BaseToken>::iterator itt;
    list<char> chs;
    list<char>::iterator itc;
    string prev, curr;

    list<BaseToken> parse(string src){
        BaseToken currToken;
        for(i=0; i<5; i++){
            currToken.append(i);
        }
    }
};
