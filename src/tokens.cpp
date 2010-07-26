#include "tokens.hpp"
#include <iostream>

bool isNumberic(string text){
    int dots=0, es=0, xs=0, dot=0;
    char last = NULL;
     for(string::iterator it=text.begin(); it<text.end(); it++){
        switch(*it){
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            break;
        case '.':
            dot++; if(dot>1){return false;}
            break;
        case 'x': case 'X':
            if('0'!=last){return false;}
            xs++; if(xs>1){return false;} break;
        case 'e': case 'E':
            if('.'==last){return false;}
            es++; if(es>1){return false;} break;
        case '+': case '-':
            if(NULL!=last && 'e'!=last && 'E'!=last){return false;}
            break;
        default:
            return false;
        }
        last = *it;
    }
    return true;
}
/*bool is_numeric(const std::string& s){
    std::stringstream ss(s);
    double d;
    ss >> d;
    return ss.good();
}*/

BaseToken * createToken(string text){
    int len=text.length();

    if(len<=0){throw string("Empty string is not a token.");}

    string s1=text.substr(0,1), s2=text.substr(0,(len>=2?2:1)),
        e1=text.substr(len-1,1), e2=text.substr(len-(len>=2?2:1),(len>=2?2:1));
    char c=text.at(0);

    // Comment.
    if(("/*"==s2 && "*/"==e2) || "//"==s2){return new CommentToken(text);}
    // Keyword.
    if("break"==text){return new BreakToken(text);}
    if("case"==text){return new CaseToken(text);}
    if("catch"==text){return new CatchToken(text);}
    if("continue"==text){return new ContinueToken(text);}
    if("default"==text){return new DefaultToken(text);}
    if("delete"==text){return new DeleteToken(text);}
    if("do"==text){return new DoToken(text);}
    if("else"==text){return new ElseToken(text);}
    if("final"==text){return new FinalToken(text);}
    if("finally"==text){return new FinallyToken(text);}
    if("function"==text){return new FunctionToken(text);}
    if("if"==text){return new IfToken(text);}
    if("in"==text){return new InToken(text);}
    if("instanceof"==text){return new InstanceOfToken(text);}
    if("new"==text){return new NewToken(text);}
    if("return"==text){return new ReturnToken(text);}
    if("switch"==text){return new SwitchToken(text);}
    if("this"==text){return new ThisToken(text);}
    if("throw"==text){return new ThrowToken(text);}
    if("try"==text){return new TryToken(text);}
    if("typeof"==text){return new TypeOfToken(text);}
    if("var"==text){return new VarToken(text);}
    if("void"==text){return new VoidToken(text);}
    if("while"==text){return new WhileToken(text);}
    if("with"==text){return new WithToken(text);}
    // Literal.
    if("false"==text){return new FalseLiteralToken(text);}
    if("true"==text){return new TrueLiteralToken(text);}
    // Regular Expression.
    if("/"==s1 && "//"!=s2 && "/*"!=s2 &&
            ("/"==e1 || "i"==e1 || "m"==e1 || "g"==e1)){
        return new RegularExpressionLiteralToken(text);
    }
    // String Literal.
    if(("'"==s1 && "'"==e1) || ("\""==s1 && "\""==e1)){return new StringLiteralToken(text);}
    // Null.
    if("null"==text){return new NullLiteralToken(text);}
    // Whitespace.
    //if(" "==s1 || "\t"==s1){return new WhiteSpaceToken(text);}
    if(' '==c || '\t'==c){return new WhiteSpaceToken(text);}
    // LineTerminator.
    if("\r"==s1 || "\n"==s1){return new LineTerminatorToken(text);}
    // Operator.
    if("="==text){return new AssignToken(text);}
    if("&="==text){return new BitwiseAndAssignToken(text);}
    if("&"==text){return new BitwiseAndToken(text);}
    if("|="==text){return new BitwiseOrAssignToken(text);}
    if("|"==text){return new BitwiseOrToken(text);}
    if("^="==text){return new BitwiseXOrAssignToken(text);}
    if("^"==text){return new BitwiseXOrToken(text);}
    if("~"==text){return new ComplementToken(text);}
    if("/="==text){return new DividesAssignToken(text);}
    if("/"==text){return new DividesToken(text);}
    if("=="==text){return new EqualToken(text);}
    if("==="==text){return new ExactlyEqualToken(text);}
    if("!=="==text){return new ExactlyNotEqualToken(text);}
    if(">="==text){return new GreaterThanOrEqualToken(text);}
    if(">"==text){return new GreaterThanToken(text);}
    if("<<="==text){return new LeftShiftAsignToken(text);}
    if("<<"==text){return new LeftShiftToken(text);}
    if("<="==text){return new LessThanOrEqualToken(text);}
    if("<"==text){return new LessThanToken(text);}
    if("&&"==text){return new LogicalAndToken(text);}
    if("||"==text){return new LogicalOrToken(text);}
    if("-="==text){return new MinusAssignToken(text);}
    if("--"==text){return new MinusMinusToken(text);}
    if("-"==text){return new MinusToken(text);}
    if("%="==text){return new ModuloAssignToken(text);}
    if("%"==text){return new ModuloToken(text);}
    if("!="==text){return new NotEqualToken(text);}
    if("!"==text){return new NotToken(text);}
    if("+="==text){return new PlusAssignToken(text);}
    if("++"==text){return new PlusPlusToken(text);}
    if("+"==text){return new PlusToken(text);}
    if(">>>="==text){return new RightShiftAssignRotateToken(text);}
    if(">>="==text){return new RightShiftAssignToken(text);}
    if(">>>"==text){return new RightShiftRotateToken(text);}
    if(">>"==text){return new RightShiftToken(text);}
    if("?"==text){return new TernaryToken(text);}
    if("*="==text){return new TimesAssignToken(text);}
    if("*"==text){return new TimesToken(text);}
    if(":"==text){return new ColonToken(text);}
    if(","==text){return new CommaToken(text);}
    if("{"==text){return new LeftBraceToken(text);}
    if("["==text){return new LeftBracketToken(text);}
    if("("==text){return new LeftParenToken(text);}
    if("}"==text){return new RightBraceToken(text);}
    if("]"==text){return new RightBracketToken(text);}
    if(")"==text){return new RightParenToken(text);}
    if(";"==text){return new SemicolonToken(text);}
    if("."==text){return new PeriodToken(text);}
    // Numberic.
    if((('0'<=c && c<='9') ||
            (('+'==c || '-'==c) && text.length()>1))
            && isNumberic(text)){
        return new NumbericLiteralToken(text);
    }
    // FutureReservedWord.
    if("abstract"==text){return new AbstractToken(text);}
    if("byte"==text){return new ByteToken(text);}
    if("char"==text){return new CharToken(text);}
    if("class"==text){return new ClassToken(text);}
    if("const"==text){return new ConstToken(text);}
    if("debugger"==text){return new DebuggerToken(text);}
    if("double"==text){return new DoubleToken(text);}
    if("enum"==text){return new EnumToken(text);}
    if("export"==text){return new ExportToken(text);}
    if("extends"==text){return new ExtendsToken(text);}
    if("float"==text){return new FloatToken(text);}
    if("goto"==text){return new GotoToken(text);}
    if("implement"==text){return new ImplementsToken(text);}
    if("int"==text){return new IntToken(text);}
    if("interface"==text){return new InterfaceToken(text);}
    if("long"==text){return new LongToken(text);}
    if("native"==text){return new NativeToken(text);}
    if("package"==text){return new PackageToken(text);}
    if("private"==text){return new PrivateToken(text);}
    if("protected"==text){return new ProtectedToken(text);}
    if("public"==text){return new PublicToken(text);}
    if("static"==text){return new StaticToken(text);}
    if("super"==text){return new SuperToken(text);}
    if("synchronized"==text){return new SynchronizedToken(text);}
    if("throws"==text){return new ThrowsToken(text);}
    if("transient"==text){return new TransientToken(text);}
    if("volatile"==text){return new VolatileToken(text);}

    // Identifier
    if(('a'<=c && c<='z') || ('A'<=c && c<='Z') || '_'==c || '$'==c){
        return new IdentifierToken(text);
    }

    throw string("Unknow JavaScript token: ["+text+"]");
}
