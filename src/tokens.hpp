#ifndef HEADER_TOKENS
#define HEADER_TOKENS

#include <string>
#include "exceptions.hpp"

using namespace std;

class SYMBOL{
protected:
    string _text, _name;
    int _value;
public:
    SYMBOL(){
        _text = "<SYMBOL>";
        _name = "SYMBOL";
        _value = 0;
    }
    virtual ~SYMBOL(){}

    virtual string getText(){return _text;}
    virtual string getName(){return _name;}
    virtual int getValue(){return _value;}
};
class TOKEN : public SYMBOL{
public:
    TOKEN(){
        _text = "<TOKEN>";
        _name = "TOKEN";
    }
    ~TOKEN(){}
};

class BaseToken : public TOKEN{
public:
    BaseToken(){
        _text = "<BaseToken>";
        _name = "BaseToken";
    }
    ~BaseToken(){}
};

class CommentToken            : public BaseToken{
protected:
    int _lines;
public:
    CommentToken(){
        _text = "<CommentToken>";
        _lines = 0;
        _name = "CommentToken";
    }
    CommentToken(string text, int lines){
        _text = text;
        _lines = lines;
        _name = "CommentToken";
    }
    int getLines(){
        return _lines;
    }
};
class FutureReservedWordToken : public BaseToken{
public:
    FutureReservedWordToken(){
        _text = "<FutureReservedWordToken>";
        _name = "FutureReservedWordToken";
    }
    FutureReservedWordToken(string text){
        _text = text;
        _name = "FutureReservedWordToken";
    }
};
class IdentifierToken         : public BaseToken{
public:
    IdentifierToken(){
        _text = "<IdentifierToken>";
        _name = "IdentifierToken";
    }
    IdentifierToken(string text){
        _text = text;
        _name = "IdentifierToken";
    }
};
class KeywordToken            : public BaseToken{
public:
    KeywordToken(){
        _text = "<KeywordToken>";
        _name = "KeywordToken";
    }
    KeywordToken(string text){
        _text = text;
        _name = "KeywordToken";
    }
};
class LineTerminatorToken     : public BaseToken{
protected:
    int _lines;
public:
    LineTerminatorToken(){
        _text = "\r";
        _lines = 0;
        _name = "LineTerminatorToken";
    }
    LineTerminatorToken(string text, int lines){
        if('\r'!=text.at(0) && '\n'!=text.at(0)){throw string("Parse error: "+text+" is not <LineTerminatorToken>.");}
        _text = text;
        _lines = lines;
        _name = "LineTerminatorToken";
    }
    int getlines(){
        return _lines;
    }
};
class LiteralToken            : public BaseToken{
public:
    LiteralToken(){
        _text = "<LiteralToken>";
        _name = "LiteralToken";
    }
    LiteralToken(string text){
        _text = text;
        _name = "LiteralToken";
    }
};
class NullLiteralToken        : public BaseToken{
public:
    NullLiteralToken(){
        _text = "null";
        _name = "NullLiteralToken";
    }
    NullLiteralToken(string text){
        if("null"!=text){throw string("Parse error: "+text+" is not <NullLiteralToken>.");}
        _text = text;
        _name = "NullLiteralToken";
    }
};
class OperatorToken           : public BaseToken{
public:
    OperatorToken(){
        _text = "<OperatorToken>";
        _name = "OperatorToken";
    }
    OperatorToken(string text){
        _text = "OperatorToken";
        _name = "OperatorToken";
    }
};
class PunctuationToken        : public BaseToken{
public:
    PunctuationToken(){
        _text = "<PunctuationToken>";
        _name = "PunctuationToken";
    }
    PunctuationToken(string text){
        _text = "<PunctuationToken>";
        _name = "PunctuationToken";
    }
};
class WhiteSpaceToken         : public BaseToken{
public:
    WhiteSpaceToken(){
        _text = " ";
        _name = "WhiteSpaceToken";
    }
    WhiteSpaceToken(string text){
        _text = text;
        _name = "WhiteSpaceToken";
    }
};

