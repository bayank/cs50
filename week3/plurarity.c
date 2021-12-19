#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    //iterate over the candiates array
    for (int i = 0; i < candidate_count; i++)
    {
        //if name matches a candidate
        if (strcmp(name, candidates[i].name) == 0)
        {
            //increase the vote count
            candidates[i].votes++;
            return true;
        }
    }
    //if name does not match a candidate then return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //define the max number votes
    int max = 0;
    //iterate over th candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        //printf("%s: %d\n", candidates[i].name, candidates[i].votes);
        //test if the number of votes is less than max (0)
        if (candidates[i].votes > max)
        {
            //if true then the new max is candidate[i]
            max = candidates[i].votes;
        }
    }

    //iterate over the candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        //if candidtaes[i] matches the max # of votes, then we have the winner(s)
        if (candidates[i].votes == max)
        {
            //prints the winner's name
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

