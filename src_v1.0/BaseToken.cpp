#include <string>

class BaseToken : public TOKEN {
public:
    string value;
    void set(string value);
    string get();
    void append(string value);
};
