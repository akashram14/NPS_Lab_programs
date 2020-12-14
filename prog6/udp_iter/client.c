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

void dg_cli(FILE *fp, int sockfd, struct sockaddr * servaddr, socklen_t servlen){
	int n;
	char sendline[max], recvline[max + 1];
	while(fgets(sendline, max, fp) != NULL){
		sendto(sockfd, sendline, strlen(sendline), 0, servaddr, servlen);
		n = recvfrom(sockfd, recvline, max, 0, NULL, NULL);
		recvline[n] = '\0';
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

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(12345);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	dg_cli( stdin, sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
	exit(0);
}
