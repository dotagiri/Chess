/******************************************************/
/* EECS 22 - W20 Reference Solution for Bingo         */
/* a typical (but not necessarily best) solution      */
/* Author: EECS 22 W20 Team                           */
/******************************************************/

#include <stdio.h>
#include <stdlib.h>

#define WHITE "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"


int main()
{
    /** File input handling **/
    int n, m;
    FILE *fp;
    fp = fopen("BingoSampleInput1.txt", "r");
    if (fp == NULL)
    {
        printf("Error! no file found\n");
        exit(1);
    }
    // scan the first line: n and m
    fscanf(fp, "%d %d", &n, &m);

    // scan name and board for each player
    char names[n][64+1];
    int boards[n][m][m];
    int states[n][m][m];
    int bingo[n];
    int sequence[m*m];
    for (int i = 0; i < n; i++)
    {
        for (int x = 0; x < m; x++)
        {
            for (int y = 0; y < m; y++)
            {
                states[i][x][y] = 0;
            }
        }
        bingo[i] = 0;
    }


    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%s", names[i]);
        for (int x = 0; x < m; x++)
        {
            for (int y = 0; y < m; y++)
            {
                fscanf(fp, "%d", &boards[i][x][y]);
            }
        }
    }
    // scan the number sequence for Bingo
    for (int i = 0; i < m*m; i++)
    {
        fscanf(fp, "%d", &sequence[i]);
    }
    fclose(fp);


    /** Game start **/
    printf(WHITE "\nStart the game\n");
    for (int i = 0; i < n; i++)
    {
        printf(WHITE "***%s***\n", names[i]);
        for (int x = 0; x < m; x++)
        {
            for (int y = 0; y < m; y++)
            {
                printf("%d ", boards[i][x][y]);
            }
            printf("\n");
        }
    }

    // print the result after each step
    for (int round = 0; round < m*m; round++)
    {
        int called_number = sequence[round];
        printf(WHITE "\nCaller called: %d\n", called_number);
        // mark called number to green
        for (int i = 0; i < n; i++)
        {
            for (int x = 0; x < m; x++)
            {
                for (int y = 0; y < m; y++)
                {
                    if (called_number == boards[i][x][y])
                    {
                        states[i][x][y] = 1;
                        x = y = m; // break loops
                    }
                }
            }
        }

        // Check horizontal bingo (-)
        for (int i = 0; i < n; i++)
        {
            if (bingo[i])
                continue;

            for (int x = 0; x < m; x++)
            {
                int count = 0;
                for (int y = 0; y < m; y++)
                {
                    if (states[i][x][y])
                    {
                        count++;
                    }
                }
                if (count == m)
                {
                    bingo[i] = 1;
                    break;
                }
            }
        }

        // Check vertial bingo (|)
        for (int i = 0; i < n; i++)
        {
            if (bingo[i])
                continue;

            for (int y = 0; y < m; y++)
            {
                int count = 0;
                for (int x = 0; x < m; x++)
                {
                    if (states[i][x][y])
                    {
                        count++;
                    }
                }
                if (count == m)
                {
                    bingo[i] = 1;
                    break;
                }
            }
        }

        // Check diagonal bingo (/)
        for (int i = 0; i < n; i++)
        {
            if (bingo[i])
                continue;

            int count = 0;
            for (int x = 0; x < m; x++)
            {
                if (states[i][x][x])
                {
                    count++;
                }
            }
            if (count == m)
            {
                bingo[i] = 1;
            }
        }

        // Check diagonal bingo (\)
        for (int i = 0; i < n; i++)
        {
            if (bingo[i])
                continue;

            int count = 0;
            for (int x = 0; x < m; x++)
            {
                if (states[i][m-1-x][x])
                {
                    count++;
                }
            }
            if (count == m)
            {
                bingo[i] = 1;
            }
        }

        // Print the round
        for (int i = 0; i < n; i++)
        {
            if (bingo[i])
            {
                printf(WHITE "***%s Bingo! ***\n", names[i]);
            }
            else
            {
                printf(WHITE "***%s***\n", names[i]);
            }

            for (int x = 0; x < m; x++)
            {
                for (int y = 0; y < m; y++)
                {
                    switch (states[i][x][y])
                    {
                        case 1:
                            printf(GREEN "%d ", boards[i][x][y]);
                            states[i][x][y] = 2;
                            break;
                        case 2:
                            printf(RED "%d ", boards[i][x][y]);
                            break;
                        case 0:
                            printf(WHITE "%d ", boards[i][x][y]);
                            break;
                        default:
                            printf(WHITE "ERROR! invalid state %d at (%d, %d, %d)", states[i][x][y], i, x, y);
                            break;
                    }
                }
                printf("\n");
            }

        }

        // If bingo, Print the game result and break
        for (int i = 0; i < n; i++)
        {
            if (bingo[i])
            {
                printf(WHITE "The game result:\n");
                printf("%d ", called_number);
                for (int j = i; j < n; j++)
                {
                    if (bingo[j])
                    {
                        printf("%s ", names[j]);
                    }
                }
                printf("\n");
                round = m*m;
                break;
            }
        }
    }
    return 0;
}
