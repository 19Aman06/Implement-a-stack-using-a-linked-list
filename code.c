#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Configuration ---
#define MAX_STACK_SIZE 32

// --- Data Structures ---

// Node structure to hold sensor error codes
typedef struct Node {
    int errorCode;
    struct Node* next;
} Node;

// Stack structure to manage the linked list and size
typedef struct Stack {
    Node* top;      // Pointer to the most recent element
    int count;      // Current number of elements
} Stack;

// --- Function Prototypes ---
Stack* createStack();
void push(Stack* stack, int errorCode);
bool pop(Stack* stack, int* outErrorCode);
void removeOldest(Stack* stack);
void printStack(Stack* stack);
void freeStack(Stack* stack);

// --- Main Driver (Demonstration) ---
int main() {
    Stack* sensorStack = createStack();

    printf("--- Pushing 35 sensor codes (Max size is 32) ---\n");
    // We push 35 items. The first 3 (100, 101, 102) should be overwritten.
    for (int i = 0; i < 35; i++) {
        // Simulating error codes starting from 100
        push(sensorStack, 100 + i);
    }

    printf("\n--- Current Stack State (Top to Bottom) ---\n");
    printStack(sensorStack);

    printf("\n--- Popping 5 items ---\n");
    int code;
    for (int i = 0; i < 5; i++) {
        if (pop(sensorStack, &code)) {
            printf("Popped: %d\n", code);
        }
    }

    printf("\n--- Final Stack State ---\n");
    printStack(sensorStack);

    // Cleanup
    freeStack(sensorStack);
    return 0;
}

// --- Implementation Details ---

/**
 * Initializes a new empty stack.
 */
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed for Stack structure.\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    stack->count = 0;
    return stack;
}

/**
 * Removes the oldest node (the bottom of the stack).
 * Logic: Traverse to the second-to-last node and unlink the last node.
 * Complexity: O(N) where N is stack size (max 32).
 */
void removeOldest(Stack* stack) {
    if (stack->top == NULL) return;

    // Case 1: Only one item in the stack
    if (stack->top->next == NULL) {
        free(stack->top);
        stack->top = NULL;
    } 
    // Case 2: Multiple items. Traverse to find the second to last node.
    else {
        Node* current = stack->top;
        // Stop when current->next is the last node
        while (current->next->next != NULL) {
            current = current->next;
        }
        
        // current->next is now the node to be removed
        Node* toDelete = current->next;
        current->next = NULL; // Unlink
        free(toDelete);
    }
    
    stack->count--;
}

/**
 * Pushes a new error code onto the stack.
 * Handles overflow by removing the oldest entry first.
 */
void push(Stack* stack, int errorCode) {
    // Check if we hit the limit
    if (stack->count >= MAX_STACK_SIZE) {
        removeOldest(stack);
    }

    // Allocate new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for Node.\n");
        return; 
    }

    newNode->errorCode = errorCode;
    newNode->next = stack->top; // Link new node to current top
    stack->top = newNode;       // Update top pointer
    stack->count++;
}

/**
 * Pops the top error code from the stack.
 * Returns true if successful, false if stack is empty.
 * The value is stored in *outErrorCode.
 */
bool pop(Stack* stack, int* outErrorCode) {
    if (stack->top == NULL) {
        return false; // Stack is empty
    }

    Node* temp = stack->top;
    *outErrorCode = temp->errorCode;
    
    stack->top = temp->next; // Move top pointer down
    free(temp);
    stack->count--;

    return true;
}

/**
 * Helper to display stack contents (Iterative / No Recursion).
 */
void printStack(Stack* stack) {
    Node* current = stack->top;
    printf("Stack [Count: %d]: ", stack->count);
    
    if (current == NULL) {
        printf("Empty\n");
        return;
    }

    while (current != NULL) {
        printf("%d -> ", current->errorCode);
        current = current->next;
    }
    printf("NULL (Bottom)\n");
}

/**
 * Frees all memory associated with the stack (Iterative).
 */
void freeStack(Stack* stack) {
    Node* current = stack->top;
    Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    free(stack);
}
