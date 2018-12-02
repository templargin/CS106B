#include "Boggle.h"
#include "bogglegui.h"

/** Constants */
const int ROWS = 4;
const int COLS = 4;

/** Instance Variables */
Grid<char> board(ROWS, COLS);
Grid<bool> markedBoard(ROWS, COLS);


// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

static string myCubes = "ABCDCFLHIDKAEEDW";

/** Member functions bodies */
Boggle::Boggle(Lexicon& dictionary, string boardText) {
    Boggle::dictionaryLocal = dictionary;
    if (boardText == "") setRandomBoard();
    else setUserBoard();
    drawBoard();
}

char Boggle::getLetter(int row, int col) {  
    return board.get(row, col);
}

bool Boggle::checkWord(string word) {
    return (Boggle::dictionaryLocal.contains(word) &&
            word.length() > 3 &&
            !Boggle::wordsHuman.contains(word));
    return false;
}

bool Boggle::humanWordSearch(string word) {
    unMarkBoard(markedBoard);
    BoggleGUI::clearHighlighting();
    for(int row = 0; row < board.numRows(); row++)
    {
        for(int col = 0; col < board.numCols(); col++)
            {
                if(searchWordHuman(row, col, "", word, board, markedBoard))
                    return true;
                unMarkBoard(markedBoard);
            }
    }
    return false;
}

int Boggle::getScoreHuman() {
    return Boggle::wordsHuman.size();
}

Set<string> Boggle::computerWordSearch() {
    unMarkBoard(markedBoard);
    BoggleGUI::clearHighlighting();

    // go through every letter on the grid and see
    // how many words can be formed with each letter
    for(int row = 0; row < board.numRows(); row++)
    {
        for(int col = 0; col < board.numCols(); col++)
            {
                searchWordComputer(row, col, "", board, markedBoard);
                unMarkBoard(markedBoard);
            }
    }
    return Boggle::wordsComputer;
}

void Boggle::searchWordComputer(int row, int col, string soFar, Grid<char> &board, Grid<bool> &logicBoard){
    if (Boggle::dictionaryLocal.containsPrefix(soFar)){
        if(Boggle::dictionaryLocal.contains(soFar)
                && soFar.length() > 3
                && !Boggle::wordsHuman.contains(soFar)
                && !Boggle::wordsComputer.contains(soFar)){
            Boggle::wordsComputer.add(soFar);
            BoggleGUI::recordWord(soFar, BoggleGUI::COMPUTER);
        }

        char picked;
        if (!isMarked(row, col, logicBoard)){
            picked = board.get(row, col);
            markCube(row, col, logicBoard);
        }

        // check all the neighbors of picked letter
        for(int rowRound = -1; rowRound <= 1; rowRound++)
        {
            for(int colRound = -1; colRound <= 1; colRound++)
            {
                if((locationOnGrid(rowRound + row, colRound + col, board)) && (!isMarked(rowRound + row, colRound + col, logicBoard))){
                    (searchWordComputer(rowRound + row, colRound + col, soFar + picked, board, logicBoard));
                }
            }
        }
    }
    unMarkCube(row, col, logicBoard);
}



int Boggle::getScoreComputer() {
    // TODO: implement
    return 0;   // remove this
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}

void Boggle::drawBoard(){
    BoggleGUI::initialize(ROWS, COLS);
    for (int rows = 0; rows < ROWS; rows++)
    {
        for (int cols = 0; cols < COLS; cols++)
        {
            BoggleGUI::labelCube(rows, cols, board.get(rows, cols), 0);
        }
    }
}

void Boggle::setRandomBoard(){
    shuffleArray(CUBES, ROWS * COLS);
    for (int rows = 0; rows < ROWS; rows++)
    {
        for (int cols = 0; cols < COLS; cols++)
        {
            board.set(rows, cols, CUBES[rows*4 + cols%4][randomInteger(0,5)]);
        }
    }
}

void Boggle::setUserBoard(){
    for (int rows = 0; rows < ROWS; rows++)
    {
        for (int cols = 0; cols < COLS; cols++)
        {
            board.set(rows, cols, myCubes[rows*4 + cols%4]);
        }
    }
}

void Boggle::shuffleArray(string array[], int length) {
    for (int i = 0; i < length; i++) {
        int j = randomInteger(i, length - 1);
        if (i != j) {
            string temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}

bool Boggle::locationOnGrid(int row, int col, Grid<char> & myBoard)
{
    return row >= 0 && col >= 0 && row < myBoard.numRows()
    && col < myBoard.numCols();
}

bool Boggle::isMarked(int row, int col, Grid<bool> &logicBoard){
    return logicBoard.get(row, col);
}

void Boggle::markCube(int row, int col, Grid<bool> &logicBoard){
    logicBoard.set(row, col, true);
}

void Boggle::unMarkCube(int row, int col, Grid<bool> &logicBoard){
    logicBoard.set(row, col, false);
}

void Boggle::unMarkBoard(Grid<bool> &board){
    for(int row = 0; row < board.numRows(); row++)
    {
        for(int col = 0; col < board.numCols();col++)
            {
                board.set(row, col, false);
            }
    }
}

bool Boggle::searchWordHuman(int row, int col, string soFar, string word, Grid<char> &board, Grid<bool> &logicBoard){
    if (word == ""){
        Boggle::wordsHuman.add(soFar);
        return true;
    }
    char picked;
    if (!isMarked(row, col, logicBoard)){
        picked = board.get(row, col);
        markCube(row, col, logicBoard);
        BoggleGUI::setHighlighted(row, col, 1);
    }

    if (picked == word[0]){
        for(int rowRound = -1; rowRound <= 1; rowRound++)
        {
            for(int colRound = -1; colRound <= 1; colRound++)
            {
                if((locationOnGrid(rowRound + row, colRound + col, board)) && (!isMarked(rowRound + row, colRound + col, logicBoard))){
                    if (searchWordHuman(rowRound + row, colRound + col, soFar + picked, word.substr(1), board, logicBoard))
                        return true;
                }
            }
        }
    }
    unMarkCube(row, col, logicBoard);
    BoggleGUI::setHighlighted(row, col, 0);

    return false;
}


int Boggle::getWordsGuessed(){
    return Boggle::wordsHuman.size();
}

Set<string> Boggle::wordsGuessed(){
    return Boggle::wordsHuman;
}

int Boggle::numberOfComputerWords(){
    return Boggle::wordsComputer.size();
}



