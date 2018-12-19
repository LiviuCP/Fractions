#pragma once
#include <string>
#include <fstream>
#include <stdexcept>

enum class FractionString
{
	ERROR_INDEX = -2,
	NULL_INDEX = 0
};

enum class DecimalString
{
	ERROR_INDEX = -2,
	NO_DECIMAL_INDEX = -1,
	NULL_INDEX = 0
};

class WrongFormatException
{
public:
	WrongFormatException();
	std::string what();
private:
	std::exception wrongFormatException;
};

class Fraction
{
public:
	// constructors
	Fraction(void);
	explicit Fraction(int);
	explicit Fraction(double);
	Fraction(int, int);
	explicit Fraction(const std::string&);
	// getters
	int getNumerator() const;
	int getDenominator() const;
	double getDecimal() const;
	// setters
	void setNumerator(int);
	void setDenominator(int);
	void setDecimal(double);
	// arithmetic operators
	Fraction operator+(const Fraction&);
	Fraction operator+(const std::string&);
	Fraction operator+(const char*);
	friend Fraction operator+(const std::string&, const Fraction&);
	friend Fraction operator+(const char*, const Fraction&);
	Fraction operator-(const Fraction&);
	Fraction operator-(const std::string&);
	Fraction operator-(const char*);
	friend Fraction operator-(const std::string&, const Fraction&);
	friend Fraction operator-(const char*, const Fraction&);
	Fraction operator*(const Fraction&);
	Fraction operator*(const std::string&);
	Fraction operator*(const char*);
	friend Fraction operator*(const std::string&, const Fraction&);
	friend Fraction operator*(const char*, const Fraction&);
	Fraction operator/(const Fraction&);
	Fraction operator/(const std::string&);
	Fraction operator/(const char*);
	friend Fraction operator/(const std::string&, const Fraction&);
	friend Fraction operator/(const char*, const Fraction&);
	Fraction operator^(int);
	void operator+=(const Fraction&);
	void operator+=(const std::string&);
	void operator+=(const char*);
	void operator-=(const Fraction&);
	void operator-=(const std::string&);
	void operator-=(const char*);
	void operator*=(const Fraction&);
	void operator*=(const std::string&);
	void operator*=(const char*);
	void operator/=(const Fraction&);
	void operator/=(const std::string&);
	void operator/=(const char*);
	void operator^=(int);
	Fraction& operator++();
	Fraction operator++(int);
	Fraction& operator--();
	Fraction operator--(int);
	// logical operators
	bool operator>(const Fraction&) const;
	bool operator>(const std::string&) const;
	friend bool operator>(const std::string&, const Fraction&);
	bool operator>(const char*) const;
	friend bool operator>(const char*, const Fraction&);
	bool operator>=(const Fraction&) const;
	bool operator>=(const std::string&) const;
	friend bool operator>=(const std::string&, const Fraction&);
	bool operator>=(const char*) const;
	friend bool operator>=(const char*, const Fraction&);
	bool operator<(const Fraction&) const;
	bool operator<(const std::string&) const;
	friend bool operator<(const std::string&, const Fraction&);
	bool operator<(const char*) const;
	friend bool operator<(const char*, const Fraction&);
	bool operator<=(const Fraction&) const;
	bool operator<=(const std::string&) const;
	friend bool operator<=(const std::string&, const Fraction&);
	bool operator<=(const char*) const;
	friend bool operator<=(const char*, const Fraction&);
	bool operator!=(const Fraction&) const;
	bool operator!=(const std::string&) const;
	friend bool operator!=(const std::string&, const Fraction&);
	bool operator!=(const char*) const;
	friend bool operator!=(const char*, const Fraction&);
	bool operator==(const Fraction&) const;
	bool operator==(const std::string&) const;
	friend bool operator==(const std::string&, const Fraction&);
	bool operator==(const char*) const;
	friend bool operator==(const char*, const Fraction&);
	operator bool() const;
	// other logical test functions
	bool isLargerThanUnit();
	bool isSmallerThanUnit();
	bool isUnit();
	// assignment operators
	Fraction& operator=(int);
	Fraction& operator=(double);
	Fraction& operator=(const char*);
	Fraction& operator=(const std::string&);
	// IO operators
	friend std::ostream& operator<<(std::ostream&, Fraction&);
	friend std::istream& operator >> (std::istream&, Fraction&);
	friend std::ofstream& operator<<(std::ofstream&, Fraction&);
	friend std::ifstream& operator >> (std::ifstream&, Fraction&);
	// other functions
	Fraction inverse();
	// destructor
	~Fraction(void);
	// static helper functions
	static int greatestCommonDivisor(int, int);
	static int checkFractionString(const std::string&);
	static int checkDecimalString(const std::string&);
private:
	int numerator;
	int denominator;
	double decimal;
private:
	void normalize();
};
