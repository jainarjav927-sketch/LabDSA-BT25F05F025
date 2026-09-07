#include <stdio.h>
#include <stdlib.h>

#define MAX 5   // size of circular queue

int queue[MAX];
int front = -1, rear = -1;

// ---------- CHECKS ----------
int isFull() {
    return (rear + 1) % MAX == front;
}

int isEmpty() {
    return front == -1;
}

// ---------- ENQUEUE ----------
void enqueue(int val) {
    if (isFull()) {
        printf("Queue is Full! Cannot insert %d\n", val);
        return;
    }
    if (isEmpty()) {
        front = 0;
        rear = 0;
    } else {
        rear = (rear + 1) % MAX;
    }
    queue[rear] = val;
    printf("Inserted %d\n", val);
}

// ---------- DEQUEUE ----------
int dequeue() {
    if (isEmpty()) {
        printf("Queue is Empty! Cannot delete\n");
        return -1;
    }
    int val = queue[front];
    if (front == rear) {
        // last element hi tha
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % MAX;
    }
    return val;
}

// ---------- DISPLAY ----------
void display() {
    if (isEmpty()) {
        printf("Queue is Empty\n");
        return;
    }
    printf("Queue elements: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// ---------- MAIN ----------
int main() {
    int choice, val;

    while (1) {
        printf("\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                enqueue(val);
                break;
            case 2:
                val = dequeue();
                if (val != -1)
                    printf("Deleted %d\n", val);
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
