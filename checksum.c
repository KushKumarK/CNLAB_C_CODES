#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate the checksum
unsigned short calculateChecksum(char *data, int dataSize)
{
    unsigned long sum = 0;
    int i;

    // Calculate the sum of all 16-bit chunks
    for (i = 0; i < dataSize - 1; i += 2)
    {
        unsigned short chunk = (data[i] << 8) | data[i + 1];
        sum += chunk;

        // Handle carry overflow
        if (sum & 0xFFFF0000)
        {
            sum = (sum & 0xFFFF) + 1;
        }
    }

    // If there is an odd number of bytes, add the last byte to the sum
    if (dataSize % 2 == 1)
    {
        unsigned short lastByte = data[dataSize - 1] << 8;
        sum += lastByte;

        // Handle carry overflow
        if (sum & 0xFFFF0000)
        {
            sum = (sum & 0xFFFF) + 1;
        }
    }

    return (unsigned short)(~sum);
}

int main()
{
    char data[100];
    unsigned short checksum;
    int dataSize, i;

    printf("Enter the data: ");
    fgets(data, sizeof(data), stdin);
    dataSize = strlen(data) - 1;
    data[dataSize] = '\0';

    checksum = calculateChecksum(data, dataSize);

    printf("\nStep-by-Step Calculation:\n");
    printf("Data: %s\n", data);

    // Print each 16-bit chunk
    printf("16-bit Chunks:\n");
    for (i = 0; i < dataSize - 1; i += 2)
    {
        unsigned short chunk = (data[i] << 8) | data[i + 1];
        printf("%04X ", chunk);
    }
    if (dataSize % 2 == 1)
    {
        printf("%02X00 ", data[dataSize - 1]);
    }
    printf("\n");

    // Calculate the sum of all 16-bit chunks
    unsigned long sum = 0;
    for (i = 0; i < dataSize - 1; i += 2)
    {
        unsigned short chunk = (data[i] << 8) | data[i + 1];
        sum += chunk;

        // Handle carry overflow
        if (sum & 0xFFFF0000)
        {
            sum = (sum & 0xFFFF) + 1;
        }

        printf("Sum: %08lX\n", sum);
    }

    // If there is an odd number of bytes, add the last byte to the sum
    if (dataSize % 2 == 1)
    {
        unsigned short lastByte = data[dataSize - 1] << 8;
        sum += lastByte;

        // Handle carry overflow
        if (sum & 0xFFFF0000)
        {
            sum = (sum & 0xFFFF) + 1;
        }

        printf("Sum: %08lX\n", sum);
    }

    // Calculate the one's complement of the sum
    unsigned short onesComplement = (unsigned short)(~sum);

    printf("\nChecksum (One's Complement): %04X\n", onesComplement);
    printf("Final Checksum: %04X\n", checksum);

    return 0;
}
