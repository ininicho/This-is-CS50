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
    int diff;
}
pair;

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i],name) == 0)
        {
            ranks[rank] = i;
            return true;
            break;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pairs[pair_count].diff = preferences[i][j] - preferences[j][i];
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - 1; j++)
        {
            if (pairs[j].diff < pairs[j + 1].diff)
            {
                int dummyw = pairs[j].winner;
                int dummyl = pairs[j].loser;
                int dummyd = pairs[j].diff;
                pairs[j].winner = pairs[j + 1].winner;
                pairs[j].loser = pairs[j + 1].loser;
                pairs[j].diff = pairs[j + 1].diff;
                pairs[j + 1].winner = dummyw;
                pairs[j + 1].loser = dummyl;
                pairs[j + 1].diff = dummyd;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[pairs[i].winner][pairs[i].loser] == false && locked[pairs[i].loser][pairs[i].winner] == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else if (locked[pairs[i].loser][pairs[i].winner] == true)
        {
            lock_pairs();
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int sum[candidate_count];
    for (int n = 0; n < candidate_count; n++)
    {
        sum[n] = 0;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            sum[i] = sum[i] + locked[i][j];
        }
    }

    for (int x = 0; x < candidate_count; x++)
    {
        for (int y = 0; y < candidate_count - 1; y++)
        {
            if (sum[y] < sum[y + 1])
            {
                int dummy = sum[y + 1];
                sum[y] = sum[y + 1];
                sum[y + 1] = dummy;
            }
        }
    }

    printf("%s\n", candidates[sum[0]]);
    return;
}