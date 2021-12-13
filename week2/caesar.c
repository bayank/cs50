#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Points assigned to each letter of the alphabet, This ended up not being needed at all...
string upper[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
string lower[] =  {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};



int main(int argc, string argv[])
{
    //Check that argc =2, which means that the command passed only 1 argument
    if (argc == 2)
    {
        string key = argv[1];
        //Check that argv is a digit, iterate over the string
        for (int i = 0; i < strlen(key); i ++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

        //Still in the if = true part of this conditional, then proceed with the rest of the program
        //printf("Success");

        //Get plaintext string from user
        string plaintext = get_string("plaintext: ");

        //convert key to int
        int key_int = atoi(key);
        printf("ciphertext: ");

        //calculate ciphertext
        for (int i = 0; i < strlen(plaintext); i++)
        {
            if (isupper(plaintext[i]))
            {
                printf("%c", (((plaintext[i] - 'A') + key_int) % 26) + 'A');
            }
            else if (islower(plaintext[i]))
            {
                printf("%c", (((plaintext[i] - 'a') + key_int) % 26) + 'a');
            }
            else
            {
                printf("%c", plaintext[i]);
            }
        }



    }
    //drop out of the if conditional since argc != 0 and return 1, end the program
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    printf("\n");
    return 0;
}
