
#pragma once
#ifndef MATH_UTILS_H
#define MATH_UTILS_H


/**
 * @brief Обчислює значення заданої математичної функції для переданого аргументу.
 *        (В даному випадку f(x) = sin(x) + cos(x)).
 *
 * @param x Поточне значення аргументу математичної функції.
 * @return Результат обчислення функції у вигляді числа з плаваючою комою (double).
 */
double f(double x);

/**
 * @brief Множе значення змінної в пам'яті на 2, та виводить на консоль результат
 *
 * @param x вказівник
 * 
 */
void PointerTest(int* x);

#endif // MATH_UTILS_H