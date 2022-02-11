#include <sstream>
#include <cmath>
#include <cctype>
#include <cassert>
#include <algorithm>

#include "fraction.h"

static constexpr int scDigitMultiplier{10};

Fraction::Fraction()
    : mNumerator{0}
    , mDenominator{1}
    , mDecimalValue{0.0}
{
}

Fraction::Fraction(int numerator)
    : mNumerator{numerator}
    , mDenominator{1}
    , mDecimalValue{ static_cast<double>(numerator) }
{
}

Fraction::Fraction(double decimalValue)
    : mDenominator{1}
{
    std::ostringstream decimalStream;
    decimalStream << decimalValue;

    const std::string cDecimalString{decimalStream.str()};
    const size_t cCommaIndex{cDecimalString.find('.')};
    const size_t cDecimalsCount{cCommaIndex != std::string::npos ? cDecimalString.size() - 1 - cCommaIndex : 0u};

    for (size_t currentDecimal{0u}; currentDecimal < cDecimalsCount; ++currentDecimal)
	{
        mDenominator *= scDigitMultiplier;
	}

    mNumerator = static_cast<int>(decimalValue * mDenominator);

    normalize();
}

Fraction::Fraction(int numerator, int denominator)
    : Fraction{}
{
    if (0 != denominator)
    {
        mNumerator = numerator;
        mDenominator = denominator;

        normalize();
    }
    else
    {
        throw std::runtime_error{ "Fatal error! Division by 0." };
	}
}

Fraction::Fraction(const std::string& fractionString)
    : Fraction{}
{
    int separatorIndex;
    NumericStringType status{parseNumericString(fractionString, separatorIndex)};

    switch(status)
    {
    case NumericStringType::FRACTION:
    {
        mDenominator = std::stoi(fractionString.substr(separatorIndex + 1, fractionString.length() - separatorIndex - 1));
        if (0 != mDenominator)
        {
            mNumerator = std::stoi(fractionString.substr(0, separatorIndex));
            normalize();
        }
        else
        {
            throw std::runtime_error{ "Fatal error! Division by 0." };
        }
    }
        break;
    case NumericStringType::DECIMAL:
    {
        int numberOfDecimals{ static_cast<int>(fractionString.length()) - 1 - separatorIndex };

        for (int currentDecimal{ 0 }; currentDecimal < numberOfDecimals; ++currentDecimal)
        {
            mDenominator *= scDigitMultiplier;
        }

        mNumerator = static_cast<int>(std::stod(fractionString) * mDenominator);
        normalize();
    }
        break;
    case NumericStringType::INTEGER:
        mNumerator = std::stoi(fractionString);
        mDecimalValue = static_cast<double>(mNumerator);
        break;
    case NumericStringType::INVALID:
        throw std::runtime_error{"Error! Wrong fraction format"};
        break;
    default:
        assert(false);
        break;
    }
}

Fraction& Fraction::operator=(int fractionString)
{
    *this = Fraction{fractionString};
    return *this;
}

Fraction& Fraction::operator=(double decimalValue)
{
    *this = Fraction{decimalValue};
    return *this;
}

Fraction& Fraction::operator=(const std::string& fractionString)
{
    *this = Fraction{fractionString};
    return *this;
}

Fraction& Fraction::operator=(const char* fractionString)
{
    *this = Fraction{fractionString};
    return *this;
}

void Fraction::setNumerator(int numerator)
{
    mNumerator = numerator;
    normalize();
}

int Fraction::getNumerator() const
{
    return mNumerator;
}

void Fraction::setDenominator(int denominator)
{
    if (denominator != 0)
    {
        mDenominator = denominator;
        normalize();
    }
    else
    {
        throw std::runtime_error{ "Fatal error! Division by 0." };
    }
}

int Fraction::getDenominator() const
{
    return mDenominator;
}

void Fraction::setDecimalValue(double decimalValue)
{
    *this = Fraction{decimalValue};
}

double Fraction::getDecimalValue() const
{
    return mDecimalValue;
}

Fraction Fraction::operator+(const Fraction& fraction)
{
    const Fraction cResult{add(fraction, Sign::Plus)};
    return cResult;
}

