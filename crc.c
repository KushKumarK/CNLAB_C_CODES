#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to perform CRC error detection
int performCRCCheck(char *data, char *divisor)
{
    int dataLen = strlen(data);
    int divisorLen = strlen(divisor);
    int i, j;

    // Append zeros to the data equal to the divisor length minus 1
    for (i = 0; i < divisorLen - 1; i++)
    {
        data[dataLen + i] = '0';
    }
    data[dataLen + i] = '\0';

    // Perform CRC division
    for (i = 0; i < dataLen; i++)
    {
        if (data[i] == '1')
        {
            for (j = 0; j < divisorLen; j++)
            {
                if (data[i + j] == divisor[j])
                {
                    data[i + j] = '0';
                }
                else
                {
                    data[i + j] = '1';
                }
            }
        }

        // Print intermediate steps
        printf("Iteration %d: %s\n", i + 1, data);
    }

    // Check if remainder is zero or not
    for (i = 0; i < dataLen; i++)
    {
        if (data[i] == '1')
        {
            return 0; // Error detected
        }
    }
    return 1; // No error detected
}

int main()
{
    char data[100];
    char divisor[100];

    printf("Enter the data bits: ");
    scanf("%s", data);

    printf("Enter the divisor: ");
    scanf("%s", divisor);

    printf("\nStep-by-Step Calculation:\n");

    if (performCRCCheck(data, divisor))
    {
        printf("\nNo error detected. Data is correct.\n");
    }
    else
    {
        printf("\nError detected. Data is corrupted.\n");
    }

    return 0;
}
