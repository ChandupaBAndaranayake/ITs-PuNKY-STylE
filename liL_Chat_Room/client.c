#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define MAX_MESSAGE_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET client_socket;
    struct sockaddr_in server_addr;
    char message[MAX_MESSAGE_SIZE];
    int bytes_received;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return 1;
    }

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Prepare server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server's IP address
    server_addr.sin_port = htons(55555); // Server's port

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Connection failed\n");
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    // Receive welcome message from server
    bytes_received = recv(client_socket, message, MAX_MESSAGE_SIZE, 0);
    if (bytes_received > 0) {
        message[bytes_received] = '\0';
        printf("%s", message);
    }

    // Start sending and receiving messages
    while (1) {
        // Read user input
        fgets(message, MAX_MESSAGE_SIZE, stdin);

        // Send message to server
        send(client_socket, message, strlen(message), 0);

        // Check for quit command
        if (strcmp(message, "/quit\n") == 0) {
            break;
        }

        // Receive message from server
        bytes_received = recv(client_socket, message, MAX_MESSAGE_SIZE, 0);
        if (bytes_received > 0) {
            message[bytes_received] = '\0';
            printf("%s", message);
        }
    }

    // Cleanup
    closesocket(client_socket);
    WSACleanup();

    return 0;
}
