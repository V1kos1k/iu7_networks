#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void create_message(char* buf)
{
	
	char msg[30 + 49];
	int k = 0; 
    int n = rand() % 30;
	for(int i = 0 ; i < n ; i++ ) {
		msg[i] = (char) 65+rand()%(90-65);
    }

	strcpy(buf, (const char *) msg);
}

int main(int argc, char *argv[])
{
    const char *server_name = "localhost";
    const int server_port = 8877;

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;

    //записываем имя сервера в sin_addr
    inet_pton(AF_INET, server_name, &server_address.sin_addr);

    server_address.sin_port = htons(server_port);

    int sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        printf("could not create socket\n");
        return 1;
    }
    srand (time(NULL));  

    for (int i = 0; i < 10; i++) {
        char s[512];
        create_message(s);
        printf("1\t%s\n", s);
        const char *data_to_send = s; 
        int len = sendto(sock, data_to_send, strlen(data_to_send), 0, 
                    (struct sockaddr *)&server_address, sizeof(server_address));
        sleep(1);
    }

    close(sock);
    return 0;
}