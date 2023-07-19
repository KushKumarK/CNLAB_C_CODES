#include <stdio.h>
#include <string.h>

// Simulate server processing the request
void processRequest(const char* request, char* response) {
    // In this simple example, the server echoes the request back as the response
    strcpy(response, request);
}

int main() {
    char request[100];
    char response[100];

    printf("Client: Enter your request: ");
    scanf("%s", request);

    // Simulate network delay (in a real-world scenario, this would be actual network communication)
    printf("Sending request to server...\n");
    sleep(1);

    // Simulate server processing the request (in a real-world scenario, the server would perform actual processing)
    processRequest(request, response);

    // Simulate network delay (in a real-world scenario, this would be actual network communication)
    printf("Sending response to client...\n");
    sleep(1);

    printf("Server: Response: %s\n", response);

    return 0;
}
