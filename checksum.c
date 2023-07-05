#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate the checksum
unsigned short calculateChecksum(unsigned char *data, int dataSize)
{
    unsigned long sum = 0;
    int i;

    // If there is an extra byte at the start, add it to the sum
    if (dataSize % 2 == 1)
    {
        unsigned short firstByte = data[0];
        sum += firstByte;

        // Handle carry overflow
        if (sum & 0xFFFF0000)
        {
            sum = (sum & 0xFFFF) + 1;
        }

        // Increment the data pointer and decrement the data size
        data++;
        dataSize--;
    }

    // Calculate the sum of all 16-bit chunks
    for (i = 0; i < dataSize; i += 2)
    {
        unsigned short chunk = (data[i] << 8) | data[i + 1];
        sum += chunk;

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
    char hexData[100];
    unsigned char data[50];
    unsigned short checksum;
    int dataSize, i;

    printf("Enter the data in hexadecimal format: ");
    fgets(hexData, sizeof(hexData), stdin);
    dataSize = strlen(hexData) - 1;
    hexData[dataSize] = '\0';

    // Remove spaces from the input
    for (i = 0; i < dataSize; i++)
    {
        if (hexData[i] == ' ')
        {
            memmove(hexData + i, hexData + i + 1, dataSize - i);
            dataSize--;
            i--;
        }
    }

    // Convert the input from hexadecimal to binary
    dataSize = dataSize / 2;
    for (i = 0; i < dataSize; i++)
    {
        sscanf(hexData + i * 2, "%2hhx", &data[i]);
    }

    checksum = calculateChecksum(data, dataSize);

    printf("\nStep-by-Step Calculation:\n");
    printf("Data: %s\n", hexData);

    // Print each 16-bit chunk
    printf("16-bit Chunks:\n");
    
    // If there is an extra byte at the start, print it
    if (dataSize % 2 == 1)
    {
        printf("%02X ", data[0]);
        
        // Increment the data pointer and decrement the data size
        *(data+1);
        dataSize--;
    }
    
    for (i = 0; i < dataSize; i += 2)
    {
        unsigned short chunk = (data[i] << 8) | data[i + 1];
        printf("%04X ", chunk);
    }
    
    printf("\n");

    // Calculate the sum of all 16-bit chunks
    unsigned long sum = calculateChecksum(data, dataSize);

    printf("\nChecksum (One's Complement): %04X\n", checksum);

    return 0;
}
