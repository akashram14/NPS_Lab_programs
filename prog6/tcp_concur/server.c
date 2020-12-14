#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

void str_echo(int sockfd){
	ssize_t n;
	char buf[2048];
again:
	while((n = read(sockfd, buf, 2048)) > 0){
		write(sockfd, buf, n);
		buf[n] = 0;
		printf("Received : %s",buf);
	}
	if(n<0 && errno == EINTR)
		goto again;
	else if(n<0)
		perror("str_echo: read error");
}

int main(int argc, char **argv){
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd <= 0){
		perror("Socket creation failed\n");
		exit(0);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(12345);

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	listen(listenfd, 100);
	for(; ;){
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
		if((childpid = fork() == 0)){
			close(listenfd);
			str_echo(connfd);
			close(connfd);
			exit(0);
		}
		close(connfd);
	}
}