Fraction Fraction::operator+(const std::string& fractionString)
{
    const Fraction cResult{add(Fraction{fractionString}, Sign::Plus)};
    return cResult;
}

Fraction operator+(const std::string& fractionString, const Fraction& fraction)
{
    const Fraction cResult{Fraction{fractionString}.add(fraction, Fraction::Sign::Plus)};
    return cResult;
}

Fraction Fraction::operator+(const char* fractionString)
{
    const Fraction cResult{add(Fraction{fractionString}, Sign::Plus)};
    return cResult;
}

Fraction operator+(const char* fractionString, const Fraction& fraction)
{
    const Fraction cResult{Fraction{fractionString}.add(fraction, Fraction::Sign::Plus)};
    return cResult;
}

Fraction Fraction::operator-(const Fraction& fraction)
{
    const Fraction cResult{add(fraction, Sign::Minus)};
    return cResult;
}

Fraction Fraction::operator-(const std::string& fractionString)
{
    const Fraction cResult{add(Fraction{fractionString}, Sign::Minus)};
    return cResult;
}

Fraction operator-(const std::string& fractionString, const Fraction& fraction)
{
    const Fraction cResult{Fraction{fractionString}.add(fraction, Fraction::Sign::Minus)};
    return cResult;
}

Fraction Fraction::operator-(const char* fractionString)
{
    const Fraction cResult{add(Fraction{fractionString}, Sign::Minus)};
    return cResult;
}

Fraction operator-(const char* fractionString, const Fraction& fraction)
{
    const Fraction cResult{Fraction{fractionString}.add(fraction, Fraction::Sign::Minus)};
    return cResult;
}

Fraction Fraction::operator*(const Fraction& fraction)
{
    const Fraction cResult{multiply(fraction)};
    return cResult;
}

Fraction Fraction::operator*(const std::string& fractionString)
{
    const Fraction cResult{multiply(Fraction{fractionString})};
    return cResult;
}

Fraction operator*(const std::string& fractionString, const Fraction& fraction)
{
    const Fraction cResult{Fraction{fractionString}.multiply(fraction)};
    return cResult;
}

Fraction Fraction::operator*(const char* fractionString)
{
    const Fraction cResult{multiply(Fraction{fractionString})};
    return cResult;
}

Fraction operator*(const char* fractionString, const Fraction& fraction)
{
    const Fraction cResult{Fraction{fractionString}.multiply(fraction)};
    return cResult;
}

Fraction Fraction::operator/(const Fraction& fraction)
{
    const Fraction cResult{divide(fraction)};
    return cResult;
}

Fraction Fraction::operator/(const std::string& fractionString)
{
    const Fraction cResult{divide(Fraction{fractionString})};
    return cResult;
}

Fraction operator/(const std::string& fractionString, const Fraction& fraction)
{
    const Fraction cResult{Fraction{fractionString}.divide(fraction)};
    return cResult;
}

Fraction Fraction::operator/(const char* fractionString)
{
    const Fraction cResult{divide(Fraction{fractionString})};
    return cResult;
}

Fraction operator/(const char* fractionString, const Fraction& fraction)
{
    const Fraction cResult{Fraction{fractionString}.divide(fraction)};
    return cResult;
}

Fraction Fraction::operator^(int power)
{
    int numeratorMultiplicator{mNumerator};
    int denominatorMultiplicator{mDenominator};

    int resultingNumerator{1};
    int resultingDenominator{1};

    if (power < 0)
    {
        power = -power;
        std::swap(numeratorMultiplicator, denominatorMultiplicator);
    }

    while (power > 0)
    {
        resultingNumerator *= numeratorMultiplicator;
        resultingDenominator *= denominatorMultiplicator;
        --power;
    }

    const Fraction result{resultingNumerator, resultingDenominator};

    return result;
}

void Fraction::operator+=(const Fraction& fraction)
{
    *this = *this + fraction;
}

void Fraction::operator+=(const std::string& fractionString)
{
    *this = *this + fractionString;
}

void Fraction::operator+=(const char* fractionString)
{
    *this = *this + fractionString;
}

