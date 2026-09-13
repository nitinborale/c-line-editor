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
    // Shift existing lines down
    for (int i = line_count; i >= line_num; i--) {
        strcpy(lines[i], lines[i - 1]);
    }
    // Insert new text at the specified index (0-indexed)
    strcpy(lines[line_num - 1], text);
    line_count++;
    printf("Line inserted successfully.\n");
}

void delete_line(int line_num) {
    if (line_num < 1 || line_num > line_count) {
        printf("Error: Line number does not exist[cite: 1].\n");
        return;
    }
    // Shift subsequent lines up
    for (int i = line_num - 1; i < line_count - 1; i++) {
        strcpy(lines[i], lines[i + 1]);
    }
    line_count--;
    printf("Line deleted successfully[cite: 1].\n");
}

int main() {
    int choice;
    int line_num;
    char text[MAX_LEN];

    do {
        printf("\nLine Editor Menu:\n");
        printf("1. Display Document\n");
        printf("2. Insert Line\n");
        printf("3. Delete Line\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number[cite: 1].\n");
            while(getchar() != '\n'); // clear buffer
            continue;
        }
        while(getchar() != '\n'); // clear newline

        switch (choice) {
            case 1:
                display_document();
                break;
            case 2:
                printf("Enter line number to insert at: ");
                if (scanf("%d", &line_num) != 1) {
                    printf("Invalid line number[cite: 1].\n");
                    while(getchar() != '\n');
                    break;
                }
                while(getchar() != '\n');
                printf("Enter text: ");
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = 0; // remove trailing newline
                insert_line(line_num, text);
                break;
            case 3:
                printf("Enter line number to delete: ");
                if (scanf("%d", &line_num) != 1) {
                    printf("Invalid line number[cite: 1].\n");
                    while(getchar() != '\n');
                    break;
                }
                while(getchar() != '\n');
                delete_line(line_num);
                break;
            case 4:
                printf("Exiting editor.\n");
                break;
            default:
                printf("Invalid choice. Try again[cite: 1].\n");
        }
    } while (choice != 4);

    return 0;
}