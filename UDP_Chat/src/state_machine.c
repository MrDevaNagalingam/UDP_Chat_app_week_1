#include "state_machine.h"

void init_state_machine() {
    // Initialization if needed
}

ChatState process_event(ChatState current_state, int event) {
    switch (current_state) {
        case STATE_IDLE:
            if (event == 1) { // Event: Send message
                return STATE_SENDING;
            } else if (event == 2) { // Event: Receive message
                return STATE_RECEIVING;
            }
            break;
        case STATE_SENDING:
            if (event == 3) { // Event: Send complete
                return STATE_IDLE;
            } else if (event == 4) { // Event: Error
                return STATE_ERROR;
            }
            break;
        case STATE_RECEIVING:
            if (event == 5) { // Event: Receive complete
                return STATE_IDLE;
            } else if (event == 4) { // Event: Error
                return STATE_ERROR;
            }
            break;
        case STATE_ERROR:
            if (event == 6) { // Event: Reset
                return STATE_IDLE;
            }
            break;
        default:
            return STATE_ERROR;
    }
    return current_state;
}
