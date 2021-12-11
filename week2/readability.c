#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int letters(string input);
int words(string input);
int sen(string input);

int main(void)
{
    // Get input text
    string text = get_string("Text: ");

    // Call the letter, word, and snetence counter functions and store the result in ints.

    int num_letters = letters(text);
    int num_words = words(text);
    int num_sen = sen(text);

    //printf("Letters: %d\n", num_letters);
    //printf("Words: %d\n", num_words);
    //printf("Sentences: %d\n", num_sen);

    //do some type casting to make division work
    double l = ((double)num_letters / (double)num_words) * 100;
    double s = ((double)num_sen / (double)num_words) * 100;

    //formula for the readability index
    //Here, L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text
    double index = 0.0588 * l - 0.296 * s - 15.8;

    //round the result to compare it below and spit out an int
    int grade = round(index);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %d\n", grade);
    }



    return (0);
}

//compute number of letters function definition
int letters(string input)
{
    int n = strlen(input), count = 0;
    for (int i = 0; i < n; i++)
    {
        //Check if the letter is uppercase
        if (isupper(input[i]))
        {
            count ++;
        }
        //check is the letter is lowercase
        else if (islower(input[i]))
        {
            count ++;
        }
        //if not upper or lower, then it must be a special char and worth 0
        else
        {
            count += 0;
        }
    }
    return (count);
}


//compute number of words function definition
int words(string input)
{
    int n = strlen(input), count = 1;
    for (int i = 0; i < n; i++)
    {
        //Check if there is a space
        if (isspace(input[i]))
        {
            count ++;
        }
        else
        {
            count += 0;
        }
    }
    return (count);
}

//compute number of sentences function definition

int sen(string input)
{
    int n = strlen(input), count = 0;
    for (int i = 0; i < n; i++)
    {
        //Check if the char is .!?
        if (input[i] == '.' || input[i] == '?' || input[i] == '!')
        {
            count ++;
        }
    }
    return (count);
}