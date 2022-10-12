#include <stdio.h>
#include <stdbool.h>
#include "lotto.h"
#include "number_baseball.h"
#include "util.h"

int main()
{
    // 
    bool is_continue = true;
    while (is_continue)
    {
        int game_number = 0;
        printf("게임을 선택해주세요.\n1. 로또 게임\t\t2. 숫자야구 게임\t\t-1. 그만두기(언제든 사용 가능합니다)\n>");
        scanf("%d", &game_number);
        char message[] = "게임을 종료합니다.";
        switch (game_number)
        {
        case 1:
            lotto();
            break;
        case 2:
            number_baseball();
            break;
        case -1:
            is_continue = false;
            break;
        }
        printf("%s\n", message);
    }

    return 0;
}