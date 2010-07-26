#include "LexicalAnalyzer.hpp"

LexicalAnalyzer::LexicalAnalyzer(){
    escapeLen = 0;
    line = 1;
    cols = 0;
    status = ST_NONE;
    lastStatus = ST_NONE;
    stateList.clear();
}
LexicalAnalyzer::~LexicalAnalyzer(){
    status = ST_NONE;
    lastStatus = ST_NONE;
}
list<BaseToken *> LexicalAnalyzer::parseFile(string filename){
    string src = file_get_contents(filename);
    return parse(src);
}
list<BaseToken *> LexicalAnalyzer::parse(string src){
    string::iterator it;

    for(it=src.begin(); it<=src.end(); it++){
        parseChar(*it);
    }

    return tokens;
}
void LexicalAnalyzer::parseChar(char c){
        switch(c){
        case '\r':
        case '\n':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
                curr.push_back(c);
                tokens.push_back(createToken(curr));
                curr.clear();
                status = ST_NONE;
                break;
            case ST_MULTI_LINE_COMMENT:
                curr.push_back(c);
                break;
            case ST_LINE_TERMINATOR:
                curr.push_back(c);
                break;
            case ST_PUNCTUATION:
            case ST_OPERATOR:
            case ST_NUMERAL:
            case ST_IDENTIFIER:
            case ST_REGEXP_FLAG:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
                //return tokens;
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_LINE_TERMINATOR;
                break;
            case ST_STRING:
                // Support multiline string by the last '\'
                if('\\'==lastChar && 0!=(escapeLen%2)){
                    curr = curr.substr(0, curr.length()-1);
                }else if('\r'==lastChar && '\n'==c){
                    // for window \r\n, continue but do nothing.
                }else{
                    curr.push_back(c);
                    throw JSSyntaxException("Unterminated string constant: "+curr, "error", line, cols);
                }
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_LINE_TERMINATOR;
                break;
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
            default:
                curr.push_back(c);
                throw JSSyntaxException("Line Terminator can not in the regular expression: "+curr,"error", line, cols);
                break;
            }
            if('\n'==c && '\r'!=lastChar){
                // Unix    \n
                line++;
            }else if('\r'==c){
                // Windows \r\n
                // Mac     \r
                line++;
            }
            break;
        case '=':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_OPERATOR:
                if("=="==curr || "!="==curr || // "===","!=="
                        "+"==curr || "-"==curr || "*"==curr || "/"==curr || "%"==curr ||
                        "^"==curr || "&"==curr || "|"==curr || "<<"==curr || ">>>"==curr){
                    curr.push_back(c);
                    lastToken = createToken(curr);
                    tokens.push_back(createToken(curr));
                    curr.clear();
                    status = ST_NONE;
                }else if("="==curr || "!"==curr){ // "==","!="
                    curr.push_back(c);
                    //! parse operator continue.
                }else {
                    lastToken = createToken(curr);
                    tokens.push_back(createToken(curr));
                    curr.clear();

                    curr.push_back(c);
                    //! parse operator continue.
                }
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            case ST_PUNCTUATION:
            case ST_NUMERAL:
            case ST_IDENTIFIER:
            case ST_REGEXP_FLAG:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
            default:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            }
            break;
        case '+':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_OPERATOR:
                if("+"==curr){
                    curr.push_back(c);
                    lastToken = createToken(curr);
                    tokens.push_back(createToken(curr));
                    curr.clear();
                    status = ST_NONE;
                }else{
                    lastToken = createToken(curr);
                    tokens.push_back(createToken(curr));
                    curr.clear();

                    curr.push_back(c);
                    // flag of positive number.
                    status = ST_NUMERAL;
                    lastStatus = ST_NUMERAL;
                    stateList.push_back(ST_NUMERAL);
                }
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            case ST_NUMERAL:
                if('e'==lastChar || 'E'==lastChar){
                    // 1e+3
                    curr.push_back(c);
                    break;
                }
            case ST_PUNCTUATION:
            case ST_IDENTIFIER:
            case ST_REGEXP_FLAG:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            default:
                break;
            }
            break;
        case '-':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            case ST_OPERATOR:
                if("-"==curr){ // '-'==lastChar
                    curr.push_back(c);
                    tokens.push_back(createToken(curr));
                    lastToken = createToken(curr);
                    curr.clear();
                    status = ST_NONE;
                }else{
                    tokens.push_back(createToken(curr));
                    lastToken = createToken(curr);
                    curr.clear();

                    curr.push_back(c);
                    status = ST_NUMERAL;
                    lastStatus = ST_NUMERAL;
                    stateList.push_back(ST_NUMERAL);
                }
                break;
            case ST_NUMERAL:
                if('e'==lastChar || 'E'==lastChar){
                    // 1e-3
                    curr.push_back(c);
                    break;
                }
            case ST_PUNCTUATION:
            case ST_IDENTIFIER:
            case ST_REGEXP_FLAG:
                    lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            default:
                break;
            }
            break;
        case '*':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_REGEXP:
                if("/"==curr){
                    curr.push_back(c);
                    status = ST_MULTI_LINE_COMMENT;
                    if(!stateList.empty()){
                        stateList.pop_back();
                        if(!stateList.empty()){
                            list<PARSE_STATUS>::iterator _lastIt = stateList.end();
                            _lastIt--;
                            lastStatus = *_lastIt;
                        }else{
                            lastStatus = ST_NONE;
                        }
                        //! DEBUG:
                        //cout << "star(*) I: " << convert(lastStatus) << endl;
                    }
                    break;
                }else{
                    curr.push_back(c);
                }
                break;
            case ST_OPERATOR:
                if("/"==curr){
                    curr.push_back(c);
                    status = ST_MULTI_LINE_COMMENT;

                    if(!stateList.empty()){
                        stateList.pop_back();
                        if(!stateList.empty()){
                            list<PARSE_STATUS>::iterator _lastIt = stateList.end();
                            _lastIt--;
                            lastStatus = *_lastIt;
                        }else{
                            lastStatus = ST_NONE;
                        }
                        //! DEBUG:
                        //cout << "star(*) II: " << convert(lastStatus) << endl;
                    }else{
                        lastStatus = ST_NONE;
                    }
                }else{
                    tokens.push_back(createToken(curr));
                    lastToken = createToken(curr);
                    curr.clear();

                    curr.push_back(c);
                    //! parse operator continue.
                }
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            case ST_PUNCTUATION:
            case ST_NUMERAL:
            case ST_IDENTIFIER:
            case ST_REGEXP_FLAG:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            default:
                break;
            }
            break;
        case '/': // TODO: for divs, regexp.
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_MULTI_LINE_COMMENT:
                if('*'==lastChar){
                    curr.push_back(c);
                    tokens.push_back(createToken(curr));
                    curr.clear();
                    status = ST_NONE;
                }else{
                    curr.push_back(c);
                }
                break;
            case ST_OPERATOR:
                //! FIX: thinking in deep.
                if("/"==curr){
                    curr.push_back(c);
                    status = ST_SINGLE_LINE_COMMENT;

                    if(!stateList.empty()){
                        stateList.pop_back();
                        if(!stateList.empty()){
                            list<PARSE_STATUS>::iterator _lastIt = stateList.end();
                            _lastIt--;
                            lastStatus = *_lastIt;
                        }else{
                            lastStatus = ST_NONE;
                        }
                        //! DEBUG:
                        //cout << "slash(/) I:" << convert(lastStatus) << endl;
                    }
                }else{
                    tokens.push_back(createToken(curr));
                    lastToken = createToken(curr);
                    curr.clear();

                    curr.push_back(c);
                    status = ST_REGEXP;
                    lastStatus = ST_REGEXP;
                    stateList.push_back(ST_REGEXP);
                }
                break;
            case ST_REGEXP:
                if("/"==curr){
                    curr.push_back(c);
                    status = ST_SINGLE_LINE_COMMENT;
                    if(!stateList.empty()){
                        stateList.pop_back();
                        if(!stateList.empty()){
                            list<PARSE_STATUS>::iterator _lastIt = stateList.end();
                            _lastIt--;
                            lastStatus = *_lastIt;
                        }else{
                            lastStatus = ST_NONE;
                        }
                        //! DEBUG:
                        //cout << "slash(/) II:" << convert(lastStatus) << endl;
                    }
                }else if('\\'!=lastChar || ('\\'==lastChar && 0==(escapeLen%2))){
                    curr.push_back(c);
                    status = ST_REGEXP_FLAG;
                    lastStatus = ST_REGEXP_FLAG;
                    stateList.push_back(ST_REGEXP_FLAG);
                }else{
                    curr.push_back(c);
                }
                break;
            case ST_REGEXP_FLAG:
                throw JSSyntaxException("Do not expect slash(/) immediately after regular expression.", "error", line, cols);
                break;
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();
                //! continue following...
            case ST_NONE:
                // "/" IS OPERATOR WHEN UNKNOW (NOT REGEXP) STATUS.
                switch(lastStatus){
                case ST_OPERATOR:
                    curr.push_back(c);
                    status = ST_REGEXP;
                    lastStatus = ST_REGEXP;
                    stateList.push_back(ST_REGEXP);
                    break;
                case ST_PUNCTUATION:
                    curr.push_back(c);
                    //if(//dynamic_cast<PunctuationToken *>(&lastToken) &&
                            //("}"==(*lastToken).getText() ||
                            //"]"==(*lastToken).getText() ||
                            //")"==(*lastToken).getText())){
                    if(typeid(*lastToken)==typeid(RightBraceToken) ||
                           typeid(*lastToken)==typeid(RightBracketToken) ||
                           typeid(*lastToken)==typeid(RightParenToken)){
                    //if(dynamic_cast<RightBraceToken *>(lastToken) ||
                      //dynamic_cast<RightBracketToken *>(lastToken) ||
                      //dynamic_cast<RightParenToken *>(lastToken)){
                        status = ST_OPERATOR;
                        lastStatus = ST_OPERATOR;
                        stateList.push_back(ST_OPERATOR);
                    }else{
                        status = ST_REGEXP;
                        lastStatus = ST_REGEXP;
                        stateList.push_back(ST_REGEXP);
                    }
                    break;
                case ST_IDENTIFIER:
                    curr.push_back(c);
                    // FIX: for check KeywordToken.
                    if(dynamic_cast<KeywordToken *>(lastToken)){
                        status = ST_REGEXP;
                        lastStatus = ST_REGEXP;
                        stateList.push_back(ST_REGEXP);
                    }else{
                        status = ST_OPERATOR;
                        lastStatus = ST_OPERATOR;
                        stateList.push_back(ST_OPERATOR);
                    }
                    break;
                case ST_NUMERAL:
                    curr.push_back(c);
                    status = ST_OPERATOR;
                    lastStatus = ST_OPERATOR;
                    stateList.push_back(ST_OPERATOR);
                    break;
                case ST_NONE:
                    // Slash(/) at file start, maybe:
                    //   ST_SINGLE_LINE_COMMENT,
                    //   ST_MULTI_LINE_COMMENT,
                    //   ST_REGEXP (meaningless).
                    curr.push_back(c);
                    status = ST_REGEXP;
                    lastStatus = ST_REGEXP;
                    stateList.push_back(ST_REGEXP);
                    break;
                case ST_STRING:
                case ST_REGEXP_FLAG:
                // impossible lastStatus before ST_NONE.
                case ST_SINGLE_LINE_COMMENT:
                case ST_MULTI_LINE_COMMENT:
                case ST_WHITE_SPACE:
                case ST_LINE_TERMINATOR:
                case ST_REGEXP:
                default:
                    curr.push_back(c);
                    throw JSSyntaxException("syntax error I:"+curr+" "+convert(status)+" "+convert(lastStatus), "error", line, cols);
                    break;
                }
                break;
            case ST_PUNCTUATION:
            //! if("}"==lastToken || "]"==lastToken || ")"==lastToken){
                if("}"==curr || "]"==curr || ")"==curr){
                    // IS DIVISION.
                    tokens.push_back(createToken(curr));
                    lastToken = createToken(curr);
                    curr.clear();

                    curr.push_back(c);
                    status = ST_OPERATOR;
                    lastStatus = ST_OPERATOR;
                    stateList.push_back(ST_OPERATOR);
                }else{
                    tokens.push_back(createToken(curr));
                    lastToken = createToken(curr);
                    curr.clear();

                    curr.push_back(c);
                    status = ST_REGEXP;
                    lastStatus = ST_REGEXP;
                    stateList.push_back(ST_REGEXP);
                }
                break;
            case ST_NUMERAL:
            case ST_IDENTIFIER:
                tokens.push_back(createToken(curr));
                lastToken = createToken(curr);
                curr.clear();

                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            default:
                //! FIX: thinking in deep.
                //if('/'==lastChar){}
                throw JSSyntaxException("Unknow error", "error", line, cols);
                break;
            }
            break;
        case '%':
        case '^':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            case ST_IDENTIFIER:
            case ST_NUMERAL:
            case ST_PUNCTUATION:
            case ST_OPERATOR:
            case ST_REGEXP_FLAG:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            default:
                break;
            }
            break;
        case '!':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            case ST_OPERATOR:
            case ST_IDENTIFIER:
            case ST_NUMERAL:
            case ST_PUNCTUATION:
            case ST_REGEXP_FLAG:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();
                // waiting for "!==","!=","!!..."
                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
            }
            break;
        case '&':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            case ST_OPERATOR:
                if('&'==lastChar){
                    curr.push_back(c);
                    tokens.push_back(createToken(curr));
                    lastToken = createToken(curr);
                    curr.clear();
                    status = ST_NONE;
                    break;
                }
                //! else continue following...
            case ST_IDENTIFIER:
            case ST_NUMERAL:
            case ST_PUNCTUATION:
            case ST_REGEXP_FLAG:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
            }
            break;
        case '|':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            case ST_OPERATOR:
                if('|'==lastChar){
                    curr.push_back(c);
                    tokens.push_back(createToken(curr));
                    lastToken = createToken(curr);
                    curr.clear();
                    status = ST_NONE;
                    break;
                }
                //! else continue following...
            case ST_IDENTIFIER:
            case ST_NUMERAL:
            case ST_PUNCTUATION:
            case ST_REGEXP_FLAG:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();
                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            }
            break;
        case '~':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            case ST_OPERATOR:
            case ST_IDENTIFIER:
            case ST_NUMERAL:
            case ST_PUNCTUATION:
            case ST_REGEXP_FLAG:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();
                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            }
            break;
        case '?':
        case ':':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                tokens.push_back(createToken(curr));
                curr.clear();
                status = ST_NONE;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            case ST_IDENTIFIER:
            case ST_NUMERAL:
            case ST_PUNCTUATION:
            case ST_REGEXP_FLAG:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                tokens.push_back(createToken(curr));
                curr.clear();
                status = ST_NONE;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            case ST_OPERATOR:
                curr.push_back(c);
                throw JSSyntaxException("syntax error II: "+curr, "error", line, cols);
                break;
            }
            break;
        case '[':
            switch(status){
            case ST_MULTI_LINE_COMMENT:
            case ST_SINGLE_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_REGEXP:
                curr.push_back(c);

                if('\\'!=lastChar || ('\\'!=lastChar && 0==(escapeLen%2))){
                    status = ST_REGEXP_BRACKET;
                    // this is addition for regular expression.
                    // need not push to stateList or change last status.
                }
                break;
            case ST_NONE:
                curr.push_back(c);
                tokens.push_back(createToken(curr));
                curr.clear();
                status = ST_NONE; //! NOTE.
                lastStatus = ST_PUNCTUATION;
                stateList.push_back(ST_PUNCTUATION);
                break;
            case ST_IDENTIFIER:
            case ST_OPERATOR:
            case ST_PUNCTUATION:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                tokens.push_back(createToken(curr));
                curr.clear();
                status = ST_NONE; //! NOTE.
                lastStatus = ST_PUNCTUATION;
                stateList.push_back(ST_PUNCTUATION);
                break;
            case ST_REGEXP_FLAG:
            case ST_NUMERAL:
            default:
                curr.push_back(c);
                throw JSSyntaxException("Do not expect left brace: "+curr, "error", line, cols);
            }
            break;
        case ']':
            switch(status){
            case ST_MULTI_LINE_COMMENT:
            case ST_SINGLE_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
                curr.push_back(c);
                break;
            case ST_REGEXP_BRACKET:
                curr.push_back(c);

                if('\\'!=lastChar || ('\\'==lastChar && 0==(escapeLen%2))){
                    status = ST_REGEXP;
                    // this is addition for regular expression.
                    // need not push to stateList or change last status.
                }
                break;
            case ST_NONE:
                curr.push_back(c);
                tokens.push_back(createToken(curr));
                lastToken = createToken(curr);
                curr.clear();
                status = ST_NONE; //! NOTE.
                lastStatus = ST_PUNCTUATION;
                stateList.push_back(ST_PUNCTUATION);
                break;
            case ST_IDENTIFIER:
            case ST_OPERATOR:
            case ST_PUNCTUATION:
            case ST_REGEXP_FLAG:
            case ST_NUMERAL:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                tokens.push_back(createToken(curr));
                lastToken = createToken(curr);
                curr.clear();
                status = ST_NONE;
                lastStatus = ST_PUNCTUATION;
                stateList.push_back(ST_PUNCTUATION);
                break;
            }
            break;
        case '{':
        case '}':
        case '(':
        case ')':
        case '.':
        case ',':
        case ';':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                tokens.push_back(createToken(curr));
                lastToken = createToken(curr);
                curr.clear();
                status = ST_NONE; //! NOTE.
                lastStatus = ST_PUNCTUATION;
                stateList.push_back(ST_PUNCTUATION);
                break;
            case ST_NUMERAL:
                if('.'==c){
                    curr.push_back(c);
                    break;
                }
                //! else continue following...
            case ST_OPERATOR:
            case ST_PUNCTUATION:
            case ST_REGEXP_FLAG:
            case ST_IDENTIFIER:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                tokens.push_back(createToken(curr));
                lastToken = createToken(curr);
                curr.clear();
                status = ST_NONE;
                lastStatus = ST_PUNCTUATION;
                stateList.push_back(ST_PUNCTUATION);
                break;
            default:
                break;
            }
            break;
        case '<':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
            case ST_OPERATOR: // if "<<"==curr, waiting for "<<=".
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            case ST_NUMERAL:
            case ST_REGEXP_FLAG:
            case ST_IDENTIFIER:
            case ST_PUNCTUATION:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            }
            break;
        case '>':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
            case ST_OPERATOR: // if ">>>"==curr, waiting for ">>>="
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            case ST_NUMERAL:
            case ST_REGEXP_FLAG:
            case ST_IDENTIFIER:
            case ST_PUNCTUATION:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_OPERATOR;
                lastStatus = ST_OPERATOR;
                stateList.push_back(ST_OPERATOR);
                break;
            }
            break;
        case '"':
        case '\'':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                stringQuote = c;
                status = ST_STRING;
                lastStatus  = ST_STRING;
                stateList.push_back(ST_STRING);
                break;
            case ST_STRING:
                //TODO: multiline string.
                if(c==stringQuote && ('\\'!=lastChar || ('\\'==lastChar && 0==(escapeLen%2)))){
                    curr.push_back(c);
                    tokens.push_back(createToken(curr));
                    lastToken = createToken(curr);
                    curr.clear();
                    stringQuote = '\0';
                    status = ST_NONE;
                }else{
                    curr.push_back(c);
                }
                break;
            case ST_NUMERAL:
            case ST_REGEXP_FLAG:
            case ST_IDENTIFIER:
            case ST_PUNCTUATION:
            case ST_OPERATOR:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
            default:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                stringQuote = c;
                status = ST_STRING;
                lastStatus = ST_STRING;
                stateList.push_back(ST_STRING);
                break;
            }
            break;
        case '\\':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
                curr.push_back(c);
                break;
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
            case ST_STRING:
                if('\\'==lastChar){escapeLen++;}
                else{escapeLen=1;}
                curr.push_back(c);
                break;
            case ST_NONE:
            case ST_OPERATOR:
            case ST_NUMERAL:
            case ST_PUNCTUATION:
            case ST_LINE_TERMINATOR:
            case ST_IDENTIFIER:
            case ST_REGEXP_FLAG:
            case ST_WHITE_SPACE:
            default:
                curr.push_back(c);
                throw JSSyntaxException("Javascript syntax error by backslash(\\)", "error", line, cols);
            }
            break;
        case 'i':
        case 'g':
        case 'm':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
            case ST_REGEXP_FLAG:
            case ST_STRING:
            case ST_IDENTIFIER:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_IDENTIFIER;
                lastStatus = ST_IDENTIFIER;
                stateList.push_back(ST_IDENTIFIER);
                break;
            case ST_PUNCTUATION:
            case ST_OPERATOR:
            case ST_NUMERAL:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_IDENTIFIER;
                lastStatus = ST_IDENTIFIER;
                stateList.push_back(ST_IDENTIFIER);
                break;
            }
            break;
        case ' ':
        case '\t':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
            case ST_WHITE_SPACE:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_WHITE_SPACE;
                break;
            case ST_REGEXP_FLAG:
            case ST_NUMERAL:
            case ST_OPERATOR:
            case ST_PUNCTUATION:
            case ST_IDENTIFIER:
                lastToken = createToken(curr);
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_WHITE_SPACE;
                break;
            }
            break;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
            case ST_NUMERAL:
            case ST_IDENTIFIER:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_NUMERAL;
                lastStatus = ST_NUMERAL;
                stateList.push_back(ST_NUMERAL);
                break;
            case ST_REGEXP_FLAG:
            case ST_OPERATOR:
            case ST_PUNCTUATION:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_NUMERAL;
                lastStatus  = ST_NUMERAL;
                stateList.push_back(ST_NUMERAL);
                break;
            }
            break;
        case 'x':
        case 'X':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
            case ST_IDENTIFIER:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_IDENTIFIER;
                lastStatus = ST_IDENTIFIER;
                stateList.push_back(ST_IDENTIFIER);
                break;
            case ST_NUMERAL:
                if("0"==curr){ // hex number.
                    curr.push_back(c);
                }else{
                    curr.push_back(c);
                    throw JSSyntaxException("Illegal numeral token: "+curr, "error", line, cols);
                }
                break;
            case ST_OPERATOR:
            case ST_PUNCTUATION:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_IDENTIFIER;
                lastStatus = ST_IDENTIFIER;
                stateList.push_back(ST_IDENTIFIER);
                break;
            case ST_REGEXP_FLAG:
                curr.push_back(c);
                throw JSSyntaxException("Illegal regular expression: "+curr, "error", line, cols);
                break;
            }
            break;
        case 'e': case 'E':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
            case ST_IDENTIFIER:
            case ST_NUMERAL: // 1E3 1E+3 1E-3
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_IDENTIFIER;
                lastStatus = ST_IDENTIFIER;
                stateList.push_back(ST_IDENTIFIER);
                break;
            case ST_OPERATOR:
            case ST_PUNCTUATION:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_IDENTIFIER;
                lastStatus = ST_IDENTIFIER;
                stateList.push_back(ST_IDENTIFIER);
                break;
            case ST_REGEXP_FLAG:
                curr.push_back(c);
                throw JSSyntaxException("Illegal regular expression: "+curr, "error", line, cols);
            }
            break;
        case 'a': case 'b': case 'c': case 'd':           case 'f':
        case 'h':           case 'j': case 'k': case 'l':           case 'n':
        case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
        case 'v': case 'w':           case 'y': case 'z': case 'A': case 'B':
        case 'C': case 'D':           case 'F': case 'G': case 'H': case 'I':
        case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P':
        case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W':
                  case 'Y': case 'Z': case '_':  case '$':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
            case ST_IDENTIFIER:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_IDENTIFIER;
                lastStatus = ST_IDENTIFIER;
                stateList.push_back(ST_IDENTIFIER);
                break;
            case ST_NUMERAL:
            case ST_REGEXP_FLAG:
                curr.push_back(c);
                throw JSSyntaxException("Illegal regular expression token: "+curr, "error", line, cols);
                break;
            case ST_OPERATOR:
            case ST_PUNCTUATION:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_IDENTIFIER;
                lastStatus= ST_IDENTIFIER;
                stateList.push_back(ST_IDENTIFIER);
                break;
            }
            break;
        case '@': case '#': case '`':
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
                curr.push_back(c);
                break;
            case ST_NONE:
            case ST_NUMERAL:
            case ST_REGEXP_FLAG:
            case ST_OPERATOR:
            case ST_WHITE_SPACE:
            case ST_PUNCTUATION:
            case ST_LINE_TERMINATOR:
            case ST_IDENTIFIER:
                curr.push_back(c);
                throw JSSyntaxException("Illegal identifier: "+curr, "error", line, cols);
                break;
            }
            break;
        default:
            switch(status){
            case ST_SINGLE_LINE_COMMENT:
            case ST_MULTI_LINE_COMMENT:
            case ST_STRING:
            case ST_REGEXP:
            case ST_REGEXP_BRACKET:
            case ST_IDENTIFIER:
                curr.push_back(c);
                break;
            case ST_NONE:
                curr.push_back(c);
                status = ST_IDENTIFIER;
                lastStatus = ST_IDENTIFIER;
                stateList.push_back(ST_IDENTIFIER);
                break;
            case ST_OPERATOR:
            case ST_PUNCTUATION:
                lastToken = createToken(curr);
            case ST_WHITE_SPACE:
            case ST_LINE_TERMINATOR:
                tokens.push_back(createToken(curr));
                curr.clear();

                curr.push_back(c);
                status = ST_IDENTIFIER;
                lastStatus = ST_IDENTIFIER;
                stateList.push_back(ST_IDENTIFIER);
                break;
            case ST_NUMERAL:
            case ST_REGEXP_FLAG:
                break;
            }
            break;
        }

        if('\\'!=c && '\\'==lastChar){escapeLen=0;}

        if('\r'==c || '\n'==c){cols = 0;}
        else{cols++;}

        lastChar = c;
}
void LexicalAnalyzer::clear(){
    curr.clear();
    lastChar = '\0';
    stringQuote = '\0';
    escapeLen = 0;
    line = 1;
    cols = 0;
    status = ST_NONE;
    lastStatus = ST_NONE;
    tokens.clear();
    stateList.clear();
}
