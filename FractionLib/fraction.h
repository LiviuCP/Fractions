#ifndef FRACTION_H
#define FRACTION_H

#include <string>
#include <fstream>
#include <stdexcept>

class Fraction
{
public:
    enum class DecimalStringIndexes
    {
        INVALID = -2,
        INTEGER = -1, // integer string, still valid
        NIL = 0 // just checking the string is "pure" decimal (index of the dot should be greater than 0)
    };

    enum class FractionStringIndexes
    {
        ERROR = -2, // same error index for consistency to decimal string
        NIL = 0 // just for validity checking (index of the slash should be greater than 0)
    };

    // constructors
    Fraction();
    explicit Fraction(int numerator);
    explicit Fraction(double decimalValue);
    Fraction(int numerator, int denominator);
    explicit Fraction(const std::string& fractionString);

    // assignment operators
    Fraction& operator=(int numerator);
    Fraction& operator=(double decimalValue);
    Fraction& operator=(const std::string& fractionString);
    Fraction& operator=(const char* fractionString);

    // getters and setters
    void setNumerator(int numerator);
    int getNumerator() const;

    void setDenominator(int denominator);
    int getDenominator() const;

    void setDecimalValue(double decimalValue);
    double getDecimalValue() const;

    // arithmetic operators
    Fraction operator+(const Fraction& fraction);
    Fraction operator+(const std::string& fractionString);
    friend Fraction operator+(const std::string& fractionString, const Fraction& fraction);
    Fraction operator+(const char* fractionString);
    friend Fraction operator+(const char* fractionString, const Fraction& fraction);

    Fraction operator-(const Fraction& fraction);
    Fraction operator-(const std::string& fractionString);
    friend Fraction operator-(const std::string& fractionString, const Fraction& fraction);
    Fraction operator-(const char* fractionString);
    friend Fraction operator-(const char* fractionString, const Fraction& fraction);

    Fraction operator*(const Fraction& fraction);
    Fraction operator*(const std::string& fractionString);
    friend Fraction operator*(const std::string& fractionString, const Fraction& fraction);
    Fraction operator*(const char* fractionString);
    friend Fraction operator*(const char* fractionString, const Fraction& fraction);

    Fraction operator/(const Fraction& fraction);
    Fraction operator/(const std::string& fractionString);
    friend Fraction operator/(const std::string& fractionString, const Fraction& fraction);
    Fraction operator/(const char* fractionString);
    friend Fraction operator/(const char* fractionString, const Fraction& fraction);

    Fraction operator^(int power);

    void operator+=(const Fraction& fraction);
    void operator+=(const std::string& fractionString);
    void operator+=(const char* fractionString);

    void operator-=(const Fraction& fraction);
    void operator-=(const std::string& fractionString);
    void operator-=(const char* fractionString);

    void operator*=(const Fraction& fraction);
    void operator*=(const std::string& fractionString);
    void operator*=(const char* fractionString);

    void operator/=(const Fraction& fraction);
    void operator/=(const std::string& fractionString);
    void operator/=(const char* fractionString);

    void operator^=(int power);

    Fraction& operator++();
	Fraction operator++(int);
	Fraction& operator--();
	Fraction operator--(int);

    // logical operators
    bool operator<(const Fraction& fraction) const;
    bool operator<(const std::string& fractionString) const;
    friend bool operator<(const std::string& fractionString, const Fraction& fraction);
    bool operator<(const char* fractionString) const;
    friend bool operator<(const char* fractionString, const Fraction& fraction);

    bool operator<=(const Fraction& fraction) const;
    bool operator<=(const std::string& fractionString) const;
    friend bool operator<=(const std::string& fractionString, const Fraction& fraction);
    bool operator<=(const char* fractionString) const;
    friend bool operator<=(const char* fractionString, const Fraction& fraction);

    bool operator>(const Fraction& fraction) const;
    bool operator>(const std::string& fractionString) const;
    friend bool operator>(const std::string& fractionString, const Fraction& fraction);
    bool operator>(const char* fractionString) const;
    friend bool operator>(const char* fractionString, const Fraction& fraction);

    bool operator>=(const Fraction& fraction) const;
    bool operator>=(const std::string& fractionString) const;
    friend bool operator>=(const std::string& fractionString, const Fraction& fraction);
    bool operator>=(const char* fractionString) const;
    friend bool operator>=(const char* fractionString, const Fraction& fraction);

    bool operator==(const Fraction& fraction) const;
    bool operator==(const std::string& fractionString) const;
    friend bool operator==(const std::string& fractionString, const Fraction& fraction);
    bool operator==(const char* fractionString) const;
    friend bool operator==(const char* fractionString, const Fraction& fraction);

    bool operator!=(const Fraction& fraction) const;
    bool operator!=(const std::string& fractionString) const;
    friend bool operator!=(const std::string& fractionString, const Fraction& fraction);
    bool operator!=(const char* fractionString) const;
    friend bool operator!=(const char* fractionString, const Fraction& fraction);

    operator bool() const;

    // other logical test functions
    bool isLargerThanUnit() const;
    bool isSmallerThanUnit() const;
    bool isUnit() const;

    // IO operators
    friend std::istream& operator>>(std::istream& inputStream, Fraction& fraction);
    friend std::ostream& operator<<(std::ostream& outputStream, Fraction& fraction);
    friend std::ifstream& operator>>(std::ifstream& inputFileStream, Fraction& fraction);
    friend std::ofstream& operator<<(std::ofstream& outputFileStream, Fraction& fraction);

    // other functions
    Fraction inverse() const;

    // static helper functions
    static int parseFractionString(const std::string& fractionString);
    static int parseDecimalString(const std::string& decimalString);
    static int getGreatestCommonDivisor(int first, int second);

private:
    enum class Sign : short
    {
        Minus = -1,
        Plus = 1
    };

    void normalize();

    Fraction add(const Fraction& fraction, Sign sign) const;
    Fraction multiply(const Fraction& fraction) const;
    Fraction divide(const Fraction& fraction) const;

    bool isLessThan(const Fraction& fraction) const;
    bool isGreaterThan(const Fraction& fraction) const;
    bool isEqualTo(const Fraction& fraction) const;

	int mNumerator;
	int mDenominator;
    double mDecimalValue;
};

#endif // FRACTION_H
