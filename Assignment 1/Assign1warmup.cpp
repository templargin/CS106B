#include <iostream>
#include "simpio.h"
#include "console.h"
#include <fstream>
#include "vector.h"

using namespace std;

/* Function prototypes */

bool isPerfect(int n);
void chanceOfInvalid();
string removeChar(string word, char toRemove);
void soundex();
void histogram();
void chaosGame();

int main ()
{

    chaosGame();
	return 0;
}


void chaosGame()
{
    GWindow gw(800, 600);

    Vector <double> x;
    Vector <double> y;
   // Vector <GOval*> circle;
    int i = 0;
    int random;

    struct point
    {
        double x;
        double y;
    };

    while(i < 3)
    {
        GMouseEvent e = waitForEvent(MOUSE_EVENT);

        if (e.getEventType() == MOUSE_CLICKED)
        {
            x.add(e.getX());
            y.add(e.getY());
            i++;
        }
    }

    GLine *line1 = new GLine(x[0], y[0], x[1], y[1]);
    GLine *line2= new GLine(x[1], y[1], x[2], y[2]);
    GLine *line3 = new GLine(x[2], y[2], x[0], y[0]);
    gw.add(line1);
    gw.add(line2);
    gw.add(line3);


    random = randomInteger(0, 2);

    point currentPoint;
    point floating;
    currentPoint.x = x[random];
    currentPoint.y = y[random];


    while (true)
    {
        GOval *circle = new GOval(currentPoint.x - 1.5, currentPoint.y - 1.5, 3, 3);
        circle->setFilled(true);
        gw.add(circle);

        random = randomInteger(0, 2);
        floating.x = (x[random] + currentPoint.x)/2;
        floating.y = (y[random] + currentPoint.y)/2;

      //  pause(3);

        GOval *circle2 = new GOval(floating.x - 1.5, floating.y - 1.5, 3, 3);
        circle2->setFilled(true);
        gw.add(circle2);

        currentPoint = floating;

      //  pause(3);

    }
}



string removeChar(string word, char toRemove)
{
    string result;
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] != toRemove)
            result += word[i];
    }
    return result;
}

void soundex()
{

    while (true)
    {
        cout << "Enter surname (RETURN to quit): ";
        string name = getLine();
        if (name == "") break;

        name = toUpperCase(name);

         char letter;
         int code;
         int currentCode = -1;
         string result;

         for (int i = 1; i < name.length(); i++)
         {
            letter = name[i];
            switch (letter)
                 {
                    case 'A' : code = 0; break;
                    case 'E' : code = 0; break;
                    case 'I' : code = 0; break;
                    case 'O' : code = 0; break;
                    case 'U' : code = 0; break;
                    case 'H' : code = 0; break;
                    case 'W' : code = 0; break;
                    case 'Y' : code = 0; break;
                         case 'B' : code = 1; break;
                         case 'F' : code = 1; break;
                         case 'P' : code = 1; break;
                         case 'V' : code = 1; break;
                     case 'C' : code = 2; break;
                     case 'G' : code = 2; break;
                     case 'J' : code = 2; break;
                     case 'K' : code = 2; break;
                     case 'Q' : code = 2; break;
                     case 'S' : code = 2; break;
                     case 'X' : code = 2; break;
                     case 'Z' : code = 2; break;
                         case 'D' : code = 3; break;
                         case 'T' : code = 3; break;
                     case 'M' : code = 4; break;
                     case 'N' : code = 4; break;
                         case 'L' : code = 5; break;
                     case 'R' : code = 6; break;
                 }

            if (currentCode != code)
                result = result + integerToString(code);

            currentCode = code;
         }

         result = name[0] + removeChar(result, '0');

         if (result.length() == 3) result += '0';
         if (result.length() == 2) result = result + '0' + '0' ;
         if (result.length() == 1) result = result + '0' + '0' + '0';

         cout << "Soundex code for " << name << " is " << result << endl;
    }

}

bool isPerfect(int n)
{
    int sum = 0;
    for (int i = 1; i < n; i++)
    {
        if (n % i == 0) sum += i;
    }
    return (n == sum);
}

void chanceOfInvalid()
{
    cout << "Enter number of voters:";
    int numberVoters = getInteger();
    cout << "Enter percentage spread between candidates:";
    double spread = getReal();
    cout << "Enter voting error percentage:";
    double error = getReal();

    int voterA = int(numberVoters * (0.5 + spread));
    int voterB = numberVoters - voterA;
    int invalid = 0;

    for (int j = 0; j < 500; j++)
    {
        int simA = 0;
        int simB = 0;
        for (int i = 1; i <= voterA; i++)
        {
            if(!randomChance(0.08)) simA ++;
        }

        for (int i = 1; i <= voterB; i++)
        {
            if(!randomChance(error)) simB ++;
        }

        int voterAsim = simA + (voterB - simB);
        int voterBsim = simB + (voterA - simA);

        if (!(voterAsim > voterBsim)) invalid++;
    }

    cout << "Chance of an invalid election result after 500 trials = " << double(invalid) / 500 * 100 << "%" << endl;
}

void histogram()
{
    Vector<string> scores;
    for (int i = 0; i < 10; i++)
    {
        scores.add("");
    }

    ifstream in;
    cout << "Please enter filename" << endl;
    while (true)
    {
        string filename = getLine();
        in.open(filename.c_str());
        if (!in.fail()) break;
            cout << "Couldn't read '"<< filename <<  "'. Please try again" << endl;
        in.clear();
    }

    while (true)
    {
        string s;
        getline(in, s);
        if (in.fail()) break;

        int number = stringToInteger(s) / 10;

        if (scores[number] != "") scores[number] = scores[number] + 'X';
        else scores[number] = "X";

    }

    for (int i = 0; i < scores.size(); i++)
    {
        cout << i << ": " << scores.get(i) << endl;
    }
}
