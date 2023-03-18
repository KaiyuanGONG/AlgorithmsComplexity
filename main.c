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

// Function to rotate the blocks
void rotate(int id) {
    int tmp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tmp[j][3 - i] = B[id][i][j];
        }
    }
    memcpy(B[id], tmp, sizeof(tmp));
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
// Function to check if the block can be placed
// Function to check if the block can be placed
bool can_place(int id, int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (B[id][i][j] && (x + i >= 8 || y + j >= 7 || T[x + i][y + j])) {
                return false;
            }
        }
    }
    return true;
}


// Place the block.
void place(int id, int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (B[id][i][j]) {
                T[x + i][y + j] = 1;
            }
        }
    }
}
// Function to unplace the block
void unplace(int id, int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (B[id][i][j]) {
                T[x + i][y + j] = 0;
            }
        }
    }
}
// recursion
// Function to solve the problem
bool solve(int id) {
    if (id == 10) {
        return true;
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 7; j++) {
            for (int k = 0; k < 4; k++) {
                if (can_place(id, i, j)) {
                    place(id, i, j);
                    if (solve(id + 1)) {
                        return true;
                    }
                    unplace(id, i, j);
                }
                rotate(id);
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
int main() {

    char Cond[][10] = {"17", "Mar", "Fri"};
    _init_T(Cond);
    if (solve(0)) {
        // Output the result
        /*
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 7; j++) {
                printf("%d", T[i][j]);
            }
            printf("\n");
        }
        */
       display();
    } else {
        printf("No solution found.\n");
    }

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
