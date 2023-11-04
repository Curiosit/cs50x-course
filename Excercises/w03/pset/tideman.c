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
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_circle(int start, int loser);
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

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            printf("Rank nr %i is %i \n", rank, i);
            printf("Proper vote on %s \n", name);
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int r = 0; r < (candidate_count - 1); r++)
    {
        // r is rank number, for each apart from last we need to record all the other ranks
        // ranks[r][iterate r+1]
        printf("Comparing %i, with: ", ranks[r]);

        int rr = r + 1;
        do
        {
            printf("%i, ", ranks[rr]);

            preferences[ranks[r]][ranks[rr]]++;
            rr++;
        }
        while (rr < (candidate_count - r));

        printf("\n");
        // preferences[i][j] is number of voters who prefer i over j
    }

    return;
}

void print_matrix(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        printf("candidate id: %i >", i);
        for (int j = 0; j < candidate_count; j++)
        {

            printf("| %i |", preferences[i][j]);
        }
        printf(" || name: %s >", candidates[i]);
        printf("\n");
    }
    printf("\n");
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    printf("Pairs: \n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                printf("Pair [%i] [%i] \n", i, j);
                printf("Votes on left [%i] \n", preferences[i][j]);
                printf("Votes on right [%i] \n", preferences[j][i]);
                if (preferences[i][j] == preferences[j][i])
                {
                    printf("Tied! \n");
                }
                else if (preferences[i][j] > preferences[j][i])
                {
                    printf("Winner left \n");
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
                /* else if (preferences[i][j] < preferences[j][i])
                {
                    printf("Winner right \n");
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;
                } */
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    for (int i = 0; i < pair_count - 1; i++)
    {

        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                int winner = pairs[j].winner;
                int loser = pairs[j].loser;
                pairs[j].winner = pairs[i].winner;
                pairs[j].loser = pairs[i].loser;
                pairs[i].winner = winner;
                pairs[i].loser = loser;
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!check_circle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

bool check_circle(int start, int loser)
{
    if (start == loser)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (check_circle(start, i))
            {

                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int candidate_ = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                candidate_++;
                if (candidate_ == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }

    return;
}
