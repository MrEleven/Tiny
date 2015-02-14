#ifndef __CSAPP_H__
#define __CSAPP_H__

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

#define MAXLINE 8192
#define RIO_BUFSIZE 8192
#define LISTENQ  1024  /* second argument to listen() */

typedef struct sockaddr SA;

typedef struct {
    int rio_fd;                /* descriptor for this internal buf */
    int rio_cnt;               /* unread bytes in internal buf */
    char *rio_bufptr;          /* next unread byte in internal buf */
    char rio_buf[RIO_BUFSIZE]; /* internal buffer */
} rio_t;


int open_clientfd(char *hostname, int port);
int Open_clientfd(char *hostname, int port);

int open_listenfd(int port);
int Open_listenfd(int port);

/* Rio (Robust I/O) package */
ssize_t rio_readn(int fd, void *usrbuf, size_t n);
ssize_t rio_writen(int fd, void *usrbuf, size_t n);
void rio_readinitb(rio_t *rp, int fd); 
ssize_t	rio_readnb(rio_t *rp, void *usrbuf, size_t n);
ssize_t	rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

/* Wrappers for Rio package */
ssize_t Rio_readn(int fd, void *usrbuf, size_t n);
void Rio_writen(int fd, void *usrbuf, size_t n);
void Rio_readinitb(rio_t *rp, int fd); 
ssize_t Rio_readnb(rio_t *rp, void *usrbuf, size_t n);
int Rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

#endif /* __CSAPP_H__ */ 
