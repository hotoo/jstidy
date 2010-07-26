/**
 * @author 闲耘™ (@hotoo, mail[AT]xianyun.org)
 * @version 2009/12/10
 */

#include "jstidy.hpp"

using namespace std;

int main(int argc, const char *argv[]){
    //if(argc<1){printf("you forget javascript source."); exit(1);}
    string src;
    //string src("function test(arg1,arg2){    window.alert('0\"\\'');\n}\n\nvar num=2/3, reg=/re/img;\n");

if(argc>1){

    settings["remove_last_semicolon"] = 1;
    settings["left-brace-at-newline"] = 0;

    for(int i=1; i<argc; i++){
        //cout << argv[i] << endl;
    }

    LexicalAnalyzer lex;
    SyntaxAnalyzer syn;
    list<BaseToken *> tokens;
    string minifyed = "";

    try{src = file_get_contents(argv[1]);}
    catch(string e){cout << e << endl; exit(0);}
    catch(...){cout << "Cannot get file content.";exit(0);}

    try{
        tokens = lex.parse(src);
        minifyed = syn.minify(tokens);
    }catch(JSSyntaxException ex){
        cout << ex.getFile() << "|" << ex.getLine() << "," <<
            ex.getCols() << "| " << ex.getType() << " " <<
            ex.getMessage() << endl;
    }catch(string ex){
        cout << "|" << lex.getLine() << "," << lex.getCols() << "|" << ex << endl;
    }catch(...){
        cout << "Occer unknow javascript parse exception." << endl;
    }
    list<BaseToken *>::iterator it;
    ofstream out("OUT.js");
    out << minifyed;
    //for(it=tokens.begin(); it!=tokens.end(); it++){
        //out << "[" << (**it).getText() << "]";
    //}
    out.close();

    exit(0);
}

    cout << "Usage:" << endl;
    cout << "jstidy" << endl;
    cout << "  -remove_last_semicolon=true|false" << endl;
    cout << "  -o=outputfile" << endl;
    return 0;
}
