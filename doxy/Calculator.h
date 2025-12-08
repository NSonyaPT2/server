#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <vector>
#include <cstdint>

/**
 * @class Calculator
 * @brief Класс для математических вычислений
 * @details Содержит статические методы для вычислений над векторами данных
 */
class Calculator {
public:
    /**
     * @brief Вычисление суммы квадратов элементов вектора
     * @param[in] data Вектор значений типа uint16_t
     * @return Результат вычислений (uint16_t)
     * @note При переполнении возвращается максимальное значение uint16_t
     * @see Требования к функции обработки данных (ТЗ п.4.2.5)
     */
    static uint16_t calculateSumOfSquares(const std::vector<uint16_t>& data);
};

#endif