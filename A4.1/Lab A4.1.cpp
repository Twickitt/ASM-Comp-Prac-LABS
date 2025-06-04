#include <stdio.h>
#include<stdlib.h>
#define N 5


void CreateMassive(char* A)
{
    int input;
    for (int i = 0; i < N; i++)
    {
        scanf_s("%d", &input);
        A[i] = (char)input;
    }
}

void PrintMassive(char* A, int n)
{
    if (n == 1)
        printf("A[15] = {");
    else
        printf("\nB[15] = {");
    for (int i = 0; i < N; i++)
        printf("%d, ", A[i]);
    printf("\b}");
}

int main()
{
    char A[16] = {5, 12, 113, 244, 2};

    char B[16] = {122, 116, 1, 244, 126};

    int C[2 * N] = { 0 }; 
    short counter = 0;

    PrintMassive(A, 1);
    PrintMassive(B, 2);

    __asm {

        lea esi, A; адрес A
        lea edi, B; адрес B
        lea ebx, C; адрес C
        mov ecx, N; счетчик циклов

        xor ax, ax; обнуляем ax
        mov counter, ax

    loop_start :
        cmp ecx, 0
        je loop_end

        movsx eax, byte ptr[esi]; eax = A[i](со знаком)
        movsx edx, byte ptr[edi]; edx = B[i](со знаком)

        add eax, edx; 

        cmp eax, 127
        jg skip_pair; если сумма > 127, скип
        cmp eax, -128
        jl skip_pair; если сумма < -128, ские

        ; Увеличиваем счетчик
        mov ax, counter
        inc ax
        mov counter, ax

        ; Записываем адреса минимальных элементов пары в массив C
        movsx eax, byte ptr[esi]; 
        movsx edx, byte ptr[edi]; 

        cmp eax, edx
            jle a_min

            ; B[i] меньше, сначала адрес B[i]
            mov eax, edi
            mov[ebx], eax
            add ebx, 4

            mov eax, esi
            mov[ebx], eax
            add ebx, 4;чтобы указывало на следующий слот записи в массиве C(4 байта)

        jmp next_iter

    a_min :
        ; A[i] меньше или равен, сначала адрес A[i]
        mov eax, esi
        mov[ebx], eax
        add ebx, 4

    next_iter:
        inc esi
        inc edi
        dec ecx
        jmp loop_start

    skip_pair :
        inc esi
        inc edi
        dec ecx
        jmp loop_start

    loop_end :
        nop
    }

    printf("\nКоличество подходящих пар: %d\n", counter);
    printf("Адреса минимальных элементов пар и их значения:\n");

    for (int i = 0; i < counter * 2; i += 2)
    {
        char* ptr1 = (char*)C[i];
        char* ptr2 = (char*)C[i + 1];
        printf("Пара %d: min addr = %p, value = %d (с учетом переполнения)\n",  i / 2 + 1, ptr1, *ptr1);
    }

    return 0;
}
