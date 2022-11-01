#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

using namespace std;

// �� �������� ���� �������� �����ϰ� ���� ���� Ǯ �� �־���.
// ���̵��� �ܼ��ϴ�. ���� ������� ������.
// ��ĺ�ȯ���� ������ ��������� ������. ���� �� ���� ���� ũ���� ���ϱ⳪ ���⸦ �ص� ���� ��Ȳ�̶�� ���̴�.
// ���� ������ ������ �ٲ��� �ǹ��� ������ ����ȭ�� �ϸ� ���� �ٸ���.
// 
// �º��� �����̰� ��ȯ �� �캯�� �Ǵµ� ������ ���� A => B�̴�. ���⼭ �Ʊ�� ���� ���� ��ġ��
// A-? => B-?�� ��, ?�� ������ �����ؼ� A-?�� 0����� �ǰ� ����� ������ �ſ� ��������.
// �׷��� ������ 0��� => B-?����� �ǰ� ���� B-?����� �׷����� ���� �ܼ��� ������ ������ ���� �� �� �ִ�.
// 
// ���⼭ ��ȯ�� �Ǵ� ����� ������ ���� ������ �����ؾ��Ѵ�.
// 1. B-?��Ŀ� ������ �� �� ������ �����Ѵ�.
// 2. �� ������ ���Ͽ��� �� ������ �������� ���� �� ������ �ٲ��.
// �� ���� ����� ��ȯ�� �Ұ����ϴ�.
// 
// ���⼭ �����ϰ� ������ Ǯ���� 0��Ŀ��� B-?����� ����� ���� B-?����� 0��ķ� ����� ���� �� ���ϴ�.
// ���� ����� ������ ������ �����⵵ �����ؾ��Ѵ�.
// 
// B-?����� 0��ķ� ����� ����� �����ϴ� ���������� ������ ������ ���� �κи� �ٲٰ� ���������� ���� 1�� ���� �ٲٸ� 0����� ���´�.
// �׷��� ���⼭ �� ������ ������ �� �� �����غ��� Ƚ���� �ٸ��� ���´�. ��, � ������ �ϴ� �ٲܼ��� ������ �ִ� ��Ʈ�� 1���� ���̴�.
// �׷��� �� ���Ͽ� ���ؼ� �غ��� ���� ���� ���� ����ϸ� �ȴ�.
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

// beginning_rows�� 2���� �迭 beginning�� �� ����, beginning_cols�� 2���� �迭 beginning�� �� �����Դϴ�.
// target_rows�� 2���� �迭 target�� �� ����, target_cols�� 2���� �迭 target�� �� �����Դϴ�.
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
