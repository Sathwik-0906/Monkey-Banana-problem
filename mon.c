#include <stdio.h>
#include <stdbool.h>

#define MIDDLE 0
#define DOOR 1
#define WINDOW 2

#define ON_FLOOR 0
#define ON_BOX 1

typedef struct {
    int monkeyHPos;  // Horizontal position of the monkey (middle, door, window)
    int monkeyVPos;  // Vertical position of the monkey (on floor, on box)
    int boxPos;      // Position of the box (middle, door, window)
    bool hasBananas; // Whether the monkey has the bananas
} State;

// Function to print the current state
void printState(State s) {
    const char *positions[] = {"Middle", "Door", "Window"};
    const char *verticalPositions[] = {"On Floor", "On Box"};
    
    printf("\nMonkey position: %s, %s\n", positions[s.monkeyHPos], verticalPositions[s.monkeyVPos]);
    printf("Box position: %s\n", positions[s.boxPos]);
    printf("Has Bananas: %s\n", s.hasBananas ? "Yes" : "No");
}

// Function for the "Grasp" action
State grasp(State s) {
    if (s.monkeyHPos == MIDDLE && s.monkeyVPos == ON_BOX && !s.hasBananas) {
        s.hasBananas = true;
        printf("Monkey has grasped the bananas!\n");
    } else {
        printf("Cannot grasp bananas (conditions not met).\n");
    }
    return s;
}

// Function for the "Climb" action
State climb(State s) {
    if (s.monkeyHPos == s.boxPos && s.monkeyVPos == ON_FLOOR) {
        s.monkeyVPos = ON_BOX;
        printf("Monkey climbs onto the box.\n");
    } else {
        printf("Cannot climb (conditions not met).\n");
    }
    return s;
}

// Function for the "Push" action
State push(State s, int newBoxPos) {
    if (s.monkeyVPos == ON_FLOOR && s.monkeyHPos == s.boxPos) {
        s.boxPos = newBoxPos;  // Move the box to the new position
        printf("Monkey pushes the box to %s.\n", 
            (newBoxPos == MIDDLE) ? "middle" : 
            (newBoxPos == DOOR) ? "door" : "window");
    } else {
        printf("Cannot push (conditions not met: Monkey and Box must be in the same position and Monkey must be on the floor).\n");
    }
    return s;
}

// Function for the "Walk" action
State walk(State s, int newHPos) {
    if (s.monkeyVPos == ON_FLOOR) {
        s.monkeyHPos = newHPos;
        printf("Monkey walks to %s.\n", 
            (newHPos == MIDDLE) ? "middle" : 
            (newHPos == DOOR) ? "door" : "window");
    } else {
        printf("Cannot walk while on the box.\n");
    }
    return s;
}

// Main game loop
int main() {
    State monkeyState = {DOOR, ON_FLOOR, DOOR, false};  // Initial state

    int action, position;

    while (!monkeyState.hasBananas) {
        // Show action options
        printf("\nSelect an action:\n");
        printf("1. Walk\n2. Push the box\n3. Climb onto the box\n4. Grasp the bananas\n5. Show current state\n6. Exit\n");
        printf("Enter action number: ");
        scanf("%d", &action);

        switch (action) {
            case 1: // Walk
                printf("Select new position for the monkey (0 = middle, 1 = door, 2 = window): ");
                scanf("%d", &position);
                monkeyState = walk(monkeyState, position);
                break;
            case 2: // Push
                printf("Select new position for the box (0 = middle, 1 = door, 2 = window): ");
                scanf("%d", &position);
                monkeyState = push(monkeyState, position);
                break;
            case 3: // Climb
                monkeyState = climb(monkeyState);
                break;
            case 4: // Grasp
                monkeyState = grasp(monkeyState);
                break;
            case 5: // Show current state
                printState(monkeyState);
                break;
            case 6: // Exit
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option, please try again.\n");
        }

        // After each action, print the current state
        printState(monkeyState);
    }

    return 0;
}

