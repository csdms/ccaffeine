#include <stdio.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pwd.h>
#include <string.h>
#include <gnu/getopt/getCCAFEopt.h>

#define BSIZ 3*BUFSIZ 
  
enum {
NO_FUNCTION,
PUSH,
PULL
};

  enum {
    NORMAL_BUF,
    LINE_BUF,
    NO_BUF
    };

enum {
  NO_CONNECTION,
  SERVER,
  CLIENT
};

char *basename();

static void usage()
{
  char *usg = "usage: \tpull [-csnl] <port#> [<hostname>]\n \tpush [-csnl] <port#> [<hostname>]\n\t\t-c\tclient - arguments <port#> *and* <hostname> required \n\t\t-s\tserver - argument <port#> only required\n\t\t-l\tline buffered IO\n\t\t-n\tIO not buffered\n";
  fprintf(stderr,usg);
}


main(argc,argv)
int argc;
char **argv;
{
  int s, t, buffering = NORMAL_BUF, connectionType = NO_CONNECTION, error = 0;
  char buf[BSIZ], *pname, *hostName = NULL;
  struct sockaddr_in from, sin, server;
  int len = sizeof(from),pno,red, function = NO_FUNCTION, opt;
  FILE *fp;
  struct servent *sp;
  struct hostent *hp;
/* 
/* Whether or not the stdin or stdout is line or not buffered fread will
/* block until if reads the number of bytes it is told or until it gets
/* an EOF.  ReadBufLen is the length of the reads: it must be 1 if it is
/* either line or not buffered.
 */  
  int readBufLen = BSIZ;

  while((opt = getCCAFEopt(argc, argv, "scln")) != -1)
    {
      switch (opt) {
      case 's':
	/* server - listens for connections */
	connectionType = SERVER;
	break;
      case 'c':
	/* client - attempts to connect to a server */
	connectionType = CLIENT;
	break;
      case 'l':
	buffering = LINE_BUF;
	readBufLen = 1;
	break;
      case 'n':
	buffering = NO_BUF;
	readBufLen = 1;
	break;
      case '?':
	error++;
	break;
      }
    }
  pname = basename(argv[0]);
  if(!strcmp(pname, "push"))
    {
      function = PUSH;
      if(connectionType == NO_CONNECTION) connectionType = CLIENT;
    }
  else
    {
      if(!strcmp(pname, "pull"))
	{
	  function = PULL;
	  if(connectionType == NO_CONNECTION) connectionType = SERVER;
	}
      else
	{
	  error++;
	  fprintf(stderr, 
		  "command name should be either \"push\" or \"pull\"\n");
	}
    }
  if(error)
    {
      usage();
      exit(-1);
    }
  if(argc <= optCCAFEind)
    {
      usage();
      exit(-1);
    }

  pno = atoi(argv[optCCAFEind]);

  if(connectionType == CLIENT)
    {
      if(argc <= optCCAFEind)
	{
	  usage();
	  exit(-1);
	}
      hostName = argv[++optCCAFEind];
    }


  switch((char)connectionType)
    {
    case SERVER:
      bzero(&sin, sizeof(sin));
      bzero(&from, sizeof(from));
      sin.sin_port = htons(pno);
      t = socket(AF_INET,SOCK_STREAM, 0);
      if(bind(t,&sin,sizeof(sin))) { perror(pname);
				     fprintf(stderr,"bind: network problem\n");
				     exit(-4);
				   }
      listen(t,5);
      s = accept(t, &from, &len);
      break;
    case CLIENT:
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
      break;
    default:
      perror("This cannot happen");
      break;
    }
  
  switch((char)function) {
  case PULL:
    fp = fdopen(s,"r");
    break;
  case PUSH:
    fp = fdopen(s,"w");
    break;
  }


  switch((char)buffering)
    {
    case NORMAL_BUF:
      break;
    case LINE_BUF:
      setvbuf(fp, NULL, _IOLBF, BSIZ);
      setvbuf(stdout, NULL, _IOLBF, BSIZ);
      break;
    case NO_BUF:
      setvbuf(fp, NULL, _IONBF, BSIZ);
      setvbuf(stdout, NULL, _IONBF, BSIZ);
      break;
    }

  
  switch((char)function) {
  case PULL:
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
    break;
  case PUSH: 
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
    break;
  }
  exit(0);
}
