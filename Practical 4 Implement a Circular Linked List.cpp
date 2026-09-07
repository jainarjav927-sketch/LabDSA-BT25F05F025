#include <stdio.h>
#include <stdlib.h>

// ---------- NODE STRUCTURE ----------
struct Node {
    int data;
    struct Node *next;
};

struct Node *last = NULL;   // "last" points to last node, last->next = first node

// ---------- INSERT AT BEGINNING ----------
void insertAtBeginning(int val) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = val;

    if (last == NULL) {
        last = newNode;
        newNode->next = newNode;   // khud se hi circle
        return;
    }

    newNode->next = last->next;   // naya node purane first ko point kare
    last->next = newNode;         // last ab naye node ko point kare (first ban gaya)
}

// ---------- INSERT AT END ----------
void insertAtEnd(int val) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = val;

    if (last == NULL) {
        last = newNode;
        newNode->next = newNode;
        return;
    }

    newNode->next = last->next;   // naya node first ko point kare
    last->next = newNode;         // purana last naye node ko point kare
    last = newNode;               // ab naya node hi "last" hai
}

// ---------- INSERT AT POSITION (1-indexed) ----------
void insertAtPosition(int val, int pos) {
    if (pos == 1) {
        insertAtBeginning(val);
        return;
    }
    if (last == NULL) {
        printf("List is Empty, inserting at beginning instead\n");
        insertAtBeginning(val);
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = val;

    struct Node *temp = last->next;  // first node se start
    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
        if (temp == last->next) {   // ek pura chakkar lag gaya, position galat
            printf("Position out of range\n");
            free(newNode);
            return;
        }
    }

    newNode->next = temp->next;
    temp->next = newNode;

    if (temp == last) {   // agar end mein insert hua
        last = newNode;
    }
}

// ---------- DELETE BY VALUE ----------
void deleteByValue(int val) {
    if (last == NULL) {
        printf("List is Empty\n");
        return;
    }

    struct Node *curr = last->next;   // first node
    struct Node *prev = last;

    do {
        if (curr->data == val) {
            if (curr == last && curr->next == last) {
                // sirf ek hi node tha
                last = NULL;
            } else {
                prev->next = curr->next;
                if (curr == last) {
                    last = prev;
                }
            }
            free(curr);
            printf("Deleted %d\n", val);
            return;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != last->next);

    printf("Value %d not found\n", val);
}

// ---------- SEARCH ----------
int search(int val) {
    if (last == NULL) return -1;

    struct Node *temp = last->next;
    int pos = 1;
    do {
        if (temp->data == val)
            return pos;
        temp = temp->next;
        pos++;
    } while (temp != last->next);

    return -1;
}

// ---------- DISPLAY ----------
void display() {
    if (last == NULL) {
        printf("List is Empty\n");
        return;
    }

    struct Node *temp = last->next;   // first node se start
    printf("Circular List: ");
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != last->next);
    printf("(back to head)\n");
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
