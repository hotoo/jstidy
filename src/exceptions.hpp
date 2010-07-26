#ifndef _H_JS_EXCEPTIONS
#define _H_JS_EXCEPTIONS

#include <string>

using namespace std;

class JSSyntaxException{
public:
    JSSyntaxException(string file, string msg, string type, int line, int cols);
    JSSyntaxException(string msg, string type, int line, int cols);
    JSSyntaxException();
    ~JSSyntaxException();

    void setFile(string file);
    void setMessage(string msg);
    void setType(string type);
    void setLine(int line);
    void setCols(int cols);

    string getFile();
    string getMessage();
    string getType();
    int getLine();
    int getCols();

private:
    string _file, _message, _type;
    int _line, _cols;
};

#endif
