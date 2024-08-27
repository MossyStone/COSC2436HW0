//Madison Reynolds
//Cosc2346
//HW0
//Goal: Find the frequency of letters from inputted string
//inputs string
//outputs word frequency of letters with that aren't zero

//start of set up
#include <iostream>
#include <fstream>
#include <cctype> 
#include "ArgumentManager.h"

using namespace std;

int lettersCount[26] = {0};
char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I','J',
   'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
   'U', 'V', 'W', 'X', 'Y', 'Z'};
//end of set up

//start of arrayPrinterSentenceOrder
//Prints the array in the word order that appears w/out duplicates
void arrayPrinterSentenceOrder(char lettersRead[], int size, ofstream &outputfile){
    //remove duplicated letters
    char temp[size];
    int tempIndex = 0;

    for(int i = 0; i < size; i++){
        bool isDup = false;
        char upperChar = toupper(lettersRead[i]);

        for(int j = 0; j < tempIndex; j++){
            if(temp[j] == upperChar){
                isDup = true;
                break;
            }
        }

        if(!isDup){
            temp[tempIndex] = upperChar;
            tempIndex++;
        }
    }

    // Print in the order of appearance
    for(int i = 0; i < tempIndex; i++){
        for(int j = 0; j < 26; j++){
            if(temp[i] == alphabet[j]){
                if(lettersCount[j] != 0){
                    outputfile << alphabet[j] << " " << lettersCount[j] << endl;
                }
            }
        }
    }
} //end of arrayPrinterSentenceOrder

//start of printArray
//Takes the 2D array and prints out the letter and number if
//the arrays number val is greater than 0
void printArray(ofstream &outputfile){
    for(int i = 0; i < 26; i++){
        //this way returns the letter frequency in alpha order
        if(lettersCount[i] > 0){
            outputfile << alphabet[i] << " " << lettersCount[i] << endl;
        }
    }
} //end of printArray

//start of arrayCounter
//input: takes the read string
//output: nothing - turns our empty array into a filled array
//Also makes our 2D arry stored to print
void arrayCounter(const string &readInput, ofstream &outputfile){
    //create the coutning array
    //Will convert to 2D array letter - set it up like a dict
    char lettersRead[readInput.size()];

    for(size_t i = 0; i < readInput.size(); i++){
        char currentLetter = tolower(readInput[i]); //separate the string

        //sanity check
        //make sure the letter is a letter
        //REMEMBER: ASCII values for lowercase letters are 97-122
        if(currentLetter >= 'a' && currentLetter <= 'z'){
            //yay you found a letter!
            lettersRead[i] = currentLetter;

            lettersCount[currentLetter - 'a']++; //add one to the letter
        }
    }

    arrayPrinterSentenceOrder(lettersRead, readInput.size(), outputfile);
} //end of arrayCounter

//start of main
int main(int argc, char* argv[]) {

    ArgumentManager am(argc, argv);

    string input = am.get("input");
    string output = am.get("output");

    ifstream inputfile(input); //reads the file given via command
    ofstream outputfile(output); //writes to the file given via command

    // Check if the input file opens correctly
    if (!inputfile.is_open()) {
        cerr << "Failed to open input file: " << input << endl;
        return 1;
    }

    // Check if the output file opens correctly
    if (!outputfile.is_open()) {
        cerr << "Failed to open output file: " << output << endl;
        return 1;
    }

    string readInput;
    getline(inputfile, readInput); //push the read line into the string

    arrayCounter(readInput, outputfile); //calls the function to count the letters

    inputfile.close(); //close the input file
    outputfile.close(); //close the output file

    return 0;
} //end of main
