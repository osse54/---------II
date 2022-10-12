#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "util.h"
#include "number_baseball.h"

void number_baseball()
{
    // 숫자 생성 길이: 3
    int* numbers = get_numbers(3, 9);

    // 맞출 수 있는 기회는 9번
    for (int chance = 9; chance > 0; chance--)
    {
        printf("1~9 사이의 숫자를 3개 입력해주세요. (남은 기회: %d)\n예)9 1 5\n>", chance);
        // 정답이 들어갈 배열 메모리 할당
        int* input_numbers = (int*)malloc(sizeof(int) * 3);

        // 숫자 3개 입력받기
        scanf("%d %d %d", &input_numbers[0], &input_numbers[1], &input_numbers[2]);

        // 입력받은 숫자와 정답을 비교하여 스트라이크와 볼의 개수를 센다.
        int strike = 0;
        int ball = 0;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (numbers[i] == input_numbers[j])
                {
                    if (i == j)
                    {
                        strike++;
                    }
                    else
                    {
                        ball++;
                    }
                }
            }
        }
        // 할당된 메모리 해제
        free(input_numbers);
    }
    // 할당된 메모리 해제
    free(numbers);
}