#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_PORT 9991
#define IPADDRESS "127.0.0.1"


int main()
{
	int sockfd;
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("create sockfd error");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in client_addr;
	memset(&client_addr, 0, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(SERVER_PORT);
	client_addr.sin_addr.s_addr = inet_addr(IPADDRESS);
	
	char messages[521] = "I am client bot";
	char buffer[521];
	socklen_t client_addr_size = sizeof(client_addr);
	for(int i=0; i< 10; ++i)
	{
		sendto(sockfd, messages, sizeof(messages), 0, (struct sockaddr*)&client_addr, client_addr_size);
		recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &client_addr_size);
		if(i == 3)
		{
			sendto(sockfd, "exit", sizeof("exit"), 0, (struct sockaddr*)&client_addr, client_addr_size);
			break;
		}
		//printf("received data from server: %s\n", buffer);

	}
	close(sockfd);

}
