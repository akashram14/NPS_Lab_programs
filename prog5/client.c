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
	int n;
	char send[max],recv[max];
	while(1){
		fputs("Me:", stdout);
		fgets(send, max, fp);
		if(strlen(send) == 0) break;
		write(sockfd, send, strlen(send));
		if((n = read(sockfd, recv, max)) == 0){
			perror("something bad happened");
		}
		recv[n] = 0;
		fputs("Server:", stdout);
		fputs(recv, stdout);
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
