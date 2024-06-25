#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define MAX_CLIENTS 10
#define MAX_MESSAGE_SIZE 1024

SOCKET client_sockets[MAX_CLIENTS]; // Array to hold client sockets
int num_clients = 0; // Number of connected clients

// Function to handle each client separately
DWORD WINAPI handle_client(LPVOID client_socket_ptr) {
    SOCKET client_socket = *((SOCKET*)client_socket_ptr);
    char message[MAX_MESSAGE_SIZE];
    int bytes_received;

    // Welcome message
    send(client_socket, "Welcome to the chatroom! Type '/quit' to exit.\n", 47, 0);

    while (1) {
        bytes_received = recv(client_socket, message, MAX_MESSAGE_SIZE, 0);
        if (bytes_received > 0) {
            message[bytes_received] = '\0';
            printf("Received: %s", message);

            // Broadcast message to all clients
            for (int i = 0; i < num_clients; ++i) {
                if (client_sockets[i] != INVALID_SOCKET && client_sockets[i] != client_socket) {
                    send(client_sockets[i], message, bytes_received, 0);
                }
            }

            // Check for quit command
            if (strcmp(message, "/quit\n") == 0) {
                break;
            }
        }
        else if (bytes_received == 0) {
            printf("Client disconnected\n");
            break;
        }
        else {
            printf("recv() failed with error\n");
            break;
        }
    }

    // Remove client from the list
    for (int i = 0; i < num_clients; ++i) {
        if (client_sockets[i] == client_socket) {
            closesocket(client_sockets[i]);
            client_sockets[i] = INVALID_SOCKET;
            break;
        }
    }

    closesocket(client_socket);
    return 0;
}

int main() {
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_size = sizeof(client_addr);
    DWORD thread_id;
    HANDLE thread_handle;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return 1;
    }

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Prepare server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(55555); // Port to listen on

    // Bind socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed with error: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CLIENTS) == SOCKET_ERROR) {
        printf("Listen failed with error: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Server started. Waiting for incoming connections...\n");

    // Accept incoming connections and handle clients
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
        if (client_socket == INVALID_SOCKET) {
            printf("Accept failed with error: %d\n", WSAGetLastError());
            closesocket(server_socket);
            WSACleanup();
            return 1;
        }

        printf("Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Add client to the list
        if (num_clients < MAX_CLIENTS) {
            client_sockets[num_clients++] = client_socket;
        } else {
            printf("Too many clients. Connection rejected.\n");
            closesocket(client_socket);
            continue;
        }

        // Create a new thread for each client
        thread_handle = CreateThread(NULL, 0, handle_client, &client_socket, 0, &thread_id);
        if (thread_handle == NULL) {
            printf("CreateThread failed with error: %d\n", GetLastError());
            closesocket(client_socket);
            closesocket(server_socket);
            WSACleanup();
            return 1;
        }

        // Close thread handle (thread will continue to execute)
        CloseHandle(thread_handle);
    }

    // Cleanup
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
