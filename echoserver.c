#include "csapp.h"

void echo(int connfd)
{
     size_t n;
     char buf[MAXLINE];
     rio_t rio;

     Rio_readinitb(&rio, connfd);
     while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
     {
	  printf("server received %d bytes\n", n);
	  Rio_writen(connfd, buf, n);
     }
}

int main(int argc, char **argv)
{
     int listenfd, connfd, port, clientlen;
     struct sockaddr_in clientaddr;
     struct hostent *hp;
     char *haddrp;

     if( argc != 2 ) {
	  fprintf(stderr, "usage: %s <port>\n", argv[0]);
	  exit(0);
     }
     port = atoi(argv[1]);

     listenfd = Open_listenfd(port);
     while(1)
     {
	  clientlen = sizeof(clientaddr);
	  connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);

	  hp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
	  haddrp = inet_ntoa(clientaddr.sin_addr);
	  printf("server connected to %s (%s)\n", hp->h_name, haddrp);

	  echo(connfd);
	  close(connfd);
     }
     
     exit(0);
}
