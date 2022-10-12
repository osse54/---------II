#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdlib.h>
#include <limits.h>

/**
 * 로또 게임에 사용할 랜덤 숫자를 생성하는 함수
 */
int get_random_number(int limit)
{
    // srand(time(NULL) * rand() + time(NULL) + rand()); // 현재 시간과 랜덤 숫자를 시드로 이용해 랜덤 숫자 생성
    return (rand() % limit) + 1;
}

/**
 * 입력받은 수만큼 난수를 생성하여 반환하는 함수
 */
int* get_numbers(int amount, int limit)
{
    // 메모리 할당
    int* numbers = (int*)malloc(sizeof(int) * amount);
    int random_number;
    for (int i = 0; i < amount; i++)
    {
        do {
            random_number = get_random_number(limit);
        } while (contains(numbers, random_number, i));
        numbers[i] = random_number;
    }
    return numbers;
}

/**
 * array가 number를 가지고 있는지 검사하는 함수
 * int* array : 검사할 int형 배열의
 * int number : 검사할 숫자
 * int size : 검사할 int형 배열의 크기
 */ 
int contains(int* array, int number, int size)
{
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        // printf("left: %d, right: %d\n", array[i], number); // 작동하는지 확인을 위해 만든 출력 코드
        if (array[i] == number)
        {
            result = 1;
            break;
        }
    }
    return result;
}