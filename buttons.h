#ifndef ADJ
#define ADJ

#include <iostream>
using namespace std;

/* 
* The buttons header file keeps information on the buttons of the calculator. An adjacency list keeps track of
* the highlighted button and what is next to it.
*/

class adjList{
private:

// String arrays corresponding to all buttons on the calculator.
string squarP[4] = {" _______ ", "| squar |", "|_______|", ""};
string sqrtP[4]  = {" _______ ", "| sqrt  |", "|_______|", ""};
string offP[4]   = {" ________ ", "|  OFF   |", "|________|", ""};

string plusP[4]  = {" _______ ", "|       |", "|   +   |", "|_______|"};
string minusP[4] = {" _______ ", "|       |", "|   -   |", "|_______|"};
string multP[4]  = {" _______ ", "|       |", "|   *   |", "|_______|"};
string divP[4]   = {" _______ ", "|       |", "|   /   |", "|_______|"};
string eqP[4]    = {" _______ ", "|       |", "|   =   |", "|_______|"};

string oneP[4]   = {" _______ ", "|       |", "|   1   |", "|_______|"};
string twoP[4]   = {" _______ ", "|       |", "|   2   |", "|_______|"};
string threeP[4] = {" _______ ", "|       |", "|   3   |", "|_______|"};
string fourP[4]  = {" _______ ", "|       |", "|   4   |", "|_______|"};
string fiveP[4]  = {" _______ ", "|       |", "|   5   |", "|_______|"};
string sixP[4]   = {" _______ ", "|       |", "|   6   |", "|_______|"};
string sevenP[4] = {" _______ ", "|       |", "|   7   |", "|_______|"};
string eightP[4] = {" _______ ", "|       |", "|   8   |", "|_______|"};
string nineP[4]  = {" _______ ", "|       |", "|   9   |", "|_______|"};
string zeroP[4]  = {" _______ ", "|       |", "|   0   |", "|_______|"};

string backP[4]  = {" ________ ", "|        |", "|   <-   |", "|________|"};
string decP[4]   = {" _______ ", "|       |", "|   .   |", "|_______|"};
string clearP[4] = {" ________ ", "|        |", "|   C    |", "|________|"};
string negP[4]   = {" ________ ", "|        |", "|  neg   |", "|________|"};

    // The private button class keeps track of a button's variables and neighbors in the adjacency list.
    class button{
    public:

        // The button's character is used in the eventHandler header class.
        char n;

        // The button's (x, y) coordinates and string array are used in the output header class.
        int x;
        int y;
        string *print;

        // The button's directional neighbors for when an arrow key is pressed.
        button *up;
        button *down;
        button *left;
        button *right;

        // Button constructor class to set variables.
        button(char name, int x, int y, string *p){
            n = name;
            this->x = x;
            this->y = y;
            print = p;
        }

        // Secondary class acts as a constructor for the button's adjacencies.
        void setAdj(button *up, button *down,
                    button *left, button *right){
            
            this->up = up;
            this->down = down;
            this->left = left;
            this->right = right;
        }
    };

// Instantiation of all buttons on the calculator.
button *squar = new button('^', 5, 24, squarP);
button *sqrt = new button('_', 14, 24, sqrtP);
button *off = new button('O', 41, 24, offP);

button *plus = new button('+', 32, 20, plusP);
button *minus = new button('-', 32, 16, minusP);
button *mult = new button('*', 32, 12, multP);
button *div = new button('/', 32, 8, divP);
button *eq = new button('=', 23, 8, eqP);

button *one = new button(1, 5, 12, oneP);
button *two = new button(2, 14, 12, twoP);
button *three = new button(3, 23, 12, threeP);
button *four = new button(4, 5, 16, fourP);
button *five = new button(5, 14, 16, fiveP);
button *six = new button(6, 23, 16, sixP);
button *seven = new button(7, 5, 20, sevenP);
button *eight = new button(8, 14, 20, eightP);
button *nine = new button(9, 23, 20, nineP);
button *zero = new button(0, 14, 8, zeroP);

button *back = new button('<', 41, 12, backP);
button *dec = new button('.', 5, 8, decP);
button *clear = new button('C', 41, 8, clearP);
button *neg = new button('n', 41, 20, negP);

public:

    // Public button object that keeps track of the current highlighted button.
    button *head;

    // Constructor class to set all initial variables.
    adjList(){

        // Set adjacencies of all button variables.
        squar->setAdj(dec, seven, off, sqrt);
        sqrt->setAdj(zero, eight, squar, off);
        neg->setAdj(off, back, plus, seven);

        plus->setAdj(div, minus, nine, neg);
        minus->setAdj(plus, mult, six, four);
        mult->setAdj(minus, div, three, back);
        div->setAdj(mult, plus, eq, clear);
        eq->setAdj(three, nine, zero, div);

        one->setAdj(four, dec, back, two);
        two->setAdj(five, zero, one, three);
        three->setAdj(six, eq, two, mult);
        four->setAdj(seven, one, minus, five);
        five->setAdj(eight, two, four, six);
        six->setAdj(nine, three, five, minus);
        seven->setAdj(squar, four, neg, eight);
        eight->setAdj(sqrt, five, seven, nine);
        nine->setAdj(eq, six, eight, plus);
        zero->setAdj(two, sqrt, dec, eq);

        back->setAdj(neg, clear, mult, one);
        dec->setAdj(one, squar, clear, zero);
        clear->setAdj(back, off, div, dec);
        off->setAdj(clear, neg, sqrt, squar);

        // The starting node is supposed to be "OFF", so we start on the button below and move it up so that it can update the button's color.
        head = neg;
    }

    // Function for when an arrow key is pressed.
    void newCoords(char direction){

        // Update the head based on the direction pressed.
        switch (direction){

            case 'u':
                head = head->up;
                break;
            case 'd':
                head = head->down;
                break;
            case 'l':
                head = head->left;
                break;
            case 'r':
                head = head->right;
                break;
        }
    }
};

#endif