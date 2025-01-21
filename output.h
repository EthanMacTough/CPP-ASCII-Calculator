#ifndef OUTPUT
#define OUTPUT

#include "num.h"
#include "buttons.h"
#include <iostream>
#include <stdlib.h>
#include <list>
using namespace std;

/* 
* The output header file prints out changes in the calculator's buttons and number display.
    * 
    * ANSI Escape Sequences are command strings that can change the way the terminal acts. Here are the ones used in this program:
        \x1b[#A - Move the cursor up # lines.
        \x1b[#B - Move the cursor down # lines.
        \x1b[#C - Move the cursor right # lines.
        \x1b[#D - Move the cursor left # lines.

        \x1b[0m - Reset style and color of text.
        \x1b[?25l - Makes cursor invisible.

    * Source: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797 
    *
*/

class output{
private:
    
    // num.h object to get the stack of strings for display.
    NUM::num *number = new NUM::num();
    
public:

    // Public buttons.h object to keep track of the current highlighted button.
    ADJ::adjList *buttons = new ADJ::adjList();


    // Function to print the starting shell of the calculator.
    void printShell(){

        // Clear console and print the calculator string.
        system("cls");
        cout << " _______________________________________________________ \n"
            << "|                                                       |\n"
            << "|                                                       |\n"
            << "|  ___________________________________________________  |\n"
            << "| |                                                   | |\n"
            << "| |                                             ____  | |\n"
            << "| |                                            |    | | |\n"
            << "| |                                            |    | | |\n"
            << "| |                                            |    | | |\n"
            << "| |                                            |____|.| |\n"
            << "| |___________________________________________________| |\n"
            << "|   _________________________________________________   |\n"
            << "|  |                                                 |  |\n"
            << "|  |  _______  _______                    ________   |  |\n"
            << "|  | | squar || sqrt  |                  |  OFF   |  |  |\n"
            << "|  | |_______||_______|                  |________|  |  |\n"
            << "|  |                                                 |  |\n"
            << "|  |  _______  _______  _______  _______  ________   |  |\n"
            << "|  | |       ||       ||       ||       ||        |  |  |\n"
            << "|  | |   7   ||   8   ||   9   ||   +   ||  neg   |  |  |\n"
            << "|  | |_______||_______||_______||_______||________|  |  |\n"
            << "|  |  _______  _______  _______  _______             |  |\n"
            << "|  | |       ||       ||       ||       |            |  |\n"
            << "|  | |   4   ||   5   ||   6   ||   -   |            |  |\n"
            << "|  | |_______||_______||_______||_______|            |  |\n"
            << "|  |  _______  _______  _______  _______  ________   |  |\n"
            << "|  | |       ||       ||       ||       ||        |  |  |\n"
            << "|  | |   1   ||   2   ||   3   ||   *   ||   <-   |  |  |\n"
            << "|  | |_______||_______||_______||_______||________|  |  |\n"
            << "|  |  _______  _______  _______  _______  ________   |  |\n"
            << "|  | |       ||       ||       ||       ||        |  |  |\n"
            << "|  | |   .   ||   0   ||   =   ||   /   ||   C    |  |  |\n"
            << "|  | |_______||_______||_______||_______||________|  |  |\n"
            << "|  |_________________________________________________|  |\n"
            << "|                                                       |\n"
            << "|_______________________________________________________|\n\n";
    }

    // Function for changing the button head and printing the changes.
    void newButton(char direction){

        // Get the previous button's string array and coordinates.
        string *oldPrint = buttons->head->print;
        int x = buttons->head->x;
        int y = buttons->head->y;

        // Call buttons.h function to update the head.
        buttons->newCoords(direction);

        // Move terminal cursor to the x, y position of the old button. Change the print color to black, make cursor invisible.
        cout << "\x1b[" << x << "C"
             << "\x1b[" << y << "A"
             << "\x1b[?25l\x1b[0m";

        // Print out all four lines of the button's string array.
        for (int i = 0; i < 4; i++){

            cout << oldPrint[i];
            cout << "\x1b[1B\r\x1b[" << x << "C";
        }

        // Move the cursor back to the starting position.
        cout << "\r\x1b[" << (y - 4) << "B";


        // Get the new button's string array and coordinates.
        string *newPrint = buttons->head->print;
        x = buttons->head->x;
        y = buttons->head->y;

        // Move terminal cursor to the x, y position of the new button. Change the print color to red. 
        cout << "\x1b[" << x << "C"
             << "\x1b[" << y << "A"
             << "\x1b[31m";

        // Print out all four lines of the button's string array.
        for (int i = 0; i < 4; i++){

            cout << newPrint[i];
            cout << "\r\x1b[1B\x1b[" << x << "C";
        }

        // Move the cursor back to the starting position. Change the color back to black.
        cout << "\x1b[0m\r\x1b[" << (y - 4) << "B";
    }


