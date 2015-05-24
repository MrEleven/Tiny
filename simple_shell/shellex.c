#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "unistd.h"

#define MAXARGS 128
#define MAXLINES 1024

extern char **environ;

void eval(char *cmdline);
int parse_line(char *buf, char **argv);
int builtin_command(char **argv);

int parse_line(char *buf, char **argv)
{
     char *delim; /* pointer to first space delimiter */
     int argc;    /* Number of args */
     int bg;      /* background job? */

     buf[strlen(buf)-1] = ' ';    // replace trailing '\n' with space
     while (*buf && (*buf == ' ')) // ignore leading spaces
     {
	  buf++;
     }
     argc = 0;
     // split the args by white-space
     while((delim = strchr(buf, ' ')))
     {
	  argv[argc++] = buf;
	  *delim = '\0';
	  buf = delim + 1;
	  while(*buf && (*buf == ' '))
	       buf++;
     }
     argv[argc] = NULL;
     if (argc == 0)
	  return 1;

     if ((bg = (*argv[argc-1] == '&')) != 0)
	  argv[--argc] = NULL;

     return bg;
}

void eval(char *cmdline)
{
     char *argv[MAXARGS];
     char buf[MAXLINES];
     int bg;
     pid_t pid;

     // analyse the command argv and if run background
     strcpy(buf, cmdline);
     bg = parse_line(buf, argv);
     // if argv[0] is NULL, the no command
     printf("argv[0] = %s", argv[0]);
     if (argv[0] == NULL)
	  printf("shit\n");
	  return;

     // anaylse if the builtin command, if not run in another process
     if(!builtin_command(argv))
     {
	  if ((pid = fork()) == 0)
	  {
	       printf("executed\n");
	       if (execve(argv[0], argv, environ) < 0)
	       {
		    printf("%s: Command not found.\n", argv[0]);
		    exit(0);
	       }
	  }

	  if (!bg)
	  {
	       int status;
	       if (waitpid(pid, &status, 0) < 0)
		    printf("waitgh: waitpid error\n");
//		    unix_error("waitfg: waitpid error");
	  }
	  else
	       printf("%d %s", pid, cmdline);
     }
     return;
}

int builtin_command(char **argv)
{
     printf("fuck\n");
     if (!strcmp(argv[0], "quit"))
	  exit(0);
     if (!strcmp(argv[0], "&"))
	  return 1;
     return 0;
}

int main()
{
     char cmdline[MAXLINES];
     while(1) {
	  printf(">");
	  fgets(cmdline, MAXLINES, stdin);
	  if (feof(stdin))
	  {
	       exit(0);
	  }
	  eval(cmdline);
     }
     return 0;
}

