#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char text[256];
    struct Node *next;
} Node;

Node *head = NULL;

// 1. Display/Print all lines
void print_doc() {
    Node *curr = head;
    int line = 1;
    if (!curr) printf("[ Document is empty ]\n");
    while (curr != NULL) {
        printf("%d: %s\n", line++, curr->text);
        curr = curr->next;
    }
}

// 2. Insert line
void insert_line(int pos, char *text) {
    Node *new_node = malloc(sizeof(Node));
    strcpy(new_node->text, text);
    
    if (pos == 1 || head == NULL) {
        new_node->next = head;
        head = new_node;
    } else {
        Node *curr = head;
        for (int i = 1; i < pos - 1 && curr->next != NULL; i++) {
            curr = curr->next;
        }
        new_node->next = curr->next;
        curr->next = new_node;
    }
    printf("Line added!\n");
}

// 3. Delete line
void delete_line(int pos) {
    if (head == NULL) return;
    Node *temp = head;
    if (pos == 1) {
        head = head->next;
        free(temp);
    } else {
        Node *curr = head;
        for (int i = 1; i < pos - 1 && curr->next != NULL; i++) {
            curr = curr->next;
        }
        if (curr->next == NULL) return;
        temp = curr->next;
        curr->next = temp->next;
        free(temp);
    }
    printf("Line deleted!\n");
}

int main() {
    char choice;
    int line;
    char text[256];

    while (1) {
        printf("\nCommands: (p)rint, (i)nsert, (d)elete, (q)uit\nEnter command: ");
        scanf(" %c", &choice);

        if (choice == 'q') break;
        if (choice == 'p') print_doc();
        if (choice == 'i') {
            printf("Enter line number & text: ");
            scanf("%d %[^\n]", &line, text);
            insert_line(line, text);
        }
        if (choice == 'd') {
            printf("Enter line number to delete: ");
            scanf("%d", &line);
            delete_line(line);
        }
    }
    return 0;
}