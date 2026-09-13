```markdown
# Line Editor Help Guide

## Supported Commands

- **p** (Print)
  - *Description:* Displays all current lines in the document with their line numbers.
  - *Usage Example:* `p`

- **i <line_number> <text>** (Insert)
  - *Description:* Inserts a new line of text at the specified line number.
  - *Usage Example:* `i 1 Hello World`

- **d <line_number>** (Delete)
  - *Description:* Deletes the line at the specified line number.
  - *Usage Example:* `d 1`

- **q** (Quit)
  - *Description:* Exits the line editor and frees allocated memory.
  - *Usage Example:* `q`