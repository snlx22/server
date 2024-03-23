#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

  char buffer[1024];
  int server = socket(AF_INET, SOCK_STREAM, 0);
  int client, x, port;

  printf("What port would you like to connect to?\n");
  scanf("%d", &port);
  printf("Server is running...\n");
  sleep(1);

  struct sockaddr_in caddr;
  struct sockaddr_in saddr = {.sin_family = AF_INET,
                              .sin_port = htons(port),
                              .sin_addr.s_addr = htonl(INADDR_ANY)};

  printf("Server is runnin on port %d...\n", port);
  sleep(1);
  bind(server, (struct sockaddr *)&saddr, sizeof(saddr));
  listen(server, 5);
  printf("Listening...\n");
  int csize = sizeof(caddr);

  while (1) {
    client = accept(server, (struct sockaddr *)&caddr, &csize);
    x = recv(client, buffer, sizeof(buffer), 0);

    send(client, buffer, x, 0);

    puts(buffer);
    fflush(stdout);
  }

  close(client);
  close(server);
  return 0;
}
