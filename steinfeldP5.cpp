/*
 * Sam Steinfeld
 *
 * File   : p5.cpp
 * Purpose: To display a list of unique words from a text file in alphabetical order
            with the number of times that words was used, and then display the words
            used once below that. Also to display words in descending order of times
            used in between two values the user inputs.
 * Input  : A valid  name of a file that contains arbitrary text, ending with "DONE".  Valid
            punctuation includes the set {'.', ',', '!', '?'}. Additionally, the low and high
            count the user wants the number of occurrences to be in between.
 * Output : An aligned table showing each unique word and its frequency, in alphabetical order followed by
            a list of word in order from highest to lowest frequency. The number of occurrences will
            be in between the high and low counts that the user inputs. Then, words that appear
            once are displayed, 10 per line. Finally, the words in descending order of times used
            with the maximum and minimum value determined by the user.
 */
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAXLINE = 10; // maximum words displayed per line

struct node{
    string word; //word in the node
    int count; //number of times "word" is used
    node *next; //pointer that points to the following node
public:
    node() {}; //default constructor
    node (string str2, int two, node* nodeType){word = str2; count = two; next = nodeType;};
    //constructor with parameters
};
class trout {
    int wordcount; //keeps count of the number of words in the linked list
    node *head; //points to the first node
    node *newitem; //creates a new node
    node *current; //points to the current node
    node *nextnode; //points to the next node
    node *loop; //point to current node in loop for output
    ifstream inFP; //input file pointer
    string text; // contains the text of the text file
public:
    void readText (string); //reads data from text file
    void displayStats (); //displays results in alphabetical order
    void displayStats (int, int); //displays results in descending count order
};

int main () {
    trout myList; //instance of the trout class
    string fileName; //user's input file name
    int low, high; //the max and min values the counts should be in between
    cout << "Enter file name: ";
    cin >> fileName;
    myList.readText (fileName);
    myList.displayStats();
    cout << "Enter low count: ";
    cin >> low;
    cout << "Enter high count: ";
    cin >> high;
    myList.displayStats(low, high);
    return 0;
}
void trout :: readText (string fname)
/*
*   Read the input text and store all of the unique words.
*   Precondition : fname is a valid string
*   Postcondition: word contains each of the unique words &&
*                   count contains each of the frequencies of the words
*/

{
    bool front; //checks to see if list is at the front(head)
    bool found; //checks to see if the word count is at 0

    inFP.open (fname.c_str());

    if (! inFP) {
      cout << "Error - file " << fname << " not found!" << endl;
   }
    else{
        head = new node("", 0, NULL);
        inFP >> text;
        while (text != "DONE") {
            newitem = new node;
            for (string::iterator i = text.begin(); i != text.end(); i++) {
                *i = tolower(*i);
            }
            int index = text.find(',');//looks for any commas
            if (index != -1){
                text.erase(index, index + 1);
            }
            int index2 = text.find('!');//looks for any exclamation points
            if (index2 != -1){
                text.erase(index2, index2 + 1);
            }
            int index3 = text.find('?');//looks for question marks
            if (index3 != -1){
            text.erase(index3, index3 + 1);
            }
            int index4 = text.find('.');//looks for periods
            if (index4 != -1){
                text.erase(index4, index4 + 1);
            }
            newitem->word = text;
            current = NULL;
            nextnode = head;
            front = true;
            found = false;
            while((nextnode->next != NULL) &&(newitem->word >= nextnode->word)&&(!found))
                {
                    front = false;
                    if(newitem->word == nextnode->word)
                    {
                        found = true;
                    }
                    else
                    {
                        current = nextnode;
                        nextnode = nextnode->next;
                    }
                }
                if(found == false)
                {
                    if(front)
                    {
                        newitem->next = head;
                        head = newitem;
                        newitem->count=1;
                    }
                    else{
                        current->next = newitem;
                        newitem-> next = nextnode;
                        newitem->count = 1;
                    }
                }
                else{
                    nextnode->count++;
                }
            inFP >> text;
            }
        }
}
void trout :: displayStats ()
/*
 * Displays words in text file with their counts in alphabetical order followed by words used only once.
 * Precondition : word contains each the unique words in the file &&
 *                count contains each of the frequencies of the words &&
 *                wordcount == number of unique words
 * Postcondition: displays an aligned chart of words and frequencies &&
 *                words are sorted alphabetically &&
 *                those words that appear just once are displayed 10/line
 */
{
    if (inFP){
        cout << endl << "Word" <<  setw(16) << "Count" << endl;
        cout << "====================" << endl;
        loop = head;

        if (loop->count >0){
            while(loop->next != NULL){
                if ((loop -> count) > 1){
                    int wordlen = (loop->word).size();//length of character in word
                    cout << loop->word << setw(20 - wordlen) << loop->count << endl;
                }
                loop = loop -> next;
            }
            loop = head;

            cout << endl << "Words with count = 1" << endl;
            cout << "====================" << endl;

            int singlecount = 0;//counts number of words used once
            while(loop->next != NULL){
                if ((loop -> count) == 1){
                    cout << loop->word << " ";
                    singlecount++;
                    if (singlecount % MAXLINE == 0){
                        cout << endl;
                        singlecount = 0;
                    }
                }
                loop = loop -> next;
            }
            cout << endl << endl;
        }
    }
}
void trout :: displayStats (int low, int high)
/*
 * Displays words in descending order based on their number of occurrences.
 * Precondition : word contains all the unique words in the file &&
 *                count contains all the frequencies of the words &&
 *                wordcount == number of unique words
 * Postcondition: displays an aligned chart of words and frequencies &&
 *                words are sorted in descending order
 */
{
    if (inFP){
        cout << "Word" <<  setw(16) << "Count" << endl;
        cout << "====================" << endl;
        loop = head;

        while(loop->next != NULL){
                if ((loop -> count) >= low && (loop -> count) <= high){
                    int wordlen2 = (loop->word).size();//length of characters in word
                    cout << loop->word << setw(20 - wordlen2) << loop->count << endl;
                }
                loop = loop -> next;
            }
            loop = head;
    }
}
