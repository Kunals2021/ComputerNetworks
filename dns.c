#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Invalid arguments - %s <host> <port>", argv[0]);
    return -1;
  }

  char* host = argv[1];
  long port = atoi(argv[2]);

  struct addrinfo hints;
  struct addrinfo *results;
  struct addrinfo *record;

  void* raw_addr;
  char cport[50];
  char buffer[50];

  sprintf(cport,"%ld",port);// converting long port to char port 

  memset(&hints,0,sizeof(struct addrinfo));
   hints.ai_family = PF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_protocol = IPPROTO_TCP;
   hints.ai_flags = AI_PASSIVE;

  if( (getaddrinfo(host,cport,&hints,&results)) != 0)
   {
   perror("Failed error");
   exit(EXIT_FAILURE);
   }

   for(record = results; record!= NULL;record = record->ai_next)
        {
        if (record->ai_family == AF_INET)
        { // Address is IPv4
        struct sockaddr_in* tmp = (struct sockaddr_in*)record->ai_addr; // Cast addr into AF_INET container
        raw_addr = &(tmp->sin_addr); // Extract the address from the container
        printf("IPv4 %s\n", inet_ntop(record->ai_family,raw_addr,buffer,50));
        }
        else
         { // Address is IPv6
         struct sockaddr_in6* tmp = (struct sockaddr_in6*)record->ai_addr; // Cast addr into AF_INET6 container
         raw_addr = &(tmp->sin6_addr); // Extract the address from the container
         printf("IPv6 %s\n", inet_ntop(record->ai_family,raw_addr,buffer,50));
         }
       }
  freeaddrinfo(results);
  return 0;
}