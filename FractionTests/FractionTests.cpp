#include "gtest/gtest.h"
#include "../Fraction/Fraction.h"
#include <exception>
#include <sstream>

/* Test exceptions */

TEST(throwingExceptions, wrongStringFormatInFractionConstructor)
{
	EXPECT_THROW(Fraction{ ".15" }, WrongFormatException);
	EXPECT_THROW(Fraction{ "-15." }, WrongFormatException);
	EXPECT_THROW(Fraction{ "1/5-" }, WrongFormatException);
	EXPECT_THROW(Fraction{ "15/" }, WrongFormatException);
}

TEST(throwingExceptions, divisionByZero)
{
	Fraction fract{ 1, 2 };
	Fraction zeroFract{};
	EXPECT_THROW(Fraction(1, 0), std::exception);
	EXPECT_THROW(Fraction{ "1/0" }, std::exception);
	EXPECT_THROW(fract.setDenominator(0), std::exception);
	EXPECT_THROW(zeroFract.inverse(), std::exception);
}

TEST(throwingExceptions, twoZeroNumbersCommonDivisor)
{
	EXPECT_THROW(Fraction::greatestCommonDivisor(0, 0), std::exception);
}

TEST(throwingNoExceptions, constructors)
{
	EXPECT_NO_THROW(Fraction{}, std::exception);
	EXPECT_NO_THROW(Fraction(1, 2), std::exception);
	EXPECT_NO_THROW(Fraction(-1, 2), std::exception);
	EXPECT_NO_THROW(Fraction(1, -2), std::exception);
	EXPECT_NO_THROW(Fraction(-1, -2), std::exception);
	EXPECT_NO_THROW(Fraction{ 3 }, std::exception);
	EXPECT_NO_THROW(Fraction{ -3 }, std::exception);
	EXPECT_NO_THROW(Fraction{ 1.5 }, std::exception);
	EXPECT_NO_THROW(Fraction{ -1.5 }, std::exception);
	EXPECT_NO_THROW(Fraction{ "1/4" }, WrongFormatException);
	EXPECT_NO_THROW(Fraction{ "1.5" }, WrongFormatException);
	EXPECT_NO_THROW(Fraction{ "3" }, WrongFormatException);
	EXPECT_NO_THROW(Fraction{ "-1/4" }, WrongFormatException);
	EXPECT_NO_THROW(Fraction{ "-1.5" }, WrongFormatException);
	EXPECT_NO_THROW(Fraction{ "-3" }, WrongFormatException);
}

TEST(throwingNoExceptions, highestCommonDivisor)
{
	EXPECT_NO_THROW(Fraction::greatestCommonDivisor(1, 0), std::exception);
	EXPECT_NO_THROW(Fraction::greatestCommonDivisor(0, 1), std::exception);
	EXPECT_NO_THROW(Fraction::greatestCommonDivisor(1, 1), std::exception);
	EXPECT_NO_THROW(Fraction::greatestCommonDivisor(6, 8), std::exception);
}

TEST(throwingNoExceptions, setTheDenominator)
{
	Fraction fract{ 1, 2 };
	EXPECT_NO_THROW(fract.setDenominator(3));
}

/* Test fraction string format (fractionary / decimal / integer) */

TEST(checkFractionFormat, checkStringIsDecimal)
{
	EXPECT_GT(Fraction::checkDecimalString("1.5"), static_cast<int>(DecimalString::NULL_INDEX));
	EXPECT_GT(Fraction::checkDecimalString("-1.5"), static_cast<int>(DecimalString::NULL_INDEX));
}

TEST(checkFractionFormat, checkStringIsInteger)
{
	EXPECT_EQ(static_cast<int>(DecimalString::NO_DECIMAL_INDEX), Fraction::checkDecimalString("1"));
	EXPECT_EQ(static_cast<int>(DecimalString::NO_DECIMAL_INDEX), Fraction::checkDecimalString("-1"));
}

TEST(checkFractionFormat, checkDecimalNotFraction)
{
	EXPECT_EQ(static_cast<int>(FractionString::ERROR_INDEX), Fraction::checkFractionString("1.5"));
	EXPECT_EQ(static_cast<int>(FractionString::ERROR_INDEX), Fraction::checkFractionString("-1.5"));
}

