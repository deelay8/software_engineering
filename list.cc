#include <stdio.h>
#include <stdlib.h>

// Define the structure representing the nodes in the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to add a new node to the end of a linked list
void append(Node** head, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* last = *head;
    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}

// Function that outputs all nodes in the linked list
void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    Node* head = NULL;
    
    // Add a value from 1 to 100 to the linked list
    for (int i = 1; i <= 100; i++) {
        append(&head, i);
    }

    // Outputs all nodes in the linked list
    printList(head);

    // Release Memory
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