class AbstractToken     : public FutureReservedWordToken{
public:
    AbstractToken(){
        _text = "abstract";
        _name = "AbstractToken";
    }
    AbstractToken(string text){
        if("abstract"!=text){throw string("Parse error: "+text+" is not <AbstractToken>.");}
        _text = text;
        _name = "AbstractToken";
    }
};
class ByteToken         : public FutureReservedWordToken{
public:
    ByteToken(){
        _text = "byte";
        _name = "ByteToken";
    }
    ByteToken(string text){
        if("byte"!=text){throw string("Parse error: "+text+" is not <ByteToken>.");}
        _text = text;
        _name = "ByteToken";
    }
};
class CharToken         : public FutureReservedWordToken{
public:
    CharToken(){
        _text = "char";
        _name = "CharToken";
    }
    CharToken(string text){
        if("char"!=text){throw string("Parse error: "+text+" is not <CharToken>.");}
        _text = text;
        _name = "CharToken";
    }
};
class ClassToken        : public FutureReservedWordToken{
public:
    ClassToken(){
        _text = "class";
        _name = "ClassToken";
    }
     ClassToken(string text){
        if("class"!=text){throw string("Parse error: "+text+" is not <ClassToken>.");}
        _text = text;
        _name = "ClassToken";
    }
};
class ConstToken        : public FutureReservedWordToken{
public:
    ConstToken(){
        _text = "const";
        _name = "ConstToken";
    }
    ConstToken(string text){
        if("const"!=text){throw string("Parse error: "+text+" is not <ConstToken>.");}
        _text = text;
        _name = "ConstToken";
    }
};
class DebuggerToken     : public FutureReservedWordToken{
public:
    DebuggerToken(){
        _text = "debugger";
        _name = "DebuggerToken";
    }
    DebuggerToken(string text){
        if("debugger"!=text){throw string("Parse error: "+text+" is not <DebuggerToken>.");}
        _text = text;
        _name = "DebuggerToken";
    }
};
class DoubleToken       : public FutureReservedWordToken{
public:
    DoubleToken(){
        _text = "double";
        _name = "DoubleToken";
    }
    DoubleToken(string text){
        if("double"!=text){throw string("Parse error: "+text+" is not <DoubleToken>.");}
        _text = text;
        _name = "DoubleToken";
    }
};
class EnumToken         : public FutureReservedWordToken{
public:
    EnumToken(){
        _text = "enum";
        _name = "EnumToken";
    }
    EnumToken(string text){
        if("enum"!=text){throw string("Parse error: "+text+" is not <EnumToken>.");}
        _text = text;
        _name = "EnumToken";
    }
};
class ExportToken       : public FutureReservedWordToken{
public:
    ExportToken(){
        _text = "export";
        _name = "ExportToken";
    }
    ExportToken(string text){
        if("export"!=text){throw string("Parse error: "+text+" is not <ExportToken>.");}
        _text = text;
        _name = "ExportToken";
    }
};
class ExtendsToken      : public FutureReservedWordToken{
public:
    ExtendsToken(){
        _text = "extends";
        _name = "ExtendsToken";
    }
    ExtendsToken(string text){
        if("extends"!=text){throw string("Parse error: "+text+" is not <ExtendsToken>.");}
        _text = text;
        _name = "ExtendsToken";
    }
};
class FloatToken        : public FutureReservedWordToken{
public:
    FloatToken(){
        _text = "float";
        _name = "FloatToken";
    }
    FloatToken(string text){
        if("float"!=text){throw string("Parse error: "+text+" is not <FloatToken>.");}
        _text = text;
        _name = "FloatToken";
    }
};
class GotoToken         : public FutureReservedWordToken{
public:
    GotoToken(){
        _text = "goto";
        _name = "GotoToken";
    }
    GotoToken(string text){
        if("goto"!=text){throw string("Parse error: "+text+" is not <GotoToken>.");}
        _text = text;
        _name = "GotoToken";
    }
};
class ImplementsToken   : public FutureReservedWordToken{
public:
    ImplementsToken(){
        _text = "implement";
        _name = "ImplementsToken";
    }
    ImplementsToken(string text){
        if("implement"!=text){throw string("Parse error: "+text+" is not <ImplementsToken>.");}
        _text = text;
        _name = "ImplementsToken";
    }
};
class IntToken          : public FutureReservedWordToken{
public:
    IntToken(){
        _text = "int";
        _name = "IntToken";
    }
    IntToken(string text){
        if("int"!=text){throw string("Parse error: "+text+" is not <IntToken>.");}
        _text = text;
        _name = "IntToken";
    }
};
class InterfaceToken    : public FutureReservedWordToken{
public:
    InterfaceToken(){
        _text = "interface";
        _name = "InterfaceToken";
    }
    InterfaceToken(string text){
        if("interface"!=text){throw string("Parse error: "+text+" is not <InterfaceToken>.");}
        _text = text;
        _name = "InterfaceToken";
    }
};
class LongToken         : public FutureReservedWordToken{
public:
    LongToken(){
        _text = "long";
        _name = "LongToken";
    }
    LongToken(string text){
        if("long"!=text){throw string("Parse error: "+text+" is not <LongToken>.");}
        _text = text;
        _name = "LongToken";
    }
};
class NativeToken       : public FutureReservedWordToken{
public:
    NativeToken(){
        _text = "native";
        _name = "NativeToken";
    }
    NativeToken(string text){
        if("native"!=text){throw string("Parse error: "+text+" is not <NativeToken>.");}
        _text = text;
        _name = "NativeToken";
    }
};
class PackageToken      : public FutureReservedWordToken{
public:
    PackageToken(){
        _text = "package";
        _name = "PackageToken";
    }
    PackageToken(string text){
        if("package"!=text){throw string("Parse error: "+text+" is not <PackageToken>.");}
        _text = text;
        _name = "PackageToken";
    }
};
class PrivateToken      : public FutureReservedWordToken{
public:
    PrivateToken(){
        _text = "private";
        _name = "PrivateToken";
    }
    PrivateToken(string text){
        if("private"!=text){throw string("Parse error: "+text+" is not <PrivateToken>.");}
        _text = text;
        _name = "PrivateToken";
    }
};
class ProtectedToken    : public FutureReservedWordToken{
public:
    ProtectedToken(){
        _text = "protected";
        _name = "ProtectedToken";
    }
    ProtectedToken(string text){
        if("protected"!=text){throw string("Parse error: "+text+" is not <ProtectedToken>.");}
        _text = text;
        _name = "ProtectedToken";
    }
};
class PublicToken       : public FutureReservedWordToken{
public:
    PublicToken(){
        _text = "public";
        _name = "PublicToken";
    }
    PublicToken(string text){
        if("public"!=text){throw string("Parse error: "+text+" is not <PublicToken>.");}
        _text = text;
        _name = "PublicToken";
    }
};
class StaticToken       : public FutureReservedWordToken{
public:
    StaticToken(){
        _text = "static";
        _name = "StaticToken";
    }
    StaticToken(string text){
        if("static"!=text){throw string("Parse error: "+text+" is not <StaticToken>.");}
        _text = text;
        _name = "StaticToken";
    }
};
class SuperToken        : public FutureReservedWordToken{
public:
    SuperToken(){
        _text = "super";
        _name = "SuperToken";
    }
    SuperToken(string text){
        if("super"!=text){throw string("Parse error: "+text+" is not <SuperToken>.");}
        _text = text;
        _name = "SuperToken";
    }
};
class SynchronizedToken : public FutureReservedWordToken{
public:
    SynchronizedToken(){
        _text = "synchronized";
        _name = "SynchronizedToken";
    }
    SynchronizedToken(string text){
        if("synchronized"!=text){throw string("Parse error: "+text+" is not <SynchronizedToken>.");}
        _text = text;
        _name = "SynchronizedToken";
    }
};
class ThrowsToken       : public FutureReservedWordToken{
public:
    ThrowsToken(){
        _text = "throws";
        _name = "ThrowsToken";
    }
    ThrowsToken(string text){
        if("throws"!=text){throw string("Parse error: "+text+" is not <ThrowsToken>.");}
        _text = text;
        _name = "ThrowsToken";
    }
};
class TransientToken    : public FutureReservedWordToken{
public:
    TransientToken(){
        _text = "transient";
        _name = "TransientToken";
    }
    TransientToken(string text){
        if("transient"!=text){throw string("Parse error: "+text+" is not <TransientToken>.");}
        _text = text;
        _name = "TransientToken";
    }
};
class VolatileToken     : public FutureReservedWordToken{
public:
    VolatileToken(){
        _text = "volatile";
        _name = "VolatileToken";
    }
    VolatileToken(string text){
        if("volatile"!=text){throw string("Parse error: "+text+" is not <VolatileToken>.");}
        _text = text;
        _name = "VolatileToken";
    }
};

