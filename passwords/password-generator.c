/*
 * Filename: password-generator.c
 * Function: Generate passwords based on user input.
 *
 * by: tcincere [https://github.com/tcincere]
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate_password(int password_length, int quantity);

int main (int argc, char *argv[]) 
{
    //Argument check.
    if (argc < 3 || argc > 3)
    {
        fprintf(stderr, "ERROR: Invalid argument count\n");
        fprintf(stderr, "Usage: %s length quantity\n", argv[0]);
        exit(1);
    }
  
    //Convert string to integer.
    int password_length = strtol(argv[1], NULL, 10);
    int quantity = strtol(argv[2], NULL, 10);
    
    //Prettier output.
    printf("\n\tPASSWORDS\n");
    printf("    -----------------\n\n");

    //Call generate_password function.
    generate_password(password_length, quantity);
    
    return 0;
}


void generate_password(int password_length, int quantity)
{
    
    srand(time(NULL));

    char alphabet[52] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char special_characters[16] = "!£$%^&();[]/+{}";
    char numbers[10] = "1234567890";

    int k = 0;

    while (k < quantity) 
    {
        char *password = (char *) malloc(password_length + 1);
        
        for (int i = 0; i < password_length; i++) 
        {
            password[i] = special_characters[rand() % strlen(special_characters)]; 

            if (i % 1 == 0)
            {
                password[i] = alphabet[rand() % strlen(alphabet)];
            }
        
            if (i % 3 == 0)
            {
                password[i] = numbers[rand() % strlen(numbers)];          
            }
        }
        
        printf("%d. %s\n", k, password);
        free(password);
        k++;
    }
} 
