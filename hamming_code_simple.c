#include <stdio.h>
#include <stdbool.h>

// Function to generate Hamming code
void generateHammingCode(int data[], int dataSize, int hammingCode[], int hammingCodeSize) {
    int i, j, k;
    bool isPowerOfTwo;

    // Initialize all bits in the Hamming code as 0
    for (i = 0; i < hammingCodeSize; i++) {
        hammingCode[i] = 0;
    }

    // Copy the data bits into the Hamming code
    j = 0;
    k = 1;
    for (i = 0; i < hammingCodeSize; i++) {
        isPowerOfTwo = (k & (k - 1)) == 0;

        if (!isPowerOfTwo) {
            hammingCode[i] = data[j++];
        }

        k++;
    }

    // Calculate and set the parity bits
    for (i = 0; i < hammingCodeSize; i++) {
        isPowerOfTwo = (i & (i + 1)) == 0;

        if (isPowerOfTwo) {
            int parityBit = 0;

            for (j = i; j < hammingCodeSize; j++) {
                if (j & (1 << i)) {
                    parityBit ^= hammingCode[j];
                }
            }

            hammingCode[i] = parityBit;
        }
    }
}

// Function to check and correct errors in Hamming code
bool checkAndCorrectHammingCode(int receivedHammingCode[], int hammingCodeSize) {
    int errorBitPosition = 0;
    int i, j;

    // Calculate the position of the error bit
    for (i = 0; i < hammingCodeSize; i++) {
        int bit = 0;

        for (j = 0; j < hammingCodeSize; j++) {
            if (j != i && (j & (1 << i))) {
                bit ^= receivedHammingCode[j];
            }
        }

        if (bit != receivedHammingCode[i]) {
            errorBitPosition += i + 1;
        }
    }

    // If an error is detected, correct the received Hamming code
    if (errorBitPosition > 0) {
        printf("Error detected at bit position %d.\n", errorBitPosition);

        // Correct the error by flipping the corresponding bit
        receivedHammingCode[errorBitPosition - 1] ^= 1;

        return true;
    }

    return false;
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // Define the original data bits
    int data[] = {1, 0, 1, 0};

    // Calculate the number of parity bits required
    int dataSize = sizeof(data) / sizeof(data[0]);
    int hammingCodeSize = 0;

    int i = 0;
    while (dataSize + i + 1 > (1 << i)) {
        i++;
    }
    hammingCodeSize = dataSize + i;

    // Create arrays for the Hamming code
    int hammingCode[hammingCodeSize];
    int receivedHammingCode[hammingCodeSize];

    // Generate Hamming code
    generateHammingCode(data, dataSize, hammingCode, hammingCodeSize);

    printf("Original data bits: ");
    printArray(data, dataSize);

    printf("Generated Hamming code: ");
    printArray(hammingCode, hammingCodeSize);

    // Simulate an error by flipping a bit in the received Hamming code
    for (int i = 0; i < hammingCodeSize; i++) {
        receivedHammingCode[i] = hammingCode[i];
    }
    receivedHammingCode[2] ^= 1; // Flip the bit at position 2

    printf("Received Hamming code (with error): ");
    printArray(receivedHammingCode, hammingCodeSize);

    // Check and correct errors in the received Hamming code
    bool hasError = checkAndCorrectHammingCode(receivedHammingCode, hammingCodeSize);

    if (!hasError) {
        printf("No error detected in the received Hamming code.\n");
    } else {
        printf("Corrected Hamming code: ");
        printArray(receivedHammingCode, hammingCodeSize);
    }

    return 0;
}
