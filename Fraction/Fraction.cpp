#include "Fraction.h"
#include <sstream>
#include <cmath>
#include <cctype>
#include <algorithm>

WrongFormatException::WrongFormatException() : wrongFormatException{ "Error! Wrong fraction format" }
{
}

std::string WrongFormatException::what()
{
	return wrongFormatException.what();
}

Fraction::Fraction(void) : numerator{0}, denominator{1}, decimal{0.0}
{
}

Fraction::Fraction(int integerNumber) : numerator{integerNumber}, denominator{1}, decimal{ static_cast<double>(integerNumber) }
{
}

Fraction::Fraction(double decimalNumber)
{
	std::ostringstream writeDecimal;
	writeDecimal << decimalNumber;
	std::string decimalString = writeDecimal.str();
	int commaPosition = decimalString.find('.');
	int numberOfDecimals = decimalString.length() - 1 - commaPosition;
	denominator = 1;
	for (int currentDecimal = 0; currentDecimal<numberOfDecimals; ++currentDecimal)
	{
		denominator = denominator * 10;
	}
	numerator = static_cast<int>(decimalNumber*denominator);
	normalize();
}

Fraction::Fraction(int numerator, int denominator)
{
	if (0 == denominator)
	{
		throw std::exception{ "Fatal error! Division by 0." };
	}
	this->numerator = numerator;
	this->denominator = denominator;
	normalize();
}

Fraction::Fraction(const std::string &inputString)
{
	int slashIndex{ Fraction::checkFractionString(inputString) };
	if (static_cast<int>(FractionString::ERROR_INDEX) == slashIndex)
	{
		int decimalIndex{ Fraction::checkDecimalString(inputString) };
		if (static_cast<int>(DecimalString::ERROR_INDEX) == decimalIndex)
		{
			throw WrongFormatException{};
		}
		else if (static_cast<int>(DecimalString::NO_DECIMAL_INDEX) == decimalIndex)
		{
			numerator = std::stoi(inputString);
			denominator = 1;
			decimal = static_cast<double>(numerator);
		}
		else
		{
			double decimalNumber{ std::stod(inputString) };
			int numberOfDecimals{ static_cast<int>(inputString.length()) - 1 - decimalIndex };
			denominator = 1;
			for (int currentDecimal{ 0 }; currentDecimal < numberOfDecimals; ++currentDecimal)
			{
				denominator *= 10;
			}
			numerator = static_cast<int>(decimalNumber*denominator);
			normalize();
		}
	}
	else
	{
		std::string num{ inputString.substr(0, slashIndex) };
		std::string den{ inputString.substr(slashIndex + 1, inputString.length() - slashIndex - 1) };
		numerator = std::stoi(num);
		denominator = std::stoi(den);
		if (0 == denominator)
		{
			throw std::exception{ "Fatal error! Division by 0." };
		}
		normalize();
	}
}

int Fraction::getNumerator() const
{
	return numerator;
}

int Fraction::getDenominator() const
{
	return denominator;
}

double Fraction::getDecimal() const
{
	return decimal;
}

void Fraction::setNumerator(int num)
{
	numerator = num;
	normalize();
}

void Fraction::setDenominator(int den)
{
	if (den == 0)
	{
		throw std::exception{ "Fatal error! Division by 0." };
	}
	denominator = den;
	normalize();
}

void Fraction::setDecimal(double dec)
{
	*this = Fraction{ dec };
}

Fraction& Fraction::operator=(const char* inputString)
{
	return (*this = std::string{ inputString });
}

Fraction& Fraction::operator=(const std::string &inputString)
{
	return (*this = Fraction{ inputString });
}

bool Fraction::operator<(const Fraction &secondFraction) const
{
	return (numerator*secondFraction.denominator < secondFraction.numerator*denominator);
}

bool Fraction::operator<(const std::string& inputString) const
{
	return (*this < Fraction{ inputString });
}

bool Fraction::operator<(const char* inputString) const
{
	return(*this < std::string{ inputString });
}

