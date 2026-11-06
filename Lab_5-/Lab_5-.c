#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Func.h"

#ifdef _WIN32
#include <windows.h>
#endif


int main() {

    //Локалізація
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    printf("Приклад з вказівниками");

    //Приклад вказівник
    int b = 10;
    //Оголошення вказівника та ініціалізація
    int* a = &b;
    
    //Виведення посилання на область в пам'яті
 
    printf("Адреса змінної b: %p\n", a);


    //Розімінування та виведення значення вказівника.
    printf("Початкове значення зміної а: %i\n", *a);
    //Так як вказівник вказує на область в пам'яті, то змінюючи змінну b ми змінюємо значення в пам'яті
    //(Такий самий ефект працює і в іншу сторону)
    //Вказівник (а) зберігає посилання на область в пам'яті зміної b, тому значення яке виведеться буде не 10 а 12
    b = 12;
    printf("Значення змінної після змінни значення в ваказівнику(b). a: %i\n", *a);
    /*
        
        Якщо ми використовували б змінні, то значення зміної b скопіювалось би в змінну а
        Змінюючи значення зміної b на змінну (а) це ніяк не впливає
    
    */
    printf("\n\n\n\n\n\n");
   
    printf("Приклад з функцією\n");

    int g = 25;

    PointerTest(&g);

    printf("значення зміної f: %i\n", g);

    printf("\n\n\n\n\n\n");
    
    



    double x1, x2, delta, x, fx;
    unsigned int N;
    char group[50];
    char name[100];

    // 1-2. Відкриття та зчитування даних з текстового файлу
    FILE* fin = fopen("input.txt", "r");
    if (!fin) {
        printf("Помилка: не вдалося відкрити input.txt\n");
        return 1;
    }


    fscanf(fin, "%lf", &x1);
    fscanf(fin, "%lf", &x2);
    fscanf(fin, "%u", &N);
    fscanf(fin, "%lf", &delta);
    fscanf(fin, " %[^\n]", group); // Зчитування рядка з пробілами
    fscanf(fin, " %[^\n]", name);
    fclose(fin);

    // 3-4. Створення вихідного текстового файлу
    FILE* fout = fopen("output.txt", "w");
    if (!fout) {
        printf("Помилка створення output.txt\n");
        return 1;
    }

    // 5. Створення бінарного файлу
    FILE* fbin = fopen("data.bin", "wb");
    if (!fbin) {
        printf("Помилка створення data.bin\n");
        fclose(fout);
        return 1;
    }

    // Запис кількості точок у бінарний файл
    fwrite(&N, sizeof(unsigned int), 1, fbin);

    // Побудова таблиці та запис у файли
    fprintf(fout, "--------------------------------------------------\n");
    fprintf(fout, "| № точки | Значення аргументу | Значення функції|\n");
    fprintf(fout, "--------------------------------------------------\n");

    x = x1;
    for (unsigned int i = 1; i <= N; i++) {
        fx = f(x);

        // Запис у текстовий файл
        fprintf(fout, "| %7u | %18.4lf | %15.4lf |\n", i, x, fx);

        // Запис пари (x, f(x)) у бінарний файл
        fwrite(&x, sizeof(double), 1, fbin);
        fwrite(&fx, sizeof(double), 1, fbin);

        x += delta;
        if (x > x2 + 1e-9) break; // Захист від похибки заокруглення
    }
    fprintf(fout, "--------------------------------------------------\n");
    fprintf(fout, "Група: %s\n", group);
    fprintf(fout, "Студент: %s\n", name);

    fclose(fout);
    fclose(fbin);

    // 7. Читання з бінарного файлу та вивід на екран
    FILE* fbin_in = fopen("data.bin", "rb");
    if (!fbin_in) {
        printf("Помилка відкриття data.bin для читання\n");
        return 1;
    }

    unsigned int read_N;
    fread(&read_N, sizeof(unsigned int), 1, fbin_in);

    // Створення динамічного масиву розміром 2N
    double* arr = (double*)malloc(2 * read_N * sizeof(double));
    if (!arr) {
        printf("Помилка виділення пам'яті\n");
        fclose(fbin_in);
        return 1;
    }

    // Читання всіх пар даних у динамічний масив одним блоком
    fread(arr, sizeof(double), 2 * read_N, fbin_in);
    fclose(fbin_in);


    // ВИВІД УСІХ ВХІДНИХ ДАНИХ
    printf("Початкове значення аргументу: %.5lf\n", x1);
    printf("Кінцеве значення аргументу: %.5lf\n", x2);
    printf("Кількість точок: %u\n", N);
    printf("Крок зміни аргументу: %.5lf\n", delta);
    printf("Група: %s\n", group);
    printf("Студент: %s\n", name);

    // Вивід прочитаних даних на екран у вигляді таблиці
    printf("Дані, зчитані з бінарного файлу data.bin:\n");


    printf("--------------------------------------------------\n");
    printf("| № точки | Значення аргументу | Значення функції|\n");
    printf("--------------------------------------------------\n");

    int line_count = 0;
    for (unsigned int i = 0; i < read_N; i++) {
        double current_x = arr[2 * i];
        double current_fx = arr[2 * i + 1];

        printf("| %7u | %18.4lf | %15.4lf |\n", i + 1, current_x, current_fx);
        line_count++;

        // Посторінковий вивід (зупинка після 20 рядків)
        if (line_count % 20 == 0 && i != read_N - 1) {
            printf("Press Enter to Continue...\n");
            getchar(); // Очікування натискання клавіші
        }
    }
    printf("--------------------------------------------------\n");

    // Звільнення пам'яті
    free(arr);

    return 0;
}