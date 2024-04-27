#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cmath>

/*
* Спарсить строку по пробелу.
* @param str - строка;
* @return - вектор строк, строки - это части начальной строки.
*/
std::vector<std::string> ParseString(const std::string& str) {
    std::vector<std::string> res;
    std::string word;
    for (char c : str) {
        if (c == ' ') {
            res.push_back(word);
            word.clear();
        }
        else {
            word += c;
        }
    }
    res.push_back(word);
    return res;
}

/*
* Рассчитать индекс массы тела.
* @param weight - вес в кг;
* @param height - рост в м;
* @return индекс массы тела: вес делится на рост в квадрате.
*/
double CalculateBodyMassIndex(const double weight, const double height) {
    double res = weight / std::pow(height, 2);
    return res;
}

/*
* Рассчитать среднее значение элементов в контейнере.
* @param values - контейнер для расчета;
* @return - среднее значение: сумма всех значений делится на количество элементов в контейнере.
*/
double CalculateAverageValue(const std::vector<double>& values) {
    auto sum = std::accumulate(values.begin(), values.end(), 0.);
    auto size = values.size();
    return sum / size;
}

/*
* Рассчитать медиану.
* @param values - контейнер, в котором происходит поиск медианного значения;
* @return - значение медианы.
*/
double CalculateMedianValue(const std::vector<double>& values) {
    auto half_index = values.size() / 2;
    return (values.size() % 2 == 0 ? (values[half_index] + values[half_index - 1]) / 2 : values[half_index]);
}

int main()
{
    // считывание количества обитателей зоопарка
    std::string str;
    std::getline(std::cin, str);
    int animals_count = std::stoi(str);
    if (animals_count == 0) {
        std::cout << "Wrong number of animals" << std::endl;
        return 0;
    }
    // контейнер, в котором будет храниться ИМТ животных
    std::vector<double> animalBodyIndexMass;
    animalBodyIndexMass.reserve(animals_count);
    // контейнер, в котором будет храниться размах крыла птиц
    std::vector<double> birdWingSpan;

    // считываем вводимые строки с характеристиками животных
    while (animals_count != 0) {
        std::getline(std::cin, str);
        // разбиваем строку на данные: имя, вес, рост, при необходимости размах крыла
        auto res = ParseString(str.substr(2));
        // для расчета ИМТ нужны вес и рост животного
        const double weight = std::stoi(res[1]) / 1000.;
        const double height = std::stoi(res[2]) / 100.;
        // расчет и сохранение ИМТ животного
        animalBodyIndexMass.push_back(CalculateBodyMassIndex(weight, height));
        // если вводятся данные птицы, то сохраняем ее размах крыла
        if (str[0] == '1') {
            const double wing_span = std::stoi(res[3]);
            birdWingSpan.push_back(wing_span);
        }
        --animals_count;
    }

    std::sort(animalBodyIndexMass.begin(), animalBodyIndexMass.end());
    // расчет и вывод в консоль среднего значения ИМТ и медианы ИМТ среди всех обитателей зоопарка
    std::cout << CalculateAverageValue(animalBodyIndexMass) << ' ' << CalculateMedianValue(animalBodyIndexMass);

    if (!birdWingSpan.empty()) {
        std::sort(birdWingSpan.begin(), birdWingSpan.end());
        // расчет и вывод в консоль и медианы размахов крыла у птиц
        std::cout << ' ' << CalculateMedianValue(birdWingSpan);
    }

    std::cout << std::endl;
    return 0;
}
