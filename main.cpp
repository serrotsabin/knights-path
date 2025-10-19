#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAXN = 8;

int board[MAXN][MAXN];
int N;
int numSolutions;
int found = 0;

// Knight move directions
int knightDirectionRows[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int knightDirectionColumns[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// Print current board to file
void printBoard(ofstream &ofs)
{
    ofs << "Knight's Path Solution " << found << ":\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            ofs << setw(3) << board[i][j];
        }
        ofs << "\n";
    }
    ofs << "\n";
}

// DFS + backtracking
void dfs(int row, int column, int moveNum, ofstream &ofs)
{
    if (found >= numSolutions)
        return;

    board[row][column] = moveNum;

    if (moveNum == N * N - 1)
    {
        found++;
        printBoard(ofs);
        board[row][column] = -1; // backtrack to find another solution
        return;
    }

    // Try all 8 moves in order and check valid moves.
    for (int k = 0; k < 8; k++)
    {
        int currentRow = row + knightDirectionRows[k];
        int currentColumn = column + knightDirectionColumns[k];
        if (currentRow >= 0 && currentRow < N && currentColumn >= 0 && currentColumn < N && board[currentRow][currentColumn] == -1)
        {
            dfs(currentRow, currentColumn, moveNum+1, ofs); // move forward with valid moves.
        }
    }

    board[row][column] = -1; // backtrack to move along another path.
}

int main()
{
    int startingRow;
    int startingColumn;

    cout << "Board size (N): ";
    cin >> N;
    while(N < 4 || N>8){
        cout << "Invalid Board Size (N) Re-enter : ";
        cin >> N;
    };

    cout << "Number of solutions to find: ";
    cin >> numSolutions;

    cout << "Starting row: ";
    cin>>startingRow;
    while(startingRow < 1 || startingRow>N){
        cout << "Invalid Row Re-enter : ";
        cin >> startingRow;
    };

    cout << "Starting column: ";
    cin>>startingColumn;
    while( startingColumn < 1 || startingColumn>N){
        cout << "Invalid Column Re-enter: ";
        cin >> startingColumn;
    };

    startingRow--;
    startingColumn--;

    ofstream ofs("kp.out");
    if (!ofs)
    {
        cout << "Error opening kp.out\n";
        return 1;
    }

    // mark board with -1 for all the paths.
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = -1;

    dfs(startingRow, startingColumn, 0, ofs);

    if (found == 0)
        ofs << "No solutions found for " << N << " size board, starting position from (" << startingRow << "," << startingColumn << ").\n";
    else
        ofs << "Total solutions written : " << found << "\n";
    ofs.close();

    cout << "Knight's Tour Complete - Check kp.out for results. \n";
    cout << "Solutions Found : " << found << "\n";
    return 0;
}