void Fraction::operator-=(const Fraction& fraction)
{
    *this = *this - fraction;
}

void Fraction::operator-=(const std::string& fractionString)
{
    *this = *this - fractionString;
}

void Fraction::operator-=(const char* fractionString)
{
    *this = *this - fractionString;
}

void Fraction::operator*=(const Fraction& fraction)
{
    *this = *this * fraction;
}

void Fraction::operator*=(const std::string& fractionString)
{
    *this = *this * fractionString;
}

void Fraction::operator*=(const char* fractionString)
{
    *this = *this * fractionString;
}

void Fraction::operator/=(const Fraction& fraction)
{
    *this = *this / fraction;
}

void Fraction::operator/=(const std::string& fractionString)
{
    *this = *this / fractionString;
}

void Fraction::operator/=(const char* fractionString)
{
    *this = *this / fractionString;
}

void Fraction::operator^=(int power)
{
    *this = *this ^ power;
}

Fraction& Fraction::operator++()
{
    mNumerator += mDenominator;
    mDecimalValue = static_cast<double>(mNumerator) / mDenominator;

    return *this;
}

Fraction Fraction::operator++(int)
{
    Fraction fraction{ *this };
    fraction.mNumerator += fraction.mDenominator;
    fraction.mDecimalValue = static_cast<double>(fraction.mNumerator) / fraction.mDenominator;

    return fraction;
}

Fraction& Fraction::operator--()
{
    mNumerator -= mDenominator;
    mDecimalValue = static_cast<double>(mNumerator) / mDenominator;

    return *this;
}

Fraction Fraction::operator--(int)
{
    Fraction fract{ *this };
    fract.mNumerator -= fract.mDenominator;
    fract.mDecimalValue = static_cast<double>(fract.mNumerator) / fract.mDenominator;

    return fract;
}

bool Fraction::operator<(const Fraction& fraction) const
{
    const bool cIsLessThan{isLessThan(fraction)};
    return cIsLessThan;
}

bool Fraction::operator<(const std::string& fractionString) const
{
    const bool cIsLessThan{isLessThan(Fraction{fractionString})};
    return cIsLessThan;
}

bool operator<(const std::string& fractionString, const Fraction& fraction)
{
    const bool cIsLessThan{Fraction{fractionString}.isLessThan(fraction)};
    return cIsLessThan;
}

bool Fraction::operator<(const char* fractionString) const
{
    const bool cIsLessThan{isLessThan(Fraction{fractionString})};
    return cIsLessThan;
}

bool operator<(const char* fractionString, const Fraction& fraction)
{
    const bool cIsLessThan{Fraction{fractionString}.isLessThan(fraction)};
    return cIsLessThan;
}

bool Fraction::operator<=(const Fraction& fraction) const
{
    const bool cIsLessThanOrEqual{!isGreaterThan(fraction)};
    return cIsLessThanOrEqual;
}

bool Fraction::operator<=(const std::string& fractionString) const
{
    const bool cIsLessThanOrEqual{!isGreaterThan(Fraction{fractionString})};
    return cIsLessThanOrEqual;
}

bool operator<=(const std::string& fractionString, const Fraction& fraction)
{
    const bool cIsLessThanOrEqual{!Fraction{fractionString}.isGreaterThan(fraction)};
    return cIsLessThanOrEqual;
}

bool Fraction::operator<=(const char* fractionString) const
{
    const bool cIsLessThanOrEqual{!isGreaterThan(Fraction{fractionString})};
    return cIsLessThanOrEqual;
}

bool operator<=(const char* fractionString, const Fraction& fraction)
{
    const bool cIsLessThanOrEqual{!Fraction{fractionString}.isGreaterThan(fraction)};
    return cIsLessThanOrEqual;
}

bool Fraction::operator>(const Fraction& fraction) const
{
    const bool cIsGreaterThan{isGreaterThan(fraction)};
    return cIsGreaterThan;
}

bool Fraction::operator>(const std::string& fractionString) const
{
    const bool cIsGreaterThan{isGreaterThan(Fraction{fractionString})};
    return cIsGreaterThan;
}

