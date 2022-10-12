#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "util.h"
#include "lotto.h"

int* get_winning_number();
int* get_lotto_number();
int compare(const void* a, const void* b);
void print_array(int* array, int size, int rank);
int get_rank(int* lotto_number, int* winning_number);
// int get_array_length(int* array);

void lotto()
{
    int lotto_amount; // 로또 구매 개수
    int** lotto_numbers; // 로또 번호들
    int* winning_number; // 당첨 번호
    struct lotto* winning_numbers; // 당첨된 번호들
    int winning_numbers_index = 0; // 당첨된 번호들의 인덱스
    int entered_number; // 입력한 번호

    struct lotto first_rank = { NULL, 0 }; // 1등 번호
    int repeated_count; // 반복된 횟수

    srand(time(NULL) * rand() + time(NULL) + rand());

    // 로또 개수 입력받기
    printf("자동 생성할 로또 개수를 입력해주세요\t\t1등이 나올 때까지 0번\n>");
    scanf("%d", &entered_number);
    if (entered_number != 0) lotto_amount = entered_number;
    
    // 로또 당첨 번호 생성
    winning_number = get_winning_number();
    printf("당첨 번호 생성 완료!\n\n");

    // 1등이 당첨될 때까지 로또 생성
    if (entered_number == 0)
    {
        for (int i = 0; first_rank.rank != 1; i++)
        {
            int* lotto_number = get_lotto_number();
            int rank = get_rank(lotto_number, winning_number);
            if (rank == 1)
            {
                first_rank.lotto_number = lotto_number;
                first_rank.rank = rank;
                repeated_count = i + 1;
            } 
            else if (rank < 3 && rank > 0)
            {
                printf("%d번째 : ", i + 1);
                print_array(lotto_number, LOTTO_NUMBER_LENGTH, rank);
            }
            free(lotto_number); // 메모리 해제
        }

    }
    else
    {
        // 메모리 할당
        lotto_numbers = (int**)malloc(sizeof(int*) * lotto_amount);
        winning_numbers = (struct lotto*)malloc(sizeof(struct lotto) * lotto_amount);

        // 로또 번호 생성 시작
        printf("입력 받은 수만큼 로또 번호 생성 시작!\n\n\n");
        for (int i = 0; i < lotto_amount; i++)
        {
            // 로또 번호 생성
            lotto_numbers[i] = get_lotto_number();

            // 당첨 여부 확인 및 등급 계산
            int rank = get_rank(lotto_numbers[i], winning_number);
            if (rank != 0)
            {
                winning_numbers[winning_numbers_index].lotto_number = lotto_numbers[i];
                winning_numbers[winning_numbers_index].rank = rank;
                winning_numbers_index++;
            }

            // 출력 코드
            printf("%d번째 생성한 로또 번호: ", i + 1); // 줄바꿈은 아래 print_array에서 해줌
            print_array(lotto_numbers[i], LOTTO_NUMBER_LENGTH, rank);
        }

        if(winning_numbers_index > 0)
        {
            // 당첨된 로또들 출력
            printf("\n\n\n\n\n당첨된 로또\n");
            for (int i = 0; i < winning_numbers_index + 1; i++) print_array(winning_numbers[i].lotto_number, LOTTO_NUMBER_LENGTH, winning_numbers[i].rank);
        }
        else
        {
            printf("\n\n\n\n\n당첨된 로또가 없습니다.\n\n");
        }
    }
        
    if (entered_number == 0)
    {
        printf("\n\n\n\n\n1등 번호\n");
        print_array(first_rank.lotto_number, LOTTO_NUMBER_LENGTH, first_rank.rank);
        printf("\n\n\n\n\n1등 번호가 나올 때까지 반복된 횟수: %d\n", repeated_count);
    }

    // 로또 당첨 번호 출력
    printf("당첨 번호 : ");
    for (int i = 0; i < WINNING_NUMBER_LENGTH - 1; i++) printf("%d ", winning_number[i]);
    printf("\n");
    printf("보너스 번호 : %d\n", winning_number[WINNING_NUMBER_LENGTH - 1]);
    
    if (entered_number != 0)
    {
        // 할당했던 모든 메모리 해제
        free(winning_number);
        for (int i = 0; i < lotto_amount; i++)
        {
            free(lotto_numbers[i]);
        }
        free(lotto_numbers);
        free(winning_numbers);
    }
    else free(first_rank.lotto_number);
}

/**
 * 로또 당첨번호 7개를 생성하는 함수
 */
int* get_winning_number()
{
    int* winning_number = get_numbers(WINNING_NUMBER_LENGTH, MAX_LOTTO_NUMBER);
    
    // 0~5까지 정렬
    qsort(winning_number, WINNING_NUMBER_LENGTH - 1, sizeof(int), compare);
    return winning_number;
}

/**
 * 로또 번호 6개를 생성하는 함수
 */
int* get_lotto_number()
{
    int* lotto_number = get_numbers(LOTTO_NUMBER_LENGTH, MAX_LOTTO_NUMBER);

    // 정렬
    qsort(lotto_number, LOTTO_NUMBER_LENGTH, sizeof(int), compare);
    return lotto_number;
}

/**
 * 정렬에 사용할 함수
 * 오름차순
 */
int compare(const void* a, const void* b)
{
    if (*(int*)a < *(int*)b) return -1;
    else if (*(int*)a > *(int*)b) return 1;
    else return 0;
}

/**
 * 배열 모든 요소 출력
 * 로또에서 사용함
 */
void print_array(int* array, int size, int rank)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    if(rank != 0) printf("\t\t%d등 당첨\n", rank);
    else printf("\n");
}

/**
 * 등수 알아보기
 */
int get_rank(int* lotto_number, int* winning_number)
{
    int rank = 0;
    int match_count = 0;
    int bonus_match = 0;
    for (int i = 0; i < LOTTO_NUMBER_LENGTH; i++)
    {
        for (int j = 0; j < LOTTO_NUMBER_LENGTH; j++)
        {
            if (lotto_number[i] == winning_number[j])
            {
                match_count++;
                break;
            }
        }
    }
    for (int i = 0; i < LOTTO_NUMBER_LENGTH; i++)
    {
        if (lotto_number[i] == winning_number[WINNING_NUMBER_LENGTH - 1])
        {
            bonus_match = 1;
            break;
        }
    }
    if (match_count == 6) rank = 1;
    else if (match_count == 5 && bonus_match == 1) rank = 2;
    else if (match_count == 5) rank = 3;
    else if (match_count == 4) rank = 4;
    else if (match_count == 3) rank = 5;
    return rank;
}

// 이거 왜 안되는지 모르겠음
// /**
//  * array의 길이를 반환하는 함수
//  * int* array : 검사할 int형 배열 포인터
//  * 문제 : 총 array의 길이를 알 수 없음, 할당된 개수만큼 반환 됨.
//  */
// int get_array_length(int *array)
// {
//     printf("sizeof(array) = %d\n", sizeof(array));
//     printf("sizeof(*array) = %d\n", sizeof(*array));
//     printf("sizeof(int) = %d\n", sizeof(int));
//     return sizeof(*array) / sizeof(int);
// }