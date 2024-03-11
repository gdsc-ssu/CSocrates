#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define RESPONSE_HEADER "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
#define RESPONSE_BODY "<html><body><h1>Hello, World!</h1></body></html>"

void handle_client(int client_socket)
{
    char buffer[1024];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received > 0)
    {
        buffer[bytes_received] = '\0';
        printf("Received request:\n%s\n", buffer);

        // Send HTTP response
        send(client_socket, RESPONSE_HEADER, strlen(RESPONSE_HEADER), 0);
        send(client_socket, RESPONSE_BODY, strlen(RESPONSE_BODY), 0);
    }

    close(client_socket);
}

int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Socket bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 10) == -1)
    {
        perror("Socket listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1)
    {
        // Accept a connection
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) == -1)
        {
            perror("Socket accept failed");
            exit(EXIT_FAILURE);
        }

        // Handle the client request
        handle_client(client_socket);
    }

    // Close the server socket
    close(server_socket);

    return 0;
}
