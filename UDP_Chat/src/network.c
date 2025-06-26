#include "network.h"

int create_socket() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

int bind_socket(int sockfd, int port) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    return 0;
}

int send_message(int sockfd, const char *message, struct sockaddr_in *dest_addr, socklen_t addr_len) {
    int bytes_sent = sendto(sockfd, message, strlen(message), 0, 
                           (struct sockaddr *)dest_addr, addr_len);
    if (bytes_sent < 0) {
        perror("Send failed");
        return -1;
    }
    return bytes_sent;
}

int receive_message(int sockfd, char *buffer, struct sockaddr_in *src_addr, socklen_t *addr_len) {
    int bytes_received = recvfrom(sockfd, buffer, MAX_BUFFER_SIZE - 1, 0, 
                                 (struct sockaddr *)src_addr, addr_len);
    if (bytes_received < 0) {
        perror("Receive failed");
        return -1;
    }
    buffer[bytes_received] = '\0'; // Null-terminate the received string
    return bytes_received;
}

void close_socket(int sockfd) {
    close(sockfd);
}
