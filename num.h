#ifndef NUM
#define NUM

#include <iostream>
#include <stack>
#include <list>
using namespace std;

/* 
* The num header file keeps track of the strings that are printed for each 
* number in the display, and returns the ones needed in a stack.
*/

class num{
    
private:

    // Arrays of strings correspond to rows of 8-digit displays for each number.
    string ZERO[5]  = {" ____ ", "|    |", "|    |", "|    |", "|____|"};
    string ONE[5]   = {"      ", "     |", "     |", "     |", "     |"};
    string TWO[5]   = {" ____ ", "     |", " ____|", "|     ", "|____ "};
    string THREE[5] = {" ____ ", "     |", " ____|", "     |", " ____|"};
    string FOUR[5]  = {"      ", "|    |", "|____|", "     |", "     |"};
    string FIVE[5]  = {" ____ ", "|     ", "|____ ", "     |", " ____|"};
    string SIX[5]   = {" ____ ", "|     ", "|____ ", "|    |", "|____|"};
    string SEVEN[5] = {" ____ ", "     |", "     |", "     |", "     |"};
    string EIGHT[5] = {" ____ ", "|    |", "|____|", "|    |", "|____|"};
    string NINE[5]  = {" ____ ", "|    |", "|____|", "     |", " ____|"};

    // String array of an entirely blank number.
    string BLANK[5] = {"      ", "      ", "      ", "      ", "      "};

    // Array is set up so that the number needed can be accessed through it.
    string *NUMSTRINGS[10] = {ZERO, ONE, TWO, THREE, FOUR,
                             FIVE, SIX, SEVEN, EIGHT, NINE};    

public:

    // Function to get a stack of string arrays corresponding to the integers we want to print out.
    stack<string*> getNumArray(list<int> numList){

        stack<string*> ret;

        // The stack is initialized with blanks.
        for (int i = 0; i < 7; ++i){
            ret.push(BLANK);
        }

        // Because the calculator will print numbers right to left, we use a stack to keep track of the strings.
        for (int number: numList){

            ret.push(NUMSTRINGS[number]);
        }
        return ret;
    }
};

#endif