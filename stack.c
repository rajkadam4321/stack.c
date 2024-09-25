#include <stdio.h>
#include <stdlib.h>

#define MAX 10 

int stack[MAX];
int top = -1;


void push() {
    int x;
    if (top == MAX - 1) {
        printf("Stack Overflow! \n");
    } else {
        printf("Enter the value to push: ");
        scanf("%d", &x);
        top++;
        stack[top] = x;
        printf("Pushed %d onto the stack.\n", x);
    }
}


void pop() {
    if (top == -1) {
        printf("Stack Underflow! \n");
    } else {
        printf("Popped %d from the stack.\n", stack[top]);
        top--;
    }
}


void print() {
    if (top == -1) {
        printf("Stack is empty.\n");
    } else {
        printf("Stack elements are:\n");
        for (int i = top; i >= 0; i--) {
            printf("%d\n", stack[i]);
        }
    }
}

void main() {
    int choice;
    while (1) {
        printf("\nStack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Print\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                print();
                break;
            case 4:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. \n");
        }
    }
   
}
