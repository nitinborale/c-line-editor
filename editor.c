#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100
#define MAX_LEN 256

char lines[MAX_LINES][MAX_LEN];
int line_count = 0;

void display_document() {
    printf("\n--- Document State ---\n");
    if (line_count == 0) {
        printf("(Document is empty)\n");
    }
    for (int i = 0; i < line_count; i++) {
        printf("%d: %s\n", i + 1, lines[i]);
    }
    printf("----------------------\n");
}

void insert_line(int line_num, const char *text) {
    if (line_num < 1 || line_num > line_count + 1) {
        printf("Error: Invalid line number for insertion.\n");
        return;
    }
    if (line_count >= MAX_LINES) {
        printf("Error: Document is full.\n");
        return;
    }
    for (int i = line_count; i >= line_num; i--) {
        strcpy(lines[i], lines[i - 1]);
    }
    strcpy(lines[line_num - 1], text);
    line_count++;
    printf("Line inserted successfully.\n");
}

void delete_line(int line_num) {
    if (line_num < 1 || line_num > line_count) {
        printf("Error: Line number does not exist.\n");
        return;
    }
    for (int i = line_num - 1; i < line_count - 1; i++) {
        strcpy(lines[i], lines[i + 1]);
    }
    line_count--;
    printf("Line deleted successfully.\n");
}

int main() {
    char input[MAX_LEN];
    char cmd;
    int line_num;
    char text[MAX_LEN];

    printf("Simple Line Editor. Commands: p, i <num> <text>, d <num>, q\n");
    
    while (1) {
        printf("\n> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = 0; 

        if (strlen(input) == 0) continue;

        cmd = input[0];

        if (cmd == 'q') {
            printf("Exiting editor and freeing memory.\n");
            break;
        } else if (cmd == 'p') {
            display_document();
        } else if (cmd == 'i') {
            if (sscanf(input, "i %d %[^\n]", &line_num, text) == 2) {
                insert_line(line_num, text);
            } else {
                printf("Usage: i <line_number> <text>\n");
            }
        } else if (cmd == 'd') {
            if (sscanf(input, "d %d", &line_num) == 1) {
                delete_line(line_num);
            } else {
                printf("Usage: d <line_number>\n");
            }
        } else {
            printf("Unknown command. Type 'p', 'i', 'd', or 'q'.\n");
        }
    }
    return 0;
}