bool operator<(const char* inputString, const Fraction &secondFraction)
{
	return (Fraction(std::string{ inputString }) < secondFraction);
}

bool operator<(const std::string &inputString, const Fraction &secondFraction)
{
	return (Fraction{ inputString } < secondFraction);
}

bool Fraction::operator<=(const Fraction &secondFraction) const
{
	return (numerator*secondFraction.denominator <= secondFraction.numerator*denominator);
}

bool Fraction::operator<=(const std::string& inputString) const
{
	return (*this <= Fraction{ inputString });
}

bool Fraction::operator<=(const char* inputString) const
{
	return(*this <= std::string{ inputString });
}

bool operator<=(const char* inputString, const Fraction &secondFraction)
{
	return (Fraction(std::string{ inputString }) <= secondFraction);
}

bool operator<=(const std::string &inputString, const Fraction &secondFraction)
{
	return (Fraction{ inputString } <= secondFraction);
}

bool Fraction::operator>(const Fraction &secondFraction) const
{
	return (numerator*secondFraction.denominator > secondFraction.numerator*denominator);
}

bool Fraction::operator>(const std::string& inputString) const
{
	return (*this > Fraction{ inputString });
}

bool Fraction::operator>(const char* inputString) const
{
	return(*this > std::string{ inputString });
}

bool operator>(const char* inputString, const Fraction &secondFraction)
{
	return (Fraction(std::string{ inputString }) > secondFraction);
}

bool operator>(const std::string &inputString, const Fraction &secondFraction)
{
	return (Fraction{ inputString } > secondFraction);
}

bool Fraction::operator>=(const Fraction &secondFraction) const
{
	return (numerator*secondFraction.denominator >= secondFraction.numerator*denominator);
}

bool Fraction::operator>=(const std::string& inputString) const
{
	return (*this >= Fraction{ inputString });
}

bool Fraction::operator>=(const char* inputString) const
{
	return(*this >= std::string{ inputString });
}

bool operator>=(const char* inputString, const Fraction &secondFraction)
{
	return (Fraction(std::string{ inputString }) >= secondFraction);
}

bool operator>=(const std::string &inputString, const Fraction &secondFraction)
{
	return (Fraction{ inputString } >= secondFraction);
}

bool Fraction::operator!=(const Fraction &secondFraction) const
{
	return ((numerator != secondFraction.numerator) || (denominator != secondFraction.denominator));
}

bool Fraction::operator!=(const std::string& inputString) const
{
	return (*this != Fraction{ inputString });
}

bool Fraction::operator!=(const char* inputString) const
{
	return(*this != std::string{ inputString });
}

bool operator!=(const char* inputString, const Fraction &secondFraction)
{
	return (Fraction(std::string{ inputString }) != secondFraction);
}

bool operator!=(const std::string &inputString, const Fraction &secondFraction)
{
	return (Fraction{ inputString } != secondFraction);
}

bool Fraction::operator==(const Fraction &secondFraction) const
{
	return ((numerator == secondFraction.numerator) && (denominator == secondFraction.denominator));
}

bool Fraction::operator==(const std::string& inputString) const
{
	return (*this == Fraction{ inputString });
}

bool Fraction::operator==(const char* inputString) const
{
	return(*this == std::string{ inputString });
}

bool operator==(const char* inputString, const Fraction &secondFraction)
{
	return (Fraction(std::string{ inputString }) == secondFraction);
}

bool operator==(const std::string &inputString, const Fraction &secondFraction)
{
	return (Fraction{ inputString } == secondFraction);
}

Fraction::operator bool() const
{
	return (numerator != 0);
}

bool Fraction::isLargerThanUnit()
{
	return (numerator > denominator);
}

bool Fraction::isSmallerThanUnit()
{
	return (numerator < denominator);
}

bool Fraction::isUnit()
{
	return (numerator == denominator);
}

