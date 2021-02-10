#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <netinet/in.h>

#include <sys/socket.h>
#include <unistd.h>

#define PORT 9002
int main() {

    char server_message[256] = "You have reached the server!";

    // Connect to Socket
    int server_socket;
    server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in server_address;
    server_address.sin_family = PF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    listen(server_socket, 5);
    
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);
    if(client_socket == -1){
        printf("Failed to Accept Connection: %d", client_socket);
        exit(1);
    }
    close(server_socket);
}