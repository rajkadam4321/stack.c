#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data; 
    struct Node *next;
} Node;

typedef struct Stack {
    Node* top; 
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL; 
    return stack;
}

int isEmpty(Stack* stack) {
    return stack->top == NULL; 
}

void push(Stack* stack, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data; 
    newNode->next = stack->top; 
    stack->top = newNode; 
    printf("%d value is pushed.\n", data);
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n"); 
        return -1;
    }
    Node* tmp = stack->top; 
    int poppedValue = tmp->data; 
    stack->top = stack->top->next; 
    free(tmp); 
    return poppedValue;  
}

void printStack(Stack* stack) {
    if (isEmpty(stack)) {
        printf("No Elements in Stack\n"); 
        return;
    }
    printf("Elements in stack are:\n");
    Node* current = stack->top;
    while (current != NULL) {
        printf("%d\n", current->data); 
        current = current->next; 
    }
}

void freeStack(Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack); 
    }
    free(stack); 
}

void menu() {
    printf("\nMenu:\n");
    printf("1. PUSH\n");
    printf("2. POP\n");
    printf("3. PRINT\n");
    printf("4. EXIT\n");
}
int main() {
    Stack* stack = createStack();
    int choice, value;
    char cont;
    do {
        menu(); 
        printf("Enter choice: ");   
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(stack, value);
                break;
            case 2:
                value = pop(stack);
                if (value != -1) {
                    printf("Popped element: %d\n", value); 
                }
                break;
            case 3:
                printStack(stack);
                break;
            case 4:
                freeStack(stack); 
                printf("Exiting...\n");
                return 0; 
            default:
                printf("Invalid choice.\n");
                break;
        }
        printf("Do you want to continue (Y/y)? ");  
        scanf(" %c", &cont);
    } while (cont == 'y' || cont == 'Y');
    freeStack(stack);
    return 0; 
}