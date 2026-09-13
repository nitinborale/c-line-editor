#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 100
#define MAX_LINE_LENGTH 256

typedef struct {
    char **lines;
    int count;
    int capacity;
} TextDocument;

void init_document(TextDocument *doc) {
    doc->count = 0;
    doc->capacity = INITIAL_CAPACITY;
    doc->lines = malloc(doc->capacity * sizeof(char *));
}

void free_document(TextDocument *doc) {
    for (int i = 0; i < doc->count; i++) {
        free(doc->lines[i]);
    }
    free(doc->lines);
}

void print_document(TextDocument *doc) {
    if (doc->count == 0) {
        printf("(empty document)\n");
        return;
    }
    for (int i = 0; i < doc->count; i++) {
        printf("%d: %s\n", i + 1, doc->lines[i]);
    }
}

void insert_line(TextDocument *doc, int line_num, const char *text) {
    int index = line_num - 1;
    if (index < 0 || index > doc->count) {
        printf("Error: Invalid line number.\n");
        return;
    }
    if (doc->count >= doc->capacity) {
        doc->capacity *= 2;
        doc->lines = realloc(doc->lines, doc->capacity * sizeof(char *));
    }
    // Shift lines down
    for (int i = doc->count; i > index; i--) {
        doc->lines[i] = doc->lines[i - 1];
    }
    doc->lines[index] = strdup(text);
    doc->count++;
    printf("Line inserted successfully.\n");
}

void delete_line(TextDocument *doc, int line_num) {
    int index = line_num - 1;
    if (index < 0 || index >= doc->count) {
        printf("Error: Invalid line number.\n");
        return;
    }
    free(doc->lines[index]);
    // Shift lines up
    for (int i = index; i < doc->count - 1; i++) {
        doc->lines[i] = doc->lines[i + 1];
    }
    doc->count--;
    printf("Line deleted successfully.\n");
}

int main() {
    TextDocument doc;
    init_document(&doc);

    char input[512];
    printf("=== Simple Line Editor ===\n");
    printf("Commands:\n");
    printf("  p          - Print document\n");
    printf("  i <n> <txt>- Insert text at line <n>\n");
    printf("  d <n>      - Delete line <n>\n");
    printf("  q          - Quit program\n\n");

    while (1) {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        
        // Remove trailing newline character
        input[strcspn(input, "\r\n")] = 0;

        if (strcmp(input, "q") == 0) {
            break;
        } else if (strcmp(input, "p") == 0) {
            print_document(&doc);
        } else if (strncmp(input, "i ", 2) == 0) {
            int line_num;
            char text[MAX_LINE_LENGTH];
            if (sscanf(input + 2, "%d %[^\n]", &line_num, text) == 2) {
                insert_line(&doc, line_num, text);
            } else {
                printf("Usage: i <line_number> <text>\n");
            }
        } else if (strncmp(input, "d ", 2) == 0) {
            int line_num;
            if (sscanf(input + 2, "%d", &line_num) == 1) {
                delete_line(&doc, line_num);
            } else {
                printf("Usage: d <line_number>\n");
            }
        } else {
            printf("Unknown command. Use p, i, d, or q.\n");
        }
    }

    free_document(&doc);
    return 0;
}