class BreakToken      : public KeywordToken{
public:
    BreakToken(){
        _text = "break";
        _name = "BreakToken";
    }
    BreakToken(string text){
        if("break"!=text){throw string("Parse error: "+text+" is not <BreakToken>.");}
        _text = text;
        _name = "BreakToken";
    }
};
class CaseToken       : public KeywordToken{
public:
    CaseToken(){
        _text = "case";
        _name = "CaseToken";
    }
    CaseToken(string text){
        if("case"!=text){throw string("Parse error: "+text+" is not <CaseToken>.");}
        _text = text;
        _name = "CaseToken";
    }
};
class CatchToken      : public KeywordToken{
public:
    CatchToken(){
        _text = "catch";
        _name = "CatchToken";
    }
    CatchToken(string text){
        if("catch"!=text){throw string("Parse error: "+text+" is not <CatchToken>.");}
        _text = text;
        _name = "CatchToken";
    }
};
class ContinueToken   : public KeywordToken{
public:
    ContinueToken(){
        _text = "continue";
        _name = "ContinueToken";
    }
    ContinueToken(string text){
        if("continue"!=text){throw string("Parse error: "+text+" is not <ContinueToken>.");}
        _text = text;
        _name = "ContinueToken";
    }
};
class DefaultToken    : public KeywordToken{
public:
    DefaultToken(){
        _text = "default";
        _name = "DefaultToken";
    }
    DefaultToken(string text){
        if("default"!=text){throw string("Parse error: "+text+" is not <DefaultToken>.");}
        _text = text;
        _name = "DefaultToken";
    }
};
class DeleteToken     : public KeywordToken{
public:
    DeleteToken(){
        _text = "delete";
        _name = "DeleteToken";
    }
    DeleteToken(string text){
        if("delete"!=text){throw string("Parse error: "+text+" is not <DeleteToken>.");}
        _text = text;
        _name = "DeleteToken";
    }
};
class DoToken         : public KeywordToken{
public:
    DoToken(){
        _text = "do";
        _name = "DoToken";
    }
    DoToken(string text){
        if("do"!=text){throw string("Parse error: "+text+" is not <DoToken>.");}
        _text = text;
        _name = "DoToken";
    }
};
class ElseToken       : public KeywordToken{
public:
    ElseToken(){
        _text = "else";
        _name = "ElseToken";
    }
    ElseToken(string text){
        if("else"!=text){throw string("Parse error: "+text+" is not <ElseToken>.");}
        _text = text;
        _name = "ElseToken";
    }
};
class FinalToken      : public KeywordToken{
public:
    FinalToken(){
        _text = "final";
        _name = "FinalToken";
    }
    FinalToken(string text){
        if("final"!=text){throw string("Parse error: "+text+" is not <FinalToken>.");}
        _text = text;
        _name = "FinalToken";
    }
};
class FinallyToken    : public KeywordToken{
public:
    FinallyToken(){
        _text = "finally";
        _name = "FinallyToken";
    }
    FinallyToken(string text){
        if("finally"!=text){throw string("Parse error: "+text+" is not <FinallyToken>.");}
        _text = text;
        _name = "FinallyToken";
    }
};
class FunctionToken    : public KeywordToken{
public:
    FunctionToken(){
        _text = "function";
        _name = "FunctionToken";
    }
    FunctionToken(string text){
        if("function"!=text){throw string("Parse error: "+text+" is not <FunctionToken>.");}
        _text = text;
        _name = "FunctionToken";
    }
};
class IfToken         : public KeywordToken{
public:
    IfToken(){
        _text = "if";
        _name = "IfToken";
    }
    IfToken(string text){
        if("if"!=text){throw string("Parse error: "+text+" is not <IfToken>.");}
        _text = text;
        _name = "IfToken";
    }
};
class InToken         : public KeywordToken{
public:
    InToken(){
        _text = "in";
        _name = "InToken";
    }
    InToken(string text){
        if("in"!=text){throw string("Parse error: "+text+" is not <InToken>.");}
        _text = text;
        _name = "InToken";
    }
};
class InstanceOfToken : public KeywordToken{
public:
    InstanceOfToken(){
        _text = "instanceof";
        _name = "InstanceOfToken";
    }
    InstanceOfToken(string text){
        if("instanceof"!=text){throw string("Parse error: "+text+" is not <InstanceOfToken>.");}
        _text = text;
        _name = "InstanceOfToken";
    }
};
class NewToken        : public KeywordToken{
public:
    NewToken(){
        _text = "new";
        _name = "NewToken";
    }
    NewToken(string text){
        if("new"!=text){throw string("Parse error: "+text+" is not <NewToken>.");}
        _text = text;
        _name = "NewToken";
    }
};
class ReturnToken     : public KeywordToken{
public:
    ReturnToken(){
        _text = "return";
        _name = "ExtendsToken";
    }
    ReturnToken(string text){
        if("return"!=text){throw string("Parse error: "+text+" is not <ReturnToken>.");}
        _text = text;
        _name = "ReturnToken";
    }
};
class SwitchToken     : public KeywordToken{
public:
    SwitchToken(){
        _text = "switch";
        _name = "SwitchToken";
    }
    SwitchToken(string text){
        if("switch"!=text){throw string("Parse error: "+text+" is not <SwitchToken>.");}
        _text = text;
        _name = "SwitchToken";
    }
};
class ThisToken       : public KeywordToken{
public:
    ThisToken(){
        _text = "this";
        _name = "ThisToken";
    }
    ThisToken(string text){
        if("this"!=text){throw string("Parse error: "+text+" is not <ThisToken>.");}
        _text = text;
        _name = "ThisToken";
    }
};
class ThrowToken      : public KeywordToken{
public:
    ThrowToken(){
        _text = "throw";
        _name = "ThrowToken";
    }
    ThrowToken(string text){
        if("throw"!=text){throw string("Parse error: "+text+" is not <ThrowToken>.");}
        _text = text;
        _name = "ThrowToken";
    }
};
class TryToken        : public KeywordToken{
public:
    TryToken(){
        _text = "try";
        _name = "TryToken";
    }
    TryToken(string text){
        if("try"!=text){throw string("Parse error: "+text+" is not <TryToken>.");}
        _text = text;
        _name = "TryToken";
    }
};
class TypeOfToken     : public KeywordToken{
public:
    TypeOfToken(){
        _text = "typeof";
        _name = "TypeOfToken";
    }
    TypeOfToken(string text){
        if("typeof"!=text){throw string("Parse error: "+text+" is not <TypeOfToken>.");}
        _text = text;
        _name = "TypeOfToken";
    }
};
class VarToken        : public KeywordToken{
public:
    VarToken(){
        _text = "var";
        _name = "VarToken";
    }
    VarToken(string text){
        if("var"!=text){throw string("Parse error: "+text+" is not <VarToken>.");}
        _text = text;
        _name = "VarToken";
    }
};
class VoidToken       : public KeywordToken{
public:
    VoidToken(){
        _text = "void";
        _name = "VoidToken";
    }
    VoidToken(string text){
        if("void"!=text){throw string("Parse error: "+text+" is not <VoidToken>.");}
        _text = text;
        _name = "VoidToken";
    }
};
class WhileToken      : public KeywordToken{
public:
    WhileToken(){
        _text = "while";
        _name = "WhileToken";
    }
    WhileToken(string text){
        if("while"!=text){throw string("Parse error: "+text+" is not <WhileToken>.");}
        _text = text;
        _name = "WhileToken";
    }
};
class WithToken       : public KeywordToken{
public:
    WithToken(){
        _text = "with";
        _name = "WithToken";
    }
    WithToken(string text){
        if("with"!=text){throw string("Parse error: "+text+" is not <WithToken>.");}
        _text = text;
        _name = "WithToken";
    }
};

