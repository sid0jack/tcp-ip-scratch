#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
  int sockfd;
  struct sockaddr_in server_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("Error creating socket");
    exit(EXIT_FAILURE);
  }

  // Define server address
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(12345);      // Server port
  server_addr.sin_addr.s_addr = INADDR_ANY; // Bind to any available interface

  // Bind socket to the server address
  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(sockfd, 5) < 0)
  {
    perror("Listen failed");
    exit(EXIT_FAILURE);
  }

  printf("Server is listening on port 12345\n");

  // Accept connections (blocking call)
  int client_sockfd;
  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
  if (client_sockfd < 0)
  {
    perror("Accept failed");
    exit(EXIT_FAILURE);
  }

  // Connection is established, can send/receive data...

  // Close client socket
  close(client_sockfd);

  // Close server socket
  close(sockfd);

  return 0;
}
