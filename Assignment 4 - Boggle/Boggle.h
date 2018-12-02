#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"

using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();
    friend ostream& operator<<(ostream& out, Boggle& boggle);

    void drawBoard();
    int getWordsGuessed();
    int numberOfComputerWords();
    Set<string> wordsGuessed();


private:
    void setRandomBoard();
    void setUserBoard();
    bool isMarked(int row, int col, Grid<bool> &logicBoard);
    void markCube(int row, int col, Grid<bool> &logicBoard);
    void unMarkCube(int row, int col, Grid<bool> &logicBoard);
    void unMarkBoard(Grid<bool> &board);
    bool locationOnGrid(int row, int col, Grid<char> & myBoard);
    bool searchWordHuman(int row, int col, string soFar, string word, Grid<char> &board, Grid<bool> &logicBoard);
    void shuffleArray(string array[], int length);
    bool humanWordSearchHelper(string word);
    void searchWordComputer(int row, int col, string soFar, Grid<char> &board, Grid<bool> &logicBoard);
    Set<string> wordsHuman;
    Set<string> wordsComputer;
    Lexicon dictionaryLocal;

};

#endif // _boggle_h
