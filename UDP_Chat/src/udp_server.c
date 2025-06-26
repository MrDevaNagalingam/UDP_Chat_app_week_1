#include "network.h"
#include "state_machine.h"

int main(int argc, char *argv[]) {
    int port = (argc > 1) ? atoi(argv[1]) : DEFAULT_PORT;
    NetworkConfig server;
    ChatState state = STATE_IDLE;

    init_state_machine();
    server.sockfd = create_socket();
    bind_socket(server.sockfd, port);
    server.addr_len = sizeof(server.addr);

    printf("Server listening on port %d...\n", port);

    while (1) {
        char buffer[MAX_BUFFER_SIZE] = {0};
        state = process_event(state, 2); // Event: Ready to receive

        if (state == STATE_RECEIVING) {
            int bytes = receive_message(server.sockfd, buffer, &server.addr, &server.addr_len);
            if (bytes > 0) {
                printf("Received: %s\n", buffer);
                state = process_event(state, 5); // Event: Receive complete

                // Echo back to client
                state = process_event(state, 1); // Event: Send message
                if (state == STATE_SENDING) {
                    if (send_message(server.sockfd, buffer, &server.addr, server.addr_len) >= 0) {
                        state = process_event(state, 3); // Event: Send complete
                    } else {
                        state = process_event(state, 4); // Event: Error
                    }
                }
            } else {
                state = process_event(state, 4); // Event: Error
            }
        }

        if (state == STATE_ERROR) {
            fprintf(stderr, "Error occurred, resetting...\n");
            state = process_event(state, 6); // Event: Reset
        }
    }

    close_socket(server.sockfd);
    return 0;
}
