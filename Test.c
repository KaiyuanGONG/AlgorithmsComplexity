#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

// Define the ccorrect date
char C[31][3][10];
const char Start[][10] = {"17", "Mar", "Fri"};

// Define the arry for result
char Cond[][10] = {"0"};
// char Result[][10] = {"0"};

// Define a two-dimensional array to represent the cells on the green paper
// Actual two-dimensional array, symbolic
const char *G[8][7] = {
    {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "#"},
    {"Jul", "Aug", "Sep", "Oct", "Nov", "Dec", "#"},
    {"1", "2", "3", "4", "5", "6", "7"},
    {"8", "9", "10", "11", "12", "13", "14"},
    {"15", "16", "17", "18", "19", "20", "21"},
    {"22", "23", "24", "25", "26", "27", "28"},
    {"29", "30", "31", "Sun", "Mon", "Tue", "Wed"},
    {"#", "#", "#", "#", "Thu", "Fri", "Sat"}};
//  0->exept value， 1-> occupied, 2-> outside area
int T[8][7] = {
    0, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 0, 0, 0

};

// Represents 10 blue graphic blocks
// Consider the case of rotation, the maximum range does not exceed 4*4
// 1 -> effective area, 0-> vacant area
int B[10][4][4] = {
    {{0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0},
     {1, 1, 0, 0}},
    {{0, 1, 0, 0},
     {0, 1, 0, 0},
     {1, 1, 1, 0},
     {0, 0, 0, 0}},
    {{1, 1, 1, 0},
     {1, 0, 0, 0},
     {1, 0, 0, 0},
     {0, 0, 0, 0}},
    {{1, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 0, 0, 0}},
    {{0, 1, 0, 0},
     {0, 1, 0, 0},
     {1, 1, 0, 0},
     {1, 0, 0, 0}},
    {{1, 0, 1, 0},
     {1, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    {{1, 0, 0, 0},
     {1, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0}},
    {{0, 1, 0, 0},
     {0, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0}},
    {{1, 0, 0, 0},
     {1, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0}},
    {{0, 0, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0},
     {1, 1, 1, 1}}};
// Rotate the blue square
// 90 -> Rotate 90 degrees clockwise, 180, 270 same

void rotate(int input[4][4], int output[4][4], int angle)
{
    switch (angle)
    {
    case 0:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                output[i][j] = input[i][j];
            }
        }
        break;

    case 90:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                output[j][3 - i] = input[i][j];
            }
        }
        break;
    case 180:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                output[3 - i][3 - j] = input[i][j];
            }
        }
        break;
    case 270:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                output[3 - j][i] = input[i][j];
            }
        }
        break;
    default:
        printf("Invalid angle. Please enter 90, 180, or 270.\n");
    }
}

// Define the rotated array
int B_R[10][4][4];

// input an 2dimantional array
void display() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 7; j++) {
            if (T[i][j] == 2) {
                printf("#   ");
            } else if (T[i][j] == 3) {
                printf("%-3s", G[i][j]);
            } else {
                printf("    ");
            }
        }
        printf("\n");
    }
}

// according to the cond[][], initialize the T
void _init_T(char Cond[][10]) {
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 7; j++) {
                if (strcmp(G[i][j], Cond[k]) == 0) {
                    T[i][j] = 3;
                }
            }
        }
    }
}

// Check if the block can be placed without overlapping with occupied positions or going outside the paper.
bool check(int block[4][4], int row, int col)
{

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[i][j] == 1)
            {
                int newRow = row + i;
                int newCol = col + j;

                if (newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 7)
                {
                    //printf("Placement failed: outside of the paper.\n");
                    return false;
                }

                if (T[newRow][newCol] != 0)
                {
                    //printf("Placement failed: overlapping with occupied position.\n");
                    return false;
                }
            }
        }
    }
    return true;
}

// Place the block.
void place(int block[4][4], int row, int col)
{

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[i][j] == 1)
            {
                T[row + i][col + j] = 1;
            }
        }
    }
}

// recursion
bool solve(int row, int col)
{
    if (row >= 8)
    {
        return true;
    }

    if (T[row][col] != 0)
    {
        if (col == 6)
        {
            return solve(row + 1, 0);
        }
        else
        {
            return solve(row, col + 1);
        }
    }

    for (int k = 0; k < 10; k++)
    {
        for (int l = 0; l <= 360; l+=90) // Changed from l < 360 to l <= 360 to include the case when the angle is 0.
        {
            rotate(B[k], B_R[k], l);
            if (check(B_R[k], row, col))
            {
                place(B_R[k], row, col);
                if (col == 6)
                {
                    if (solve(row + 1, 0))
                    {
                        return true;
                    }
                }
                else
                {
                    if (solve(row, col + 1))
                    {
                        return true;
                    }
                }
                // Remove the block if it doesn't lead to a solution.
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (B_R[k][i][j] == 1)
                        {
                            T[row + i][col + j] = 0;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// According to the given date, initialize 31 dates in array C
void _init_C(const char start_date[][10])
{
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    const char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int current_day = atoi(start_date[0]);
    int current_month = 0;
    for (int i = 0; i < 12; i++)
    {
        if (strcmp(months[i], start_date[1]) == 0)
        {
            current_month = i;
            break;
        }
    }
    int current_weekday = 0;
    for (int i = 0; i < 7; i++)
    {
        if (strcmp(days[i], start_date[2]) == 0)
        {
            current_weekday = i;
            break;
        }
    }

    for (int i = 0; i < 31; i++)
    {
        sprintf(C[i][0], "%02d", current_day);
        strcpy(C[i][1], months[current_month]);
        strcpy(C[i][2], days[current_weekday]);

        current_day++;
        if (current_day > days_in_month[current_month])
        {
            current_day = 1;
            current_month++;
            if (current_month >= 12)
            {
                break;
            }
        }
        current_weekday = (current_weekday + 1) % 7;

        if (i == 30 && current_month == 0)
        {
            break;
        }
    }
}

// valide the condition
void valid(int T[8][7], char Cond[][10])
{
    int border_error = 0;
    int threes_count = 0;
    int condition_error = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (T[i][j] == 2)
            {
                if (strcmp(G[i][j], "#") != 0)
                {
                    border_error = 1;
                }
            }
            else if (T[i][j] == 3)
            {
                threes_count++;
                int found = 0;
                for (int k = 0; k < 3; k++)
                {
                    if (strcmp(G[i][j], Cond[k]) == 0)
                    {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    condition_error = 1;
                }
            }
        }
    }

    if (border_error)
    {
        printf("Border damaged, result invalid.\n");
    }
    else if (threes_count != 3)
    {
        printf("Placement error, extra space.\n");
    }
    else if (condition_error)
    {
        printf("Does not satisfy the condition.\n");
    }
    else
    {
        printf("Congratulations!\n");
    }
}
int main(int argc, char *aegv[])
{
    // place the block
    int row = 2;
    int col = 1;

    char Cond[][10] = {"17", "Mar", "Fri"};
    _init_T(Cond);

    if (solve(0, 0))
    {
        display();
    }
    else
    {
        printf("Solution does not exist.\n");
    }

    // initialize 31 dates
    _init_C(Start);

    // valide , check the result
    
    valid(T, Cond);
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 7; j++){
            printf("%d", T[i][j]);
        }
        printf("\n");
    }

    return 0;
}
