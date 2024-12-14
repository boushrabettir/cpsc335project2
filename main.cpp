#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// The following code will be the Exhaustive
// Search algorithm and the other algorithmic approach
// that we as a team created.

// Algorithm Number 1
int exhaustiveSearchAlgorithm(
    const vector<vector<char>> &grid)
{

    char X = 'X';
    char Y = 'Y';
    int gridRow = grid.size();
    int gridColumn = grid[0].size();
    int moves = gridRow + gridColumn - 2;

    int c = 0;

    // i are the bits in the algorithm.
    for (int i = 0; i < (1 << moves); ++i)
    {
        int m = 0; // Down, Up
        int n = 0; // Left, Right
        bool isValid = true;

        for (int n = 0; n < moves; ++n)
        {
            if ((i >> n) & 1)
            {
                m++;

                if (m >= gridRow || grid[m][n] == X)
                {
                    isValid = false;
                    break;
                }
            }
            else
            {

                n++;

                if (n >= gridColumn || grid[m][n] == Y)
                {
                    isValid = false;
                    break;
                }
            }
        }

        if (isValid && m == gridRow - 1 && n == gridColumn - 1)
        {
            c++;
        }
    }

    return c;
}

// Algorithm Number 2
int dynamicProgrammingAlgorithm(
    const vector<vector<char>> &grid)
{
    int gridRow = grid.size();
    int gridColumn = grid[0].size();

    char X = 'X';
    char Y = 'Y';

    if (grid[0][0] == X || grid[gridRow - 1][gridColumn - 1] == X)
    {
        return 0;
    }

    vector<vector<int>> dynamicProgramming(gridRow, vector<int>(gridColumn, 0));

    // Base case scenario so it the algorithm
    // doesn't go in an infinite loop.
    dynamicProgramming[0][0] = 1;

    for (int i = 0; i < gridRow; ++i)
    {
        for (int j = 0; j < gridColumn; ++j)
        {
            if (grid[i][j] == 'X')
            {
                dynamicProgramming[i][j] = 0;
            }
            else
            {
                if (i > 0)
                {
                    // Above path
                    dynamicProgramming[i][j] += dynamicProgramming[i - 1][j];
                }
                if (j > 0)
                {
                    // Left path
                    dynamicProgramming[i][j] += dynamicProgramming[i][j - 1];
                }
            }
        }
    }

    return dynamicProgramming[gridRow - 1][gridColumn - 1];
}

// Main to test
int main()
{
    vector<vector<char>> grid = {
        {'.', '.', '.', '.', '.', 'X', '.', 'X'},
        {'X', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', 'X', '.', '.', '.', 'X', '.'},
        {'.', 'X', '.', '.', '.', '.', 'X', '.'},
        {'X', '.', '.', '.', 'X', '.', '.', '.'},
        {'.', '.', 'X', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', 'X', '.', 'X'},
        {'.', '.', '.', '.', '.', '.', '.', '.'}};

    cout << "Algorithm 1: " << exhaustiveSearchAlgorithm(grid) << endl;
    cout << "Algorithm 2: " << dynamicProgrammingAlgorithm(grid) << endl;

    return 0;
}
