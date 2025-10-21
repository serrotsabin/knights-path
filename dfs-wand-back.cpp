#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAXN = 30; // allow bigger boards if needed

int board[MAXN][MAXN];
int N;
int numSolutions;
int found = 0;

// Knight move directions
int knightDirectionRows[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int knightDirectionColumns[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// Print current board
void printBoard(ofstream &ofs)
{
    ofs << "Knight's Path Solution " << found << ":\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            ofs << setw(5) << board[i][j];
        }
        ofs << "\n";
    }
    ofs << "\n";
}

// Count how many valid onward moves exist from (r,c)
int countOnwardMoves(int r, int c)
{
    int cnt = 0;
    for (int k = 0; k < 8; k++)
    {
        int nr = r + knightDirectionRows[k];
        int nc = c + knightDirectionColumns[k];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N && board[nr][nc] == -1)
            cnt++;
    }
    return cnt;
}

// DFS + Warnsdorff ordering
void dfsWarnsdorff(int row, int column, int moveNum, ofstream &ofs)
{
    if (found >= numSolutions)
        return;

    board[row][column] = moveNum;

    if (moveNum == N * N - 1)
    {
        found++;
        printBoard(ofs);
        board[row][column] = -1;
        return;
    }

    // Store moves and their degree
    int moves[8][3]; // row, col, degree
    int mcount = 0;

    for (int k = 0; k < 8; k++)
    {
        int nr = row + knightDirectionRows[k];
        int nc = column + knightDirectionColumns[k];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N && board[nr][nc] == -1)
        {
            moves[mcount][0] = nr;
            moves[mcount][1] = nc;
            moves[mcount][2] = countOnwardMoves(nr, nc);
            mcount++;
        }
    }

    // Sort moves by onward degree (smallest first)
    for (int i = 0; i < mcount; i++)
    {
        for (int j = i + 1; j < mcount; j++)
        {
            if (moves[j][2] < moves[i][2])
            {
                int tmp0 = moves[i][0], tmp1 = moves[i][1], tmp2 = moves[i][2];
                moves[i][0] = moves[j][0];
                moves[i][1] = moves[j][1];
                moves[i][2] = moves[j][2];
                moves[j][0] = tmp0;
                moves[j][1] = tmp1;
                moves[j][2] = tmp2;
            }
        }
    }

    // Try moves in Warnsdorff order
    for (int i = 0; i < mcount; i++)
    {
        dfsWarnsdorff(moves[i][0], moves[i][1], moveNum + 1, ofs);
    }

    // Backtrack
    board[row][column] = -1;
}

int main()
{
    int startingRow, startingColumn;
    cout << "Board size (N): ";
    cin >> N;
    cout << "Number of solutions to find: ";
    cin >> numSolutions;
    cout << "Starting row: ";
    cin >> startingRow;
    cout << "Starting column: ";
    cin >> startingColumn;

    startingRow--;
    startingColumn--;

    ofstream ofs("kp.out");
    if (!ofs)
    {
        cout << "Error opening kp.out\n";
        return 1;
    }

    // Clear board
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = -1;

    dfsWarnsdorff(startingRow, startingColumn, 0, ofs);

    if (found == 0)
        ofs << "No solutions found.\n";
    else
        ofs << "Total solutions written: " << found << "\n";

    ofs.close();
    cout << "Done. Check kp.out\n";
    return 0;
}
