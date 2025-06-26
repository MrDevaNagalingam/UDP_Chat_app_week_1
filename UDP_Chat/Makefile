CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinc
LDFLAGS =

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SERVER_SRC = $(SRC_DIR)/udp_server.c $(SRC_DIR)/network.c $(SRC_DIR)/state_machine.c
CLIENT_SRC = $(SRC_DIR)/udp_client.c $(SRC_DIR)/network.c $(SRC_DIR)/state_machine.c
SERVER_OBJ = $(OBJ_DIR)/udp_server.o $(OBJ_DIR)/network.o $(OBJ_DIR)/state_machine.o
CLIENT_OBJ = $(OBJ_DIR)/udp_client.o $(OBJ_DIR)/network.o $(OBJ_DIR)/state_machine.o
SERVER_EXEC = udp_server
CLIENT_EXEC = udp_client

all: $(SERVER_EXEC) $(CLIENT_EXEC)

$(SERVER_EXEC): $(SERVER_OBJ)
	$(CC) $(SERVER_OBJ) -o $(SERVER_EXEC) $(LDFLAGS)

$(CLIENT_EXEC): $(CLIENT_OBJ)
	$(CC) $(CLIENT_OBJ) -o $(CLIENT_EXEC) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(SERVER_EXEC) $(CLIENT_EXEC)

.PHONY: all clean

