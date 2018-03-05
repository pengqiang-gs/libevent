/*
 * This is a simple blocking client.
 * It opens a connection to host[www.bing.com], send a simple HTTP request header, and print response to stdout.
 * If the network is blocked or unreachable, connection will blocked.
 * If the host is blocked, recv will blocked until host have any response to client.
 * */

#include <netinet/in.h> 	// for sockaddr_in
#include <sys/socket.h> 	// for socket
#include <netdb.h> 			// for gethostbyname

#include <string.h>
#include <unistd.h>
#include <stdio.h>

const char* header = "GET / HTTP/1.0\r\nHost: www.bing.com\r\n\r\n";
const char* hostname = "www.bing.com";

int main(const int argc, const char* argv[])
{
	struct hostent* host = NULL;
	struct sockaddr_in sockaddr;
	const char* current_pos = NULL;
	char recv_buffer[2048] = {0};
	int client_socket = -1;
	int current_len = 0;
	int send_len = 0;
	int recv_len = 0;

	// get hostent by hostname
	if((host = gethostbyname(hostname)) == NULL)
	{
		printf("gethostbyname[name = %s] error.\n", hostname);
		return -1;
	}

	// ipv6 support
	if(host->h_addrtype != AF_INET)
	{
		printf("host[name=%s] don't support ipv6.\n", hostname);
		return -1;
	}

	// create client socket
	if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("create client socket error.\n");
		return -1;
	}

	// connect host
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(80);
	sockaddr.sin_addr = *(struct in_addr*)host->h_addr;
	printf("connecting host[%s]...\n\n", hostname);
	if(connect(client_socket, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
	{
		printf("connect host[name=%s] error.\n", hostname);
		close(client_socket);
		return -1;
	}

	// send header request
	current_pos = header;
	current_len = strlen(header);
	printf("send to host[%s]:\n%s\n", hostname, header);
	while(current_len > 0)
	{
		send_len = send(client_socket, current_pos, current_len, 0);
		if(send_len < 0)
		{
			printf("send request error.\n");
			close(client_socket);
			return -1;
		}

		current_len -= send_len;
		current_pos += send_len;
	}

	// recv message with blocking
	while(1)
	{
		recv_len = recv(client_socket, recv_buffer, sizeof(recv_buffer), 0);
		if(recv_len == 0)
			break;
		else if(recv_len < 0)
		{
			printf("recv response error.\n");
			close(client_socket);
			return -1;
		}
		else
		{
			printf("recv from host[%s]:\n%s\n", hostname, recv_buffer);
		}
	}

	close(client_socket);
	return 0;
}
