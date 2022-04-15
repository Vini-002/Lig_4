#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <windows.h>
#include <time.h>

#define SEARCH_DEPTH 9

#define ROWS 6
#define COLUMNS 7
#define EMPTY (-1)


typedef struct {
    int mystack[ROWS];
    int top;
} column;

int top = EMPTY;
int mystack[ROWS];

bool push(int value)
{
    if (top >= ROWS - 1) return false;

    top ++;
    mystack[top] = 1;
    return true;

}

int pop()
{
    if (top == EMPTY) printf("Underflow error!");

    mystack[top] = 0;
    top --;
}

void init()
{
    int col, row;
    int game[COLUMNS][ROWS];
    for (col = 0; col < COLUMNS; col++)
    {
        for (row = 0; row < ROWS; row++)
        {
            game[col][row] = 0;
        }
    }
}