Fraction Fraction::operator+(const Fraction& secondFraction)
{
	int gcd = greatestCommonDivisor(abs(denominator), abs(secondFraction.denominator));
	int multiplyFactor = secondFraction.denominator / gcd;
	int secondMultiplyFactor = denominator / gcd;
	int resultNumerator = numerator*multiplyFactor + secondFraction.numerator*secondMultiplyFactor;
	int resultDenominator = multiplyFactor*denominator;
	return Fraction{ resultNumerator, resultDenominator };
}

Fraction Fraction::operator-(const Fraction& secondFraction)
{
	int gcd = greatestCommonDivisor(abs(denominator), abs(secondFraction.denominator));
	int multiplyFactor = secondFraction.denominator / gcd;
	int secondMultiplyFactor = denominator / gcd;
	int resultNumerator = numerator*multiplyFactor - secondFraction.numerator*secondMultiplyFactor;
	int resultDenominator = multiplyFactor*denominator;
	return Fraction{ resultNumerator, resultDenominator };
}

Fraction Fraction::operator*(const Fraction& secondFraction)
{
	return Fraction{ numerator*secondFraction.numerator, denominator*secondFraction.denominator };
}

Fraction Fraction::operator/(const Fraction& secondFraction)
{
	return Fraction{ numerator*secondFraction.denominator, denominator*secondFraction.numerator };
}

Fraction Fraction::operator+(const std::string& inputString)
{
	return(*this + Fraction{ inputString });
}

Fraction Fraction::operator-(const std::string& inputString)
{
	return(*this - Fraction{ inputString });
}

Fraction Fraction::operator*(const std::string& inputString)
{
	return(*this*Fraction{ inputString });
}

Fraction Fraction::operator/(const std::string& inputString)
{
	return(*this / Fraction{ inputString });
}

Fraction Fraction::operator+(const char* inputString)
{
	return(*this + std::string{ inputString });
}

Fraction Fraction::operator-(const char* inputString)
{
	return(*this - std::string{ inputString });
}

Fraction Fraction::operator*(const char* inputString)
{
	return(*this * std::string{ inputString });
}

Fraction Fraction::operator/(const char* inputString)
{
	return(*this / std::string{ inputString });
}

Fraction operator+(const std::string &inputString, const Fraction &secondFraction)
{
	return (Fraction{ inputString } + secondFraction);
}

Fraction operator-(const std::string &inputString, const Fraction &secondFraction)
{
	return (Fraction{ inputString } - secondFraction);
}

Fraction operator*(const std::string &inputString, const Fraction &secondFraction)
{
	return (Fraction{ inputString } * secondFraction);
}

Fraction operator/(const std::string &inputString, const Fraction &secondFraction)
{
	return (Fraction{ inputString } / secondFraction);
}

Fraction operator+(const char* inputString, const Fraction &secondFraction)
{
	return (std::string{ inputString } + secondFraction);
}

Fraction operator-(const char* inputString, const Fraction &secondFraction)
{
	return (std::string{ inputString } - secondFraction);
}

Fraction operator*(const char* inputString, const Fraction &secondFraction)
{
	return (std::string{ inputString } * secondFraction);
}

Fraction operator/(const char* inputString, const Fraction &secondFraction)
{
	return (std::string{ inputString } / secondFraction);
}

Fraction Fraction::operator^(int n)
{
	Fraction multiplier{ *this };
	Fraction result(1);
	if (n<0)
	{
		multiplier = inverse();
		n = -n;
	}
	while (0 < n--)
	{
		result = result*multiplier;
	}
	return result;
}

void Fraction::operator+=(const Fraction& secondFraction)
{
	*this = *this + secondFraction;
}

void Fraction::operator+=(const std::string& inputString)
{
	*this = *this + inputString;
}

void Fraction::operator+=(const char* inputString)
{
	*this = *this + inputString;
}

void Fraction::operator-=(const Fraction& secondFraction)
{
	*this = *this - secondFraction;
}

void Fraction::operator-=(const std::string& inputString)
{
	*this = *this - inputString;
}

void Fraction::operator-=(const char* inputString)
{
	*this = *this - inputString;
}

