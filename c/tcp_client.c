#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
  int sockfd;
  struct sockaddr_in server_addr;
  char message[] = "Hello, server!";
  char buffer[1024];

  // Create a socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("Error creating socket");
    exit(EXIT_FAILURE);
  }

  // Define the server address
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(12345);                  // Server port
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

  // Connect to the server
  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    perror("Connect failed");
    exit(EXIT_FAILURE);
  }

  // Send a message to the server
  if (send(sockfd, message, strlen(message), 0) < 0)
  {
    perror("Send failed");
    exit(EXIT_FAILURE);
  }

  // Optionally, receive a response from the server
  if (recv(sockfd, buffer, sizeof(buffer), 0) < 0)
  {
    perror("Receive failed");
    exit(EXIT_FAILURE);
  }

  printf("Server response: %s\n", buffer);

  // Close the socket
  close(sockfd);

  return 0;
}
