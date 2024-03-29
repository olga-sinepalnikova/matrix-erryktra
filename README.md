## Реализация функций библиотеки matrix.h

Реализованы основные действия с матрицами: 
- create_matrix (создание)
- remove_matrix (очистка и уничтожение)
- eq_matrix (сравнение)
- sum_matrix (сложение)
- sub_matrix (вычитание)
- mult_matrix (умножение)
- mult_number (умножение на число)
- transpose (транспонирование)
- determinant (вычисление определителя)
- calc_complements (вычисление матрицы алгебраических дополнений)
- inverse_matrix (поиск обратной матрицы)

Библиотека разработана на языке Си стандарта C11 с использованием компилятора gcc \
При написании кода придерживался Google Style\
Проект оформлен как статическая библиотека с заголовочным файлом s21_matrix.h\
Библиотека разработана в соответствии с принципами структурного программирования\
У проекта полное покрытие unit-тестами функций библиотеки c помощью библиотеки Check. Unit-тесты должны покрывать не менее 80% каждой функции\
Предусмотрен Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_matrix.a, gcov_report). В цели gcov_report должен формироваться отчёт gcov в виде html страницы \
Матрица должна быть реализована в виде структуры:
```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```
Проверяемая точность дробной части - максимум 6 знаков после запятой.\
Все операции (кроме сравнения матриц) возвращают результирующий код:  
- 0 - OK
- 1 - Ошибка, некорректная матрица   
- 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т.д.)

Для сравнения используются следующие коды:
- 1 - Матрицы равны
- 0 - Матрицы не равны

