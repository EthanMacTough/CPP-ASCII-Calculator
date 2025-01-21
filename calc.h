#ifndef CALC
#define CALC

#include "output.h"
#include <stack>
#include <list>

/* 
* The calc header file keeps track of all the calculations of the program. It also holds information on what the output.h file will print.
* Calculations are prone to imprecision at lower decimal places.
*/

class calculator{
private:

    /* 
    * The calculator is centered around num1, num2, and an operation. The two num variables hold floating point values that are combined by 
    * the operation, where the result is stored back into num1. The opIndex variable keeps track of which number is being added to when a button is pressed.
    */
    double num1;
    double num2;

    int opIndex;
    char operation;

    // Special boolean variables that keep track of what has happened last when a button was pressed.
    bool toClear;
    bool eqLast;
    bool numLock;

    // Variable to keep track of whether the decimal point value will move when a number is entered.
    bool decLock;

    // Function to calculate the operation between num1 and num2. Stores the value into num1.
    void calculateOperation(){

        switch (operation){

            case '+':
                num1 = num1 + num2;
                break;
            case '-':
                num1 = num1 - num2;
                break;
            case '*':
                num1 = num1 * num2;
                break;
            case '/':
                // An error is not thrown when x / 0 is calculated. Rather, we are crudely treating the result as inf.
                if (num2 == 0){
                    num1 = 9999999;
                    break;
                }
                num1 = num1 / num2;
                break;
        }
    }

    // Function to update the current number based on what is being printed to the display.
    void updateNum(){

        double temp = 0.0;

        // Each digit in the new number is added through the current list of printable numbers.
        int i = 1;
        for (int num : numList){

            // The new double is created through a left-to-right addition of each digit in the list.
            temp += num * pow(10, numList.size() - i);
            i++;
        }

        // If the sign variable and sign of the number are not consistent, update the number.
        if (sign == -1 && temp >= 0) temp *= -1;

        // Incorporate the index of the decimal value into the number.
        temp /= pow(10, decIndex);

        // Move the new number into the current number being worked on.
        switch (opIndex){

            case 1:
                num1 = temp;
                break;
            case 2:
                num2 = temp;
                break;
        }
    }

    // Function to update the number list based on the calculated number value.
    void updateList(){

        double temp = num1;
        decIndex = 0;

        // Update sign
        if (temp < 0) {
            sign = -1;
            temp *= -1;
        } else sign = 1;

        numList.clear();

        // Special case for the result of 0.0;
        if (temp == 0){

            numList.push_front(0);
            return;
        }

        // Convert numer into a seven-digit value.
        // Keep track of the decimal places.
        while (int(temp) / 1'000'000 == 0 && decIndex != 6){

            temp *= 10;
            decIndex++;
        }
        int dispNum = int(temp);

        // Insert new integer into the numList by digit.
        while (dispNum != 0){

            numList.push_front(dispNum % 10);
            dispNum /= 10;
        }

        // Remove all unnessary leading 0s
        while (numList.back() == 0 && decIndex != 0){

            numList.pop_back();
            decIndex--;
        }

        // Adds leading 0s consistent with the decimal place of the first digit
        for (int i = numList.size(); i < decIndex + 1; ++i){

            numList.push_front(0);
        }
    }

public:

    // Variables to keep track of printing out the current number to the display.
    int decIndex;
    int sign;
    list<int> numList;

    // Constructor function to initiate all values.
    calculator(){

        num1 = 0.0;
        num2 = 0.0;
        opIndex = 1;
        operation = '+';
        toClear = false;
        eqLast = false;
        numLock = false;

        numList.clear();
        numList.push_front(0);
        decIndex = 0;
        sign = 1;
        decLock = true;
    }

    // Function to add a new number when a number button is pressed.
    void numButton(int n){

        // If a new number cannot be added
        if (numLock) return;

        // Moving on to the next number to keep track of
        if (toClear) {
            numList.clear();

            decIndex = 0;
            sign = 1;
            decLock = true;
            toClear = false;

            if (opIndex == 1) {
                opIndex++;
            } else {
                opIndex--;
            }
        }
        // If the last button to be pressed was the equal button
        if (eqLast){
            numList.clear();    

            num2 = 0.0;
            operation = '+';
            eqLast = false;
            decIndex = 0;
            decLock = true;
            sign = 1;
        }

        // Numbers cannot be breater than seven digits
        if (numList.size() == 7) return;

        // An empty number in the calculator will default to 0.
        if (numList.size() == 1 && numList.front() == 0
             && decLock){
            numList.remove(0);
        }
            
        // Insert the new value into the back of the number list
        numList.push_back(n);
        // Update the index of the decimal point
        decIndex += !decLock;

        // Update the current number
        updateNum();
    }

    // Function to update when the decimal point button was pressed.
    void decButton(){

        decLock = false;
    }

    // Function to update the number list when the backspace button was pressed.
    void backButton(){

        // Cannot backspace when an operation, equal, square, or square root button is pressed.
        if (toClear || eqLast || numLock) return;

        // If the value is the last one left, a 0 will remain.
        if (numList.size() == 1){

            decLock = true;
            numList.pop_back();
            numList.push_back(0);
            return;
        }

        // Delete the rightmost value from the calculator
        numList.pop_back();

        // If the decimal point is deleted, the index of the point will no longer update until the decimal button is pressed again.
        if (decIndex == 0) decLock = true;

        // Update the decimal index
        decIndex -= !decLock;

        // Update the current number
        updateNum();
    }

    // Function for when the negative sign button is pressed.
    void negButton(){
    
    // Cannot update the current value after an operation or equal button is pressed.
    if (toClear || eqLast) return;

        // Update sign variable and current number's sign.
        if (opIndex == 1) num1 *= -1;
        else num2 *= -1;

        sign *= -1;
    }

    // Function for when an operation button is pressed.
    void operationButton(char op){
        
        // If two numbers are already filled, put their solution into num1 first.
        if (opIndex == 2) {
            calculateOperation();
            num2 = 0.0;
            opIndex = 1;
        }
        // Update the current operation.
        operation = op;

        // Set boolean values to clear the printed number when a number button is pressed.
        toClear = true;
        eqLast = false;
        numLock = false;
    }

    // Function for when the equal sign button is pressed.
    void equalButton(){

        // Calculate the current operation on num1 and num2, update the printed value.
        calculateOperation();
        updateList();

        // Set values to allow the user to reset values or use the resulting value in num1.
        opIndex = 1;
        eqLast = true;
        numLock = false;
    }

    // Function for when the square button is pressed.
    void square(){

        // If the first number is squared, do not allow calculations using the previous operation.
        if (opIndex == 1){

            num1 *= num1;
            num2 = 0.0;
            operation = '+';
        } else {

            num2 *= num2;
        }

        // Update the printed list. Do not allow the user to input another number value.
        updateList();
        numLock = true;
    }

    // Function for when the square root button is pressed. Similar to the square() function, but does not allow the root of a negative value.
    bool sqrt(){

        if (opIndex == 1){

            // Disallow the root of a negative value
            if (num1 < 0){
                return false;
            }

            num1 = sqrtl(num1);
            num2 = 0.0;
            operation = '+';
        } else {

            // Disallow the root of a negative value
            if (num2 < 0){
                return false;
            }

            num2 = sqrtl(num2);
        }

        // Update the printed list
        updateList();
        numLock = true;
        return true;
    }
};

#endif