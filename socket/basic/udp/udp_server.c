#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFF_SIZE 521
#define BIND_PORT 9991

int main()
{
	int sockfd;
	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	{
		perror("create sockfd error");
		exit(EXIT_FAILURE);
	}
	struct sockaddr_in bind_addr;
	memset(&bind_addr, 0, sizeof(bind_addr));
	bind_addr.sin_family = AF_INET;
	bind_addr.sin_port = htons(BIND_PORT);
	bind_addr.sin_addr.s_addr = INADDR_ANY;

	if( (bind(sockfd, (struct sockaddr *)&bind_addr, sizeof(bind_addr))) < 0 )
	{
		perror("bind sockfd error");
		exit(EXIT_FAILURE);
	}

//	if( (listen(sockfd, 6)) < 0 )
//	{
//		perror("listen sock error");
//		exit(EXIT_FAILURE);
//	}
	socklen_t paddr_len = sizeof(bind_addr);
	char buffer[BUFF_SIZE];
	char messages[521] = "I am server bot";
	for(;;)
	{
		recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&bind_addr, &paddr_len);
		printf("received data: %s\n", buffer);
		if(strcmp(buffer, "exit") == 0)
		{
			break;
		}
		sendto(sockfd, messages, sizeof(messages), 0, (struct sockaddr*)&bind_addr, paddr_len);
	}
	close(sockfd);
}

