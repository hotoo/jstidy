// TODO: numeral.
// @see F:\yangku\StronwebWare\StronwebTools\Stronweb.Script.JsCompile
// @see http://www.mozilla.org/js/language/js20-1999-02-18/tokens.html

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <string>

using namespace std;

// TODO:
enum STATUS {WHITE_SPACE, MULTILINE_COMMENT, SIGNLINE_COMMENT, WORD_TOKEN, OPERATOR, PUNCTUATION, LINETERMINATOR,
    STRING, REGEXP}

class BaseToken{
    public:
        string value;
};
class BreakToken : BaseToken{};
class CaseToken : BaseToken{};
class CatchToken : BaseToken{};
class ClassToken : BaseToken{};
class ConstToken : BaseToken{};
class ContinueToken : BaseToken{};
class DefaultToken : BaseToken{};
class DeleteToken : BaseToken{};
class DoToken : BaseToken{};
class ElseToken : BaseToken{};
class EvalToken : BaseToken{};
class ExtendsToken : BaseToken{};
class FalseToken : BaseToken{};
class FieldToken : BaseToken{};
class FinallyToken : BaseToken{};
class ForToken : BaseToken{};
class FunctionToken : BaseToken{};
class IfToken : BaseToken{};
class ImportToken : BaseToken{};
class InToken : BaseToken{};
class InstanceOfToken : BaseToken{};
class NewToken : BaseToken{};
class NullToken : BaseToken{};
class PackageToken : BaseToken{};
class PrivateToken : BaseToken{};
class ProtectedToken : BaseToken{};
class PublicToken : BaseToken{};
class ReturnToken : BaseToken{};
class SuperToken : BaseToken{};
class SwitchToken : BaseToken{};
class ThisToken : BaseToken{};
class ThrowToken : BaseToken{};
class TrueToken : BaseToken{};
class TryToken : BaseToken{};
class TypeofToken : BaseToken{};
class VarToken : BaseToken{};
class WhileToken : BaseToken{};
class WithToken : BaseToken{};

class WhiteSpaceToken : BaseToken{};
class LineTerminatorToken : BaseToken{};
class CommentToken : BaseToken{};

class OperatorToken : BaseToken{};
class LeftBraceToken : OperatorToken{};
class RightBraceToken : OperatorToken{};

// blocks.
class BaseBlock{};
class CaseBlock : BaseBlock{};
class CatchBlock : BaseBlock{};
class DefaultBlock : BaseBlock{};
class DoBlock : BaseBlock{};
class ElseBlock : BaseBlock{};
class FinallyBlock : BaseBlock{};
class ForBlock : BaseBlock{};
class IfBlock : BaseBlock{};
class ObjectBlock : BaseBlock{};
class SwitchBlock : BaseBlock{};
class TryBlock : BaseBlock{};
class WhileBlock : BaseBlock{};
class WithBlock : BaseBlock{};

class BaseScope : BaseBlock{};
class GlobalScope : BaseScope{};
class FunctionScope : BaseScope{};

list<BaseToken> parseTokens(string src);

/* isAlphanum -- return true if the character is a letter, digit, underscore,
        dollar sign, or non-ASCII character.
*/
/*static int isAlphanum(int c){
    return ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') ||
        (c >= 'A' && c <= 'Z') || c == '_' || c == '$' || c == '\\' ||
        c > 126);
}*/
static bool isWhiteSpace(string s){
    string::iterator it;
    for(it=s.begin(); it<s.end(); it++){
        if(' '!=*it && '\t'!=*it){
            return false;
        }
    }
    return true;
}
static bool isWhiteSpace(char c){
    return ' '==c || '\t'==c;
}
static bool isAssign(string s){
    return "="==s || "+="==s || "-="==s || "*="==s || "/="==s;
}
/*static bool isOperator(string s){
    return "+"==s || "-"==s || "*"==s || "/"==s || "%"==s || "++"==s || "--"==s;
}*/
static bool isOperator(char c){
    return '~'==c || '!'==c || '%'==c || '^'==c || '&'==c || '*'==c ||
        '+'==c || '|'==c || '/'==c;
}

