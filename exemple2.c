#include <stdio.h>
#include <stdbool.h>

#define N 8

// 检查当前位置是否可以放置皇后
bool isSafe(int board[N][N], int row, int col) {
    int i, j;

    // 检查同一列
    for (i = 0; i < row; i++) {
        if (board[i][col]) {
            return false;
        }
    }

    // 检查左上对角线
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    // 检查右上对角线
    for (i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

// 递归解决八皇后问题
bool solveNQueens(int board[N][N], int row) {
    // 基本情况：所有皇后都已放置
    if (row >= N) {
        return true;
    }

    // 遍历当前行的所有列
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            // 放置皇后
            board[row][col] = 1;

            // 递归放置剩余的皇后
            if (solveNQueens(board, row + 1)) {
                return true;
            }

            // 回溯：移除当前位置的皇后
            board[row][col] = 0;
        }
    }

    // 当前行没有可放置皇后的位置
    return false;
}

// 打印棋盘
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int board[N][N] = {0};

    if (solveNQueens(board, 0)) {
        printBoard(board);
    } else {
        printf("Solution does not exist.\n");
    }

    return 0;
}
