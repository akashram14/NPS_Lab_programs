#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char const *argv[]){
	int sock = 0;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[2048] = {0};
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket error");
		exit(0);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0){
		perror("wrong ip");
		exit(0);
	}
	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		perror("connection failed");
		exit(0);
	}
	send(sock, hello, strlen(hello), 0);
	printf("Hello message sent to server\n");
	read(sock, buffer, 2048);
	printf("%s\n", buffer);
	return 0;
}