class BooleanLiteralToken           : public LiteralToken{
public:
    BooleanLiteralToken(){
        _text = "<BooleanLiteralToken>";
        _name = "BooleanLiteralToken";
    }
    BooleanLiteralToken(string text){
        _text = text;
        _name = "BooleanLiteralToken";
    }
};
    class FalseLiteralToken             : public BooleanLiteralToken{
    public:
        FalseLiteralToken(){
            _text = "false";
            _name = "FalseLiteralToken";
        }
        FalseLiteralToken(string text){
            if("false"!=text){throw string("Parse error: "+text+" is not <FalseLiteralToken>.");}
            _text = text;
            _name = "FalseLiteralToken";
        }
    };
    class TrueLiteralToken              : public BooleanLiteralToken{
    public:
        TrueLiteralToken(){
            _text = "true";
            _name = "TrueLiteralToken";
        }
        TrueLiteralToken(string text){
            if("true"!=text){throw string("Parse error: "+text+" is not <TrueLiteralToken>.");}
            _text = text;
            _name = "TrueLiteralToken";
        }
    };
class NumbericLiteralToken          : public LiteralToken{
public:
    NumbericLiteralToken(){
        _text = "<NumbericLiteralToken>";
        _name = "NumbericLiteralToken";
    }
    NumbericLiteralToken(string text){
        _text = text;
        _name = "NumbericLiteralToken";
    }
};
class RegularExpressionLiteralToken : public LiteralToken{
public:
    RegularExpressionLiteralToken(){
        _text = "<RegularExpressionLiteralToken>";
        _name = "RegularExpressionLiteralToken";
    }
    RegularExpressionLiteralToken(string text){
        _text = text;
        _name = "RegularExpressionLiteralToken";
    }
};
class StringLiteralToken            : public LiteralToken{
protected:
    int _lines;
public:
    StringLiteralToken(){
        _text = "<StringLiteralToken>";
        _lines = 0;
        _name = "StringLiteralToken";
    }
    StringLiteralToken(string text, int lines){
        //if(('"'!=text.at(0) && '"'!=text.at(text.length()-1)) ||
          //('\''!=text.at(0) && '\''!=text.at(text.length()-1))){
        if('"'!=text.at(0) && '\''!=text.at(0)){
            throw string("Parse error: "+text+" is not <StringLiteralToken>.");
        }
        _text = text;
        _lines = lines;
        _name = "StringLiteralToken";
    }
    int getLines(){
        return _lines;
    }
};

