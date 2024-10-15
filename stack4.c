#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
// Stack structure definition
typedef struct {
    int top;
    int items[MAX];
} Stack;
// Initialize stack
void init(Stack *s) {
    s->top = -1;
}
// Check if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}
// Check if stack is full
int isFull(Stack *s) {
    return s->top == MAX - 1;
}
// Push item onto stack
void push(Stack *s, int item) {
    if (isFull(s)) {
        printf("Overflow!!!\n");
        return;
    }
    s->items[++(s->top)] = item;
}
// Pop item from stack
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Underflow!!!\n");
        return 0; // Return 0 or handle error
    }
    return s->items[(s->top)--];
}
// Peek at top item of stack
int peek(Stack *s) {
    return isEmpty(s) ? 0 : s->items[s->top];
}
// Get precedence of operators
int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0; // Invalid operator
    }
}
// Convert infix to postfix
void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    init(&s);
    int j = 0; // Index for postfix string
    for (int i = 0; infix[i] != '\0'; i++) {
        char current = infix[i];
        if (isalnum(current)) {
            postfix[j++] = current; // Add operand to output
        } else if (current == '(') {
            push(&s, current); // Push '(' onto stack
        } else if (current == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s); // Pop until '('
            }
            pop(&s); // Discard '('
        } else { // Operator
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(current)) {
                postfix[j++] = pop(&s); // Pop higher or equal precedence
            }
            push(&s, current); // Push current operator
        }
    }
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s); // Pop remaining operators
    }
    postfix[j] = '\0'; // Null-terminate the string
}
// Reverse a string
void reverse(char *exp) {
    int n = strlen(exp);
    for (int i = 0; i < n / 2; i++) {
        char temp = exp[i];
        exp[i] = exp[n - 1 - i];
        exp[n - 1 - i] = temp;
    }
}
// Convert infix to prefix
void infixToPrefix(char *infix, char *prefix) {
    reverse(infix); // Reverse the infix expression
    // Replace '(' with ')' and vice versa
    for (int i = 0; infix[i] != '\0'; i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        } else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }
    char postfix[MAX];
    infixToPostfix(infix, postfix); // Convert to postfix
    reverse(postfix);               // Reverse postfix to get prefix
    strcpy(prefix, postfix);        // Copy result to prefix
}
// Evaluate a postfix expression
int evaluatePostfix(char *postfix) {
    Stack s;
    init(&s);
    char *token = strtok(postfix, " "); // Tokenize based on spaces
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && token[1] != '\0')) { // Handle negative numbers
            push(&s, atoi(token)); // Convert string to int and push
        } else {
            int operand2 = pop(&s);
            int operand1 = pop(&s);
            switch (token[0]) {
                case '+':
                    push(&s, operand1 + operand2);
                    break;
                case '-':
                    push(&s, operand1 - operand2);
                    break;
                case '*':
                    push(&s, operand1 * operand2);
                    break;
                case '/':
                    push(&s, operand1 / operand2);
                    break;
                default:
                    printf("Invalid operator: %s\n", token);
                    return 0; // Error condition
            }
        }
        token = strtok(NULL, " "); // Get next token
    }
    return pop(&s); // Return final result
}
// Display menu options
void menu() {
    printf("1 - Infix to Postfix\n");
    printf("2 - Infix to Prefix\n");
    printf("3 - Evaluate Postfix Expression\n");
    printf("4 - Exit\n");
}
// Main function
int main() {
    char infix[MAX], postfix[MAX], prefix[MAX];
    int choice;
    do {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character after choice
        switch (choice) {
            case 1:
                printf("Enter an infix expression: ");
                fgets(infix, sizeof(infix), stdin);
                infixToPostfix(infix, postfix);
                printf("\n\nPostfix: %s\n\n", postfix);
                break;
            case 2:
                printf("Enter an infix expression: ");
                fgets(infix, sizeof(infix), stdin);
                infixToPrefix(infix, prefix);
                printf("\n\nPrefix: %s\n\n", prefix);
                break;
            case 3:
                printf("Enter a postfix expression to evaluate (use spaces): ");
                fgets(postfix, sizeof(postfix), stdin);
                int result = evaluatePostfix(postfix);
                printf("\n\nPostfix Evaluation Result: %d\n\n", result);
                break;
            case 4:
                printf("\n\nExiting...\n\n");
                break;
            default:
                printf("Enter valid choice!\n\n");
                break;
        }
    } while (choice != 4);
    return 0;
}