list<string> parseWord(string src){
    list<string> tokens;
    string::iterator it;
    string curr;
    char lastChar, stringQuote;
    int escapeLen=0;
    bool inMultiComment=false,
        inLineComment=false,
        inString=false,
        inWhiteSpace=false,
        inOperator=false,
        inNumeral=false,
        inRegExp=false, inRegExpFlag=false;

    for(it=src.begin(); it<src.end(); it++){
        if(inWhiteSpace && !isWhiteSpace(*it)){
            tokens.push_back(curr);
            curr.clear();
            inWhiteSpace = false;
        }
        switch(*it){
        case '\n':
        case '\r':
            if(inLineComment){
                curr.push_back(*it);
                tokens.push_back(curr);
                curr.clear();
            }else if(inMultiComment){
                curr.push_back(*it);
            }else if(inString){
                // support multiline string by '\'
                // TODO: replace last whitespaces after '\'
            }else{
                //! 2. throw new Error();
            }
            break;
        case '=':
            if(inLineComment || inMultiComment || inString || inRegExp){
                curr.push_back(*it);
            }else if("+"==curr || "-"==curr || "*"==curr || "/"==curr || "%"==curr ||
                    "^"==curr || "&"==curr || "|"==curr || "<"==curr || ">"==curr){
                curr.push_back(*it);
                tokens.push_back(curr);
                curr.clear();
                inOperator = false;
            }else if("=="==curr || "!="==curr){ // "===","!=="
                curr.push_back(*it);
                tokens.push_back(curr);
                curr.clear();
                inOperator = false;
            }else if("="==curr || "!"==curr){ // "==","!="
                curr.push_back(*it);
                inOperator = true;
            }else{
                curr.push_back(*it);
                inOperator = true;
            }
            break;
        case '+':
            if(inLineComment || inMultiComment || inRegExp || inString){
                curr.push_back(*it);
            }else if("+"==curr){
                curr.push_back(*it);
                tokens.push_back(curr);
                curr.clear();
                inOperator = false;
            }else{
                // End the before token.
                tokens.push_back(curr);
                curr.clear();

                curr.push_back(*it);
                inOperator = true;
            }
            break;
        case '-':
            if(inLineComment || inMultiComment || inString || inRegExp){
                curr.push_back(*it);
            }else if("-"==curr){
                curr.push_back(*it);
                tokens.push_back(curr);
                curr.clear();
                inOperator = false;
            }else{
                // End the before token.
                tokens.push_back(curr);
                curr.clear();

                curr.push_back(*it);
                inOperator = true;
            }
            break;
        case '*':
            if(inLineComment || inMultiComment || inString || inRegExp){
                curr.push_back(*it);
            }else if("/"==curr){
                inMultiComment = true;
                curr.push_back(*it);
            }else{
                // End the before token.
                tokens.push_back(curr);
                curr.clear();

                curr.push_back(*it);
                inOperator = true;
            }
            break;
        case '/': // TODO: for divs, regexp.
            //if(inMultiComment && '*'==*(curr.end())){
            if(inMultiComment && '*'==lastChar){
                // End of multiline comment.
                curr.push_back(*it);
                tokens.push_back(curr);
                curr.clear();
                inMultiComment = false;
            }else if('/'==lastChar){
                curr.push_back(*it);
                inLineComment = true;
                inOperator = false;
            }else{
                if(inRegExp){
                    if('\\'==lastChar){
                        curr.push_back(*it);
                    }else{
                        curr.push_back(*it);
                        tokens.push_back(curr);
                        curr.clear();
                        inRegExpFlag = false;
                    }
                }else if(isWhiteSpace(curr)){
                    string str=*(tokens.end());
                    if(isAssign(str)){
                        inRegExp = true;
                    }else if("\n"==str || "\r"==str){
                        //! TODO: with new line, maybe divs,or regexp.
                    }else{
                        // divs.
                        curr.push_back(*it);
                        inOperator = true;
                    }
                }else{
                    curr.push_back(*it);
                    inOperator = true;
                }
            }
            break;
        case '%':
        case '^':
            if(inLineComment || inMultiComment || inString || inRegExp){
                curr.push_back(*it);
            }else{
                // End of prev token.
                tokens.push_back(curr);
                curr.clear();

                // waiting for "%=","^="
                curr.push_back(*it);
                inOperator = true;
            }
            break;
        case '!':
            if(inLineComment || inMultiComment || inString || inRegExp){
                curr.push_back(*it);
            }else if(inOperator){
                tokens.push_back(curr);
                curr.clear();

                // waiting for "!=","!!..."
                curr.push_back(*it);
                inOperator = true;
            }else{
                // End of prev token.
                tokens.push_back(curr);
                curr.clear();

                // waiting for "%=","^=","!="
                curr.push_back(*it);
                inOperator = true;
            }
            break;
        case '&':
            if(inLineComment || inMultiComment || inString || inRegExp){
                curr.push_back(*it);
            }else if('&'==lastChar){
                curr.push_back(*it);
                tokens.push_back(curr);
                curr.clear();
                inOperator = false;
            }else{
                // End of prev token.
                tokens.push_back(curr);
                curr.clear();

                // waiting for "&=","&&"
                curr.push_back(*it);
                inOperator = true;
            }
            break;
        case '|':
            if(inLineComment || inMultiComment || inString || inRegExp){
                curr.push_back(*it);
            }else if('|'==*it){
                curr.push_back(*it);
                tokens.push_back(curr);
                curr.clear();
            }else{
                tokens.push_back(curr);
                curr.clear();

                // waiting for "|="
                curr.push_back(*it);
                inOperator = true;
            }
            break;
        case '~':
            if(inLineComment || inMultiComment || inString || inRegExp){
                curr.push_back(*it);
            }else{
                // End of prev token.
                tokens.push_back(curr);
                curr.clear();

                // Bitwise NOT.
                curr.push_back(*it);
                tokens.push_back(curr);
                curr.clear();
            }
            break;
        case '{':
        case '}':
        case '[':
        case ']':
        case '(':
        case ')':
            if(inLineComment || inMultiComment || inString || inRegExp){
                curr.push_back(*it);
            }else{
                tokens.push_back(curr);
                curr.clear();

                curr.push_back(*it);
                tokens.push_back(curr);
                curr.clear();
            }
            break;
        case '<':
            if(inLineComment || inMultiComment || inString || inRegExp){
                curr.push_back(*it);
            }else if("<<"==curr){
                curr.push_back(*it);
                tokens.push_back(curr);
                curr.clear();
                inOperator = false;
            }else if("<"==curr){
                curr.push_back(*it);
            }else{
                curr.push_back(*it);
                inOperator = true;
            }
            break;
        case '>':
            if(inLineComment || inMultiComment || inString || inRegExp){
                curr.push_back(*it);
            }else if(">"==curr){
                curr.push_back(*it);
                tokens.push_back(curr);
                curr.clear();
                inOperator = false;
            }else{
                // End of prev token.
                tokens.push_back(curr);
                curr.clear();

                curr.push_back(*it);
                inOperator = true;
            }
            break;
        case ',':
        case ';':
        case '.':
        case '?':
        case ':':
            if(inLineComment || inMultiComment || inString){
                curr.push_back(*it);
            }else{
                if(inRegExp && inRegExpFlag){inRegExp=false; inRegExpFlag=false;}
                else if(inNumeral){inNumeral = false;}
                else if(inWhiteSpace){inWhiteSpace = false;}
                else if(inRegExp && inRegExpFlag){inRegExp=false; inRegExpFlag=false;}
                // End of prev token.
                tokens.push_back(curr);
                curr.clear();

                curr.push_back(*it);
                tokens.push_back(curr);
                curr.clear();
            }
            break;
        case '"':
        case '\'':
            if(inLineComment || inMultiComment || inRegExp){
                curr.push_back(*it);
            }else if(inString){
                if(*it==stringQuote){
                    if('\\'==lastChar && 1==(escapeLen%2)){
                        curr.push_back(*it);
                    }else{
                        curr.push_back(*it);
                        tokens.push_back(curr);
                        curr.clear();
                        inString = false;
                        stringQuote = '0';
                    }
                }else{
                    curr.push_back(*it);
                }
            }else{
                tokens.push_back(curr);
                curr.clear();

                curr.push_back(*it);
                inString = true;
                stringQuote = *it;
            }
            break;
        case '\\':
            if(inLineComment || inMultiComment){
                curr.push_back(*it);
            }else{
                if('\\'==lastChar){escapeLen++;}
                else{escapeLen = 0;}
                curr.push_back(*it);
            }
            break;
        case 'i':
        case 'g':
        case 'm':
            if(inLineComment || inMultiComment){
                curr.push_back(*it);
            }else if(inWhiteSpace){
                tokens.push_back(curr);
                curr.clear();
                inWhiteSpace = false;

                curr.push_back(*it);
            }else if(inOperator){
                tokens.push_back(curr);
                curr.clear();
                inOperator = false;

                curr.push_back(*it);
            }else if(inRegExp){
                // regexp continue.
                if(inRegExpFlag){
                    curr.push_back(*it);
                    //!inRegExpFlag = true;
                }else{
                    curr.push_back(*it);
                }
            }else if(inNumeral){
                //! Error.
            }else{
                curr.push_back(*it);
            }
            break;
        case ' ':
        case '\t':
            if(inLineComment || inMultiComment || inString){
                curr.push_back(*it);
            }else if(inRegExp && inRegExpFlag){
                tokens.push_back(curr);
                curr.clear();
                inRegExp = false;
                inRegExpFlag = false;
            }else if(inNumeral){
                tokens.push_back(curr);
                curr.clear();
                inNumeral = false;

                curr.push_back(*it);
                inWhiteSpace = true;
            }else if(inOperator){
                tokens.push_back(curr);
                curr.clear();
                inOperator = false;

                curr.push_back(*it);
                inWhiteSpace = true;
            }else if(inWhiteSpace){
                // whitespace continue.
                // end whitespace when next non-whitespace.
                curr.push_back(*it);
            }else{
                tokens.push_back(curr);
                curr.clear();

                curr.push_back(*it);
                inWhiteSpace = true;
            }
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if(inLineComment || inMultiComment || inString || inRegExpFlag){
                curr.push_back(*it);
            }else if(inOperator){
                tokens.push_back(curr);
                curr.clear();
                inOperator = false;

                curr.push_back(*it);
                inNumeral = true;
            }else if(inWhiteSpace){
                tokens.push_back(curr);
                curr.clear();
                inWhiteSpace = false;

                curr.push_back(*it);
                inNumeral = true;
            }else{
                curr.push_back(*it);
            }
            break;
        default:
            if(inLineComment || inMultiComment || inString || inRegExp){
                curr.push_back(*it);
            }else{
                curr.push_back(*it);
            }
            break;
        }
        if(inOperator && !isOperator(*it)){
            inOperator = false;
        }
        lastChar = *it;
    }
    return tokens;
}
list<BaseToken> parseTokens(list<string> strs){
    list<BaseToken> tokens;

    return tokens;
}
void outputTokens(list<BaseToken> tokens){
    list<BaseToken>::iterator it;
    for(it=tokens.begin(); it!=tokens.end(); it++){
        //cout << "[" << *it.value << "]";
    }
}
void outputWord(list<string> tokens){
    list<string>::iterator it;
    for(it=tokens.begin(); it!=tokens.end(); it++){
        cout << "[" << *it << "]";
    }
}
/*
string getSource4File(string fileName){
    FILE *fp;
    if((fp=fopen(name, "r"))==NULL){
        printf("Cannot open source file.");
        exit(1);
    }
    fclose(fp);
}


protected static readonly string UP = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
protected static readonly string LOW = "abcdefghijklmnopqrstuvwxyz";
public static readonly int IN = 271, IF = 264, DO = 144; //调整大小写字母排序时，此处需要同步修正。
//	FOR: Letter Frequency
//	protected static readonly string UP = "ETAOINRSHDCLMPUFGWYBVKXJQZ";//"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//	protected static readonly string LOW = "etaoinrshdclmpufgwybvkxjqz";//"abcdefghijklmnopqrstuvwxyz"
protected static readonly string NUM = "0123456789";
//	public static readonly int IN = 161, IF = 171, DO = 289; //调整大小写字母排序时，此处需要同步修正。
char varName(int i){

}
*/

int main(int argc, const char *argv[]){
    //if(argc<1){printf("you forget javascript source."); exit(1);}
    string src("function test(arg1,arg2){\n    window.alert('0');\n}");
    int i;
    for (i = 1; i < argc; i += 1) {
        fprintf(stdout, "// %s\n", argv[i]);
    }
    list<BaseToken> tokens;
    list<string> ls;
    ls = parseWord(src);
    outputWord(ls);
    //tokens = parseTokens(ls);
    return 0;
}
