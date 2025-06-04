#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <iostream>

typedef int (*IsDigit) (int);

int main()
{
    IsDigit p = isdigit;
    char a, b, c;
    printf("Enter your string(3 digits):\n");
    std::cin >> a >> b >> c;

    if (p(a) && p(b) && p(c))
    {
        __asm {
            mov al, a
            sub al, '0'
            mov ah, b
            sub ah, '0'
            sub al, ah
            mov bl, b
            mov bh, c
            sub bl, bh
            sub al, bl
            cmp al, 1
            je replacement; если разница разностей = 1, идем к замене
            cmp al, -1
            je replacement; если разница разностей = -1, тоже заменяем
            jmp replace_all; если разницы разностей нет, заменяем все на '5'

            replacement:
            // Определяем максимальную и минимальную цифры
                mov al, a
                mov ah, b
                mov bl, c

                cmp al, ah
                jge check
                mov al, ah
                check_al_bl :
            cmp al, bl
                jge found_max
                mov al, bl
                found_max :

            mov ah, a
                cmp ah, b
                jle check
                mov ah, b
                check_ah_bl :
            cmp ah, c
                jle found_min
                mov ah, c
                found_min :

            // Заменяем максимальную цифру на минимальную
                cmp a, al
                jne check_b
                mov a, ah
                check_b :
            cmp b, al
                jne check_c
                mov b, ah
                check_c :
            cmp c, al
                jne fin
                mov c, ah
                jmp fin

                replace_all :
            mov a, '5'
                mov b, '5'
                mov c, '5'

                fin :
        }
        printf("Modified string: %c%c%c\n", a, b, c);
    }
    else
        printf("Your string includes non digits\n");

    return 0;
}


/*Тесты:
532
431
643
631
111
925
AAA
01A
!!!
964
*/