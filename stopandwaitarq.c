#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>

#define TIMEOUT 2

typedef struct {
    int sequenceNumber;
    bool isAcked;
} Frame;

void simulateStopAndWaitARQ() {
    Frame frame;
    frame.sequenceNumber = 0;
    frame.isAcked = true;

    printf("Simulating Stop-and-Wait ARQ\n");

    while (frame.sequenceNumber < 10) {
        // Transmit frame
        if (frame.isAcked) {
            printf("Sending frame %d\n", frame.sequenceNumber);
        }

        // Simulating network delay and frame transmission time
        // Here, we assume successful transmission

        // Receive ACK or NAK
        printf("Waiting for ACK\n");
        sleep(1); // Simulating network delay

        if (rand() % 2 == 0) {
            printf("Received ACK for frame %d\n", frame.sequenceNumber);
            frame.isAcked = true;
            frame.sequenceNumber++;
        } else {
            printf("Received NAK for frame %d. Retransmitting...\n", frame.sequenceNumber);
            frame.isAcked = false;
        }
    }

    printf("All frames transmitted successfully.\n");
}

int main() {
    srand(time(NULL)); // Initialize random seed

    simulateStopAndWaitARQ();

    return 0;
}
