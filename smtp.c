#include <stdio.h>
#include <string.h>

int connect_smtp(const char* host, int port);

void send_smtp(int sock, const char* msg, char* resp, size_t len);

/*
  Use the provided 'connect_smtp' and 'send_smtp' functions
  to connect to the "lunar.open.sice.indian.edu" smtp relay
  and send the commands to write emails asdescribed in the
  assignment wiki.
 */

  int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Invalid arguments - %s <email-to> <email-filepath>", argv[0]);
    return -1;
  }

  char* rcpt = argv[1];
  char* filepath = argv[2];
  char response[4096];
  char buffer[4096];

  int socket = connect_smtp("lunar.open.sice.indiana.edu",25);
  printf("%s\n", response);

  FILE *fp = fopen(filepath,"r");
         int a = fread(&buffer,sizeof(char),4096,fp);
         (void) a;

    fclose(fp);

   strcat(buffer,"\r\n.\r\n");

   send_smtp(socket,"HELO iu.edu\n", response, 4096);
   printf("%s\n", response);
   char msg2[512];
   sprintf(msg2,"MAIL FROM: %s\n",rcpt);
   send_smtp(socket, msg2, response, 4096);
   printf("%s\n", response);

   char msg3[512];
   sprintf(msg3,"RCPT TO: %s\n",rcpt);
   send_smtp(socket, msg3, response, 4096);
   //printf("%s\n", response);

   send_smtp(socket,"DATA\r\n", response, 4096);
   printf("%s\n", response);

   //sprintf(buffer,"%s.\n.",buffer);
   strcat(buffer,".\n.");
   send_smtp(socket, buffer, response, 4096);
   printf("%s", response);

    // send_smtp(socket,"QUIT\n", response, 1024);
    // printf("%s\n", response);


  return 0;

}