bool operator>(const std::string& fractionString, const Fraction& fraction)
{
    const bool cIsGreaterThan{Fraction{fractionString}.isGreaterThan(fraction)};
    return cIsGreaterThan;
}

bool Fraction::operator>(const char* fractionString) const
{
    const bool cIsGreaterThan{isGreaterThan(Fraction{fractionString})};
    return cIsGreaterThan;
}

bool operator>(const char* fractionString, const Fraction& fraction)
{
    const bool cIsGreaterThan{Fraction{fractionString}.isGreaterThan(fraction)};
    return cIsGreaterThan;
}

bool Fraction::operator>=(const Fraction& fraction) const
{
    const bool cIsGreaterThanOrEqual{!isLessThan(fraction)};
    return cIsGreaterThanOrEqual;
}

bool Fraction::operator>=(const std::string& fractionString) const
{
    const bool cIsGreaterThanOrEqual{!isLessThan(Fraction{fractionString})};
    return cIsGreaterThanOrEqual;
}

bool operator>=(const std::string& fractionString, const Fraction& fraction)
{
    const bool cIsGreaterThanOrEqual{!Fraction{fractionString}.isLessThan(fraction)};
    return cIsGreaterThanOrEqual;
}

bool Fraction::operator>=(const char* fractionString) const
{
    const bool cIsGreaterThanOrEqual{!isLessThan(Fraction{fractionString})};
    return cIsGreaterThanOrEqual;
}

bool operator>=(const char* fractionString, const Fraction& fraction)
{
    const bool cIsGreaterThanOrEqual{!Fraction{fractionString}.isLessThan(fraction)};
    return cIsGreaterThanOrEqual;
}

bool Fraction::operator==(const Fraction& fraction) const
{
    const bool cIsEqualTo(isEqualTo(fraction));
    return cIsEqualTo;
}

bool Fraction::operator==(const std::string& fractionString) const
{
    const bool cIsEqualTo(isEqualTo(Fraction{fractionString}));
    return cIsEqualTo;
}

bool operator==(const std::string& fractionString, const Fraction& fraction)
{
    const bool cIsEqualTo(Fraction{fractionString}.isEqualTo(fraction));
    return cIsEqualTo;
}

bool Fraction::operator==(const char* fractionString) const
{
    const bool cIsEqualTo(isEqualTo(Fraction{fractionString}));
    return cIsEqualTo;
}

bool operator==(const char* fractionString, const Fraction& fraction)
{
    const bool cIsEqualTo(Fraction{fractionString}.isEqualTo(fraction));
    return cIsEqualTo;
}

bool Fraction::operator!=(const Fraction& fraction) const
{
    const bool cIsDifferentFrom{!isEqualTo(fraction)};
    return cIsDifferentFrom;
}

bool Fraction::operator!=(const std::string& fractionString) const
{
    const bool cIsDifferentFrom{!isEqualTo(Fraction{fractionString})};
    return cIsDifferentFrom;
}

bool operator!=(const std::string& fractionString, const Fraction& fraction)
{
    const bool cIsDifferentFrom{!Fraction{fractionString}.isEqualTo(fraction)};
    return cIsDifferentFrom;
}

bool Fraction::operator!=(const char* fractionString) const
{
    const bool cIsDifferentFrom{!isEqualTo(Fraction{fractionString})};
    return cIsDifferentFrom;
}

bool operator!=(const char* fractionString, const Fraction& fraction)
{
    const bool cIsDifferentFrom{!Fraction{fractionString}.isEqualTo(fraction)};
    return cIsDifferentFrom;
}

Fraction::operator bool() const
{
    const bool cResult{mNumerator != 0};
    return cResult;
}

bool Fraction::isLargerThanUnit() const
{
    const bool cIsLargerThanUnit{mNumerator > mDenominator};
    return cIsLargerThanUnit;
}

bool Fraction::isSmallerThanUnit() const
{
    const bool cIsSmallerThanUnit{mNumerator < mDenominator};
    return cIsSmallerThanUnit;
}

bool Fraction::isUnit() const
{
    const bool cIsUnit{mNumerator == mDenominator};
    return cIsUnit;
}

