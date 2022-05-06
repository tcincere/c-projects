
/*
 * Filename: affine-bruteforce.c
 * Function: Crack cipher text encrypted with the affine algorithm [uppercase only]
 * Test cipher-text: CHSPZKXKFSQEQEQZVUQCEUXCUGDKXKFSBEXMKXLTHUKWEXM
 *					 IKJFWGHEGFNHWVUXIGHOFWGPVFIMHUGHEG
 *					 IYVHZHCJBWJWGGBRQSBIPQFGWFQNVSZ
 *					   	
 * by: tcincere [https://github.com/tcincere]
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Define colours to use in output.
#define BGREEN "\e[1;32m"
#define BBLUE  "\e[1;34m"
#define BRED   "\e[1;31m" 
#define RESET  "\x1b[0m"
#define BWHITE "\e[1;37m"

//Function declarations.
int findInverse(int a_key);
int findGCD(int a_key, int alphabet_size);
int findString(char plaintext[75], int a_key, int b_key);

int main (void) 
{

    //Introductory text.
    printf("\n");
    printf(BWHITE"\t--------------------------\n");
    printf("\t AFFINE CIPHER BRUTEFORCE \n");
    printf("\t--------------------------"RESET);
    printf("\t\n\t  written by: tcincere\n");
    printf("\n");
   
    //Asking user for input using fgets().
    char cipher_text[75];
    
    printf("Enter cipher-text [letters only]: ");
    fgets(cipher_text, 75, stdin);


    //Creating variables for decryption process.
    int a_key, b_key, a_inverse, gcd;
    char plaintext[75];

    //Brute-forcing decryption algorithm with A & B keys.
    printf(BWHITE"\n\n\t\tRESULTS\n");
    printf("\t------------------------\n\n\n" RESET);
    for (a_key = 1; a_key <= 25; a_key++)
    {
            gcd = findGCD(a_key, 26);
            if (gcd == 1)
            {
                //Calculate inverse of used for decryption if GCD = 1.
                a_inverse = findInverse(a_key);
                for(b_key = 0; b_key <= 25; b_key++)
                {
                    //strlen() - 1 for NULL character.
                    for (int i = 0; i < (strlen(cipher_text) - 1); i++) 
                    {                   
                        //Typical affine decryption algorithm using A & B keys.
                        plaintext[i] = (a_inverse * (cipher_text[i] - b_key)) % 26;
                       
                        // Store each character + value of 'A' in ASCII - for capitalisation
                        plaintext[i] += 65;
                    }

                    //After decryption, call findString() to find most relevent plaintexts.
                    findString(plaintext, a_key, b_key);
                }
          }
    }
       
    return 0;
}


int findInverse(int a_key)
{
    int i, modular_inverse;

    //i increases by 1 until integer divides evenly into a_key.
    for (i = 1; i <= a_key; i++)
    {
        modular_inverse = (i * 26) + 1;
       
        if (modular_inverse % a_key == 0)
            break;
    }
    
    modular_inverse /= a_key;
    return(modular_inverse);
}    


int findGCD(int a_key, int alphabet_size)
{

    if (a_key == 0)
    {
        return alphabet_size;
    }
 
    if (alphabet_size == 0)
    {
        return a_key;
    }

   //Recursive function for step two of Euclid's algorithm.
   if (a_key > alphabet_size) 
   {
        return findGCD(a_key % alphabet_size, alphabet_size);
   }
   else
   {
        return findGCD(a_key, alphabet_size % a_key);
   } 
}


int findString(char plaintext[75], int a_key, int b_key) 
{
    
    //Creating a file pointer and opening wordlist to read.
	FILE *fpointer = fopen("affine-wordlist.txt", "r");

    //File pointer error catcher.
   	if (fpointer == NULL)
    {
       perror("WORDLIST ERROR");
       exit(1);
    }

    //Creating variable to store word from list.
     char word[20];
     
     //While loop to read from file until NULL (end of file).
     while (fgets(word, 20, fpointer) != NULL)
     {
        //Removing new line character from each word. 
        word[strcspn(word, "\n")] = 0;
                      
        //Pointer variable to store value of strstr().
        char *result;
        
        //Omit words short words; filter most relevant string matches e.g. HI, BYE, YOU.
        if (strlen(word) > 4) 
        {
            //strstr() points to first char of substring if found, else points to NULL.
        	result = strstr(plaintext, word);
        }
        else 
        {
            //Skip words smaller than 4 letters.
         	continue;
        }
                       
        //If substring is not found, strstr() returns a NULL pointer.
        if (result != NULL) 
        {
            printf("A: " BRED "%d" RESET  "  B: "BBLUE "%d\n" RESET, a_key, b_key);
        	printf("Possible match: " BGREEN "%s\n" RESET, word);
         	printf("Plain-text: " BWHITE "%s\n" RESET, plaintext);
            printf("\n");
            break;
            
        } else
        {
          continue;
        }
                        
     }

    //Close the file.
    fclose(fpointer);
    return 0;
}
