#include "csapp.h"

int main(int argc, char **argv)
{
     int clientfd, port;
     char *host, buf[MAXLINE];
     rio_t rio;

     if( argc != 3 ){
	  fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	  exit(0);
     }
     host = argv[1];
     port = atoi(argv[2]);

     clientfd = Open_clientfd(host, port);
     Rio_readinitb(&rio, clientfd);

     while( fgets(buf, MAXLINE, stdin) != NULL)
     {
	  Rio_writen(clientfd, buf, strlen(buf));
	  Rio_readlineb(&rio, buf, MAXLINE);
	  fputs(buf, stdout);
     }
     close(clientfd);
     exit(0);
}


