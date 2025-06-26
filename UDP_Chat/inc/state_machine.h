#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum {
    STATE_IDLE,
    STATE_SENDING,
    STATE_RECEIVING,
    STATE_ERROR
} ChatState;

typedef struct {
    ChatState current_state;
} StateMachine;

// Function prototypes
void init_state_machine();
ChatState process_event(ChatState current_state, int event);
#endif // STATE_MACHINE
