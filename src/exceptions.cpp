#include "exceptions.hpp"

using namespace std;

JSSyntaxException::JSSyntaxException(){
    _file = "";
    _message = "";
    _type = "";
    _line = 1;
    _cols = 1;
}
JSSyntaxException::JSSyntaxException(string file, string msg, string type, int line, int cols){
    _file = file;
    _message = msg;
    _type = type;
    _line = line;
    _cols = cols;
}
JSSyntaxException::JSSyntaxException(string msg, string type, int line, int cols){
    _file = "";
    _message = msg;
    _type = type;
    _line = line;
    _cols = cols;
}
JSSyntaxException::~JSSyntaxException(){
}
void JSSyntaxException::setFile(string file){
    _file = file;
}
void JSSyntaxException::setMessage(string msg){
    _message = msg;
}
void JSSyntaxException::setType(string type){
    _type = type;
}
void JSSyntaxException::setLine(int line){
    _line = line;
}
void JSSyntaxException::setCols(int cols){
    _cols = cols;
}
string JSSyntaxException::getFile(){
    return _file;
}
string JSSyntaxException::getMessage(){
    return _message;
}
string JSSyntaxException::getType(){
    return _type;
}
int JSSyntaxException::getLine(){
    return _line;
}
int JSSyntaxException::getCols(){
    return _cols;
}
