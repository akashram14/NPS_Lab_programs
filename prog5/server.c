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

void str_echo(int sockfd){
	int n;
	char send[max],recv[max];
	while((n = read(sockfd, recv, 2048)) > 0){
		recv[n] = 0;
		printf("Client %d :", getpid());
		fputs(recv,stdout);
		fputs("Me:",stdout);
		fgets(send, max, stdin);
		write(sockfd, send, strlen(send));
	}
		
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