void Fraction::operator*=(const Fraction& secondFraction)
{
	*this = *this * secondFraction;
}

void Fraction::operator*=(const std::string& inputString)
{
	*this = *this * inputString;
}

void Fraction::operator*=(const char* inputString)
{
	*this = *this * inputString;
}

void Fraction::operator/=(const Fraction& secondFraction)
{
	*this = *this / secondFraction;
}

void Fraction::operator/=(const std::string& inputString)
{
	*this = *this / inputString;
}

void Fraction::operator/=(const char* inputString)
{
	*this = *this / inputString;
}

void Fraction::operator^=(int n)
{
	*this = *this ^ n;
}

Fraction Fraction::operator++(int)
{
	Fraction fract{ *this };
	fract.numerator += fract.denominator;
	fract.decimal = static_cast<double>(fract.numerator) / fract.denominator;
	return fract;
}

Fraction& Fraction::operator++()
{
	numerator += denominator;
	decimal = static_cast<double>(numerator) / denominator;
	return *this;
}

Fraction Fraction::operator--(int)
{
	Fraction fract{ *this };
	fract.numerator -= fract.denominator;
	fract.decimal = static_cast<double>(fract.numerator) / fract.denominator;
	return fract;
}

Fraction& Fraction::operator--()
{
	numerator -= denominator;
	decimal = static_cast<double>(numerator) / denominator;
	return *this;
}

Fraction Fraction::inverse()
{
	if (!numerator)
	{
		throw std::exception{ "Error! Division by 0" };
	}
	return Fraction{ denominator, numerator };
}

std::istream& operator >> (std::istream& inputStream, Fraction& fraction)
{
	std::string streamBuffer;
	std::getline(inputStream, streamBuffer);
	fraction = streamBuffer;
	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, Fraction& fraction)
{
	outputStream << fraction.numerator << "/" << fraction.denominator;
	return outputStream;
}

std::ifstream& operator >> (std::ifstream& inputFileStream, Fraction& fraction)
{
	std::string streamBuffer;
	std::getline(inputFileStream, streamBuffer);
	fraction = streamBuffer;
	return inputFileStream;
}

std::ofstream& operator<<(std::ofstream& outputFileStream, Fraction &fraction)
{
	outputFileStream << fraction.numerator << "/" << fraction.denominator;
	return outputFileStream;
}

Fraction::~Fraction(void)
{
	// not used
}

void Fraction::normalize()
{
	int gcd{ greatestCommonDivisor(abs(numerator), abs(denominator)) };
	if (gcd != 1)
	{
		numerator /= gcd;
		denominator /= gcd;
	}
	if (denominator<0)
	{
		numerator = -numerator;
		denominator = -denominator;
	}
	decimal = static_cast<double>(numerator) / denominator;
}

int Fraction::checkFractionString(const std::string &fractionString)
{
	int slashIndex{ static_cast<int>(fractionString.find_first_of('/')) };
	// calculate specific parameters of the fraction string (e.g. number of minus characters)
	int minusCount{ std::count(fractionString.begin(), fractionString.end(), '-') };
	int slashCount{ std::count(fractionString.begin(), fractionString.end(), '/') };
	int nonDigitCount{ 0 };
	for (std::string::const_iterator it{ fractionString.cbegin() }; it != fractionString.cend(); ++it)
	{
		if (!isdigit(*it))
		{
			++nonDigitCount;
		}
	}
	// check that the format of the string is correct
	// - enforce the right number and types of non-numeric characters
	if (slashCount != 1)
	{
		slashIndex = static_cast<int>(FractionString::ERROR_INDEX);
	}
	else if (minusCount > 2)
	{
		slashIndex = static_cast<int>(FractionString::ERROR_INDEX);
	}
	else if (nonDigitCount > slashCount + minusCount)
	{
		slashIndex = static_cast<int>(FractionString::ERROR_INDEX);
	}
	// - last character should always be numeric
	else if (!isdigit(fractionString[fractionString.length() - 1]))
	{
		slashIndex = static_cast<int>(FractionString::ERROR_INDEX);
	}
	// - ensure the slash character is correctly placed
	else if ( (0 == slashIndex) || ( '-' == fractionString[0] && 1 == slashIndex) )
	{
		slashIndex = static_cast<int>(FractionString::ERROR_INDEX);
	}
	// - ensure the minus character(s) is/are correctly placed (if any)
	else if ( (1 == minusCount) && ( '-' !=  fractionString[0] && '-' != fractionString[slashIndex + 1] ) )
	{
		slashIndex = static_cast<int>(FractionString::ERROR_INDEX);
	}
	else if ( (2 == minusCount) && ( '-' != fractionString[0] || '-' != fractionString[slashIndex + 1] ) )
	{
		slashIndex = static_cast<int>(FractionString::ERROR_INDEX);
	}
	// return index of the slash character if format is ok (or an error number if not)
	return slashIndex;
}

