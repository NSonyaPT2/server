#include "Calculator.h"
#include <limits>

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