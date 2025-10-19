#include "number.h"
#include <cstring>
#include <cctype>
#include <stdexcept>

namespace {

const int BITS_IN_BYTE = 8;
const int TOTAL_BITS = 2025;
const int DATA_BITS = int2025_t::SIZE * BITS_IN_BYTE; // должно быть 253 * 8 = 2024


// Проверка на ноль
bool is_zero(const int2025_t& num) {
    for (int i = 0; i < int2025_t::SIZE; ++i) {
        if (num.data[i] != 0) return false;
    }
    return true;
}

// Получить бит
bool get_bit(const int2025_t& num, int bit_pos) {
    int byte_index = bit_pos / BITS_IN_BYTE;
    int bit_index = bit_pos % BITS_IN_BYTE;
    return (num.data[byte_index] >> bit_index) & 1;
}

// Установить бит
void set_bit(int2025_t& num, int bit_pos, bool value) {
    int byte_index = bit_pos / BITS_IN_BYTE;
    int bit_index = bit_pos % BITS_IN_BYTE;

    if (value) {
        num.data[byte_index] |= (1 << bit_index);
    } else {
        num.data[byte_index] &= ~(1 << bit_index);
    }
}

// Проверить знак (true если отрицательное)
bool is_negative(const int2025_t& num) {
    return get_bit(num, DATA_BITS - 1);
}

    // Инвертировать число (дополнительный код)
int2025_t negate(const int2025_t& num) {
    int2025_t result;

    // Инвертируем все биты
    for (int i = 0; i < int2025_t::SIZE; ++i) {
        result.data[i] = ~num.data[i];
    }

    // Добавляем 1
    int carry = 1;
    for (int i = 0; i < int2025_t::SIZE && carry; ++i) {
        uint16_t sum = result.data[i] + carry;
        result.data[i] = sum & 0xFF;
        carry = sum >> 8;
    }

    return result;
}

// Абсолютное значение
int2025_t abs(const int2025_t& num) {
    return is_negative(num) ? negate(num) : num;
}

    // Сравнение (возвращает -1 если lhs < rhs, 0 если равны, 1 если lhs > rhs)
int compare(const int2025_t& lhs, const int2025_t& rhs) {
    bool lhs_neg = is_negative(lhs);
    bool rhs_neg = is_negative(rhs);

    if (lhs_neg && !rhs_neg) return -1;
    if (!lhs_neg && rhs_neg) return 1;

    // Оба положительные или оба отрицательные
    // Сравниваем побайтово от старшего к младшему
    for (int i = int2025_t::SIZE - 1; i >= 0; --i) {
        if (lhs.data[i] < rhs.data[i]) {
            return lhs_neg ? 1 : -1;
        } else if (lhs.data[i] > rhs.data[i]) {
            return lhs_neg ? -1 : 1;
        }
    }

    return 0; // Равны
}


// Сложение беззнаковых чисел
int2025_t add_unsigned(const int2025_t& lhs, const int2025_t& rhs) {
    int2025_t result;
    int carry = 0;

    for (int i = 0; i < int2025_t::SIZE; ++i) {
        int sum = lhs.data[i] + rhs.data[i] + carry;
        result.data[i] = sum & 0xFF;
        carry = sum >> 8;
    }

    return result;
}

