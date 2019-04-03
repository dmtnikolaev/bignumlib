# bignumlib
bignumlib — университетский проект по созданию системы компьютерной алгебры для работы с длинными числами.

Библиотека поддерживает 3 типа чисел (натуральные, целые и рациональные), а также многочлены. Она написана на C89 и имеет интерфейс утилиты командной строки.

## Использование

Так как программа является утилитой командной строки, то и использовать ее надо из командной строки. Для этого откройте в папке, в которой лежит исполняемый файл командную строку (для Windows это будет Powershell, соответственно в Проводнике выполните `Файл > Запустить Windows PowerShell`), и уже с помощью командной строки необходимо запускать файл `bignumlib.exe`.

![Пример](https://i.imgur.com/c54JUqU.gif "Пример")

В исполняемый файл передаются параметры в формате:

```shell
.\bignumlib.exe <действие> <параметры>
```

где `дейcтвие` - некоторая математическая операция над параметрами,
`параметры` - операнды для действия, перечисленные через запятую (если в операнде есть пробелы, то оберните его в двойные кавычки).

Примеры:

```shell
.\bignumlib.exe int.negate -10
.\bignumlib.exe rat.mul 5 4/15
.\bignumlib.exe int.sum -5 -4
.\bignumlib.exe pol.mul-scalar "2^2, 3^1, -1)" 5
```

Список всех возможный действий для модуля можно просмотреть с помощью help для этого модуля:

```shell
.\bignumlib.exe nat.help
.\bignumlib.exe int.help
.\bignumlib.exe rat.help
.\bignumlib.exe pol.help
```

## Доступные действия

### Натуральные числа

*   `nat.help`
    Выводит справку для модуля натуральных чисел.
  
*   `nat.compare a b`
    Сравнение чисел a и b:
    - 1 - если первое больше,
    - -1 - если первое меньше,
    - 0 - если равны.

*   `nat.is-zero a`
    Проверяет, равно ли число a 0.

*   `nat.add-one a`
     Добавляет к числу a 1.

*   `nat.sum a b`
     Складывает числа a и b.

*   `nat.sub a b`
     Вычитает из первого числа второе.

*   `nat.mul-by-digit a d`
     Умножает число a на цифру d.

*   `nat.mul-by-exp10 a k`
     Умножает число a на 10^k.

*   `nat.mul a b`
     Умножает два числа.

*   `nat.sub-proportional a b d`
     Вычитает из a b, умноженное на цифру d.

*   `nat.div-first-digit a b`
     Вычисляет первую цифру частного a и b.

*   `nat.div a b`
     Возвращаете частное от деления a на b.

*   `nat.mod a b`
    Возвращает остаток от деления a на b.

*   `nat.gcd a b`
    Находит НОД a и b.

*   `nat.lcm a b`
    Находит НОК a и b.

### Целые числа

*   `int.help`
    Выводит справку для модуля целых чисел.

*   `int.abs a`
    Возвращает модуль а.

*   `int.sign a`
    Возвращает знак a.

*   `int.negate a`
    Умножает число на -1.

*   `int.sum a b`
    Складывает два числа.

*   `int.sub a b`
    Вычитает из первого числа второе.

*   `int.mul a b`
    Умножает два числа.

*   `int.div-nat a n`
    Возвращает частное от деления a на натуральное b.

*   `int.mod-nat a n`
    Возвращает остаток от деления a на натуральное b.

### Рациональные числа

*   `rat.help`
    Выводит справку для модуля рациональных чисел.

*   `rat.reduce a`
    Сокращает дробь.

*   `rat.sum a b`
    Складывает два числа.

*   `rat.sub a b`
    Вычитает из первого числа второе.

*   `rat.mul a b`
    Умножает два числа.

*   `rat.div a b`
    Делит первое число на второе.

### Многочлены

*   `pol.help`
    Выводит справку для модуля многочленов.

*   `pol.sum f g`
    Складывает два многочлена.

*   `pol.sub f g`
    Вычитает многочлен f из многочлена g.

*   `pol.mul-scalar f q`
    Умножает f на рациональное число q.

*   `pol.mul-expx f k`
    Умножает f на x^k, где k - натуральное.

*   `pol.leading f`
    Возвращает старший коэффициент.

*   `pol.deg f`
    Возвращает степень многочлена.

*   `pol.fac f`
    Выносит из многочлена НОК знаменателей
    коэффициентов и НОД числителей.

*   `pol.mul f g`
    Умножает два многочлена

*   `pol.div f g`
    Возвращает частное от деления f на g.

*   `pol.mod f g`
    Возвращает остаток от деления f на g.

*   `pol.gcd f g`
    Возвращает НОД многочленов.

*   `pol.der f`
    Находит производную f.

*   `pol.nmr f`
    Преобразует все кратные корни f в простые.

## Сборка из исходников

Для компиляции программы сперва получите ее исходный код, для этого можно либо скачать его в виде zip-архива, либо склонировать репозиторий с помощью Git:

```shell
git clone https://github.com/dmtnikolaev/bignumlib.git 
```

Теперь можно скомпилировать программу и использовать исполняемый файл из папки `bin/Debug/`.

### Windows

Находясь в корне проекта (в папке `bignum/`) откройте через проводник Powershell (`Файл > Запустить Windows PowerShell`) и выполните:

```shell
.\build\build.ps1
```

### Linux

Откройте терминал в папке проекта (`bignum/`) и запустите скрипт:

```shell
.\build\build.sh
```

## Авторы

См. [AUTHORS.md](AUTHORS.md)
