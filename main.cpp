#include "output.h"
#include "eventHandler.h"
#include "buttons.h"
#include <conio.h>

/* 
* Main C++ file. All header files are managed through the main() function.
*/

int main(){

    // File objects for managing output printing and determining calculations.
    OUTPUT::output *o = new OUTPUT::output();
    EVENT::eventHandler *e = new EVENT::eventHandler();

    // Initiate calculator print, start user on "OFF" button.
    o->printShell();
    o->newButton('u');

    // Credit to Erik Anderson on Stack Overflow:
    // https://stackoverflow.com/questions/24708700/c-detect-when-user-presses-arrow-key
    int c, ex;

    while(1){

        // Conio getch function gets user input without printing it to the console
        c = _getch();

        // Arrow key characters all start with the character 224.
        if (c == 224){
            switch(ex = _getch()){

                // Up Arrow
                case 72:
                    o->newButton('u');
                    break;
                // Down Arrow
                case 80:
                    o->newButton('d');
                    break;
                // Left Arrow
                case 75:
                    o->newButton('l');
                    break;
                // Right Arrow
                case 77:
                    o->newButton('r');
                    break;
            }
        // Character 13 corresponds to the ENTER key.
        } else if (c == 13){

            // The event handler will return true when the "OFF" key is pressed.
            if (e->buttonPressed(o)) return 1;
        }
    }
}