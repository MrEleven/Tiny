#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

int open_clientfd(char *hostname, int port)
{
     int clientfd;
     struct hostent *hp;
     struct sockaddr_in serveraddr;

     if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
     {
	  return -1;
     }

     if ((hp = gethostbyname(hostname)) == NULL)
	  return -2;

     bzero((char *) &serveraddr, sizeof(serveraddr));
     serveraddr.sin_family = AF_INET;
     bcopy((char* )hp->h_addr_list[0],
	   (char *)&serveraddr.sin_addr.s_addr, hp->h_length);
     serveraddr.sin_port = htons(port);

     if( connect(clientfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
	  return -1;
     return clientfd;
}
