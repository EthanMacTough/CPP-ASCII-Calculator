# C++ ASCII CALCULATOR

A simple seven-digit calculator representation using [ASCII](https://en.wikipedia.org/wiki/ASCII) characters printed out in the terminal. Controlled using a keyboard's arrow and enter keys.
Code is organized into header files and is documented with comments.

![{A852FEBC-71FD-4633-BE94-237FC2820E7A}](https://github.com/user-attachments/assets/2cd7e17e-951d-4385-acbf-21deae7fd9cd)

This program makes use of Microsoft's [conio.h](https://learn.microsoft.com/en-us/cpp/c-runtime-library/console-and-port-i-o?view=msvc-170&redirectedfrom=MSDN) library to take keyboard input without printing it to the terminal (credit to Erik Anderson on [Stack Overflow](https://stackoverflow.com/questions/24708700/c-detect-when-user-presses-arrow-key)). It is therefore unable to function on any non-Microsoft OS devices.

This C++ project has two main moving parts: an adjacency list of buttons that can be pressed, and the calculator that keeps track of the numbers and operations that are given to it. All printing is done through the output.h file, which uses [ANSI Escape Codes](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797) extensively.
## Button Adjacency List
As seen in the image above, the OFF button is highlighted in red, while the rest of the calculator is white. This is all kept track of in the buttons.h header file, which keeps an adjacency list of button objects. 

Each button on the calculator has a corresponding character value, an (x, y) coordinate system, a string array to help in output, and a list of the button's neighbors on the calculator.

The buttons.h file keeps track of a head value, which is the highlighted button. When an arrow key is pressed, the head moves one node in the direction of the arrow key pressed. The output then resets the color of the previous button and updates the new button to be red.

## Internal Calculator
As with any calculator, in order to function, this project must be able to keep track of a set of numbers, and perform operations such as addition or multiplication on one another. This information is kept in the calc.h header file, which updates information when a user presses the ENTER key with any button selected.

The system of calculation consists of two decimal numbers and an operation. The user may type in two numbers separated by an operation (+, -, *, /), and the result is put back into the first number. This way, multiple calculations can make use of previous operations.