TEST(checkFractionFormat, checkIntegerNotFraction)
{
	EXPECT_EQ(static_cast<int>(FractionString::ERROR_INDEX), Fraction::checkFractionString("1"));
	EXPECT_EQ(static_cast<int>(FractionString::ERROR_INDEX), Fraction::checkFractionString("-1"));
}

TEST(checkFractionFormat, checkFractionStringIsCorrect)
{
	EXPECT_GT(Fraction::checkFractionString("1/5"), static_cast<int>(FractionString::NULL_INDEX));
	EXPECT_GT(Fraction::checkFractionString("-1/5"), static_cast<int>(FractionString::NULL_INDEX));
	EXPECT_GT(Fraction::checkFractionString("-1/-5"), static_cast<int>(FractionString::NULL_INDEX));
	EXPECT_GT(Fraction::checkFractionString("1/-5"), static_cast<int>(FractionString::NULL_INDEX));
}

TEST(checkFractionFormat, checkFractionNotDecimal)
{
	EXPECT_EQ(Fraction::checkDecimalString("1/5"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("-1/5"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("-1/-5"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("1/-5"), static_cast<int>(FractionString::ERROR_INDEX));
}

TEST(checkFractionFormat, checkFormatIsIncorrect)
{
	// check fraction format is incorrect for these strings
	EXPECT_EQ(Fraction::checkFractionString(".15"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("15."), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("-.15"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString(".-15"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("-15."), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("-1.5.6"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("1.5 -"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("-1-6.5"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("1a.5"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("1 / 1.5"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("1-/5"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("1/5-"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("-/15"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("/15"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("15/"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("1/--5"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("1a.5"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("1/-"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("1/1.5"), static_cast<int>(FractionString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkFractionString("1/5/6"), static_cast<int>(FractionString::ERROR_INDEX));
	// then check the decimal format is incorrect for these strings too
	EXPECT_EQ(Fraction::checkDecimalString(".15"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("15."), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("-.15"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString(".-15"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("-15."), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("-1.5.6"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("1.5 -"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("-1-6.5"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("1a.5"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("1 / 1.5"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("1-/5"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("1/5-"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("-/15"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("/15"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("15/"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("1/--5"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("1a.5"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("1/-"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("1/1.5"), static_cast<int>(DecimalString::ERROR_INDEX));
	EXPECT_EQ(Fraction::checkDecimalString("1/5/6"), static_cast<int>(DecimalString::ERROR_INDEX));
}

/* Test the normalize() function */

TEST(normalizeFunction, singleFraction)
{
	Fraction a{ "3/6" };
	EXPECT_EQ(a.getNumerator(), 1);
	EXPECT_EQ(a.getDenominator(), 2);
	EXPECT_EQ(a.getDecimal(), 0.5);
	Fraction b{ "-3/6" };
	EXPECT_EQ(b.getNumerator(), -1);
	EXPECT_EQ(b.getDenominator(), 2);
	EXPECT_EQ(b.getDecimal(), -0.5);
	Fraction c{ "3/-6" };
	EXPECT_EQ(c.getNumerator(), -1);
	EXPECT_EQ(c.getDenominator(), 2);
	EXPECT_EQ(c.getDecimal(), -0.5);
	Fraction d{ "-3/-6" };
	EXPECT_EQ(d.getNumerator(), 1);
	EXPECT_EQ(d.getDenominator(), 2);
	EXPECT_EQ(d.getDecimal(), 0.5);
}

TEST(normalizeFunction, twoFractions)
{
	Fraction a{ "2/5" };
	Fraction b{ "3/10" };
	Fraction sum{ a + b };
	double decimalReferenceSum = static_cast<double>(7) / 10;
	EXPECT_EQ(sum.getNumerator(), 7);
	EXPECT_EQ(sum.getDenominator(), 10);
	EXPECT_EQ(sum.getDecimal(), decimalReferenceSum);
	Fraction diff{ a - b };
	double decimalReferenceDiff = static_cast<double>(1) / 10;
	EXPECT_EQ(diff.getNumerator(), 1);
	EXPECT_EQ(diff.getDenominator(), 10);
	EXPECT_EQ(diff.getDecimal(), decimalReferenceDiff);
	Fraction prod{ a*b };
	double decimalReferenceProd = static_cast<double>(3) / 25;
	EXPECT_EQ(prod.getNumerator(), 3);
	EXPECT_EQ(prod.getDenominator(), 25);
	EXPECT_EQ(prod.getDecimal(), decimalReferenceProd);
	Fraction div{ a / b };
	double decimalReferenceDiv = static_cast<double>(4) / 3;
	EXPECT_EQ(div.getNumerator(), 4);
	EXPECT_EQ(div.getDenominator(), 3);
	EXPECT_EQ(div.getDecimal(), decimalReferenceDiv);
}

/* Test that the greatest common divisor is correctly calculated */

TEST(greatestCommonDivisor, correctOutput)
{
	EXPECT_EQ(Fraction::greatestCommonDivisor(27, 18), 9);
	EXPECT_EQ(Fraction::greatestCommonDivisor(-27, 18), 9);
	EXPECT_EQ(Fraction::greatestCommonDivisor(27, -18), 9);
	EXPECT_EQ(Fraction::greatestCommonDivisor(-27, -18), 9);
	EXPECT_EQ(Fraction::greatestCommonDivisor(18, 27), 9);
	EXPECT_EQ(Fraction::greatestCommonDivisor(18, -27), 9);
	EXPECT_EQ(Fraction::greatestCommonDivisor(-18, 27), 9);
	EXPECT_EQ(Fraction::greatestCommonDivisor(-18, -27), 9);
	EXPECT_EQ(Fraction::greatestCommonDivisor(0, 2), 2);
	EXPECT_EQ(Fraction::greatestCommonDivisor(2, 0), 2);
	EXPECT_EQ(Fraction::greatestCommonDivisor(0, -2), 2);
	EXPECT_EQ(Fraction::greatestCommonDivisor(-2, 0), 2);
	EXPECT_EQ(Fraction::greatestCommonDivisor(1, 1), 1);
	EXPECT_EQ(Fraction::greatestCommonDivisor(-1, 1), 1);
	EXPECT_EQ(Fraction::greatestCommonDivisor(1, -1), 1);
	EXPECT_EQ(Fraction::greatestCommonDivisor(-1, -1), 1);
	EXPECT_EQ(Fraction::greatestCommonDivisor(10, 10), 10);
	EXPECT_EQ(Fraction::greatestCommonDivisor(-10, 10), 10);
	EXPECT_EQ(Fraction::greatestCommonDivisor(10, -10), 10);
	EXPECT_EQ(Fraction::greatestCommonDivisor(-10, -10), 10);
}

/* Test the equivalent fractions concept */

TEST(equivalentFractions, equivalentFractionsInteger)
{
	Fraction a{ 2, 1 };
	Fraction b{ 2 };
	Fraction c{ 2.0 };
	Fraction d{ "4/2" };
	Fraction e{ "2.0" };
	EXPECT_EQ(a, b);
	EXPECT_EQ(b, c);
	EXPECT_EQ(c, d);
	EXPECT_EQ(d, e);
}

TEST(equivalentFractions, equivalentFractionsFractionary)
{
	Fraction a{ 6, 5 };
	Fraction b{ 1.2 };
	Fraction c{ "12/10" };
	Fraction d{ "1.20" };
	EXPECT_EQ(a, b);
	EXPECT_EQ(b, c);
	EXPECT_EQ(c, d);
}

TEST(equivalentFractions, equivalentFractionsNegativeSign)
{
	Fraction a{ -6, 5 };
	Fraction b{ 6, -5 };
	Fraction c{ "12/-10" };
	Fraction d{ "-12/10" };
	Fraction e{ "-1.20" };
	Fraction f{ -2 };
	Fraction g{ -2, 1 };
	EXPECT_EQ(a, b);
	EXPECT_EQ(b, c);
	EXPECT_EQ(c, d);
	EXPECT_EQ(d, e);
	EXPECT_EQ(f, g);
}

TEST(equivalentFractions, equivalentFractionsPositiveSign)
{
	Fraction a{ 6, 5 };
	Fraction b{ -6, -5 };
	Fraction c{ "-12/-10" };
	EXPECT_EQ(a, b);
	EXPECT_EQ(b, c);
}

/* Test getter and setter functions */

TEST(fractionGetters, numerator)
{
	Fraction fract(2, 4);
	EXPECT_EQ(1, fract.getNumerator());
	EXPECT_EQ(2, fract.getDenominator());
	EXPECT_EQ(0.5, fract.getDecimal());
}

TEST(fractionSetters, numeratorSetup)
{
	Fraction fract{ 1, 2 };
	fract.setNumerator(3);
	double decimalReference = static_cast<double>(3) / 2;
	EXPECT_EQ(fract, "3/2");
	EXPECT_EQ(fract.getDecimal(), decimalReference);
}

TEST(fractionSetters, denominatorSetup)
{
	Fraction fract{ 1, 2 };
	fract.setDenominator(3);
	double decimalReference = static_cast<double>(1) / 3;
	EXPECT_EQ(fract, "1/3");
	EXPECT_EQ(fract.getDecimal(), decimalReference);
}

TEST(fractionSetters, decimalSetup)
{
	Fraction fract{ 1, 2 };
	fract.setDecimal(1.2);
	EXPECT_EQ(fract, "6/5");
}

/* Test the arithmetic operators */

TEST(arithmeticOperators, plus)
{
	Fraction fract1{ "1/2" };
	Fraction fract2{ "1/3" };
	Fraction fract3{ "5/6" };
	std::string str1{ "1/2" };
	std::string str2{ "1/3" };
	EXPECT_EQ(fract1 + fract2, fract3);
	EXPECT_EQ("1/2" + fract2, fract3);
	EXPECT_EQ(fract1 + "1/3", fract3);
	EXPECT_EQ(str1 + fract2, fract3);
	EXPECT_EQ(fract1 + str2, fract3);
}

TEST(arithmeticOperators, minus)
{
	Fraction fract1{ "1/2" };
	Fraction fract2{ "1/3" };
	Fraction fract3{ "1/6" };
	std::string str1{ "1/2" };
	std::string str2{ "1/3" };
	EXPECT_EQ(fract1 - fract2, fract3);
	EXPECT_EQ("1/2" - fract2, fract3);
	EXPECT_EQ(fract1 - "1/3", fract3);
	EXPECT_EQ(str1 - fract2, fract3);
	EXPECT_EQ(fract1 - str2, fract3);
}

TEST(arithmeticOperators, multiply)
{
	Fraction fract1{ "1/2" };
	Fraction fract2{ "1/3" };
	Fraction fract3{ "1/6" };
	std::string str1{ "1/2" };
	std::string str2{ "1/3" };
	EXPECT_EQ(fract1*fract2, fract3);
	EXPECT_EQ("1/2" * fract2, fract3);
	EXPECT_EQ(fract1 * "1/3", fract3);
	EXPECT_EQ(str1*fract2, fract3);
	EXPECT_EQ(fract1*str2, fract3);
}
TEST(arithmeticOperators, divide)
{
	Fraction fract1{ "1/2" };
	Fraction fract2{ "1/3" };
	Fraction fract3{ "3/2" };
	std::string str1{ "1/2" };
	std::string str2{ "1/3" };
	EXPECT_EQ(fract1 / fract2, fract3);
	EXPECT_EQ("1/2" / fract2, fract3);
	EXPECT_EQ(fract1 / "1/3", fract3);
	EXPECT_EQ(str1 / fract2, fract3);
	EXPECT_EQ(fract1 / str2, fract3);
}
TEST(arithmeticOperators, power)
{
	Fraction fract1{ "1/2" };
	Fraction fract2{ "1" };
	Fraction fract3{ "1/8" };
	Fraction fract4{ "2" };
	Fraction fract5{ "8" };
	EXPECT_EQ(fract2, fract1 ^ 0);
	EXPECT_EQ(fract1, fract1 ^ 1);
	EXPECT_EQ(fract3, fract1 ^ 3);
	EXPECT_EQ(fract4, fract1 ^ (-1));
	EXPECT_EQ(fract5, fract1 ^ (-3));
}
TEST(arithmeticOperators, inverse)
{
	Fraction fract1{ "1/2" };
	Fraction fract2{ "2" };
	EXPECT_EQ(fract2, fract1.inverse());
}
TEST(arithmeticOperators, plusEqual)
{
	Fraction fract{ "1/2" };
	Fraction fractCopy{ fract };
	Fraction fractToAdd{ "1/3" };
	fract += fractToAdd;
	fractCopy = fractCopy + fractToAdd;
	EXPECT_EQ(fract, fractCopy);
	std::string stringToAdd{ "1/4" };
	fract += stringToAdd;
	fractCopy = fractCopy + stringToAdd;
	EXPECT_EQ(fract, fractCopy);
	fract += "1/5";
	fractCopy = fractCopy + "1/5";
	EXPECT_EQ(fract, fractCopy);
}

TEST(arithmeticOperators, minusEqual)
{
	Fraction fract{ "1/2" };
	Fraction fractCopy{ fract };
	Fraction fractToSubtract{ "1/3" };
	fract -= fractToSubtract;
	fractCopy = fractCopy - fractToSubtract;
	EXPECT_EQ(fract, fractCopy);
	std::string stringToSubtract{ "1/4" };
	fract -= stringToSubtract;
	fractCopy = fractCopy - stringToSubtract;
	EXPECT_EQ(fract, fractCopy);
	fract -= "1/5";
	fractCopy = fractCopy - "1/5";
	EXPECT_EQ(fract, fractCopy);
}

TEST(arithmeticOperators, multiplyEqual)
{
	Fraction fract{ "1/2" };
	Fraction fractCopy{ fract };
	Fraction fractToMultiply{ "1/3" };
	fract *= fractToMultiply;
	fractCopy = fractCopy*fractToMultiply;
	EXPECT_EQ(fract, fractCopy);
	std::string stringToMultiply{ "1/4" };
	fract *= stringToMultiply;
	fractCopy = fractCopy*stringToMultiply;
	EXPECT_EQ(fract, fractCopy);
	fract *= "1/5";
	fractCopy = fractCopy * "1/5";
	EXPECT_EQ(fract, fractCopy);
}

TEST(arithmeticOperators, divideEqual)
{
	Fraction fract{ "1/2" };
	Fraction fractCopy(fract);
	Fraction fractToDivide{ "1/3" };
	fract /= fractToDivide;
	fractCopy = fractCopy / fractToDivide;
	EXPECT_EQ(fract, fractCopy);
	std::string stringToDivide{ "1/4" };
	fract /= stringToDivide;
	fractCopy = fractCopy / stringToDivide;
	EXPECT_EQ(fract, fractCopy);
	fract /= "1/5";
	fractCopy = fractCopy / "1/5";
	EXPECT_EQ(fract, fractCopy);
}

TEST(arithmeticOperators, powerEqual)
{
	Fraction fract{ "1/2" };
	Fraction fractCopy{ fract };
	int exponent{ 5 };
	fract ^= exponent;
	fractCopy = fractCopy^exponent;
	EXPECT_EQ(fract, fractCopy);
}

TEST(unaryOperators, plusPlus)
{
	Fraction fract1{ "1/2" };
	Fraction fract2{ fract1 };
	Fraction fract3{ "3/2" };
	Fraction fract4{ fract1++ };
	++fract2;
	EXPECT_EQ(fract2, fract3);
	EXPECT_EQ(fract2.getDecimal(), fract3.getDecimal());
	EXPECT_EQ(fract4, fract3);
	EXPECT_EQ(fract4.getDecimal(), fract3.getDecimal());
	EXPECT_EQ(fract1, "1/2");
}

TEST(unaryOperators, minusMinus)
{
	Fraction fract1{ "5/2" };
	Fraction fract2{ fract1 };
	Fraction fract3{ "3/2" };
	Fraction fract4{ fract1-- };
	--fract2;
	EXPECT_EQ(fract2, fract3);
	EXPECT_EQ(fract2.getDecimal(), fract3.getDecimal());
	EXPECT_EQ(fract4, fract3);
	EXPECT_EQ(fract4.getDecimal(), fract3.getDecimal());
	EXPECT_EQ(fract1, "5/2");
}

/* Test the assignment operators */

TEST(assignmentOperators, chainingFractions)
{
	// should work fine, it's the default operator
	Fraction fract1{ "1/2" };
	Fraction fract2{ "4/5" };
	Fraction fract3{ "5/6" };
	fract1 = fract2 = fract3;
	EXPECT_EQ(fract1, fract3);
	EXPECT_EQ(fract2, fract3);
	EXPECT_EQ(fract1, "5/6");
}

TEST(assignmentOperators, chainingFractionsStrings)
{
	Fraction fract1{ "1/2" };
	Fraction  fract2{ "4/5" };
	std::string fract3{ "5/6" };
	// chaining goes from right to left so first 2 operands must be fractions (cannot assign fraction to string)
	fract1 = fract2 = fract3;
	EXPECT_EQ(fract1, fract3);
	EXPECT_EQ(fract2, fract3);
	EXPECT_EQ(fract1, "5/6");
}

TEST(assignmentOperators, chainingFractionsChars)
{
	Fraction fract1{ "1/2" };
	Fraction  fract2{ "4/5" };
	// chaining goes from right to left so first 2 operands must be fractions (cannot assign fraction to char*)
	fract1 = fract2 = "5/6";
	EXPECT_EQ(fract1, fract2);
	EXPECT_EQ(fract2, "5/6");
}

TEST(assignmentOperators, stringObjects)
{
	Fraction fract1{ "1/4" };
	Fraction fract2{ "2/3" };
	std::string fract3{ "2/8" };
	fract2 = fract3;
	EXPECT_EQ(fract1, fract2);
}

TEST(assignmentOperators, cStrings)
{
	Fraction fract1{ "1/4" };
	Fraction fract2{ "2/3" };
	fract2 = "3/12";
	EXPECT_EQ(fract1, fract2);
}

/* Test the logical operators */

TEST(compareOperators, greater)
{
	Fraction fract1{ 1, 2 };
	Fraction fract2{ 1, 4 };
	std::string str1{ "1/4" };
	std::string str2{ "1/2" };
	EXPECT_GT(fract1, fract2);
	EXPECT_GT(fract1, str1);
	EXPECT_GT(fract1, "1/4");
	EXPECT_GT("1/2", fract2);
	EXPECT_GT(str2, fract2);
}

TEST(compareOperators, greaterOrEqual)
{
	Fraction fract1{ 1, 2 };
	Fraction fract2{ 1, 4 };
	Fraction fract3{ 1, 4 };
	std::string str1{ "1/4" };
	std::string str2{ "1/2" };
	EXPECT_GE(fract1, fract2);
	EXPECT_GE(fract2, fract3);
	EXPECT_GE(fract1, str1);
	EXPECT_GE(fract1, str2);
	EXPECT_GE(fract1, "1/4");
	EXPECT_GE(fract2, "1/4");
	EXPECT_GE("1/2", fract1);
	EXPECT_GE("1/2", fract2);
	EXPECT_GE(str1, fract2);
	EXPECT_GE(str2, fract2);
}

TEST(compareOperators, smaller)
{
	Fraction fract1{ 1, 2 };
	Fraction fract2{ 1, 4 };
	std::string str1{ "1/4" };
	std::string str2{ "1/2" };
	EXPECT_LT(fract2, fract1);
	EXPECT_LT(fract2, str2);
	EXPECT_LT(fract2, "1/2");
	EXPECT_LT("1/4", fract1);
	EXPECT_LT(str1, fract1);
}

TEST(compareOperators, smallerOrEqual)
{
	Fraction fract1{ 1, 2 };
	Fraction fract2{ 1, 4 };
	Fraction fract3{ 1, 4 };
	std::string str1{ "1/4" };
	std::string str2{ "1/2" };
	EXPECT_LE(fract2, fract1);
	EXPECT_LE(fract3, fract2);
	EXPECT_LE(fract2, str1);
	EXPECT_LE(fract2, str2);
	EXPECT_LE(fract2, "1/4");
	EXPECT_LE(fract2, "1/2");
	EXPECT_LE("1/4", fract1);
	EXPECT_LE("1/4", fract2);
	EXPECT_LE(str1, fract1);
	EXPECT_LE(str1, fract2);
}

TEST(compareOperators, different)
{
	Fraction fract1{ 1, 2 };
	Fraction fract2{ 1, 4 };
	std::string str1{ "1/4" };
	std::string str2{ "1/2" };
	EXPECT_NE(fract1, fract2);
	EXPECT_NE(fract1, str1);
	EXPECT_NE(fract1, "1/4");
	EXPECT_NE("1/4", fract1);
	EXPECT_NE(str1, fract1);
}

TEST(compareOperators, equal)
{
	Fraction fract1{ 1, 2 };
	Fraction fract2{ 2, 4 };
	std::string str1{ "3/6" };
	EXPECT_EQ(fract1, fract2);
	EXPECT_EQ(fract1, str1);
	EXPECT_EQ(fract1, "4/8");
	EXPECT_EQ("5/10", fract1);
	EXPECT_EQ(str1, fract1);
}

TEST(boolFractionValues, booleanConversionOperator)
{
	Fraction fract1{ "0/1" };
	Fraction fract2{ "1/2" };
	EXPECT_FALSE(fract1);
	EXPECT_TRUE(fract2);
}

TEST(boolFractionValues, negationOperator)
{
	Fraction fract1{ "0/1" };
	Fraction fract2{ "1/2" };
	EXPECT_TRUE(!fract1);
	EXPECT_FALSE(!fract2);
}

TEST(boolFractionValues, andOperator)
{
	Fraction fract1{ "0/1" };
	Fraction fract2{ "1/2" };
	Fraction fract3{ "2/3" };
	Fraction fract4{ "0/3" };
	EXPECT_FALSE(fract1 && fract2);
	EXPECT_TRUE(fract2 && fract3);
	EXPECT_FALSE(fract3 && fract4);
	EXPECT_FALSE(fract4 && fract1);
}

TEST(boolFractionValues, orOperator)
{
	Fraction fract1{ "0/1" };
	Fraction fract2{ "1/2" };
	Fraction fract3{ "2/3" };
	Fraction fract4{ "0/3" };
	EXPECT_TRUE(fract1 || fract2);
	EXPECT_TRUE(fract2 || fract3);
	EXPECT_TRUE(fract3 || fract4);
	EXPECT_FALSE(fract4 || fract1);
}

TEST(otherLogicalOperations, isLargerThanUnitFraction)
{
	Fraction fract1{ "4/3" };
	Fraction fract2{ "1.2" };
	Fraction fract3{ 2 };
	Fraction fract4{ 1.1 };
	Fraction fract5(3, 2);
	EXPECT_TRUE(fract1.isLargerThanUnit());
	EXPECT_TRUE(fract2.isLargerThanUnit());
	EXPECT_TRUE(fract3.isLargerThanUnit());
	EXPECT_TRUE(fract4.isLargerThanUnit());
	EXPECT_TRUE(fract5.isLargerThanUnit());
}

TEST(otherLogicalOperations, isSmallerThanUnitFraction)
{
	Fraction fract1{ "3/4" };
	Fraction fract2{ "0.2" };
	Fraction fract3{ 0 };
	Fraction fract4{ 0.99 };
	Fraction fract5(2, 3);
	EXPECT_TRUE(fract1.isSmallerThanUnit());
	EXPECT_TRUE(fract2.isSmallerThanUnit());
	EXPECT_TRUE(fract3.isSmallerThanUnit());
	EXPECT_TRUE(fract4.isSmallerThanUnit());
	EXPECT_TRUE(fract5.isSmallerThanUnit());
}

TEST(otherLogicalOperations, isUnitFraction)
{
	Fraction fract1{ "4/4" };
	Fraction fract2{ "1.0" };
	Fraction fract3{ 1 };
	Fraction fract4{ 1.00 };
	Fraction fract5(3, 3);
	EXPECT_TRUE(fract1.isUnit());
	EXPECT_TRUE(fract2.isUnit());
	EXPECT_TRUE(fract3.isUnit());
	EXPECT_TRUE(fract4.isUnit());
	EXPECT_TRUE(fract5.isUnit());
}

/* Test the IO operators */

TEST(IOOperators, inputOutputStreams)
{
	Fraction f{ "1/2" };
	std::stringstream fractionStringStream{};
	fractionStringStream << f;
	Fraction g{};
	fractionStringStream >> g;
	EXPECT_EQ(f, g);
}

TEST(IOOperators, fileStreams)
{
	Fraction writtenFract{ "1/2" };
	std::string fileName{ "C:\\Users\\liviu.popa\\Desktop\\fraction.txt" };
	std::ofstream writeToFile{ fileName };
	writeToFile << writtenFract;
	writeToFile.close();
	Fraction readFract{};
	std::ifstream readFromFile{ fileName };
	readFromFile >> readFract;
	EXPECT_EQ(writtenFract, readFract);
}