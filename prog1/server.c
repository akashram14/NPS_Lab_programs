#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char const *argv[]){
	int listen_sock, accepted_sock;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[2048] = {0};
	char *hello = "Hello from server";

	if((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) <= 0){
		perror("socket failed");
		exit(0);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( 12345 );

	if(bind(listen_sock, (struct sockaddr *)&address, sizeof(address)) < 0){
		perror("bind failed");
		exit(0);
	}
	if(listen(listen_sock, 10) < 0){
		perror("listen");
		exit(0);
	}
	if((accepted_sock = accept(listen_sock, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
		perror("accept");
		exit(0);
	}
	read( accepted_sock, buffer, 2048);
	printf("%s\n", buffer);
	send( accepted_sock, hello, strlen(hello), 0);
	printf("Hello sent to client\n");
	close(accepted_sock);
	close(listen_sock);
	return 0;
}


