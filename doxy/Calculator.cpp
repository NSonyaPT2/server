/**
 * @file Calculator.cpp
 * @author Назарова Софья
 * @brief Реализация класса Calculator
 * @version 1.0
 * @date 2025
 * @copyright WECT ПГУ
 */

#include "Calculator.h"
#include <limits>

/**
 * @brief Вычисление суммы квадратов элементов вектора
 * @param[in] data Вектор значений типа uint16_t
 * @return Результат вычислений (uint16_t)
 * @note При переполнении возвращается максимальное значение uint16_t
 * @details Алгоритм соответствует требованиям ТЗ п.4.2.5:
 *          - Проверка переполнения при суммировании
 *          - Возврат 2^15-1 при переполнении вверх
 *          - Возврат 0 при переполнении вниз
 */
uint16_t Calculator::calculateSumOfSquares(const std::vector<uint16_t>& data) {
    uint32_t sum = 0;
    
    for (uint16_t value : data) {
        uint32_t square = static_cast<uint32_t>(value) * value;
        
        // Проверка переполнения
        if (sum > std::numeric_limits<uint32_t>::max() - square) {
            return std::numeric_limits<uint16_t>::max(); // 2^15 - 1 для uint16_t
        }
        
        sum += square;
    }
    
    // Проверка, что результат помещается в uint16_t
    return (sum <= std::numeric_limits<uint16_t>::max()) ? 
           static_cast<uint16_t>(sum) : std::numeric_limits<uint16_t>::max();
}