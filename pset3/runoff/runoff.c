#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;

    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");

    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0) //name entered is valid
        {
            preferences[voter][rank] = i; //update preferences (store candidate's index in rank)
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false) //candidate is not eliminated (take first preference)
        {
            for (int a = 0; a < voter_count; a++)
            {
                if (preferences[a][0] == i) //candidate is ranked first
                {
                    candidates[i].votes++; //update vote count
                }
            }
        }

        else //candidate is eliminated
        {
            for (int a = 0; a < voter_count; a++)
            {
                if (preferences[a][0] == i) //eliminated candidate is ranked first
                {
                    int j = 1; //initialize preference counter to second pref.

                    while (true) //find next non-eliminated candidate
                    {
                        int candx = preferences[a][j]; //shows current candidate (index) as we move through voter a's ranked list

                        if (candidates[candx].eliminated == false) //candidate is not eliminated
                        {
                            candidates[candx].votes++; //update vote count
                            break;
                        }

                        j++; //move to next preference
                    }
                }
            }
        } //end of else
    } //end of outer for loop

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int m; //majority vote

    if (voter_count % 2 == 0) //even number of votes
    {
        m = (voter_count / 2) + 1; //calculate majority vote
    }

    else //odd number of votes
    {
        m = round(voter_count / 2);
    }

    int ln = candidates[0].votes; //initialize largest vote count
    int lndx = 0; //initialize index of largest vote

    for (int i = 1; i < candidate_count; i++)
    {
        if (ln < candidates[i].votes) //compare to find largest vote count
        {
            ln = candidates[i].votes; //update ln
            lndx = i; //update lndx
        }
    }

    if (ln >= m) //reached majority vote
    {
        printf("%s\n", candidates[lndx].name); //print winner

        return true;
    }

    return false; //no winner
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    bool intlz_sm = false;
    int sm; //smallest vote count

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false) //candidate is not eliminated
        {
            if (intlz_sm == false) //sm has not been initialized
            {
                sm = candidates[i].votes; //initialize smallest number of votes
                intlz_sm = true;
            }

            else //sm has been initialized
            {
                if (candidates[i].votes < sm) //compare vote counts
                {
                    sm = candidates[i].votes; //update sm
                }
            }
        }
    }

    return sm; //return smallest vote count
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int std = min; //set minimum vote count as the standard

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes != std) //vote count does not match the standard
            {
                return false; //no tie
            }
        }
    }

    return true; //election is tied
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes == min) //candidate has minimum vote count
            {
                candidates[i].eliminated = true; //change elimination status
            }
        }
    }
    return;
}