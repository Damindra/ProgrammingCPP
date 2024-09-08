// CalculatorConsole.cpp : Simple Calculator Console Application
//

#include "..\std_lib_facilities.h"

using namespace std;

class Token {
public:
    char kind;      // what kind of token
    double value;   // for numbers: a value
    Token() : kind(0), value(0) {}  // Default constructor
    Token(char ch) : kind(ch), value(0) {}  // Constructor for char
    Token(char ch, double val) : kind(ch), value(val) {}  // Constructor for char and double
};

class Token_stream {
public:
    Token get();        // get a Token
    void putback(Token t);  // put a Token back
private:
    bool full{ false }; // is there a Token in the buffer?
    Token buffer;       // here is where we keep a Token put back using putback()
};

void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;     // copy t to buffer
    full = true;    // buffer is now full
}

Token Token_stream::get()
{
    if (full) {     // do we already have a Token ready?
        full = false;   // remove Token from buffer
        return buffer;
    }

    char ch;
    cin >> ch;      // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case '=':       // for "print"
    case 'x':       // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/':
        return Token{ ch }; // let each character represent itself
    case '.':       // a floating-point literal can start with a dot
    case '0': case '1': case '2': case '3': case '4':    // numeric literals
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);    // put digit back into the input stream
        double val;
        cin >> val;     // read a floating-point number
        return Token{ '8', val };    // let '8' represent "a number"
    }
    default:
        error("Bad token");
    }
}

Token_stream ts;    // provides get() and putback()
double expression();    // read and evaluate an Expression

double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':       // handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return d;
    }
    case '8':       // we use '8' to represent a number
        return t.value; // return the number's value
    default:
        error("primary expected");
    }
}

double term()
{
    double left = primary();    // read and evaluate a Primary
    Token t = ts.get();     // get the next token
    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary();  // evaluate the Primary to the right of the operator
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;          // evaluate the Primary to the right of the operator
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);      // put t back into the token stream
            return left;        // finally no more * or / operators; return the answer
        }
    }
}

double expression()
{


    double left = term(); // read and evaluate an expression
    Token t = ts.get();       // get the next token

    while (true) {
        switch (t.kind) {
        case '+':
            left += term();       // evaluate the expression to the right of the operator
            t = ts.get();
            break;
        case '-':
            left -= term();       // evaluate the expression to the right of the operator
            t = ts.get();
            break;
        default:
            ts.putback(t);        // put t back into the token stream
            return left;        // finally no more + or - operators; return the answer
        }
    }
}

int main()
{
    cout << "Welcome to our simple calculator.\n";
    cout << "Please enter expressions using floating-point numbers.\n";
    cout << "Operators available are +, -, *, and /.\n";
    cout << "To print the result, enter a semicolon ';' and to exit, enter 'x'.\n";

    double val = 0;
    while (cin) {
        try {

            Token t = ts.get();

            if (t.kind == 'x') break; // 'q' for quit
            if (t.kind == '=')        // ';' for "print now"
                cout << "=" << val << '\n';
            else
                ts.putback(t);
            val = expression();
        }

        catch (exception& e) {
            cerr << e.what() << '\n';
            //Clear the error state and ignore the rest of the line
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return 0;
}
