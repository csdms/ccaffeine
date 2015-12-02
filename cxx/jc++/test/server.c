#include <stdio.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pwd.h>
#include <string.h>
/* #include <getopt.h> */

#define BSIZ BUFSIZ

int main(int argc, char** argv) {

  int s, t, error = 0;
  char buf[BSIZ], *pname, *hostName = NULL;
  struct sockaddr_in from, sin, server;
  int len = sizeof(from),pno,red;
  FILE *fp;
  struct servent *sp;
  struct hostent *hp;
/*  extern char *optarg; extern int optind; */
  int readBufLen = BSIZ;

  pno = 3141;

  memset(&sin, 0, sizeof(sin));
  memset(&from,0,  sizeof(from));
  sin.sin_port = htons(pno);
  t = socket(AF_INET,SOCK_STREAM, 0);
  if(bind(t,&sin,sizeof(sin))) { perror(pname);
  fprintf(stderr,"bind: network problem\n");
  exit(-4);
  }
  listen(t,5);
  s = accept(t, &from, &len);

  fp = fdopen(s,"w");

  while((red = fread(buf,1,readBufLen,stdin)) != 0) 
    {
      if(fwrite(buf,1,red,fp) == 0){perror(pname);exit(-1);}
      if(ferror(fp))
	{
	  fprintf(stderr, "error occurred on IO stream\n");
	  perror(pname);
	  fclose(fp);
	  exit(-5);
	  break;
	}
      if(feof(stdin)) break;	
    }
  fclose(fp);
  exit(0);
}
