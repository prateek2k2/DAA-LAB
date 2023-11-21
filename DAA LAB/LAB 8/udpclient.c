#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error in socket creation");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    char message[MAX_BUFFER_SIZE];

    while (1) {
        printf("Enter a string to send (type 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);

        message[strcspn(message, "\n")] = '\0';

        sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

        if (strcmp(message, "exit") == 0) {
            break;
        }

        char buffer[MAX_BUFFER_SIZE];
        socklen_t addrLen = sizeof(serverAddr);
        ssize_t receivedBytes = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                         (struct sockaddr *)&serverAddr, &addrLen);

        if (receivedBytes < 0) {
            perror("Error in recvfrom");
            exit(EXIT_FAILURE);
        }

        buffer[receivedBytes] = '\0';  // Null-terminate the received data
        printf("Reversed string from server: %s\n", buffer);
    }

    close(sockfd);

    return 0;
}