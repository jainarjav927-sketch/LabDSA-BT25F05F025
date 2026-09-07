#include <stdio.h>
#include <stdlib.h>

// ---------- NODE STRUCTURE ----------
struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;

// ---------- INSERT AT BEGINNING ----------
void insertAtBeginning(int val) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = head;
    head = newNode;
}

// ---------- INSERT AT END ----------
void insertAtEnd(int val) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// ---------- INSERT AT GIVEN POSITION (1-indexed) ----------
void insertAtPosition(int val, int pos) {
    if (pos == 1) {
        insertAtBeginning(val);
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = val;

    struct Node *temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of range\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// ---------- DELETE BY VALUE ----------
void deleteByValue(int val) {
    if (head == NULL) {
        printf("List is Empty\n");
        return;
    }

    if (head->data == val) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
        return;
    }

    struct Node *curr = head;
    while (curr->next != NULL && curr->next->data != val) {
        curr = curr->next;
    }

    if (curr->next == NULL) {
        printf("Value %d not found\n", val);
        return;
    }

    struct Node *toDelete = curr->next;
    curr->next = curr->next->next;
    free(toDelete);
}

// ---------- SEARCH ----------
int search(int val) {
    struct Node *temp = head;
    int pos = 1;
    while (temp != NULL) {
        if (temp->data == val)
            return pos;
        temp = temp->next;
        pos++;
    }
    return -1;
}

// ---------- DISPLAY ----------
void display() {
    if (head == NULL) {
        printf("List is Empty\n");
        return;
    }
    struct Node *temp = head;
    printf("List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// ---------- MAIN ----------
int main() {
    int choice, val, pos;

    while (1) {
        printf("\n1. Insert at Beginning\n2. Insert at End\n3. Insert at Position\n"
               "4. Delete by Value\n5. Search\n6. Display\n7. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                insertAtBeginning(val);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &val);
                insertAtEnd(val);
                break;
            case 3:
                printf("Enter value and position: ");
                scanf("%d %d", &val, &pos);
                insertAtPosition(val, pos);
                break;
            case 4:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                deleteByValue(val);
                break;
            case 5:
                printf("Enter value to search: ");
                scanf("%d", &val);
                pos = search(val);
                if (pos != -1)
                    printf("Found at position %d\n", pos);
                else
                    printf("Not found\n");
                break;
            case 6:
                display();
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
