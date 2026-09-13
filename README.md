# C Line Editor

## Team Members
- Nitin Borale

## Implemented Features
- **Insert a line:** Add a new line of text at a given line number, shifting existing lines down.
- **Delete a line:** Remove the line at a given number, shifting lines up.
- **Display the document:** Print all current lines with 1-based line numbers.

## How to Compile and Run
Open your terminal in the project folder and run:
```bash
gcc -Wall -Wextra editor.c -o editor
./editor