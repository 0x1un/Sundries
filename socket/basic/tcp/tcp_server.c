#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> // for close
// #include <fcntl.h> // for open
#include <string.h>
#include <arpa/inet.h>

int main()
{
	char server_message[256] = "You have reached the server!";

	char received[1000];
	// create the server socket
	// if protocol set 0, automatically match the default protocol
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	// define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9991);
	server_address.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY == 0.0.0.0

	// bind the socket to our specified IP and port
	if( (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address))) < 0)
	{
		perror("socket bind error: ");
		exit(EXIT_FAILURE);
	}
	if( listen(server_socket, 5) )
	{
		perror("listen error: ");
		exit(EXIT_FAILURE);
	}
	int client_socket;
	
	for(;;)
	{

		if( (client_socket = accept(server_socket, NULL, NULL)) < 0 )
		{
			printf("accept from client error!\n");
			continue;
		}

		recv(client_socket, received, sizeof(received), 0);
		printf("reciving from client: %s\n\n", received);
		printf("%s, %d\n", inet_ntoa(server_address.sin_addr), server_address.sin_port);

		if( strcmp(received, "exit") == 0 )
		{
			printf("I\'m dead\n");
			break;
		}

	}
	// send(client_socket, server_message, sizeof(server_message), 0);
	close(server_socket);


	return 0;
}
