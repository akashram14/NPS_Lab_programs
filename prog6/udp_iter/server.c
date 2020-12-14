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

void str_echo(int sockfd, struct sockaddr * cliaddr, socklen_t clilen){
	ssize_t n;
	char buf[max];
	socklen_t len;	
	for(;;){
		len = clilen;
		memset(buf, '\0', max);
		n = recvfrom(sockfd, buf, max, 0, cliaddr, &len);
		printf("Received :%s", buf);
		sendto(sockfd, buf, n, 0, cliaddr, len);
	}

}

int main(int argc, char **argv){
	int listenfd;
	struct sockaddr_in cliaddr, servaddr;
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(listenfd <= 0){
		perror("Socket creation failed\n");
		exit(0);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(12345);

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	str_echo(listenfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
}


