#pragma once
#include <cmath> // для sqrt(), abs() и других математических функций
#include <cfloat> // для FLT_EPSILON (проверка на ноль с плавающей точкой)
#include <iostream> // для перегрузки оператора <<
#include <algorithm> 

namespace GameEngine
{
    // 2D Вектор
    template <typename T>
    struct Vector2D 
    {
        T x;
        T y;

        Vector2D() : x(0), y(0) {}
        Vector2D(T newX, T newY) : x(newX), y(newY) {}
        explicit Vector2D(T scalar) : x(scalar), y(scalar) {}
       
        // Базовые операции
        Vector2D operator+(const Vector2D& other) const { return Vector2D(x + other.x, y + other.y); }
        Vector2D operator-(const Vector2D& other) const { return Vector2D(x - other.x, y - other.y); }
        Vector2D operator*(T scalar) const { return Vector2D(x * scalar, y * scalar); }
        Vector2D operator*(const Vector2D& other) const { return Vector2D(x * other.x, y * other.y); }
        Vector2D operator/(T scalar) const { return scalar != 0 ? Vector2D(x / scalar, y / scalar) : Vector2D(0, 0); }

        // Операции присваивания
        Vector2D& operator+=(const Vector2D& other) { x += other.x; y += other.y; return *this; }
        Vector2D& operator-=(const Vector2D& other) { x -= other.x; y -= other.y; return *this; }
        Vector2D& operator*=(T scalar) { x *= scalar; y *= scalar; return *this; }
        Vector2D& operator/=(T scalar) { if (scalar != 0) { x /= scalar; y /= scalar; } return *this; }

        // Унарный минус
        Vector2D operator-() const { return Vector2D(-x, -y); }

        // Сравнение
        bool operator==(const Vector2D& other) const { return x == other.x && y == other.y; }
        bool operator!=(const Vector2D& other) const { return !(*this == other); }

        // Длина вектора
        float GetLength() const { return std::sqrt(x * x + y * y); }
        float Length() const { return GetLength(); } // Алиас для совместимости

        // Квадрат длины
        float LengthSquared() const { return x * x + y * y; }

        // Нормализация
        Vector2D Normalized() const {
            float len = GetLength();
            if (len > FLT_EPSILON) {
                return Vector2D(x / len, y / len);
            }
            return Vector2D(0, 0);
        }

        // Точечное произведение
        float DotProduct(const Vector2D& vector) const {
            return x * vector.x + y * vector.y;
        }

        // Расстояние между векторами
        static float Distance(const Vector2D& a, const Vector2D& b) { return (a - b).GetLength(); }

        // Линейная интерполяция
        static Vector2D Lerp(const Vector2D& a, const Vector2D& b, float t) {
            t = std::clamp(t, 0.0f, 1.0f);
            return a + (b - a) * t;
        }

        // Нулевой вектор
        static Vector2D Zero() { return Vector2D(0, 0); }

        // Векторы-орты
        static Vector2D Right() { return Vector2D(1, 0); }
        static Vector2D Up() { return Vector2D(0, 1); }
        
        friend Vector2D operator*(T scalar, const Vector2D& vec) {
            return Vector2D(scalar * vec.x, scalar * vec.y);
        }
    };


    // Перегрузка оператора вывода
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vector2D<T>& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }

    // Псевдонимы типов
    using Vector2Df = Vector2D<float>;
    using Vector2i = Vector2D<int>;
    using Vector2u = Vector2D<unsigned int>;
}