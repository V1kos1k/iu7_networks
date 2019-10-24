#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    int SERVER_PORT = 8877;

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    int sock;
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        printf("could not create socket\n");
        return 1;
    }

    if ((bind(sock, (struct sockaddr *)&server_address, sizeof(server_address))) < 0)
    {
        printf("could not bind socket\n");
        return 1;
    }

    struct sockaddr_in client_address;
    int client_address_len = 0;

    int max = 0;
    char maxValue[50];
    
    int i = 0;

    while (true)
    {
        char buffer[50];

        int len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_address, &client_address_len);

        buffer[len] = '\0';
        i++;
        printf("'%s'\n", buffer);

        if (len > max) {
            max = len;
            strcpy(maxValue, buffer);
        }
        printf("\nmaxLength: '%d' value %s\n", max, maxValue);
        // if (i == 10) {
        //     break;
        // }
    }

    printf("\nmaxLength: '%d' value %s\n", max, maxValue);
    close(sock);

    return 0;
}