std::istream& operator>>(std::istream& inputStream, Fraction& fraction)
{
    std::string streamBuffer;
    std::getline(inputStream, streamBuffer);
    fraction = streamBuffer;

    return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, Fraction& fraction)
{
    outputStream << fraction.mNumerator << "/" << fraction.mDenominator;
    return outputStream;
}

std::ifstream& operator>>(std::ifstream& inputFileStream, Fraction& fraction)
{
    std::string streamBuffer;
    std::getline(inputFileStream, streamBuffer);
    fraction = streamBuffer;

    return inputFileStream;
}

std::ofstream& operator<<(std::ofstream& outputFileStream, Fraction& fraction)
{
    outputFileStream << fraction.mNumerator << "/" << fraction.mDenominator;
    return outputFileStream;
}

Fraction Fraction::inverse() const
{
    Fraction result{1};

    if (mNumerator != 0)
    {
        result = Fraction{mDenominator, mNumerator};
    }
    else
    {
        throw std::runtime_error{ "Error! Division by 0" };
    }

    return result;
}

/* Parses a numeric string that can be in one of the three accepted formats: (integer) fraction, decimal, integer
   (decimal fraction or scientific formats are excluded)
*/
Fraction::NumericStringType Fraction::parseNumericString(const std::string& numericString, int& separatorIndex)
{
    NumericStringType numericStringType{NumericStringType::INVALID};
    NumericStringParsingState currentState{NumericStringParsingState::NO_CHARS};
    char separator{'\0'};

    separatorIndex = -1; // assume integer or invalid

    for(std::string::const_iterator it{numericString.cbegin()};  it != numericString.cend(); ++it)
    {
        switch(currentState)
        {
        case NumericStringParsingState::NO_CHARS:
            currentState = ('-' == *it || '+' == *it) ? NumericStringParsingState::FIRST_SIGN
                                                      : (0 != isdigit(*it)) ? NumericStringParsingState::DIGITS_BEFORE_SEPARATOR
                                                                            : NumericStringParsingState::INVALID;
            break;
        case NumericStringParsingState::FIRST_SIGN:
            currentState = isdigit(*it) ? NumericStringParsingState::DIGITS_BEFORE_SEPARATOR : NumericStringParsingState::INVALID;
            break;
        case NumericStringParsingState::DIGITS_BEFORE_SEPARATOR:
            if ('/' == *it)
            {
                currentState = NumericStringParsingState::FRACTION_SEPARATOR;
                separatorIndex = std::distance(numericString.cbegin(), it);
                separator = *it;
            }
            else if ('.' == *it)
            {
                currentState = NumericStringParsingState::DECIMAL_SEPARATOR;
                separatorIndex = std::distance(numericString.cbegin(), it);
                separator = *it;
            }
            else if (0 == isdigit(*it))
            {
                currentState = NumericStringParsingState::INVALID;
            }
            break;
        case NumericStringParsingState::FRACTION_SEPARATOR:
            currentState = ('-' == *it || '+' == *it) ? NumericStringParsingState::SECOND_SIGN
                                                      : isdigit(*it) ? NumericStringParsingState::DIGITS_AFTER_SEPARATOR
                                                                            : NumericStringParsingState::INVALID;
            break;
        case NumericStringParsingState::DECIMAL_SEPARATOR:
            currentState = isdigit(*it) ? NumericStringParsingState::DIGITS_AFTER_SEPARATOR : NumericStringParsingState::INVALID;
            break;
        case NumericStringParsingState::SECOND_SIGN:
            currentState = isdigit(*it) ? NumericStringParsingState::DIGITS_AFTER_SEPARATOR : NumericStringParsingState::INVALID;
            break;
        case NumericStringParsingState::DIGITS_AFTER_SEPARATOR:
            if (!isdigit(*it))
            {
                currentState = NumericStringParsingState::INVALID;
            }
            break;
        default:
            break;
        }

        if (NumericStringParsingState::INVALID == currentState)
        {
            break;
        }
    }

    if (NumericStringParsingState::DIGITS_AFTER_SEPARATOR == currentState)
    {
        if ('/' == separator)
        {
            numericStringType = NumericStringType::FRACTION;
        }
        else if ('.' == separator)
        {
            numericStringType = NumericStringType::DECIMAL;
        }
        else
        {
            assert(false);
        }
    }
    else if (NumericStringParsingState::DIGITS_BEFORE_SEPARATOR == currentState)
    {
        numericStringType = NumericStringType::INTEGER;
    }

    return numericStringType;
}

