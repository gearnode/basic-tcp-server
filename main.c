/*
Copyright 2018 Bryan Frimin.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define PROTOC_IP 0
#define BACKLOG 30

typedef struct server {
  int listen_fd;
} server_t;

int server_listen(server_t* server) {
  int err = 0;
  struct sockaddr_in server_addr = { 0 };

  err = (server->listen_fd = socket(AF_INET, SOCK_STREAM, PROTOC_IP));

  if (err == -1) {
    perror("socket");
    printf("Failed to create socket endpoint\n");
    return err;
  }


  memset(&server_addr, 0, sizeof(server_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  err = bind(server->listen_fd,
             (struct sockaddr*)&server_addr,
             sizeof(server_addr));

  if (err == -1) {
    perror("bind");
    printf("Failed to bind socket to address\n");
    return err;
  }

  err = listen(server->listen_fd, BACKLOG);
  if (err == -1) {
    perror("listen");
    printf("Failed to put socket in passive mode\n");
    return err;
  }

  return 0;
}


int server_accept(server_t* server) {
  int err = 0;
  int conn_fd;
  socklen_t client_len;
  struct sockaddr_in client_addr;

  client_len = sizeof(client_addr);

  err =
    (conn_fd = accept(server->listen_fd,
                      (struct sockaddr*)&server,
                      &client_len));
  if (err == -1) {
    perror("accept");
    printf("failed accepting connection\n");
    return err;
  }

  printf("Client connected!\n");

  err = close(conn_fd);
  if (err == -1) {
    perror("close");
    printf("failed to close connection\n");
    return err;
  }

  return err;
}

int
main()
{
  int err = 0;
  server_t server = { 0 };
  err = server_listen(&server);

  if (err) {
    printf("Failed to listen on address 0.0.0.0:%d\n",
                        PORT);
    return err;
  }

  for(;;) {
    err = server_accept(&server);
    if (err) {
      printf("Failed accepting connection\n");
      return err;
    }
  }
  return 0;
}
