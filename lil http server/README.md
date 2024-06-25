# Simple HTTP Server in C using Winsock

This is a simple HTTP server implemented in C for Windows using the Winsock API. It listens on port 8080 and responds with a basic "Hello, World!" HTML page to incoming HTTP requests.

## Prerequisites

To compile and run this program, you need:

- Windows operating system
- gcc compiler (or any other C compiler that supports Winsock)
- Winsock library (`-lws2_32`)

## Compiling the Program

You can compile the program using gcc with the following command in your command prompt or terminal:

```bash
gcc -o http_server http_server.c -lws2_32
```

## Running the Server

After compiling, you can run the server by executing the compiled executable:

```bash
http_server.exe
```
The server will start listening on port 8080.

## Notes
- Error handling is minimal for clarity in this example. In production code, consider adding more robust error handling.
- This server handles only one client at a time. For concurrent handling of multiple clients, consider using multithreading or asynchronous I/O techniques.
- Ensure that you run the server with administrator privileges if you bind to a port below 1024 (e.g., port 80, 443) as these are reserved ports.