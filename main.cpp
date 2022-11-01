#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

using namespace std;

// 이 문제같은 경우는 논리적으로 간단하게 만들어서 쉽게 풀 수 있었다.
// 아이디어는 단순하다. 선형 대수적인 원리다.
// 행렬변환에서 덧셈은 선형대수를 따른다. 따라서 양 변에 같은 크기의 더하기나 빼기를 해도 같은 상황이라는 뜻이다.
// 당장 보면은 무엇을 바꿀지 의문이 들지만 간략화를 하면 말이 다르다.
// 
// 좌변이 기존이고 변환 후 우변이 되는데 식으로 쓰면 A => B이다. 여기서 아까와 같은 논리를 펼치면
// A-? => B-?다 즉, ?를 적당히 조절해서 A-?가 0행렬이 되게 만들면 문제가 매우 쉬워진다.
// 그러면 문제가 0행렬 => B-?행렬이 되고 직접 B-?행렬을 그려보면 아주 단순한 패턴이 나오는 것을 알 수 있다.
// 
// 여기서 변환이 되는 경우라면 다음과 같은 조건을 만족해야한다.
// 1. B-?행렬에 패턴이 단 두 가지만 존재한다.
// 2. 두 가지의 패턴에서 한 가지를 뒤집으면 남은 한 가지로 바뀐다.
// 그 외의 경우라면 변환이 불가능하다.
// 
// 여기서 간단하게 문제를 풀려면 0행렬에서 B-?행렬을 만들기 보다 B-?행렬을 0행렬로 만드는 것이 더 편하다.
// 선형 대수를 따르기 때문에 역방향도 성립해야한다.
// 
// B-?행렬을 0행렬로 만드는 방법은 간단하다 가로축으로 동일한 패턴을 가진 부분만 바꾸고 세로축으로 값이 1인 열만 바꾸면 0행렬이 나온다.
// 그런데 여기서 두 가지의 패턴을 둘 다 적용해보면 횟수가 다르게 나온다. 즉, 어떤 선택을 하던 바꿀수는 있지만 최단 루트는 1개인 것이다.
// 그래서 두 패턴에 대해서 해보고 값이 작은 값을 출력하면 된다.
//

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
    int** ReTarget = (int**)malloc(sizeof(int) * target_rows * 2);
    int** ReTarget1 = (int**)malloc(sizeof(int) * target_rows*2);
    for (int i = 0; i < target_rows; i++)
    {
        ReTarget[i] = (int*)malloc(sizeof(int) * target_cols);
        ReTarget1[i] = (int*)malloc(sizeof(int) * target_cols);
    }

    for (int i = 0; i < target_rows; i++)
    {
        for (int j = 0; j < target_cols; j++)
        {
            if (beginning[i][j] == target[i][j])
            {
                ReTarget[i][j] = 0;
                ReTarget1[i][j] = 0;
            }
            else if (beginning[i][j] != target[i][j])
            {
                ReTarget[i][j] = 1;
                ReTarget1[i][j] = 1;
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
    for (int i = 0; i < target_cols; i++)
    {
        if (ReTarget1[0][i] == 0)
        {
            Reverse(ReTarget1, target_rows, i, 'r');
            count1++;
        }
    }

    for (int i = 0; i < target_rows; i++)
    {
        if (ReTarget1[i][0] == 1)
        {
            Reverse(ReTarget1, target_cols, i, 'c');
            count1++;
        }
    }

    int answer = 0;
    if (count >= count1)
    {
        answer = count1;
    }
    else if (count < count1)
    {
        answer = count;
    }

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
        free(ReTarget1[i]);
    }
    free(ReTarget);
    free(ReTarget1);
    return answer;
}

#define ROW 5
#define COL 5

int main()
{
    int* list[ROW];
    int aaa[ROW][COL] = { {0,1,1,1,1},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{0,1,1,1,1} };
    int* tlist[ROW];
    int taaa[ROW][COL] = { {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0} };
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
