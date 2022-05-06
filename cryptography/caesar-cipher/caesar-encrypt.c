/*
 * Filename: caesar-encrypt.c
 * Function: Take string and peform mono-alphabetic substitution [caesar cipher]
 * Output: Text encrypted by the shift.
 *
 * by: tcincere [https://github.com/tcincere]
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// Shift function declaration.
void shift(char plaintext[], int shift_var);


int main(int argc, char *argv[]) 
{    
    //Checking argument count.
    if (argc < 2 || argc > 2)
    {
        fprintf(stderr, "ERROR: Invalid argument count\nUsage: ./caesar shift\n");
        exit(EXIT_FAILURE);
    }
    
    //Convert string to int, for value check.
    int shift_var = strtol(argv[1], NULL, 10);

    //Check integer value.
    if (shift_var < 1 || shift_var > 25) 
    {
      fprintf(stderr, "ERROR: The shift must be between 1 & 25!\n");
      exit(EXIT_FAILURE);
    }
    
    //Introductory text.
    printf("\n");
    printf("\t-------------\n");
    printf("\tCAESAR CIPHER\n");
    printf("\t-------------\n");

    
    char plaintext[100];
    
    //Asking user for input.
    printf("\nEnter plain-text: ");
    fgets(plaintext, 100, stdin);
  
    //Calling shift function
    shift(plaintext, shift_var);

    return 0;
}

void shift(char plaintext[], int shift_var)
{
    //Calculate length of plain-text.
    //Use length to create cipher-text array.
    int length = strlen(plaintext) - 1;
    char ciphertext[length];
    
    //Print length of input string.
    printf("Length: %d\n", length);
    
    // A-Z: 65 - 90, a-z: 97, 122
    for (int j = 0; j < length; j++) 
    {
        if (isupper(plaintext[j]))
        {
            ciphertext[j] = ((plaintext[j] - 65) + shift_var) % 26;
            ciphertext[j] += 65;
        } 
        else if (islower(plaintext[j])) 
        {
            ciphertext[j] = ((plaintext[j] - 97) + shift_var) % 26;
            ciphertext[j] += 97;
        } 
        else 
        {
           ciphertext[j] = plaintext[j];
        }
    }

    printf("Cipher-text: %s\n", ciphertext);
}
    
