#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

using namespace std;

void Reverse(int** RT, int RTsize, int position, char RC)
{
    if (RC == 'r')
    {
        for (int i = 0; i < RTsize; i++)
        {
            RT[i][position] = !RT[i][position];
        }
    }
    else if (RC == 'c')
    {
        for (int i = 0; i < RTsize; i++)
        {
            RT[position][i] = !RT[position][i];
        }
    }
}

// beginning_rows는 2차원 배열 beginning의 행 길이, beginning_cols는 2차원 배열 beginning의 열 길이입니다.
// target_rows는 2차원 배열 target의 행 길이, target_cols는 2차원 배열 target의 열 길이입니다.
int solution(int** beginning, size_t beginning_rows, size_t beginning_cols, int** target, size_t target_rows, size_t target_cols) {
    int** ReTarget = (int**)malloc(sizeof(int) * target_rows*2);
    for (int i = 0; i < target_rows; i++)
    {
        ReTarget[i] = (int*)malloc(sizeof(int) * target_cols);
    }

    for (int i = 0; i < target_rows; i++)
    {
        for (int j = 0; j < target_cols; j++)
        {
            if (beginning[i][j] == target[i][j])
            {
                ReTarget[i][j] = 0;
            }
            else if (beginning[i][j] != target[i][j])
            {
                ReTarget[i][j] = 1;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < target_cols; i++)
    {
        if (ReTarget[0][i] == 1)
        {
            Reverse(ReTarget, target_rows, i, 'r');
            count++;
        }
    }

    for (int i = 0; i < target_rows; i++)
    {
        if (ReTarget[i][0] == 1)
        {
            Reverse(ReTarget, target_cols, i, 'c');
            count++;
        }
    }

    int count1 = 0;
    for (int i = 0; i < target_rows; i++)
    {
        if (ReTarget[i][0] == 1)
        {
            Reverse(ReTarget, target_cols, i, 'c');
            count1++;
        }
    }

    for (int i = 0; i < target_cols; i++)
    {
        if (ReTarget[0][i] == 1)
        {
            Reverse(ReTarget, target_rows, i, 'r');
            count1++;
        }
    }

    int answer = count;
    for (int i = 0; i < target_rows; i++)
    {
        for (int j = 0; j < target_cols; j++)
        {
            if (ReTarget[i][j] == 1)
            {
                answer = -1;
            }
        }
    }
    for (int i = 0; i < target_rows; i++)
    {
        free(ReTarget[i]);
    }
    free(ReTarget);
    return answer;
}

#define ROW 5
#define COL 5

int main()
{
    int* list[ROW];
    int aaa[ROW][COL] = { {0,1,0,0,0},{1,0,1,0,1},{0,1,1,1,0},{1,0,1,1,0},{0,1,0,1,0} };
    int* tlist[ROW];
    int taaa[ROW][COL] = { {1,0,1,1,1},{1,0,1,0,1},{0,1,1,1,0},{1,0,1,1,0},{0,1,0,1,0} };
    for (int i = 0; i < ROW; i++)
    {
        list[i] = aaa[i];
    }
    for (int i = 0; i < ROW; i++)
    {
        tlist[i] = taaa[i];
    }

    int result = solution(list, ROW, COL, tlist, ROW, COL);
    cout << result << endl;
    int j;
    cin >> j;
}
