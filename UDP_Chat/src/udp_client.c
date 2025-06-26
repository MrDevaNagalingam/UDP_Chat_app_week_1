#include "network.h"
#include "state_machine.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *server_ip = argv[1];
    int port = atoi(argv[2]);
    NetworkConfig client;
    ChatState state = STATE_IDLE;

    init_state_machine();
    client.sockfd = create_socket();
    client.addr.sin_family = AF_INET;
    client.addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &client.addr.sin_addr);
    client.addr_len = sizeof(client.addr);

    printf("Connected to server %s:%d\n", server_ip, port);

    while (1) {
        char buffer[MAX_BUFFER_SIZE] = {0};
        printf("Enter message (or 'quit' to exit): ");
        fgets(buffer, MAX_BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline

        if (strcmp(buffer, "quit") == 0) break;

        state = process_event(state, 1); // Event: Send message
        if (state == STATE_SENDING) {
            if (send_message(client.sockfd, buffer, &client.addr, client.addr_len) >= 0) {
                state = process_event(state, 3); // Event: Send complete
            } else {
                state = process_event(state, 4); // Event: Error
            }
        }

        if (state == STATE_IDLE) {
            state = process_event(state, 2); // Event: Ready to receive
            if (state == STATE_RECEIVING) {
                memset(buffer, 0, MAX_BUFFER_SIZE);
                if (receive_message(client.sockfd, buffer, &client.addr, &client.addr_len) > 0) {
                    printf("Server response: %s\n", buffer);
                    state = process_event(state, 5); // Event: Receive complete
                } else {
                    state = process_event(state, 4); // Event: Error
                }
            }
        }

        if (state == STATE_ERROR) {
            fprintf(stderr, "Error occurred, resetting...\n");
            state = process_event(state, 6); // Event: Reset
        }
    }

    close_socket(client.sockfd);
    return 0;
}
