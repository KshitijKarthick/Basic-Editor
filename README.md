# Basic Editor

## Functionality :
  * Create Files.
  * Stores Data based on user input.
  * Compliant with Posix Environment and Windows.

## Program Details :
  * Written in C.
  * Implements Double Linked Lists to store data entered by the User.
  * Based on User input of the filename, the file is created in the current directory or the specified absolute path.
  * Each node is used to store 10 characters.
  * The Program receives character by character input and stores it in the Linked List
  * Backspace deletes a character from the Linked List.
  * ctrl + c or ctrl + z saves the File and Exits the Editor.

## Execution :
```
  # Posix Compliant
  > cd Basic-Editor
  > make
  > cd dist/Debug/GNU-Linux-x86/
  > ./basic-editor [filename]

  # Windows
  > Compile the Source Code main.c with conio.h in the same directory
  > Use the Generated Executable file for execution.
  > Basic-Editor.exe [filename]
```
## To Do :
  * Append Functionality.
  * Usage of navigation button to navigate through the Input Section.
  * Cut Copy functionality.
