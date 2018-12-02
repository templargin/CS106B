#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include "vector.h"
#include "random.h"
#include "map"

using namespace std;
typedef map<string, Vector<char>> myMap;


/** Function prototypes */

void readFile(ifstream &in);
string mostFrequent(ifstream &in, int &occurrences, int order);
myMap markovMap(ifstream &in, int order);
void printVector(Vector<char> &v);
void generateText(string seed, int numberOfChars, myMap &map);


int main() {

/** Getting inputs from client */
    ifstream in;
    readFile(in);
    cout << "What order of Markov model will be used? (numbers from 1 to 10)" << endl;
    int order = getInteger();
    int numberOfChars = 30000; // this number is given in assignment

/** Determine the initial seed */
    int num;
    string seed = mostFrequent(in, num, order);

/** Return to the beginning of the file */
    in.clear();
    in.seekg(0, ios::beg);

/** Building a map of string seeds to vector of chars*/
    myMap map = markovMap(in, order);

/** Generating "random" text based on Markov's model */
    generateText(seed, numberOfChars, map);

    return 0;

}

/** Function descriptions */

void readFile(ifstream &in)
{
    cout << "Please enter filename" << endl;
    while (true)
    {
        string filename = getLine();
        in.open(filename.c_str());
        if (!in.fail()) break;
            cout << "Couldn't read '"<< filename <<  "'. Please try again" << endl;
        in.clear();
    }
}

string mostFrequent(ifstream &in, int &occurrences, int order)
{
    map<string, int> countMap;
    char ch;
    string s;

    while (true)
    {
        in.get(ch);
  //      ch = toLowerCase(ch);
        s += ch;
        if (in.fail()) break;

        if (s.size() == order)
        {
            countMap[s]++;
            s.erase(0,1);
        }
    }

    occurrences = 0;
    string mostFrequent;

    for (map<string, int>::iterator itr = countMap.begin(); itr != countMap.end(); itr++)
    {
        if (itr->second > occurrences)
        {
            mostFrequent = itr->first;
            occurrences = itr->second;
        }
    }

    return mostFrequent;
}

void printVector(Vector<char> &v)
{
    cout << "[";
    for (int i = 0; i < v.size(); i++)
    {
        cout << "'" << v[i] << "' ";
    }
    cout << "]";
}

myMap markovMap(ifstream &in, int order)
{
    myMap markovMap;
    char ch;
    string s;

    while (s.size() != order)
    {
        in.get(ch);
   //     ch = toLowerCase(ch);
        s += ch;
    }

    while(true)
    {
        in.get(ch);
        if (in.fail()) break;

        markovMap[s].add(ch);
        s.erase(0,1);
        s += ch;
    }

    /*
    for (myMap::iterator itr = markovMap.begin(); itr != markovMap.end(); itr++)
    {
        cout << "'" << itr->first << "' - ";
        printVector(itr->second);
        cout << endl;
    }
    */

    return markovMap;
}

void generateText(string seed, int numberOfChars, myMap &map)
{
    string s = seed;
    string currentSeed = seed;
    char nextChar;
    while (s.size() < numberOfChars)
    {
        if (map[currentSeed].size() == 0) break;
        nextChar = map[currentSeed].get(randomInteger(0, map[currentSeed].size() - 1));
        s = s + nextChar;
        currentSeed = currentSeed.erase(0,1) + nextChar;
    }

    cout << s;
}
