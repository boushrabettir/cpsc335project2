// Project 3 - Path Finding Algorithms
// Team Members: Boushra Bettir (boushra.bettir04@csu.fullerton.edu)

#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream> // To write to file

using namespace std;
using namespace std::chrono;

// Algorithm Number 1 - Exhaustive Search
int exhaustiveSearchAlgorithm(const vector<vector<char>> &grid)
{
    char X = 'X';
    char Y = 'Y';
    int gridRow = grid.size();
    int gridColumn = grid[0].size();
    int moves = gridRow + gridColumn - 2;

    // Final Counter
    int c = 0;

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

// Algorithm Number 2 - Dynamic Programming
int dynamicProgrammingAlgorithm(const vector<vector<char>> &grid)
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
                    dynamicProgramming[i][j] += dynamicProgramming[i - 1][j];
                }
                if (j > 0)
                {
                    dynamicProgramming[i][j] += dynamicProgramming[i][j - 1];
                }
            }
        }
    }

    return dynamicProgramming[gridRow - 1][gridColumn - 1];
}

// Main function
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

    // Open file to write execution times in the plots folder
    ofstream outFile("execution.txt");
    outFile << "# Grid Size | Exhaustive Search Time (microseconds) | Dynamic Programming Time (microseconds)\n";

    // Get the actual grid size
    int maxGridSize = grid.size();

    // Measure execution time for Exhaustive Search and Dynamic Programming
    for (int size = 5; size <= maxGridSize; size += 5)
    {
        // Debugging message for subgrid size
        cout << "Processing subgrid of size " << size << "x" << size << endl;

        // Ensure that the subgrid size does not exceed the grid size
        if (size > maxGridSize)
        {
            cout << "Error: Requested subgrid size exceeds grid size!" << endl;
            break; // Exit the loop when the size exceeds the grid's max size
        }

        // Create subgrid of the current size
        vector<vector<char>> subGrid(size, vector<char>(size));
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                subGrid[i][j] = grid[i][j];
            }
        }

        // Measure execution time for Exhaustive Search
        auto start = high_resolution_clock::now();
        exhaustiveSearchAlgorithm(subGrid);
        auto stop = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop - start);

        // Measure execution time for Dynamic Programming
        start = high_resolution_clock::now();
        dynamicProgrammingAlgorithm(subGrid);
        stop = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop - start);

        // Write execution times to the plots/execution.txt file
        outFile << size << " " << duration1.count() << " " << duration2.count() << "\n";
    }

    outFile.close();
    cout << "Execution times written to 'execution.txt'" << endl;

    return 0;
}