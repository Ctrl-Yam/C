#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main() {

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 10) <0) {
        perror("Listen failed");
        close(server_fd);
        return 1;
    }

    printf("Server listening on http://localhost:8080...\n");
    printf("Waiting for a client to connect...\n");

    int client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        return 1;
    }

    printf("Client connected\n");

    char buffer[1024] = {0};
    read(client_fd, buffer, sizeof(buffer) -1);
    printf("---Incoming Request---\n%s\n----------\n", buffer);

    char *http_response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n\r\n"
        "<h1>Hello from my C Web Server!</h1>";

    write(client_fd, http_response, strlen(http_response));

    close(client_fd);
    close(server_fd);
    return 0;
}