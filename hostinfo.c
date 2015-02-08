#include "csapp.h"

#define DEBUG

int main(int argc, char **argv)
{
     char **pp;
     struct in_addr addr;    /* Internet Address Structure */
     struct hostent *hostp;
#ifdef COMMENT
     /* DNS host entry */
     struct hostent {
	  char *h_name;          /* Official domain name of host 官方域名*/
	  char **h_aliases;      /* Null-terminated array of domain names 别名*/
	  int h_addrtype;        /* Host Addess Type (AF_INET)  */
	  int h_length;          /* Length of an address, in bytes */
	  char **h_addr_list;    /* Null-terminated array of in_addrstructures */
     }
#endif
     

     if (argc != 2)
     {
	  fprintf(stderr, "usage: %s <domain name or dotted-decimal>\n", argv[0]);
	  exit(0);
     }

     /*change application address to network address*/
     if (inet_aton(argv[1], &addr) != 0)
	  hostp = gethostbyaddr((const char *) &addr, sizeof(addr), AF_INET);
     else
	  hostp = gethostbyname(argv[1]);
     printf("official hostname: %s\n", hostp->h_name);

     /* aliases */
     for( pp = hostp->h_aliases; *pp != NULL; pp++)
	  printf("alias: %s \n", *pp);

     /* address */
     for( pp = hostp->h_addr_list; *pp != NULL; pp++ ){
	  addr.s_addr = ((struct in_addr *)*pp) -> s_addr;
	  printf( "address: %s\n", inet_ntoa(addr) );
     }
     exit(0);
}
