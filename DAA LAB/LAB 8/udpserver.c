#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024

void reverseString(char *str) {
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error in socket creation");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error in binding");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    char buffer[MAX_BUFFER_SIZE];
    socklen_t addrLen = sizeof(clientAddr);

    while (1) {
        // Receiving data from the client
        ssize_t receivedBytes = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                         (struct sockaddr *)&clientAddr, &addrLen);

        if (receivedBytes < 0) {
            perror("Error in recvfrom");
            exit(EXIT_FAILURE);
        }

        buffer[receivedBytes] = '\0';  // Null-terminate the received data
        printf("Received from client: %s\n", buffer);

        reverseString(buffer);

        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&clientAddr, addrLen);
    }

    close(sockfd);

    return 0;
}