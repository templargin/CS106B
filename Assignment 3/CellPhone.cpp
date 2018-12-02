#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include "lexicon.h"

using namespace std;

string button(char ch)
{
    switch(ch)
    {
    case '0': return "0";
    case '1': return "1";
    case '2': return "abc";
    case '3': return "def";
    case '4': return "ghi";
    case '5': return "jkl";
    case '6': return "mno";
    case '7': return "pqrs";
    case '8': return "tuv";
    case '9': return "wxyz";
    default: return "Invalid number";
    }
}

void extendWord(string soFar, Lexicon &lex)
{
    if (lex.containsPrefix(soFar))
    {
        if (lex.contains(soFar))
        {
            cout << soFar << endl;
        }

        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            extendWord(soFar + ch, lex);
        }
    }
}

void listCompletionsHelp(string soFar, string digits, Lexicon & lex)
{
    if (digits == "")
    {
        extendWord(soFar, lex);
        // cout << soFar << endl;
    }
    else
    {
        string letters = button(digits[0]);
        for (int i = 0; i < letters.length(); i++)
        {
            listCompletionsHelp(soFar + letters[i], digits.substr(1), lex);
        }
    }
}

void listCompletions(string digits, Lexicon & lex)
{
    listCompletionsHelp("", digits, lex);
}

void listPerm(string soFar, string str)
{
    if (str == "") cout << soFar << endl;
    else
    {
        string letters = button(str[0]);
        for (int i = 0; i < letters.length(); i++)
        {
            listPerm(soFar + letters[i], str.substr(1));
        }
    }
}


int main()
{

    Lexicon lex("englishwords.txt");

    listCompletions("72547", lex);


    return 0;
}




