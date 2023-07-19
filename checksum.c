#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

unsigned short calculateChecksum(const char* data) {
    int length = strlen(data);
    unsigned int sum = 0;

    for (int i = 0; i < length; i += 2) {
        // Extract two characters as a hex number
        char hexByte[3];
        strncpy(hexByte, data + i, 2);
        hexByte[2] = '\0';
        unsigned int num = (unsigned int)strtol(hexByte, NULL, 16);
        sum += num;
    }

    // Fold the carry bits
    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    // Take the one's complement of the result
    unsigned short checksum = (unsigned short)~sum;
    return checksum;
}

bool isChecksumValid(const char* data, const char* checksum, unsigned short* calculatedChecksum) {
    *calculatedChecksum = calculateChecksum(data);
    unsigned short givenChecksum = (unsigned short)strtol(checksum, NULL, 16);
    return (*calculatedChecksum == givenChecksum);
}

int main() {
    char input[100];
    char checksum[5];
    unsigned short calculatedChecksum;

    printf("Enter numbers in hexadecimal format (without spaces): ");
    scanf("%s", input);

    printf("Enter checksum in hexadecimal format: ");
    scanf("%s", checksum);

    bool isValid = isChecksumValid(input, checksum, &calculatedChecksum);

    printf("Calculated Checksum: 0x%04X\n", calculatedChecksum);

    if (isValid) {
        printf("Checksum is valid.\n");
    } else {
        printf("Checksum is invalid.\n");
    }

    return 0;
}