int Fraction::checkDecimalString(const std::string &decimalString)
{
	// assume the string is an integer
	int decimalIndex{ static_cast<int>(DecimalString::NO_DECIMAL_INDEX) };
	// calculate specific parameters of the fraction string (e.g. number of minus characters)
	int dotCount{ std::count(decimalString.begin(), decimalString.end(), '.') };
	int minusCount{ std::count(decimalString.begin(), decimalString.end(), '-') };
	int nonDigitCount{ 0 };
	for (std::string::const_iterator it{ decimalString.cbegin() }; it != decimalString.cend(); ++it)
	{
		if (!isdigit(*it))
		{
			++nonDigitCount;
		}
	}
	// check that the format of the string is correct
	// - enforce the correct number of types of non-numeric characters
	if (dotCount > 1 || minusCount > 1)
	{
		decimalIndex = static_cast<int>(DecimalString::ERROR_INDEX);
	}
	else if (nonDigitCount > dotCount + minusCount)
	{
		decimalIndex = static_cast<int>(DecimalString::ERROR_INDEX);
	}
	// - ensure the last character is always numeric
	else if (!isdigit(decimalString[decimalString.length() - 1]))
	{
		decimalIndex = static_cast<int>(DecimalString::ERROR_INDEX);
	}
	// - ensure the first character is always numeric or minus (-)
	else if ('.' == decimalString[0])
	{
		decimalIndex = static_cast<int>(DecimalString::ERROR_INDEX);
	}
	// - ensure minus is always the first character and is always followed by a digit
	else if ( 1 == minusCount && ( '-' != decimalString[0] || '.' == decimalString[1] ) )
	{
		decimalIndex = static_cast<int>(DecimalString::ERROR_INDEX);
	}
	// if format is ok and there is a dot: set index to actual dot position
	if (static_cast<int>(DecimalString::ERROR_INDEX) != decimalIndex && 1 == dotCount)
	{
		decimalIndex = decimalString.find_first_of('.');
	}
	// return the obtained index (decimal/integer/error)
	return decimalIndex;
}

int Fraction::greatestCommonDivisor(int firstNumber, int secondNumber)
{
	// assume numbers are prime between each other (so variable is initialized)
	int gcd{ 1 };
	// gcd is undefined if both numbers are 0
	if (!firstNumber && !secondNumber)
	{
		throw std::exception{ "Error! Cannot retrieve greatest common divisor of two 0 numbers" };
	}
	// if one of the numbers is 0, the other is the gcd
	else if (!firstNumber)
	{
		gcd = abs(secondNumber);
	}
	else if (!secondNumber)
	{
		gcd = abs(firstNumber);
	}
	// if both are different from 0, then gcd needs to be calculated using the remainder method
	else
	{
		firstNumber = abs(firstNumber);
		secondNumber = abs(secondNumber);
		int remainder{ firstNumber % secondNumber };
		while (remainder)
		{
			firstNumber = secondNumber;
			secondNumber = remainder;
			remainder = firstNumber % secondNumber;
		}
		gcd = secondNumber;
	}
	return gcd;
}
