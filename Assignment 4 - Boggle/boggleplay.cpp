#include "lexicon.h"
#include "bogglegui.h"
#include "Boggle.h"
#include "simpio.h"

void playOneGame(Lexicon& dictionary) {

/**  Initializing the constuctor for Boggle game;
 *   shuffling the board;
 *   drawing the board;
 */

    Boggle b(dictionary, "");
    BoggleGUI::setAnimationDelay(100);
    string status = "It's your turn!";
    BoggleGUI::setStatusMessage(status);

/** Human turn */

    while(true){
        clearConsole();
        cout << status << endl;
        cout << "Your words (" << b.getWordsGuessed() << "): " << b.wordsGuessed() << endl;
        cout << "Your score: " << b.getScoreHuman() << endl;
        cout << "Type a word (or Enter to stop):" << endl;
        string word = getLine();
        if (word == "") break;
        word = toUpperCase(word);
        if ((!b.checkWord(word)) || (!b.humanWordSearch(word)))
            status = "You must enter an unfound 4+ letter word from the dictionary";
        else{
            status = "You found a new word : " + word;
            BoggleGUI::recordWord(word, BoggleGUI::HUMAN);
            BoggleGUI::setScore(b.getScoreHuman(), BoggleGUI::HUMAN);
        }
        BoggleGUI::setStatusMessage(status);
    }

/** Computer turn */

    clearConsole();
    cout << b.computerWordSearch() << endl;
    BoggleGUI::setScore(b.numberOfComputerWords(), BoggleGUI::COMPUTER);
    BoggleGUI::setStatusMessage("That was too easy, you uneducated barbarian!");

}
