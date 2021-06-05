#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
void initial_pref(void);
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    initial_pref();

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Initialize preferences array
void initial_pref(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0; //no votes for pairings yet
        }
    }
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0) //name matches candidate
        {
            ranks[rank] = i; //store candidate index in ranks array
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int work_can = 0; //initialize working candidate

    while (work_can < candidate_count - 1)
    {
        for (int i = work_can + 1; i < candidate_count; i++) //record pairings with working candidate
        {
            int w = ranks[work_can]; //winning candidate
            int l = ranks[i]; //losing candidate
            preferences[w][l]++; //update preferences for current pairing
        }

        work_can++; //update working candidate
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int pridx = 0; //index in pairs array, shows current pair being recorded

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int pair1 = preferences[i][j]; //vote count for pair
            int pair2 = preferences[j][i]; //vote count for opposite pair

            if (pair1 == pair2) //candidates are tied
            {
                //no one gets added to pairs array
            }

            else
            {
                if (pair1 > pair2) //i is winning candidate
                {
                    pairs[pridx].winner = i;
                    pairs[pridx].loser = j;
                }

                else //j is winning candidate
                {
                    pairs[pridx].winner = j;
                    pairs[pridx].loser = i;
                }

                pair_count++; //update pair count
                pridx++; //update
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int m; //margin

    pair work_array[pair_count]; //work array

    for (int i = 0; i < pair_count; i++) //fill in values in work array
    {
        int w = pairs[i].winner; //winning candidate index
        int l = pairs[i].loser; //losing candidate index

        m = preferences[w][l] - preferences[l][w]; //calculate margin

        work_array[i].winner = m; //store margin under 'winner'
        work_array[i].loser = i; //store pairs array index under 'loser'
    }

    int n = 0; //working pair
    int v = 1; //increments the starting value in comparison check

    while (n < pair_count - 1) //sort 1 pair at a time
    {
        pair temp_array[pair_count]; //temporary array

        int lm = work_array[n].winner; //grab first value in array as largest value
        temp_array[n].winner = lm;
        temp_array[n].loser = work_array[n].loser;

        for (int i = v; i < pair_count; i++) //find largest margin
        {
            if (lm < work_array[i].winner)
            {
                lm = work_array[i].winner; //update lm
                temp_array[n].winner = lm; //update temp array
                temp_array[n].loser = work_array[i].loser;
            }
        }

        v++;
        bool lm_check = false; //lg has not been reached when filling in temp array
        int indx = n + 1; //store remaining values after the current (working) node - already in temp array

        for (int i = n; i < pair_count; i++) //fill in temp array
        {
            if (!lm_check)
            {
                if (work_array[i].winner == lm) //found largest margin
                {
                    lm_check = true; //lm has already been accounted for in temp
                }

                else
                {
                    temp_array[indx].winner = work_array[i].winner;
                    temp_array[indx].loser = work_array[i].loser;
                    indx++;
                }
            }

            else
            {
                temp_array[indx].winner = work_array[i].winner;
                temp_array[indx].loser = work_array[i].loser;
                indx++;
            }
        }

        for (int i = 0; i < pair_count; i++) //copy values over into work array
        {
            work_array[i].winner = temp_array[i].winner;
            work_array[i].loser = temp_array[i].loser;
        }

        n++; //update working value
    }

    //work array is sorted (different key: winner -> m, etc..)

    pair temp2_array[pair_count];
    int pridx; //index in pairs array

    for (int i = 0; i < pair_count; i++)
    {
        pridx = work_array[i].loser; //grab index of largest victory
        temp2_array[i].winner = pairs[pridx].winner; //copy winning candidate index
        temp2_array[i].loser = pairs[pridx].loser; //copy losing candidate index
    }

    //key is changed back (winner -> winner, etc..)

    for (int i = 0; i < pair_count; i++) //update pairs array with final values
    {
        pairs[i].winner = temp2_array[i].winner;
        pairs[i].loser = temp2_array[i].loser;
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void cycle_check(int c, bool *cyc, bool *no_nd, int *ip, int *nd);
void lock_pairs(void)
{
    bool cycle; //initialize cycle
    bool no_nodes; //no more nodes left to check - we've examined the longest pathway
    int node_array[candidate_count * (candidate_count - 1) / 2]; //stores nodes (candidate indexes)
    int node = 0; //initialize node count

    bool *cyc, *no_nd;
    int *ip, *nd;

    cyc = & cycle;
    no_nd = & no_nodes;
    ip = node_array; //array pointer
    nd = & node;

    for (int i = 0; i < pair_count; i++)
    {
        int a = pairs[i].winner; //dominant candidate
        int b = pairs[i].loser;

        node_array[0] = b; //add first node to array
        *nd = 1; //update node count

        *cyc = false; //intialize cycle
        *no_nd = false; //initialize no nodes

        cycle_check(a, cyc, no_nd, ip, nd);

        if (!*cyc) //no cycle
        {
            locked[a][b] = true; //lock in pair
        }
    }

    return;
}

void cycle_check(int c, bool *cyc, bool *no_nd, int *ip, int *nd)
{
    int temp_array[candidate_count * (candidate_count - 1) / 2]; //temp nodes array
    int tidx = 0; //temp array index

    if (*no_nd == true || *cyc == true) //determined if we have a cycle or no cycle
    {
        return; //exit function
    }

    else
    {
        int nodes = *nd; //make a copy of nodes
        *nd = 0; //reset node count

        int *tmp;
        tmp = ip; //pointer -> pointer -> first value in array

        for (int i = 0; i < nodes; i++)
        {
            int a = *ip; //working node

            for (int j = 0; j < candidate_count; j++)
            {
                if (locked[a][j]) //a is dominant over another candidate
                {
                    if (j == c) //candidate is c
                    {
                        *cyc = true;
                    }

                    else
                    {
                        temp_array[tidx] = j; //store new node in array
                        tidx++;
                        *nd = *nd + 1; //update node count
                    }
                }
            }

            ip++; //move pointer to next node
        }

        if (*nd == 0) //no new nodes created
        {
            *no_nd = true;
        }

        else
        {
            ip = tmp; //reset pointer position

            for (int i = 0; i < *nd; i++) //copy values over from temp array into work array
            {
                *ip = temp_array[i]; //update node
                ip++; //move pointer to next position
            }

            ip = tmp; //reset pointer position
        }

        cycle_check(c, cyc, no_nd, ip, nd); //call function again
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool dom = true; //initialize candidate status as dominant

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i]) //i'th candidate is non-dominant
            {
                dom = false;
            }
        }

        if (dom == true)
        {
            printf("%s\n", candidates[i]); //print winner
        }
    }

    return;
}