int Fraction::getGreatestCommonDivisor(int first, int second)
{
    int greatestCommonDivisor{1};

    if (0 != first && 0 != second)
    {
        first = std::abs(first);
        second = std::abs(second);

        int remainder{first % second};

        while (remainder)
        {
            first = second;
            second = remainder;
            remainder = first % second;
        }

        greatestCommonDivisor = second;
    }
    else if (0 != first)
    {
        greatestCommonDivisor = std::abs(first);
    }
    else if (0 != second)
    {
        greatestCommonDivisor = std::abs(second);
    }
    else
    {
        throw std::runtime_error{"Error! Cannot retrieve greatest common divisor of two 0 numbers"};
    }

    return greatestCommonDivisor;
}

void Fraction::normalize()
{
    const int cGreatestCommonDivisor{getGreatestCommonDivisor(std::abs(mNumerator), std::abs(mDenominator))};

    if (1 != cGreatestCommonDivisor)
    {
        mNumerator /= cGreatestCommonDivisor;
        mDenominator /= cGreatestCommonDivisor;
    }

    if (mDenominator < 0)
    {
        mNumerator = -mNumerator;
        mDenominator = -mDenominator;
    }

    mDecimalValue = static_cast<double>(mNumerator) / mDenominator;
}

Fraction Fraction::add(const Fraction& fraction, Fraction::Sign sign) const
{
    const int cGreatestCommonDivisor{ getGreatestCommonDivisor(std::abs(mDenominator), std::abs(fraction.mDenominator)) };
    const int cFirstMultiplicationFactor{ fraction.mDenominator / cGreatestCommonDivisor };
    const int cSecondMultiplicationFactor{ static_cast<int>(sign) * mDenominator / cGreatestCommonDivisor };
    const int cResultingNumerator{mNumerator * cFirstMultiplicationFactor + fraction.mNumerator * cSecondMultiplicationFactor};
    const int cResultingDenominator{cFirstMultiplicationFactor * mDenominator};

    const Fraction cResult{cResultingNumerator, cResultingDenominator};

    return cResult;
}

Fraction Fraction::multiply(const Fraction& fraction) const
{
    const int cResultingNumerator{mNumerator * fraction.mNumerator};
    const int cResultingDenominator{mDenominator * fraction.mDenominator};

    const Fraction cResult{cResultingNumerator, cResultingDenominator};

    return cResult;
}


Fraction Fraction::divide(const Fraction& fraction) const
{
    const int cResultingNumerator{mNumerator * fraction.mDenominator};
    const int cResultingDenominator{mDenominator * fraction.mNumerator};

    const Fraction cResult{cResultingNumerator, cResultingDenominator};

    return cResult;
}

bool Fraction::isLessThan(const Fraction& fraction) const
{
    const int cLeftNormalizedNumerator{mNumerator * fraction.mDenominator};
    const int cRightNormalizedNumerator{fraction.mNumerator * mDenominator};
    const bool cIsLessThan{cLeftNormalizedNumerator < cRightNormalizedNumerator};

    return cIsLessThan;
}

bool Fraction::isGreaterThan(const Fraction& fraction) const
{
    const int cLeftNormalizedNumerator{mNumerator * fraction.mDenominator};
    const int cRightNormalizedNumerator{fraction.mNumerator * mDenominator};
    const bool cIsGreaterThan{cLeftNormalizedNumerator > cRightNormalizedNumerator};

    return cIsGreaterThan;
}

bool Fraction::isEqualTo(const Fraction& fraction) const
{
    const int cLeftNormalizedNumerator{mNumerator * fraction.mDenominator};
    const int cRightNormalizedNumerator{fraction.mNumerator * mDenominator};
    const bool cIsEqualTo{cLeftNormalizedNumerator == cRightNormalizedNumerator};

    return cIsEqualTo;
}
