#include "SyntaxAnalyzer.hpp"

list<BaseToken *> SyntaxAnalyzer::minifyToken(list<BaseToken *> tokens){
    list<BaseToken *> mins;
    list<BaseToken *>::iterator it;
    list<BaseToken *>::iterator last=NULL;
    string text = "";
    for(it=tokens.begin(); it!=tokens.end(); it++){
        if(dynamic_cast<CommentToken *>(*it)){
            if(mins.size()>0 && dynamic_cast<WhiteSpaceToken *>(*last)){
                mins.pop_back();
                last = mins.end();
            }
            ;
        }else if(dynamic_cast<WhiteSpaceToken *>(*it)){
            if(dynamic_cast<OperatorToken *>(*last) ||
                    dynamic_cast<PunctuationToken *>(*last) ||
                    dynamic_cast<LineTerminatorToken *>(*last)){
                ;
            }else{
                mins.push_back(*it);
                last = it;
            }
        }else if(dynamic_cast<LineTerminatorToken *>(*it)){
            if(mins.size()>0 && dynamic_cast<WhiteSpaceToken *>(*last)){
                mins.pop_back();
                last = mins.end();
            }
            mins.push_back(*it);
            last = it;
        }else if(dynamic_cast<OperatorToken *>(*it) ||
                dynamic_cast<PunctuationToken *>(*it)){
            if(mins.size()>0 && dynamic_cast<WhiteSpaceToken *>(*last)){
                mins.pop_back();
                last = mins.end();
            }
            mins.push_back(*it);
            last = it;
        }else{
            mins.push_back(*it);
            last = it;
        }
    }
    return mins;
}
string SyntaxAnalyzer::minify(list<BaseToken *> tokens){
    list<BaseToken *> mins = minifyToken(tokens);
    list<BaseToken *>::iterator it;
    string text="";
    for(it=mins.begin(); it!=mins.end(); it++){
        if(dynamic_cast<CommentToken *>(*it)){
            ;
        }else if(dynamic_cast<WhiteSpaceToken *>(*it)){
            text += " ";
        }else if(dynamic_cast<LineTerminatorToken *>(*it)){
            text += "\n";
        }else if(dynamic_cast<OperatorToken *>(*it) ||
                dynamic_cast<PunctuationToken *>(*it)){
            text += (**it).getText();
        }else{
            text += (**it).getText();
        }
    }
    return text;
}

GlobalScope SyntaxAnalyzer::parse(list<BaseToken *> tokens){
    GlobalScope root;

    return root;
}
