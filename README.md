## Калькулятор:

Создайте небольшую программу для вычисления простых действий с числами. 
При запуске программа ожидает пользовательского ввода во временную переменную строку. 
После ввода строки она распарсивается на отдельные члены. 

Строка записывается в форме “<число-1><действие><число-2>” (без пробелов). 
Оба числа — это значения с плавающей точкой, повышенной точности (double). 
Действие может быть одним из: +, −, /, *. 
Результат действия выводится в стандартный вывод cout.

### Интересные сниппеты:

Два варианта удаления символов из строки:

```C++
// #include <algorithm> // remove_if
void removeDots(string &readjust) {
    const char DOT = 46;
    int count = 0;

    if (readjust[readjust.length() - 1] == '.') {
        readjust.erase(std::prev(readjust.end()));
    }

    auto it =
            std::remove_if(readjust.begin(), readjust.end(), [&count](char &c) {
                if (c == DOT) ++count;
                return (count > 1 && c == DOT);
            });

    readjust.erase(it, readjust.end());
}
```
---

Аналогичный по действию в JS includes. 
Нужно лишь передать строкой необходимый список типа `"+-*/"`:

```C++
// #include <algorithm> // any_of
bool isIncludes(const string &range, const char &item) {
    return std::any_of(range.begin(), range.end(),
                       [&item](const char &c) { return c == item; });
}
```

### Интересные ссылки:

[Удалить определенные символы из строки](https://www.techiedelight.com/ru/remove-certain-characters-string-cpp/)

[Алгоритмы диапазонов C++20](https://habr.com/ru/companies/skillfactory/articles/706458/)