class AssignToken                 : public OperatorToken{
public:
    AssignToken(){
        _text = "=";
        _name = "AssignToken";
    }
    AssignToken(string text){
        if("="!=text){throw string("Parse error: "+text+" is not <AssignToken>.");}
        _text = text;
        _name = "AssignToken";
    }
};
class BitwiseAndAssignToken       : public OperatorToken{
public:
    BitwiseAndAssignToken(){
        _text = "&=";
        _name = "BitwiseAndAssignToken";
    }
    BitwiseAndAssignToken(string text){
        if("&="!=text){throw string("Parse error: "+text+" is not <BitwiseAndAssignToken>.");}
        _text = text;
        _name = "BitwiseAndAssignToken";
    }
};
class BitwiseAndToken             : public OperatorToken{
public:
    BitwiseAndToken(){
        _text = "&";
        _name = "BitwiseAndToken";
    }
    BitwiseAndToken(string text){
        if("&"!=text){throw string("Parse error: "+text+" is not <BitwiseAndToken>.");}
        _text = text;
        _name = "BitwiseAndToken";
    }
};
class BitwiseOrAssignToken        : public OperatorToken{
public:
    BitwiseOrAssignToken(){
        _text = "|=";
        _name = "BitwiseOrAssignToken";
    }
    BitwiseOrAssignToken(string text){
        if("|="!=text){throw string("Parse error: "+text+" is not <BitwiseOrAssignToken>.");}
        _text = text;
        _name = "BitwiseOrAssignToken";
    }
};
class BitwiseOrToken              : public OperatorToken{
public:
    BitwiseOrToken(){
        _text = "|";
        _name = "BitwiseOrToken";
    }
    BitwiseOrToken(string text){
        if("|"!=text){throw string("Parse error: "+text+" is not <BitwiseOrToken>.");}
        _text = text;
        _name = "BitwiseOrToken";
    }
};
class BitwiseXOrAssignToken       : public OperatorToken{
public:
    BitwiseXOrAssignToken(){
        _text = "^=";
        _name = "BitwiseXOrAssignToken";
    }
    BitwiseXOrAssignToken(string text){
        if("^="!=text){throw string("Parse error: "+text+" is not <BitwiseXOrAssignToken>.");}
        _text = text;
        _name = "BitwiseXOrAssignToken";
    }
};
class BitwiseXOrToken             : public OperatorToken{
public:
    BitwiseXOrToken(){
        _text = "^";
        _name = "BitwiseXOrToken";
    }
    BitwiseXOrToken(string text){
        if("^"!=text){throw string("Parse error: "+text+" is not <BitwiseXOrToken>.");}
        _text = text;
        _name = "BitwiseXOrToken";
    }
};
class ComplementToken             : public OperatorToken{
public:
    ComplementToken(){
        _text = "~";
        _name = "ComplementToken";
    }
    ComplementToken(string text){
        if("~"!=text){throw string("Parse error: "+text+" is not <ComplementToken>.");}
        _text = text;
        _name = "ComplementToken";
    }
};
class DividesAssignToken          : public OperatorToken{
public:
    DividesAssignToken(){
        _text = "/=";
        _name = "DividesAssignToken";
    }
    DividesAssignToken(string text){
        if("/="!=text){throw string("Parse error: "+text+" is not <DividesAssignToken>.");}
        _text = text;
        _name = "DividesAssignToken";
    }
};
class DividesToken                : public OperatorToken{
public:
    DividesToken(){
        _text = "/";
        _name = "DividesToken";
    }
    DividesToken(string text){
        if("/"!=text){throw string("Parse error: "+text+" is not <DividesToken>.");}
        _text = text;
        _name = "DividesToken";
    }
};
class EqualToken                  : public OperatorToken{
public:
    EqualToken(){
        _text = "==";
        _name = "EqualToken";
    }
    EqualToken(string text){
        if("=="!=text){throw string("Parse error: "+text+" is not <EqualToken>.");}
        _text = text;
        _name = "EqualToken";
    }
};
class ExactlyEqualToken           : public OperatorToken{
public:
    ExactlyEqualToken(){
        _text = "===";
        _name = "ExactlyEqualToken";
    }
    ExactlyEqualToken(string text){
        if("==="!=text){throw string("Parse error: "+text+" is not <ExactlyEqualToken>.");}
        _text = text;
        _name = "ExactlyEqualToken";
    }
};
class ExactlyNotEqualToken           : public OperatorToken{
public:
    ExactlyNotEqualToken(){
        _text = "!==";
        _name = "ExactlyNotEqualToken";
    }
    ExactlyNotEqualToken(string text){
        if("!=="!=text){throw string("Parse error: "+text+" is not <ExactlyNotEqualToken>.");}
        _text = text;
        _name = "ExactlyNotEqualToken";
    }
};
class GreaterThanOrEqualToken     : public OperatorToken{
public:
    GreaterThanOrEqualToken(){
        _text = ">=";
        _name = "GreaterThanOrEqualToken";
    }
    GreaterThanOrEqualToken(string text){
        if(">="!=text){throw string("Parse error: "+text+" is not <GreaterThanOrEqualToken>.");}
        _text = text;
        _name = "GreaterThanOrEqualToken";
    }
};
class GreaterThanToken            : public OperatorToken{
public:
    GreaterThanToken(){
        _text = ">";
        _name = "GreaterThanToken";
    }
    GreaterThanToken(string text){
        if(">"!=text){throw string("Parse error: "+text+" is not <GreaterThanToken>.");}
        _text = text;
        _name = "GreaterThanToken";
    }
};
class LeftShiftAsignToken         : public OperatorToken{
public:
    LeftShiftAsignToken(){
        _text = "<<=";
        _name = "LeftShiftAsignToken";
    }
    LeftShiftAsignToken(string text){
        if("<<="!=text){throw string("Parse error: "+text+" is not <LeftShiftAsignToken>.");}
        _text = text;
        _name = "LeftShiftAsignToken";
    }
};
class LeftShiftToken              : public OperatorToken{
public:
    LeftShiftToken(){
        _text = "<<";
        _name = "LeftShiftToken";
    }
    LeftShiftToken(string text){
        if("<<"!=text){throw string("Parse error: "+text+" is not <LeftShiftToken>.");}
        _text = text;
        _name = "LeftShiftToken";
    }
};
class LessThanOrEqualToken        : public OperatorToken{
public:
    LessThanOrEqualToken(){
        _text = "<=";
        _name = "LessThanOrEqualToken";
    }
    LessThanOrEqualToken(string text){
        if("<="!=text){throw string("Parse error: "+text+" is not <LessThanOrEqualToken>.");}
        _text = text;
        _name = "LessThanOrEqualToken";
    }
};
class LessThanToken        : public OperatorToken{
public:
    LessThanToken(){
        _text = "<";
        _name = "LessThanToken";
    }
    LessThanToken(string text){
        if("<"!=text){throw string("Parse error: "+text+" is not <LessThanToken>.");}
        _text = text;
        _name = "LessThanToken";
    }
};
class LogicalAndToken             : public OperatorToken{
public:
    LogicalAndToken(){
        _text = "&&";
        _name = "LogicalAndToken";
    }
    LogicalAndToken(string text){
        if("&&"!=text){throw string("Parse error: "+text+" is not <LogicalAndToken>.");}
        _text = text;
        _name = "LogicalAndToken";
    }
};
class LogicalOrToken              : public OperatorToken{
public:
    LogicalOrToken(){
        _text = "||";
        _name = "LogicalOrToken";
    }
    LogicalOrToken(string text){
        if("||"!=text){throw string("Parse error: "+text+" is not <LogicalOrToken>.");}
        _text = text;
        _name = "LogicalOrToken";
    }
};
class MinusAssignToken            : public OperatorToken{
public:
    MinusAssignToken(){
        _text = "-=";
        _name = "MinusAssignToken";
    }
    MinusAssignToken(string text){
        if("-="!=text){throw string("Parse error: "+text+" is not <MinusAssignToken>.");}
        _text = text;
        _name = "MinusAssignToken";
    }
};
class MinusMinusToken             : public OperatorToken{
public:
    MinusMinusToken(){
        _text = "--";
        _name = "MinusMinusToken";
    }
    MinusMinusToken(string text){
        if("--"!=text){throw string("Parse error: "+text+" is not <MinusMinusToken>.");}
        _text = text;
        _name = "MinusMinusToken";
    }
};
class MinusToken                  : public OperatorToken{
public:
    MinusToken(){
        _text = "-";
        _name = "MinusToken";
    }
    MinusToken(string text){
        if("-"!=text){throw string("Parse error: "+text+" is not <MinusToken>.");}
        _text = text;
        _name = "MinusToken";
    }
};
class ModuloAssignToken           : public OperatorToken{
public:
    ModuloAssignToken(){
        _text = "%=";
        _name = "ModuloAssignToken";
    }
    ModuloAssignToken(string text){
        if("%="!=text){throw string("Parse error: "+text+" is not <ModuloAssignToken>.");}
        _text = text;
        _name = "ModuloAssignToken";
    }
};
class ModuloToken                 : public OperatorToken{
public:
    ModuloToken(){
        _text = "%";
        _name = "ModuloToken";
    }
    ModuloToken(string text){
        if("%"!=text){throw string("Parse error: "+text+" is not <ModuloToken>.");}
        _text = text;
        _name = "ModuloToken";
    }
};
class NotEqualToken               : public OperatorToken{
public:
    NotEqualToken(){
        _text = "!=";
        _name = "NotEqualToken";
    }
    NotEqualToken(string text){
        if("!="!=text){throw string("Parse error: "+text+" is not <NotEqualToken>.");}
        _text = text;
        _name = "NotEqualToken";
    }
};
class NotToken                    : public OperatorToken{
public:
    NotToken(){
        _text = "!";
        _name = "NotToken";
    }
    NotToken(string text){
        if("!"!=text){throw string("Parse error: "+text+" is not <NotToken>.");}
        _text = text;
        _name = "NotToken";
    }
};
class PlusAssignToken             : public OperatorToken{
public:
    PlusAssignToken(){
        _text = "+=";
        _name = "PlusAssignToken";
    }
    PlusAssignToken(string text){
        if("+="!=text){throw string("Parse error: "+text+" is not <PlusAssignToken>.");}
        _text = text;
        _name = "PlusAssignToken";
    }
};
class PlusPlusToken               : public OperatorToken{
public:
    PlusPlusToken(){
        _text = "++";
        _name = "PlusPlusToken";
    }
    PlusPlusToken(string text){
        if("++"!=text){throw string("Parse error: "+text+" is not <PlusPlusToken>.");}
        _text = text;
        _name = "PlusPlusToken";
    }
};
class PlusToken                   : public OperatorToken{
public:
    PlusToken(){
        _text = "+";
        _name = "PlusToken";
    }
    PlusToken(string text){
        if("+"!=text){throw string("Parse error: "+text+" is not <PlusToken>.");}
        _text = text;
        _name = "PlusToken";
    }
};
class RightShiftAssignRotateToken : public OperatorToken{
public:
    RightShiftAssignRotateToken(){
        _text = ">>>=";
        _name = "RightShiftAssignRotateToken";
    }
    RightShiftAssignRotateToken(string text){
        if(">>>="!=text){throw string("Parse error: "+text+" is not <RightShiftAssignRotateToken>.");}
        _text = text;
        _name = "RightShiftAssignRotateToken";
    }
};
class RightShiftAssignToken       : public OperatorToken{
public:
    RightShiftAssignToken(){
        _text = ">>=";
        _name = "RightShiftAssignToken";
    }
    RightShiftAssignToken(string text){
        if(">>="!=text){throw string("Parse error: "+text+" is not <RightShiftAssignToken>.");}
        _text = text;
        _name = "RightShiftAssignToken";
    }
};
class RightShiftRotateToken       : public OperatorToken{
public:
    RightShiftRotateToken(){
        _text = ">>>";
        _name = "RightShiftRotateToken";
    }
    RightShiftRotateToken(string text){
        if(">>>"!=text){throw string("Parse error: "+text+" is not <RightShiftRotateToken>.");}
        _text = text;
        _name = "RightShiftRotateToken";
    }
};
// TODO: check this.
class RightShiftToken             : public OperatorToken{
public:
    RightShiftToken(){
        _text = ">>";
        _name = "RightShiftToken";
    }
    RightShiftToken(string text){
        if(">>"!=text){throw string("Parse error: "+text+" is not <RightShiftToken>.");}
        _text = text;
        _name = "RightShiftToken";
    }
};
class TernaryToken                : public OperatorToken{
public:
    TernaryToken(){
        _text = "?";
        _name = "TernaryToken";
    }
    TernaryToken(string text){
        if("?"!=text){throw string("Parse error: "+text+" is not <TernaryToken>.");}
        _text = text;
        _name = "TernaryToken";
    }
};
class TimesAssignToken            : public OperatorToken{
public:
    TimesAssignToken(){
        _text = "*=";
        _name = "TimesAssignToken";
    }
    TimesAssignToken(string text){
        if("*="!=text){throw string("Parse error: "+text+" is not <TimesAssignToken>.");}
        _text = text;
        _name = "TimesAssignToken";
    }
};
// TODO: check this.
class TimesToken                  : public OperatorToken{
public:
    TimesToken(){
        _text = "*";
        _name = "TimesToken";
    }
    TimesToken(string text){
        if("*"!=text){throw string("Parse error: "+text+" is not <TimesToken>.");}
        _text = text;
        _name = "TimesToken";
    }
};

