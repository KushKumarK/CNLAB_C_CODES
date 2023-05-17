#include <stdio.h>
#include <math.h>

int main() {
    int data[20], hammingCode[30];
    int dataBits, hammingCodeLen, i, j, k;

    printf("Enter the number of data bits: ");
    scanf("%d", &dataBits);

    // Calculate the number of parity bits required
    for (i = 0; i < dataBits; i++) {
        hammingCode[i] = 0; // Initialize all bits to 0
    }
    hammingCodeLen = dataBits;

    // Read the data bits
    printf("Enter the data bits (in binary): ");
    for (i = 0; i < dataBits; i++) {
        scanf("%d", &data[i]);
        hammingCode[dataBits - i - 1] = data[i]; // Store data bits in reverse order
    }

    // Calculate the number of parity bits required
    for (i = 0; i < dataBits; i++) {
        if (pow(2, i) >= dataBits + i + 1)
            break;
    }
    int numParityBits = i;

    // Set the parity bits
    for (i = 0; i < numParityBits; i++) {
        int parityBitPos = pow(2, i) - 1;
        int parityBit = 0;

        for (j = parityBitPos; j < hammingCodeLen; j += (parityBitPos + 1) * 2) {
            for (k = 0; k <= parityBitPos && j + k < hammingCodeLen; k++) {
                parityBit ^= hammingCode[j + k];
            }
        }

        hammingCode[parityBitPos] = parityBit;
    }

    printf("Hamming code: ");
    for (i = hammingCodeLen - 1; i >= 0; i--) {
        printf("%d ", hammingCode[i]);
    }
    printf("\n");

    return 0;
}
