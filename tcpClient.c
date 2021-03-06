#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <netinet/in.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Easily change the port 
#define PORT 9002
#define LINE_SIZE 80

// Packet Structure 
struct packetHeader{
    int count;
    unsigned int packet_sequence_count;
};

struct hostent * server_hp;
char server_hostname[LINE_SIZE];

// Server Structure

// Output file to write to
FILE *output;

int main(void){
    
    int socket_id;
    socket_id = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socket_id < 0){
        perror("Client: Socket cannot be opened \n");
        exit(1);
    }

    output = fopen("output_result.txt", "w");

    printf("Enter Hostname of the Server: \n");
    scanf("%s", server_hostname);

    if((server_hp = gethostbyname(server_hostname)) == NULL){
        perror("Error: Hostname could not be reached");
        close(socket_id);
        exit(1);
    }
    
    // Specifiy an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = PF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Connect 
    int connection_validate = connect(socket_id, (struct sockaddr *) &server_address, sizeof(server_address));
    if(connection_validate == -1){
        printf("Something went wrong with the connection... \n\n");
        exit(1);
    } else {
        printf("Connected to Socket... \n");
    }

    // Recieve data from the server
    char server_message[256];
    recv(socket_id, server_message, sizeof(server_message), 0);
    printf("The Server Responded: %s\n", server_message);

    // Close the Socket @ the End;
    close(socket_id);
    return 0;
}