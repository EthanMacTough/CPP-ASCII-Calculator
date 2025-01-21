#ifndef EVENT
#define EVENT

#include "output.h"
#include "calc.h"

/* 
* The eventHandler header file serves to manage when a button is pressed, 
* give the information to the calc header file, and print the result in the output header file.
*/

class eventHandler{
private:
    
    // Calculator object that will keep track of the numbers and calculations.
    CALC::calculator *c = new CALC::calculator();

public:

    // The only function in the file. Main gives the output object to the function to keep track of the current highlighted button.
    bool buttonPressed(OUTPUT::output *o){

        // The character corresponding to the current button in the buttons header file.
        char pressed = o->buttons->head->n;
        
        // When the character is a digit, the calculator will try to add a new digit to the current number.
        if (pressed >= 0 && pressed <= 9){
            
            c->numButton(pressed);
        }
        // When an operation button is pressed, the calculator will save it for later.
        else if (pressed == '+' || pressed == '-' || pressed == '*' || pressed == '/'){

            c->operationButton(pressed);
        } 
        else {switch(pressed){

            // Square button
            case '^':
                c->square();
                break;
            // Square Root button
            case '_':

                // When the current number is negative, and error is thrown.
                if (!c->sqrt()) {
                    o->printERR();
                    c = new CALC::calculator();
                    return false;
                }
                break;
            // Negative Sign button
            case 'n':
                c->negButton();
                break;
            // Equal Sign button
            case '=':
                c->equalButton();
                break;

            // Backspace button
            case '<':
                c->backButton();
                break;
            // Decimal Point butotn
            case '.':
                c->decButton();
                break;
            // Clear button
            case 'C':
                o->printShell();
                o->newButton('u');
                o->newButton('d');

                c = new CALC::calculator();
                break;
            // Off button. Returns true so that the main function can stop the process.
            case 'O':
                return true;
                break;
        }}
        
        // Print the resulting current number
        o->printNum(c->numList, c->decIndex, c->sign);
        return false;
    }
};

#endif