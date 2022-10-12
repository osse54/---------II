#ifndef __LOTTO_H__
#define __LOTTO_H__

static int WINNING_NUMBER_LENGTH = 7;
static int LOTTO_NUMBER_LENGTH = 6;
static int MAX_LOTTO_NUMBER = 45;

struct lotto
{
    int* lotto_number;
    int rank;
};

void lotto();
int* get_winning_number();
int* get_lotto_number();
int compare(const void* a, const void* b);
void print_array(int* array, int size, int rank);
int get_rank(int* lotto_number, int* winning_number);

#endif