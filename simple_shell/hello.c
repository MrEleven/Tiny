#include "stdio.h"
#include "stdlib.h"

int main(int argc, char **argv, char **envp)
{
     // write is the system call of Linux,
     // compile with c89 not c99, c99 will throw a warnning
     // gcc hello.c -o hello -std=c89
     write(1, "hello world\n", 12);
     exit(0);
}
