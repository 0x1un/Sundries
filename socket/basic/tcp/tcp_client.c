#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int network_socket;
		
	// recv(network_socket, &server_response, sizeof(server_response), 0);

	// print out the server's response
	// printf("The server sent the data: %s\n", server_response);
	for(;;)
	{
		network_socket = socket(AF_INET, SOCK_STREAM, 0);

		struct sockaddr_in server_address;
		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(9991);
		server_address.sin_addr.s_addr = INADDR_ANY;

		int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

		if( connection_status == -1 )
		{
			printf("There was an error making a connection to the remote socket \n\n");
		}
		char received[256];
		scanf("%s", received);
		if ( strcmp(received, "exit") == 0 )
		{
			send(network_socket, "exit", sizeof("exit"), 0);
			close(network_socket);
			exit(0);
		}

		send(network_socket, received, sizeof(received), 0);
	}
	close(network_socket);
	return 0;
}
