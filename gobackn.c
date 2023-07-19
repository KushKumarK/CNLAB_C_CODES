#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WINDOW_SIZE 4
#define FRAME_COUNT 20

typedef struct {
    int sequenceNumber;
    bool isAcked;
} Frame;

void simulateGoBackNARQ() {
    Frame frames[FRAME_COUNT];
    int base = 0;
    int nextSequenceNumber = 0;

    // Initialize frames
    for (int i = 0; i < FRAME_COUNT; i++) {
        frames[i].sequenceNumber = i;
        frames[i].isAcked = false;
    }

    printf("Simulating Go-Back-N ARQ\n");

    while (base < FRAME_COUNT) {
        // Transmit frames within the window
        for (int i = base; i < base + WINDOW_SIZE && i < FRAME_COUNT; i++) {
            if (!frames[i].isAcked) {
                printf("Sending frame %d\n", frames[i].sequenceNumber);
            }
        }

        // Simulating network delay and frame transmission time
        // Here, we assume successful transmission for all frames

        // Receive acknowledgments
        for (int i = base; i < base + WINDOW_SIZE && i < FRAME_COUNT; i++) {
            if (!frames[i].isAcked) {
                printf("Received ACK for frame %d\n", frames[i].sequenceNumber);
                frames[i].isAcked = true;
                //frames[3].isAcked = false;
                nextSequenceNumber = i + 1;
            }
        }

        // Slide the window
        if (frames[base].isAcked) {
            printf("Sliding window, base = %d\n", base + 1);
            base++;
        } else {
            printf("Retransmitting frames starting from %d\n", base);
            nextSequenceNumber = base;  // Retransmit frames from base
        }
    }

    printf("All frames transmitted successfully.\n");
}

int main() {
    simulateGoBackNARQ();
    return 0;
}
