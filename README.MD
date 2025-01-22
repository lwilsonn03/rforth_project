# README

This project is meant to emulate a forth language terminal. For a quick introduction to forth, see [Easy Forth](https://skilldrick.github.io/easyforth/).

## Running the project

When downloaded, navigate to the R_FORTH folder in the command line. Running "./a.exe" should launch the executable. If successful, you'll see a "Welcome to RForth" message. Use "bye" to exit.

See below for a summary of the operations this project can handle. 


#Original README for class purposes:

## RFORTH Features

- Transition to C++ enabled use of more complex data structures:
    - vectors for dynamic memory handling
    - maps for variable storage
    - stack class instead of stack struct
- support for +-*/<>, mod, and /mod
- similar terminal function to gforth: take one line of input, process, print, and accept more
- "bye" and "clear-stack" keywords
- integer variable assignment & use

## RFORTH Limitations

- no negative integers
    - token processing doesn't recognize negative numbers
    - map of variables has -1 as value for created but unassigned variables
- static capacity, currently 10
