#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 32

// Sensor error codes (from Problem 1)
typedef enum {
    SENSOR_OK = 0,
    I2C_TIMEOUT,
    INVALID_DATA,
    SENSOR_DISCONNECTED
} SensorError;

// Node structure
typedef struct Node {
    SensorError error_code;
    struct Node* next;
} Node;

// Stack structure
typedef struct {
    Node* head;
    int current_size;
} Stack;

// Initialize Stack
void init_stack(Stack* s) {
    s->head = NULL;
    s->current_size = 0;
}

// Remove the oldest entry (the last node in the list)
void remove_oldest(Stack* s) {
    if (s->head == NULL) return;

    // If there is only one node
    if (s->head->next == NULL) {
        free(s->head);
        s->head = NULL;
    } else {
        Node* temp = s->head;
        // Traverse to the second-to-last node
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        // Free the last node
        free(temp->next);
        temp->next = NULL;
    }
    s->current_size--;
}

// Push operation
void push(Stack* s, SensorError code) {
    // Handle "Circular" behavior: if full, remove oldest before adding new
    if (s->current_size >= MAX_STACK_SIZE) {
        remove_oldest(s);
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    new_node->error_code = code;
    new_node->next = s->head;
    s->head = new_node;
    s->current_size++;
}

// Pop operation
int pop(Stack* s, SensorError* result) {
    if (s->head == NULL || s->current_size == 0) {
        printf("Stack Underflow\n");
        return -1; // Failure
    }

    Node* temp = s->head;
    *result = temp->error_code;
    s->head = s->head->next;
    
    free(temp);
    s->current_size--;
    return 0; // Success
}

// Helper function to display stack
void display_stack(Stack* s) {
    Node* current = s->head;
    printf("Stack (Size %d): ", s->current_size);
    while (current) {
        printf("[%d] -> ", current->error_code);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    Stack error_stack;
    init_stack(&error_stack);

    // Simulate filling the stack beyond 32 to test circular behavior
    for (int i = 0; i < 40; i++) {
        push(&error_stack, (SensorError)(i % 4));
    }

    display_stack(&error_stack);

    SensorError last_err;
    if (pop(&error_stack, &last_err) == 0) {
        printf("Popped most recent error: %d\n", last_err);
    }

    return 0;
}
