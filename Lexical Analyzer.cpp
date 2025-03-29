#include <iostream>
#include <cctype>
#include <string>
using namespace std;

#define LETTER 112
#define DIGIT 20
#define UNKNOWN 1000
#define END_OF_FILE -1
#define INT_LIT 44
#define IDENT 143
#define ASSIGN_OP 110
#define ADD_OP 77
#define SUB_OP 99
#define MULT_OP 221
#define DIV_OP 431
#define LEFT_PAREN 600
#define RIGHT_PAREN 1079

int charClass;
string lexeme;
char nextChar;
int token;
int nextToken;
string input;
int inputIndex = 0;

void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);

void addChar()
{
    lexeme += nextChar;
}

void getChar()
{
    if (inputIndex < input.length())
    {
        nextChar = input[inputIndex++];
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else
    {
        charClass = END_OF_FILE;
    }
}

void getNonBlank()
{
    while (isspace(nextChar))
        getChar();
}

int lookup(char ch)
{
    switch (ch)
    {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    case '=':
        addChar();
        nextToken = ASSIGN_OP;
        break;
    default:
        addChar();
        nextToken = END_OF_FILE;
        break;
    }
    return nextToken;
}

int lex()
{
    lexeme.clear();
    getNonBlank();
    switch (charClass)
    {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT)
        {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT)
        {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;
    case END_OF_FILE:
        nextToken = END_OF_FILE;
        lexeme = "EOF";
        break;
    }
    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}

int main()
{
    cout << "Enter Your expression: ";
    getline(cin, input);
    inputIndex = 0;
    getChar();
    do
    {
        lex();
    } while (nextToken != END_OF_FILE);
}