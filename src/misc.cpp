#include "misc.hpp"

/* isAlphanum -- return true if the character is a letter, digit, underscore,
        dollar sign, or non-ASCII character.
*/
int isAlphanum(int c){
    return ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') ||
        (c >= 'A' && c <= 'Z') || c == '_' || c == '$' || c == '\\' ||
        c > 126);
}
bool isWhiteSpace(string s){
    string::iterator it;
    for(it=s.begin(); it<s.end(); it++){
        if(' '!=*it && '\t'!=*it){
            return false;
        }
    }
    return true;
}
bool isWhiteSpace(char c){
    return ' '==c || '\t'==c;
}
bool isAssign(string s){
    return "="==s || "+="==s || "-="==s || "*="==s || "/="==s;
}
/*bool isOperator(string s){
    return "+"==s || "-"==s || "*"==s || "/"==s || "%"==s || "++"==s || "--"==s;
}*/
bool isOperator(char c){
    return '~'==c || '!'==c || '%'==c || '^'==c || '&'==c || '*'==c ||
        '+'==c || '|'==c || '/'==c;
}

void outputTokens(list<BaseToken> tokens){
    list<BaseToken>::iterator it;
    for(it=tokens.begin(); it!=tokens.end(); it++){
        cout << "[" << (*it).getText() << "]";
    }
}
void outputWord(list<string> tokens){
    list<string>::iterator it;
    for(it=tokens.begin(); it!=tokens.end(); it++){
        cout << "[" << *it << "]";
    }
}

string convert(int n){
  static string c="";
  if(n<10){
    c=(char)(n%10+'0');
    return c;
  }else{
    c=convert(n/10)+(char)(n%10+'0');
    return c;
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


protected static readonly string UP_CASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
protected static readonly string LOW_CASE = "abcdefghijklmnopqrstuvwxyz";
public static readonly int IN = 271, IF = 264, DO = 144; //调整大小写字母排序时，此处需要同步修正。
//	FOR: Letter Frequency
//	protected static readonly string UP = "ETAOINRSHDCLMPUFGWYBVKXJQZ";//"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//	protected static readonly string LOW = "etaoinrshdclmpufgwybvkxjqz";//"abcdefghijklmnopqrstuvwxyz"
protected static readonly string NUM = "0123456789";
//	public static readonly int IN = 161, IF = 171, DO = 289; //调整大小写字母排序时，此处需要同步修正。
char varName(int i){

}
*/