    // Function to print the number that should be displayed by the calculator.
    /* 
    * numList - a list of integers that keeps track of the numbers that are to be printed.
    * decIndex - an index to keep track of where the decimal point is to be placed.
    * sign - keeps track of whether the number is negative or not.
    */
    void printNum(list<int> numList, int decIndex, int sign){
        
        // Call num.h function to get the string array stack.
        stack<string*> printStack = number->getNumArray(numList);

        // Loop to print all seven digits.
        for (int i = 0; i < 7; ++i){


            // Move the cursor into the correct x, y position.
            // Reference: y = 32; x = 47 - (7 * i)
            cout << "\x1b[" << (47 - (7 * i)) << "C"
                 << "\x1b[32A";

            // Loop to print all five lines of the number.
            for (int j = 0; j < 5; ++j){

                cout << printStack.top()[j];

                // Print the decimal point at the correct index.
                if (decIndex == i && j == 4){

                    cout << ".";
                } else cout << " ";

                // Move the cursor to the next line.
                cout << "\x1b[1B\r\x1b[" << (47 - (7 * i)) << "C";
            }

            // Pop the current number off to loop the next one. Move the cursor to the starting position.
            printStack.pop();
            cout << "\r\x1b[" << (27) << "B";
        }

        // Print a negative sign if the number is negative.
        if (sign == -1){
            cout << "\x1b[30A| |__";
        } else cout << "\x1b[30A| |  ";
        cout << "\r\x1b[" << (30) << "B";
    }

    // Function for when the square root of a negative number is taken.
    void printERR(){

        system("cls");
        cout << " _______________________________________________________ \n"
            << "|                                                       |\n"
            << "|                                                       |\n"
            << "|  ___________________________________________________  |\n"
            << "| |                                                   | |\n"
            << "| |                                      ____         | |\n"
            << "| |                                     |             | |\n"
            << "| |                                 --  |____ --      | |\n"
            << "| |                                     |             | |\n"
            << "| |                                     |____         | |\n"
            << "| |___________________________________________________| |\n"
            << "|   _________________________________________________   |\n"
            << "|  |                                                 |  |\n"
            << "|  |  _______  _______                    ________   |  |\n"
            << "|  | | squar || sqrt  |                  |  OFF   |  |  |\n"
            << "|  | |_______||_______|                  |________|  |  |\n"
            << "|  |                                                 |  |\n"
            << "|  |  _______  _______  _______  _______  ________   |  |\n"
            << "|  | |       ||       ||       ||       ||        |  |  |\n"
            << "|  | |   7   ||   8   ||   9   ||   +   ||  neg   |  |  |\n"
            << "|  | |_______||_______||_______||_______||________|  |  |\n"
            << "|  |  _______  _______  _______  _______             |  |\n"
            << "|  | |       ||       ||       ||       |            |  |\n"
            << "|  | |   4   ||   5   ||   6   ||   -   |            |  |\n"
            << "|  | |_______||_______||_______||_______|            |  |\n"
            << "|  |  _______  _______  _______  _______  ________   |  |\n"
            << "|  | |       ||       ||       ||       ||        |  |  |\n"
            << "|  | |   1   ||   2   ||   3   ||   *   ||   <-   |  |  |\n"
            << "|  | |_______||_______||_______||_______||________|  |  |\n"
            << "|  |  _______  _______  _______  _______  ________   |  |\n"
            << "|  | |       ||       ||       ||       ||        |  |  |\n"
            << "|  | |   .   ||   0   ||   =   ||   /   ||   C    |  |  |\n"
            << "|  | |_______||_______||_______||_______||________|  |  |\n"
            << "|  |_________________________________________________|  |\n"
            << "|                                                       |\n"
            << "|_______________________________________________________|\n\n";
    }
};

#endif