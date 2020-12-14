#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

const int max = 2048;

void str_cli(FILE *fp, int sockfd){
	char sendline[max], recvline[max];
	while(fgets(sendline, max, fp) != NULL){
		write(sockfd, sendline, strlen(sendline));
		memset(recvline, '\0',  max);
		if(read(sockfd, recvline, max) == 0){
			perror("server terminated prematurely");
			exit(0);
		}
		fputs(recvline, stdout);
	}
}

int main(int argc, char **argv){
	int sockfd;
	struct sockaddr_in servaddr;
	if(argc != 2){
		perror("Usage: ./client <IPaddress>");
		exit(0);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(12345);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
	str_cli(stdin, sockfd);
	exit(0);
}
