#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define MAX_BUFFER_SIZE 1024
#define DEFAULT_PORT 12345

// Structure to hold network configuration
typedef struct {
    int sockfd;
    struct sockaddr_in addr;
    socklen_t addr_len;
} NetworkConfig;

// Function prototypes
int create_socket();
int bind_socket(int sockfd, int port);
int send_message(int sockfd, const char *message, struct sockaddr_in *dest_addr, socklen_t addr_len);
int receive_message(int sockfd, char *buffer, struct sockaddr_in *src_addr, socklen_t *addr_len);
void close_socket(int sockfd);

#endif // NETWORK_H
