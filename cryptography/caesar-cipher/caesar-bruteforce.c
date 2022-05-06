/*
* Filename: caesar-bruteforce.c
* Function: Bruteforce text encrypted with the caesar cipher, using wordlist.
*
* by: tcincere [https://github.com/tcincere]
*/

//For strcasestr() - insensitive substring search.
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void bruteforce(char ciphertext[]);
void find_match(char plaintext[], int key);


int main(int argc, char *argv[])
{
    //Introductory text.     
    printf("\n\tCAESAR BRUTEFORCE\n");
    printf("\t  by: tcincere\n");
    printf("    ------------------------\n");
    
    char ciphertext[100];

    printf("\n[+] Enter cipher-text: ");
    fgets(ciphertext, 100, stdin);
    
    //Call function.
    bruteforce(ciphertext);  
  
    return 0;
}


void bruteforce(char ciphertext[])
{
    int key = 1;
    while (key != 26) 
    {
        //Dynamically create plaintext array.
        char *plaintext = (char *) malloc(strlen(ciphertext) + 1);
        
        //Remove one for NULL character.
        for (int j = 0; j < strlen(ciphertext) - 1; j++)
        {
            //Check letter case.
            if (isupper(ciphertext[j]))
            {
                plaintext[j] = (ciphertext[j] - key);

                if (plaintext[j] < 'A')
                    plaintext[j] += 'Z' - 'A' + 1;
            }
            else if (islower(ciphertext[j]))
            {
                plaintext[j] = (ciphertext[j] - key);

                if (plaintext[j] < 'a')
                    plaintext[j] += 'z' - 'a' + 1;
            }
            else
            {
                //Keep non-ascii text as is.
                plaintext[j] = ciphertext[j];
            }
        }
            //Find relavent plaintexts.
            find_match(plaintext, key);
            free(plaintext);
            key++;
    }
}


void find_match(char plaintext[], int key)
{
    FILE *fpointer;
    //Initiate file pointer for readiing.
    fpointer = fopen("caesar-wordlist.txt", "r");
    
    //Error catcher.
    if (fpointer == NULL)
    {
        fprintf(stderr, "ERROR: File not found\n");
        exit(EXIT_FAILURE);
    }
    
    char word[20];
    while (fgets(word, 20, fpointer) != NULL)
    {
        //Strip new line from line.
        word[strcspn(word, "\n")] = 0;
        char *result;
        
        //Find words larger than three.
        if (strlen(word) >= 4)
            result = strcasestr(plaintext, word);
        else
            continue;
        
        if (result != NULL)
        {
            printf("\nMatch: %s\n", word);
            printf("[%d]  %s\n", key, plaintext);
            break;

        } else 
        {
            continue;
        }
    }
    
    //Close the file.
    fclose(fpointer);
}