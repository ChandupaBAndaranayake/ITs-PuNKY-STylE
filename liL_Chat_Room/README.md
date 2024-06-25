# TCP Chat Application in C for Windows

This is a simple TCP-based chat application implemented in C for Windows using Winsock (Windows Sockets API). The application allows multiple clients to connect to a server and exchange messages in a chatroom-like environment.

## Features

### Server Side:
- Listens for incoming connections from multiple clients.
- Broadcasts messages to all connected clients.
- Handles disconnections and '/quit' commands gracefully.

### Client Side:
- Connects to the server using its IP address and port.
- Sends messages to the server.
- Receives and displays messages from other clients via the server.

## Requirements

- Windows operating system
- MinGW or any other C compiler for Windows (to compile the code)
- Basic understanding of TCP/IP networking concepts

## How to Use

### Server Side

1. **Compile the Server:**
   - Open Command Prompt or PowerShell.
   - Navigate to the directory containing `server.c`.
   - Compile the server code using gcc (MinGW):

     ```
     gcc -o server server.c -lws2_32
     ```

2. **Run the Server:**
   - After compiling successfully, run the server executable:

     ```
     server.exe
     ```

   - The server will start listening for incoming connections on port 55555 (you can modify this in the code if needed).

### Client Side

1. **Compile the Client:**
   - Open another Command Prompt or PowerShell window.
   - Navigate to the directory containing `client.c`.
   - Compile the client code using gcc (MinGW):

     ```
     gcc -o client client.c -lws2_32
     ```

2. **Run the Client:**
   - After compiling successfully, run the client executable:

     ```
     client.exe
     ```

   - The client will prompt you to enter the server's IP address and port (default is 127.0.0.1:55555 for localhost).

3. **Using the Chat Application:**
   - Once the client connects to the server, you can type messages in the client's console.
   - Messages typed by a client will be sent to the server and then broadcasted to all connected clients (including the sender).
   - Type `/quit` to disconnect from the server and exit the client application.

## Notes

- This is a basic implementation for educational purposes. It lacks advanced features like encryption, user authentication, or error handling.
- Ensure that your firewall settings allow communication through the specified port (55555 by default) if you encounter connection issues.
- For more advanced functionality or security features, consider extending the application with additional programming using Winsock or integrating libraries for enhanced networking capabilities.