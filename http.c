#include <stdio.h>
#include <string.h>

void send_http(char* host, char* msg, char* resp, size_t len);


int main(int argc, char* argv[]) {
  if (argc != 4) {
    printf("Invalid arguments - %s <host> <GET|POST> <path>\n", argv[0]);
    return -1;
  }

  char* host = argv[1];
  char* verb = argv[2];
  //char* path = argv[3];

      char* line1 = "\r\n\r\n";
      char* line2 = "\r\n";
      char* line4 = "Host: ";

      char response[4096];
      char buffer[1024];

      sprintf(buffer,"%s / HTTP/1.0%s%s%s%s",verb,line2,line4,host,line1);
      send_http(argv[1],buffer,response,4096);
      printf("%s\n",response);

   return 0;
}