class ColonToken        : public PunctuationToken{
public:
    ColonToken(){
        _text = ":";
        _name = "ColonToken";
    }
    ColonToken(string text){
        if(":"!=text){throw string("Parse error: "+text+" is not <ColonToken>.");}
        _text = text;
        _name = "ColonToken";
    }
};
class CommaToken        : public PunctuationToken{
public:
    CommaToken(){
        _text = ",";
        _name = "CommaToken";
    }
    CommaToken(string text){
        if(","!=text){throw string("Parse error: "+text+" is not <CommaToken>.");}
        _text = text;
        _name = "CommaToken";
    }
};
class LeftBraceToken    : public PunctuationToken{
public:
    LeftBraceToken(){
        _text = "{";
        _name = "LeftBraceToken";
    }
    LeftBraceToken(string text){
        if("{"!=text){throw string("Parse error: "+text+" is not <LeftBraceToken>.");}
        _text = text;
        _name = "LeftBraceToken";
    }
};
class LeftBracketToken  : public PunctuationToken{
public:
    LeftBracketToken(){
        _text = "[";
        _name = "LeftBracketToken";
    }
    LeftBracketToken(string text){
        if("["!=text){throw string("Parse error: "+text+" is not <LeftBracketToken>.");}
        _text = text;
        _name = "LeftBracketToken";
    }
};
class LeftParenToken    : public PunctuationToken{
public:
    LeftParenToken(){
        _text = "(";
        _name = "LeftParenToken";
    }
    LeftParenToken(string text){
        if("("!=text){throw string("Parse error: "+text+" is not <LeftParenToken>.");}
        _text = text;
        _name = "LeftParenToken";
    }
};
class PeriodToken       : public PunctuationToken{
public:
    PeriodToken(){
        _text = ".";
        _name = "PeriodToken";
    }
    PeriodToken(string text){
        if("."!=text){throw string("Parse error: "+text+" is not <PeriodToken>.");}
        _text = text;
        _name = "PeriodToken";
    }
};
class RightBraceToken   : public PunctuationToken{
public:
    RightBraceToken(){
        _text = "}";
        _name = "RightBraceToken";
    }
    RightBraceToken(string text){
        if("}"!=text){throw string("Parse error: "+text+" is not <RightBraceToken>.");}
        _text = text;
        _name = "RightBraceToken";
    }
};
class RightBracketToken : public PunctuationToken{
public:
    RightBracketToken(){
        _text = "]";
        _name = "RightBracketToken";
    }
    RightBracketToken(string text){
        if("]"!=text){throw string("Parse error: "+text+" is not <RightBracketToken>.");}
        _text = text;
        _name = "RightBracketToken";
    }
};
class RightParenToken   : public PunctuationToken{
public:
    RightParenToken(){
        _text = ")";
        _name = "RightParenToken";
    }
    RightParenToken(string text){
        if(")"!=text){throw string("Parse error: "+text+" is not <RightParenToken>.");}
        _text = text;
        _name = "RightParenToken";
    }
};
class SemicolonToken    : public PunctuationToken{
public:
    SemicolonToken(){
        _text = ";";
        _name = "SemicolonToken";
    }
    SemicolonToken(string text){
        if(";"!=text){throw string("Parse error: "+text+" is not <SemicolonToken>.");}
        _text = text;
        _name = "SemicolonToken";
    }
};

BaseToken * createToken(string text);
bool isNumberic(string text);
//bool is_numeric(const std::string& s);

#endif
