#include <stdio.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pwd.h>
#include <string.h>
// #include <gnu/getopt/getCCAFEopt.h>

#define BSIZ BUFSIZ

int main(int argc, char** argv) {
  int s, t, error = 0;
  char buf[BSIZ], *pname, *hostName = NULL;
  struct sockaddr_in from, sin, server;
  int len = sizeof(from),pno,red;
  FILE *fp;
  struct servent *sp;
  struct hostent *hp;
  int readBufLen = BSIZ;

  hostName = "localhost";
  pno = 3141;
  

  hp = gethostbyname(hostName);
  if(hp == NULL) { perror(pname);
  fprintf(stderr,"unknown host: %s\n", hostName);
  exit(-2);
  }
  bzero(&server, sizeof(server));
  bcopy(hp->h_addr,&server.sin_addr,hp->h_length);
  server.sin_family = hp->h_addrtype;
  server.sin_port = htons(pno);  
  s = socket(AF_INET,SOCK_STREAM,0);
  if(s < 0) { perror(pname);
  fprintf(stderr,"socket: there is some network problem\n");
  exit(-3);
  }
  if(connect(s,&server,sizeof(server)) < 0)
    {
      perror(pname);
      fprintf(stderr,"connect: there is some network problem\n");
      exit(-3); 
    }
  fp = fdopen(s,"r");
  while((red = fread(buf,1,readBufLen,fp)) != 0)
    {
      if(fwrite(buf,1,red,stdout) == 0){perror(pname);exit(-1);}
      if(ferror(fp))
	{
	  fprintf(stderr, "error occurred on IO stream\n");
	  perror(pname);
	  break;
	}
      if(feof(fp)) break;	
    }
  fclose(fp);
  exit(0);
}
