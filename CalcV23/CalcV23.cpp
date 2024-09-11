// CalcV23.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Using tokens and functions
// get_token() reads characters from cin and returns them as a Token
// Token is a class with a kind and a value
// kind is an enumerated type: INT, PLUS, MINUS, MULT, DIV, PRINT, END
// expression() reads and evaluates an expression
// term() reads and evaluates a term, deals with *, /, and %
// primary() reads and evaluates a primary, deals with numbers and parentheses, calls expression() recursively and get_token()
// error() is called on bad input

import std;

#include "PPP.h"

using namespace std;
using namespace PPP;


//------------------------------------------------------------------------------

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 

	Token(char ch) :kind(ch), value(0) { }   // make a Token from a char
	Token(char ch, double val) :kind(ch), value(val) { }   // make a Token from a char and a double
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token get();                // get a Token
    void putback(Token t);      // put a token back
private:
    bool full{ false };        // is there a Token in the buffer?
    Token buffer{ '0' };         // here is where putback() stores a Token
};

//------------------------------------------------------------------------------


void Token_stream::putback(Token t)
{
    buffer = t;                 // copy t to buffer
    full = true;                // buffer is now full
};

//------------------------------------------------------------------------------

Token Token_stream::get()
// ex 2 - added '{' & '}'
// ex 3 - added '!'
{
    if (full) {             // do we already have a Token?
        full = false;       // remove Token from buffer
        return buffer;
    }

    char ch;
    cin >> ch;              // note that >> skips whitespace

    switch (ch) {
    case ';':           // for "print"
    case 'q':           // for "quit"
    case '(': case ')': case '{': case '}': case '!':
    case '+': case '-': case '*': case '/':
        return Token{ ch };
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);    // put digit back into input stream
        double val;
        cin >> val;
        return Token{ '8', val };  // let '8' represent a number
    }
    default:
        cerr<<("Bad token");
    }
};

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback()

//------------------------------------------------------------------------------

double expression();  // read and evaluate a Expression

//------------------------------------------------------------------------------

double primary()     // read and evaluate a Primary
{
    Token t = ts.get();   // get the next token from token stream
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();   // get the next token from token stream
        if (t.kind != ')') cerr << ("')' expected");
        return d;
    }
    case '8':            // we use '8' to represent a number
        return t.value;  // return the number's value
    default:
        cerr << ("primary expected");
    }
}

//------------------------------------------------------------------------------
double secondary()
// ex 3 - Add a factorial operator '!'
{
    double left = primary();
    Token t = ts.get();

    while (true) {
        if (t.kind == '!') {
            if (left == 0)
                return 1;

            for (int i = left - 1; i > 0; --i)
                left *= i;

            t = ts.get();
        }
        else {
            ts.putback(t);
            return left;
        }
    }
}

//------------------------------------------------------------------------------

double term()               // deal with * and /
{
    double left = secondary();
    Token t = ts.get();             // get next token from Token_stream

    while (true) {
        switch (t.kind) {
        case '*':
            left *= secondary();
            t = ts.get();
            break;
        case '/':
        {
            double d = secondary();
            if (d == 0) cerr<<("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);      // put t back into the Token_stream
            return left;
        }
    }
}


//------------------------------------------------------------------------------

double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get(); 
    while (true) {
        switch (t.kind) {
        case '+':
            left += term();    // evaluate Term and add
			t = ts.get(); 	// get the next token
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
			t = ts.get(); 	// get the next token
            break;
        default:
			ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}


//------------------------------------------------------------------------------

int main()

try {
	double val = 0;
    while (cin) {
		Token t = ts.get();

		if (t.kind == 'q') break; // 'q' for quit
		if (t.kind == ';')        // ';' for "print now"
			cout << "=" << val << '\n';
		else
			ts.putback(t);
		val = expression();
    }
}
catch (exception& e) {
    cerr << "Exception: " << e.what() << endl;
    return 1;
}
catch (...) {
    cerr << "Unknown Exception \n";
    return 2;
}