    // Вычитание беззнаковых чисел (корректно работает даже если lhs < rhs)
    int2025_t sub_unsigned(const int2025_t& lhs, const int2025_t& rhs) {
    int2025_t result;
    int borrow = 0;

    for (int i = 0; i < int2025_t::SIZE; ++i) {
        int diff = lhs.data[i] - rhs.data[i] - borrow;
        if (diff < 0) {
            diff += 256;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.data[i] = diff;
    }

    return result;
}

// Сдвиг влево
void shift_left(int2025_t& num) {
    int carry = 0;
    for (int i = 0; i < int2025_t::SIZE; ++i) {
        int new_carry = (num.data[i] >> 7) & 1;
        num.data[i] = (num.data[i] << 1) | carry;
        carry = new_carry;
    }
}

// Сдвиг вправо (арифметический)
void shift_right(int2025_t& num) {
    int sign_bit = is_negative(num) ? 0x80 : 0;
    int carry = 0;

    for (int i = int2025_t::SIZE - 1; i >= 0; --i) {
        int new_carry = num.data[i] & 1;
        num.data[i] = (carry << 7) | (num.data[i] >> 1);
        carry = new_carry;
    }

    // Устанавливаем знаковый бит
    if (sign_bit) {
        num.data[int2025_t::SIZE - 1] |= 0x80;
    }
}

} // namespace

int2025_t from_int(int32_t i) {
    int2025_t result;
    std::memset(result.data, 0, int2025_t::SIZE);

    if (i == 0) {
        return result;
    }

    bool negative = i < 0;
    uint32_t value = negative ? -static_cast<uint32_t>(i) : static_cast<uint32_t>(i);

    // Записываем младшие байты
    for (int j = 0; j < 4 && j < int2025_t::SIZE; ++j) {
        result.data[j] = value & 0xFF;
        value >>= 8;
    }

    // Если число отрицательное, преобразуем в дополнительный код
    if (negative) {
        result = negate(result);
    }

    return result;
}

int2025_t from_string(const char* buff) {
    if (!buff || !*buff) return from_int(0);

    bool negative = false;
    const char* ptr = buff;

    // Пропускаем пробелы
    while (*ptr == ' ' || *ptr == '\t') ++ptr;

    // Обрабатываем знак
    if (*ptr == '-') {
        negative = true;
        ptr++;
    } else if (*ptr == '+') {
        ptr++;
    }

    // Пропускаем ведущие нули
    while (*ptr == '0') ptr++;

    // Если строка пустая после знака и нулей, возвращаем 0
    if (!*ptr) return from_int(0);

    int2025_t result;
    std::memset(result.data, 0, int2025_t::SIZE);

    while (*ptr && std::isdigit(*ptr)) {
        int digit = *ptr - '0';

        // result = result * 10 + digit (без использования operator*)
        // Умножаем result на 10 вручную
        uint32_t carry = 0;
        for (int i = 0; i < int2025_t::SIZE; ++i) {
            uint32_t temp = static_cast<uint32_t>(result.data[i]) * 10 + carry;
            result.data[i] = temp & 0xFF;
            carry = temp >> 8;
        }

        // Добавляем digit
        carry = digit;
        for (int i = 0; i < int2025_t::SIZE && carry; ++i) {
            uint32_t sum = static_cast<uint32_t>(result.data[i]) + carry;
            result.data[i] = sum & 0xFF;
            carry = sum >> 8;
        }

        ptr++;
    }

    return negative ? negate(result) : result;
}

int2025_t operator+(const int2025_t& lhs, const int2025_t& rhs) {
    // Простое сложение в дополнительном коде
    int2025_t result;
    int carry = 0;

    for (int i = 0; i < int2025_t::SIZE; ++i) {
        int sum = lhs.data[i] + rhs.data[i] + carry;
        result.data[i] = sum & 0xFF;
        carry = sum >> 8;
    }

    return result;
}

int2025_t operator-(const int2025_t& lhs, const int2025_t& rhs) {
    // Вычитание через сложение с отрицанием
    return lhs + negate(rhs);
}

int2025_t operator*(const int2025_t& lhs, const int2025_t& rhs) {
    if (is_zero(lhs) || is_zero(rhs)) {
        return from_int(0);
    }

    bool result_negative = is_negative(lhs) != is_negative(rhs);

    int2025_t a = abs(lhs);
    int2025_t b = abs(rhs);

    int2025_t result;
    std::memset(result.data, 0, int2025_t::SIZE);

    // Умножение "в столбик" по байтам
    for (int i = 0; i < int2025_t::SIZE; ++i) {
        if (b.data[i] == 0) continue;

        uint32_t carry = 0;
        for (int j = 0; j < int2025_t::SIZE - i; ++j) {
            uint32_t product = static_cast<uint32_t>(a.data[j]) * static_cast<uint32_t>(b.data[i]) +
                              static_cast<uint32_t>(result.data[i + j]) + carry;
            result.data[i + j] = product & 0xFF;
            carry = product >> 8;
        }
    }

    return result_negative ? negate(result) : result;
}


int2025_t operator/(const int2025_t& lhs, const int2025_t& rhs) {
    if (is_zero(rhs)) {
        return from_int(0); // Деление на ноль
    }

    if (is_zero(lhs)) {
        return from_int(0);
    }

    bool result_negative = is_negative(lhs) != is_negative(rhs);

    int2025_t dividend = abs(lhs);
    int2025_t divisor = abs(rhs);

    if (compare(dividend, divisor) < 0) {
        return from_int(0);
    }

    int2025_t quotient = from_int(0);
    int2025_t remainder = from_int(0);

    for (int i = DATA_BITS - 1; i >= 0; --i) {
        shift_left(remainder);
        set_bit(remainder, 0, get_bit(dividend, i));

        if (compare(remainder, divisor) >= 0) {
            remainder = sub_unsigned(remainder, divisor);
            set_bit(quotient, i, true);
        }
    }

    return result_negative ? negate(quotient) : quotient;
}

int2025_t operator%(const int2025_t& lhs, const int2025_t& rhs) {
    if (is_zero(rhs)) {
        return from_int(0);
    }

    int2025_t dividend = abs(lhs);
    int2025_t divisor = abs(rhs);

    if (compare(dividend, divisor) < 0) {
        return lhs; // Остаток равен делимому
    }

    int2025_t remainder = from_int(0);

    for (int i = DATA_BITS - 1; i >= 0; --i) {
        shift_left(remainder);
        set_bit(remainder, 0, get_bit(dividend, i));

        if (compare(remainder, divisor) >= 0) {
            remainder = sub_unsigned(remainder, divisor);
        }
    }

    // Знак остатка такой же как у делимого
    return is_negative(lhs) ? negate(remainder) : remainder;
}

bool operator==(const int2025_t& lhs, const int2025_t& rhs) {
    return compare(lhs, rhs) == 0;
}

bool operator!=(const int2025_t& lhs, const int2025_t& rhs) {
    return compare(lhs, rhs) != 0;
}

std::ostream& operator<<(std::ostream& stream, const int2025_t& value) {
    if (is_zero(value)) {
        stream << "0";
        return stream;
    }

    int2025_t temp = value;
    if (is_negative(temp)) {
        stream << "-";
        temp = abs(temp);
    }

    // Конвертируем в десятичную строку
    char buffer[610] = {0};
    int pos = 0;

    int2025_t zero = from_int(0);
    int2025_t ten = from_int(10);

    while (!is_zero(temp)) {
        int2025_t rem = temp % ten;
        int2025_t div = temp / ten;

        // Получаем цифру из остатка
        int digit = 0;
        for (int i = 0; i < 4; ++i) {
            digit |= (rem.data[i] << (i * 8));
        }

        buffer[pos++] = '0' + digit;
        temp = div;
    }

    // Выводим в обратном порядке
    for (int i = pos - 1; i >= 0; --i) {
        stream << buffer[i];
    }

    return stream;
}
