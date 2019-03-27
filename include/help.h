#ifndef HELP_H
#define HELP_H

#include <wchar.h>

// Делим длинный текст на куски по <512 байт
//

static const wchar_t help_1[] = L"\
bignumlib -- библиотека и утилита командной строки для\n\
работы с длинной арифметикой.\n\
\n\
Использование: .\\bignumlib.exe <действие> <параметры>\n\
\n\
где\n\
    <действие> - некоторая математическая операция над\n\
    параметрами.\n\
\n\
";

static const wchar_t help_2[] = L"\
    <параметры> - операнды для действия, перечисленные через\n\
    пробел (если в операнде есть пробелы, то оберните его в\n\
    двойные кавычки).\n\
\n\
Чтобы просмотреть список доступных действий для модуля введите \n\
\n\
.\\bignumlib.exe <модуль>.help \n\
\n\
где <модуль> может быть 'nat', 'int', 'rat', 'pol'.\n\
\n\
";

static const wchar_t help_3[] = L"\
Примеры:\n\
\n\
.\\bignumlib.exe int.negate -10\n\
.\\bignumlib.exe rat.mul 5 4/15\n\
.\\bignumlib.exe int.sum -5 -4\n\
.\\bignumlib.exe pol.mul-scalar \"(2, 0, -1)\" 5 \n\
";

static const wchar_t nat_help_1[] = L"\
НАТУРАЛЬНЫЕ ЧИСЛА (BigNat)\n\
\n\
* nat.help\n\
    Выводит справку для модуля натуральных чисел.\n\
\n\
* nat.compare a b\n\
    Сравнение чисел a и b.\n\
     1 - если первое больше,\n\
    -1 - если первое меньше,\n\
     0 - если равны.\n\
\n\
";

static const wchar_t nat_help_2[] = L"\
* nat.is-zero a\n\
    Проверяет, равно ли число a 0.\n\
\n\
* nat.add-one a\n\
    Добавляет к числу a 1.\n\
\n\
* nat.sum a b\n\
    Складывает числа a и b.\n\
\n\
* nat.sub a b\n\
    Вычитает из первого числа второе.\n\
\n\
* nat.mul-by-digit a d\n\
    Умножает число a на цифру d.\n\
\n\
";

static const wchar_t nat_help_3[] = L"\
* nat.mul-by-exp10 a k\n\
    Умножает число a на 10^k.\n\
\n\
* nat.mul\n\
    Умножает два числа.\n\
* nat.sub-proportional a b d\n\
    Вычитает из a b, умноженное на цифру d.\n\
\n\
* nat.div-first-digit a b\n\
    Вычисляет первую цифру частного a и b.\n\
\n\
";

static const wchar_t nat_help_4[] = L"\
* nat.div a b\n\
    Возвращаете частное от деления a на b.\n\
\n\
* nat.mod a b\n\
    Возвращает остаток от деления a на b.\n\
\n\
* nat.gcd a b\n\
    Находит НОД a и b.\n\
\n\
* nat.lcm a b\n\
    Находит НОК a и b.\n\
";

static const wchar_t int_help_1[] = L"\
ЦЕЛЫЕ ЧИСЛА (BigInt)\n\
\n\
* int.help\n\
    Выводит справку для модуля целых чисел.\n\
\n\
* int.abs a\n\
    Возвращает модуль а.\n\
\n\
* int.sign a\n\
    Возвращает знак a.\n\
\n\
* int.negate a\n\
    Умножает число на -1.\n\
\n\
* int.sum a b\n\
    Складывает два числа.\n\
\n\
";
static const wchar_t int_help_2[] = L"\
* int.sub a b\n\
    Вычитает из первого числа второе.\n\
\n\
* int.mul a b\n\
    Умножает два числа.\n\
\n\
* int.div-nat a n\n\
    Возвращает частное от деления a на натуральное b.\n\
\n\
* int.mod-nat a n\n\
    Возвращает остаток от деления a на натуральное b.\n\
";

static const wchar_t rat_help_1[] = L"\
РАЦИОНАЛЬНЫЕ ЧИСЛА (BigRat)\n\
\n\
Состоят из числителя - целого числа, и знаменателя\n\
- натурального числа. Эти части разделяются с помощью\n\
слеша '/', который можно опускать, если знаменатель равен\n\
1 (например, 3/2, -3/7, -5).\n\
\n\
";

static const wchar_t rat_help_2[] = L"\
* rat.help\n\
    Выводит справку для модуля рациональных чисел.\n\
\n\
* rat.reduce a\n\
    Сокращает дробь.\n\
\n\
* rat.sum a b\n\
    Складывает два числа.\n\
\n\
";

static const wchar_t rat_help_3[] = L"\
* rat.sub a b\n\
    Вычитает из первого числа второе.\n\
\n\
* rat.mul a b\n\
    Умножает два числа.\n\
\n\
* rat.div a b\n\
    Делит первое число на второе.\n\
";

static const wchar_t pol_help_1[] = L"\
МНОГОЧЛЕНЫ (BigPol)\n\
\n\
В данный момент модуль не реализован.\n\
\n\
* pol.help\n\
    Выводит справку для модуля многочленов.\n\
";

#endif