#include <iostream>
#include <vector>
#include <algorithm> // remove_if, any_of

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Удаляем из переданной строки точки, кроме первой
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

// Возвращает true если хотя бы один из элементов range соответствует item
bool isIncludes(const string &range, const char &item) {
    return std::any_of(range.begin(), range.end(),
                       [&item](const char &c) { return c == item; });
}

// True если есть один из операторов
bool isIncludesOperators(const char &letter) {
    const std::string operators{"+-*/"};
    return isIncludes(operators, letter);
}

// True если это число или точка
bool isIncludesDotOrDigits(const char &letter) {
    const std::string operators{"0123456789."};
    return isIncludes(operators, letter);
}

void splitToParts(const string &text, vector<string> &parts) {
    const char MINUS = 45;

    bool isAlpha = false;
    string substring = "";

    for (int i = 0; i < text.length(); ++i) {
        char letter = text[i];

        if (i == 0 && letter == MINUS) substring += letter;

        if (isIncludesDotOrDigits(letter)) {
            isAlpha = true;
            substring += letter;
        } else if (isIncludesOperators(letter)) {
            if (isAlpha && substring.length()) {
                removeDots(substring);
                parts.push_back(substring);

                if ((i != text.length() - 1)) {
                    substring = letter;
                    parts.push_back(substring);
                }

                substring = "";
                isAlpha = false;
            }
        }

        if (i == (text.length() - 1)) {
            if (isAlpha && substring.length()) {
                removeDots(substring);
                parts.push_back(substring);

                substring = "";
                isAlpha = false;
            }
        }
    }
}

double stringToDouble(string const &text) {
    double result;
    try {
        result = std::stod(text);
    } catch (std::invalid_argument &err) {
        std::cerr << err.what() << endl;
    }
    return result;
}

double getResult(vector<string> const &parts) {
    double result = stringToDouble(parts[0]);
    char op;

    for (int i = 1; i < parts.size(); ++i) {
        if (i % 2 == 1) {
            op = parts[i][0];
        } else {
            double current = stringToDouble(parts[i]);
            if (op == 42) {
                result *= current;
            } else if (op == 43) {
                result += current;
            } else if (op == 45) {
                result -= current;
            } else if (op == 47) {
                result /= current;
            }
        }
    }

    return result;
}

void printResult(vector<string> const &parts) {
    cout << "After process:  ";
    for (const string &item: parts) cout << item << " ";
    cout << "= ";
    printf("%.3f\n", getResult(parts));
    cout << "---------------------" << endl;
}

int main() {
    // Нужно сменить статус для включения пользовательского ввода
    bool TEST_STATUS = true;

    if (TEST_STATUS) {
        vector<string> texts4Test = {
                "34.05 + 12",
                "2 / 3",
                "b,lf11*6.54.0.1+.65.-9.3.-",
                "345/65.36      + dfhgf45.023+ =",
                "-+=6dfsg,3245.44.4.4/8*96   +65",
        };

        for (string &text: texts4Test) {
            vector<string> parts;

            cout << "Before process: " << text << endl;

            splitToParts(text, parts);
            printResult(parts);
        }
    } else {
        vector<string> parts;
        string text;

        cout << "Enter numbers & operators in any format (example 345.4+23*45.3)\n";
        std::getline(std::cin, text);

        splitToParts(text, parts);
        printResult(parts);
    }
}

