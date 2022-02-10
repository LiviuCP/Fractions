#pragma once

#include <stdexcept>
#include <sstream>

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../FractionLib/fraction.h"


using namespace testing;

/* Test exceptions */

TEST(throwingExceptions, wrongStringFormatInFractionConstructor)
{
    EXPECT_THROW(Fraction{ ".15" }, std::runtime_error);
    EXPECT_THROW(Fraction{ "-15." }, std::runtime_error);
    EXPECT_THROW(Fraction{ "1/5-" }, std::runtime_error);
    EXPECT_THROW(Fraction{ "15/" }, std::runtime_error);
}

TEST(throwingExceptions, divisionByZero)
{
    Fraction fract{ 1, 2 };
    Fraction zeroFract{};
    EXPECT_THROW(Fraction(1, 0), std::runtime_error);
    EXPECT_THROW(Fraction{ "1/0" }, std::runtime_error);
    EXPECT_THROW(fract.setDenominator(0), std::runtime_error);
    EXPECT_THROW(zeroFract.inverse(), std::runtime_error);
}

TEST(throwingExceptions, twoZeroNumbersCommonDivisor)
{
    EXPECT_THROW(Fraction::getGreatestCommonDivisor(0, 0), std::runtime_error);
}

TEST(throwingNoExceptions, constructors)
{
    EXPECT_NO_THROW(Fraction{});
    EXPECT_NO_THROW(Fraction(1, 2));
    EXPECT_NO_THROW(Fraction(-1, 2));
    EXPECT_NO_THROW(Fraction(1, -2));
    EXPECT_NO_THROW(Fraction(-1, -2));
    EXPECT_NO_THROW(Fraction{ 3 });
    EXPECT_NO_THROW(Fraction{ -3 });
    EXPECT_NO_THROW(Fraction{ 1.5 });
    EXPECT_NO_THROW(Fraction{ -1.5 });
    EXPECT_NO_THROW(Fraction{ "1/4" });
    EXPECT_NO_THROW(Fraction{ "1.5" });
    EXPECT_NO_THROW(Fraction{ "3" });
    EXPECT_NO_THROW(Fraction{ "-1/4" });
    EXPECT_NO_THROW(Fraction{ "-1.5" });
    EXPECT_NO_THROW(Fraction{ "-3" });
}

TEST(throwingNoExceptions, highestCommonDivisor)
{
    EXPECT_NO_THROW(Fraction::getGreatestCommonDivisor(1, 0));
    EXPECT_NO_THROW(Fraction::getGreatestCommonDivisor(0, 1));
    EXPECT_NO_THROW(Fraction::getGreatestCommonDivisor(1, 1));
    EXPECT_NO_THROW(Fraction::getGreatestCommonDivisor(6, 8));
}

TEST(throwingNoExceptions, setTheDenominator)
{
    Fraction fract{ 1, 2 };
    EXPECT_NO_THROW(fract.setDenominator(3));
}

/* Test fraction string format (fractionary / decimal / integer) */

TEST(checkFractionFormat, checkStringIsDecimal)
{
    EXPECT_GT(Fraction::parseDecimalString("1.5"), static_cast<int>(Fraction::DecimalStringIndexes::NIL));
    EXPECT_GT(Fraction::parseDecimalString("-1.5"), static_cast<int>(Fraction::DecimalStringIndexes::NIL));
}

TEST(checkFractionFormat, checkStringIsInteger)
{
    EXPECT_EQ(static_cast<int>(Fraction::DecimalStringIndexes::INTEGER), Fraction::parseDecimalString("1"));
    EXPECT_EQ(static_cast<int>(Fraction::DecimalStringIndexes::INTEGER), Fraction::parseDecimalString("-1"));
}

TEST(checkFractionFormat, checkDecimalNotFraction)
{
    EXPECT_EQ(static_cast<int>(Fraction::FractionStringIndexes::ERROR), Fraction::parseFractionString("1.5"));
    EXPECT_EQ(static_cast<int>(Fraction::FractionStringIndexes::ERROR), Fraction::parseFractionString("-1.5"));
}

TEST(checkFractionFormat, checkIntegerNotFraction)
{
    EXPECT_EQ(static_cast<int>(Fraction::FractionStringIndexes::ERROR), Fraction::parseFractionString("1"));
    EXPECT_EQ(static_cast<int>(Fraction::FractionStringIndexes::ERROR), Fraction::parseFractionString("-1"));
}

TEST(checkFractionFormat, checkFractionStringIsCorrect)
{
    EXPECT_GT(Fraction::parseFractionString("1/5"), static_cast<int>(Fraction::FractionStringIndexes::NIL));
    EXPECT_GT(Fraction::parseFractionString("-1/5"), static_cast<int>(Fraction::FractionStringIndexes::NIL));
    EXPECT_GT(Fraction::parseFractionString("-1/-5"), static_cast<int>(Fraction::FractionStringIndexes::NIL));
    EXPECT_GT(Fraction::parseFractionString("1/-5"), static_cast<int>(Fraction::FractionStringIndexes::NIL));
}

TEST(checkFractionFormat, checkFractionNotDecimal)
{
    EXPECT_EQ(Fraction::parseDecimalString("1/5"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseDecimalString("-1/5"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseDecimalString("-1/-5"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseDecimalString("1/-5"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
}

TEST(checkFractionFormat, checkFormatIsIncorrect)
{
    // check fraction format is incorrect for these strings
    EXPECT_EQ(Fraction::parseFractionString(".15"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("15."), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("-.15"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString(".-15"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("-15."), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("-1.5.6"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("1.5 -"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("-1-6.5"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("1a.5"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("1 / 1.5"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("1-/5"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("1/5-"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("-/15"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("/15"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("15/"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("1/--5"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("1a.5"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("1/-"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("1/1.5"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    EXPECT_EQ(Fraction::parseFractionString("1/5/6"), static_cast<int>(Fraction::FractionStringIndexes::ERROR));
    // then check the decimal format is incorrect for these strings too
    EXPECT_EQ(Fraction::parseDecimalString(".15"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("15."), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("-.15"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString(".-15"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("-15."), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("-1.5.6"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("1.5 -"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("-1-6.5"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("1a.5"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("1 / 1.5"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("1-/5"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("1/5-"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("-/15"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("/15"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("15/"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("1/--5"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("1a.5"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("1/-"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("1/1.5"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
    EXPECT_EQ(Fraction::parseDecimalString("1/5/6"), static_cast<int>(Fraction::DecimalStringIndexes::INVALID));
}

/* Test the normalize() function */

TEST(normalizeFunction, twoFractions)
{
    Fraction a{ "2/5" };
    Fraction b{ "3/10" };
    Fraction sum{ a + b };
    double decimalReferenceSum = static_cast<double>(7) / 10;
    EXPECT_EQ(sum.getNumerator(), 7);
    EXPECT_EQ(sum.getDenominator(), 10);
    EXPECT_EQ(sum.getDecimalValue(), decimalReferenceSum);
    Fraction diff{ a - b };
    double decimalReferenceDiff = static_cast<double>(1) / 10;
    EXPECT_EQ(diff.getNumerator(), 1);
    EXPECT_EQ(diff.getDenominator(), 10);
    EXPECT_EQ(diff.getDecimalValue(), decimalReferenceDiff);
    Fraction prod{ a*b };
    double decimalReferenceProd = static_cast<double>(3) / 25;
    EXPECT_EQ(prod.getNumerator(), 3);
    EXPECT_EQ(prod.getDenominator(), 25);
    EXPECT_EQ(prod.getDecimalValue(), decimalReferenceProd);
    Fraction div{ a / b };
    double decimalReferenceDiv = static_cast<double>(4) / 3;
    EXPECT_EQ(div.getNumerator(), 4);
    EXPECT_EQ(div.getDenominator(), 3);
    EXPECT_EQ(div.getDecimalValue(), decimalReferenceDiv);
}

/* Test that the greatest common divisor is correctly calculated */

TEST(greatestCommonDivisor, correctOutput)
{
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(27, 18), 9);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(-27, 18), 9);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(27, -18), 9);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(-27, -18), 9);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(18, 27), 9);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(18, -27), 9);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(-18, 27), 9);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(-18, -27), 9);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(0, 2), 2);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(2, 0), 2);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(0, -2), 2);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(-2, 0), 2);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(1, 1), 1);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(-1, 1), 1);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(1, -1), 1);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(-1, -1), 1);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(10, 10), 10);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(-10, 10), 10);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(10, -10), 10);
    EXPECT_EQ(Fraction::getGreatestCommonDivisor(-10, -10), 10);
}

/* Test the constructors */

TEST(constructors, defaultConstructor)
{
    Fraction fract{};
    double decimal{ 0.0 };
    EXPECT_EQ(0, fract.getNumerator());
    EXPECT_EQ(1, fract.getDenominator());
    EXPECT_EQ(decimal, fract.getDecimalValue());
}

TEST(constructors, numConstructor)
{
    Fraction fract1{ 3 };
    double decimal1{ 3.0 };
    EXPECT_EQ(3, fract1.getNumerator());
    EXPECT_EQ(1, fract1.getDenominator());
    EXPECT_EQ(decimal1, fract1.getDecimalValue());
    Fraction fract2{ -3 };
    double decimal2{ -3.0 };
    EXPECT_EQ(-3, fract2.getNumerator());
    EXPECT_EQ(1, fract2.getDenominator());
    EXPECT_EQ(decimal2, fract2.getDecimalValue());
}

TEST(constructors, numDenConstructor)
{
    Fraction fract1{ 8, 10 };
    double decimal1{ static_cast<double>(4) / 5 };
    EXPECT_EQ(4, fract1.getNumerator());
    EXPECT_EQ(5, fract1.getDenominator());
    EXPECT_EQ(decimal1, fract1.getDecimalValue());
    Fraction fract2{ -8, 10 };
    double decimal2{ static_cast<double>(-4) / 5 };
    EXPECT_EQ(-4, fract2.getNumerator());
    EXPECT_EQ(5, fract2.getDenominator());
    EXPECT_EQ(decimal2, fract2.getDecimalValue());
    Fraction fract3{ 8, -10 };
    double decimal3{ static_cast<double>(-4) / 5 };
    EXPECT_EQ(-4, fract3.getNumerator());
    EXPECT_EQ(5, fract3.getDenominator());
    EXPECT_EQ(decimal3, fract3.getDecimalValue());
    Fraction fract4{ -8, -10 };
    double decimal4{ static_cast<double>(4) / 5 };
    EXPECT_EQ(4, fract4.getNumerator());
    EXPECT_EQ(5, fract4.getDenominator());
    EXPECT_EQ(decimal4, fract4.getDecimalValue());
}

TEST(constructors, stringConstructorFractionary)
{
    Fraction fract1{ "4/6" };
    double decimal1{ static_cast<double>(2) / 3 };
    EXPECT_EQ(2, fract1.getNumerator());
    EXPECT_EQ(3, fract1.getDenominator());
    EXPECT_EQ(decimal1, fract1.getDecimalValue());
    Fraction fract2{ "-4/6" };
    double decimal2{ static_cast<double>(-2) / 3 };
    EXPECT_EQ(-2, fract2.getNumerator());
    EXPECT_EQ(3, fract2.getDenominator());
    EXPECT_EQ(decimal2, fract2.getDecimalValue());
    Fraction fract3{ "4/-6" };
    double decimal3{ static_cast<double>(-2) / 3 };
    EXPECT_EQ(-2, fract3.getNumerator());
    EXPECT_EQ(3, fract3.getDenominator());
    EXPECT_EQ(decimal3, fract3.getDecimalValue());
    Fraction fract4{ "-4/-6" };
    double decimal4{ static_cast<double>(2) / 3 };
    EXPECT_EQ(2, fract4.getNumerator());
    EXPECT_EQ(3, fract4.getDenominator());
    EXPECT_EQ(decimal4, fract4.getDecimalValue());
}

TEST(constructors, stringConstructorInteger)
{
    Fraction fract1{ "8" };
    double decimal1{ 8.0 };
    EXPECT_EQ(8, fract1.getNumerator());
    EXPECT_EQ(1, fract1.getDenominator());
    EXPECT_EQ(decimal1, fract1.getDecimalValue());
    Fraction fract2{ "-8" };
    double decimal2{ -8.0 };
    EXPECT_EQ(-8, fract2.getNumerator());
    EXPECT_EQ(1, fract2.getDenominator());
    EXPECT_EQ(decimal2, fract2.getDecimalValue());
}

TEST(constructors, stringConstructorDecimal)
{
    Fraction fract1{ "2.5" };
    double decimal1{ 2.5 };
    EXPECT_EQ(5, fract1.getNumerator());
    EXPECT_EQ(2, fract1.getDenominator());
    EXPECT_EQ(decimal1, fract1.getDecimalValue());
    Fraction fract2{ "-2.5" };
    double decimal2{ -2.5 };
    EXPECT_EQ(-5, fract2.getNumerator());
    EXPECT_EQ(2, fract2.getDenominator());
    EXPECT_EQ(decimal2, fract2.getDecimalValue());
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
    EXPECT_EQ(0.5, fract.getDecimalValue());
}

TEST(fractionSetters, numeratorSetup)
{
    Fraction fract{ 1, 2 };
    fract.setNumerator(3);
    double decimalReference = static_cast<double>(3) / 2;
    EXPECT_EQ(fract, "3/2");
    EXPECT_EQ(fract.getDecimalValue(), decimalReference);
}

TEST(fractionSetters, denominatorSetup)
{
    Fraction fract{ 1, 2 };
    fract.setDenominator(3);
    double decimalReference = static_cast<double>(1) / 3;
    EXPECT_EQ(fract, "1/3");
    EXPECT_EQ(fract.getDecimalValue(), decimalReference);
}

TEST(fractionSetters, decimalSetup)
{
    Fraction fract{ 1, 2 };
    fract.setDecimalValue(1.2);
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
    EXPECT_EQ(fract2.getDecimalValue(), fract3.getDecimalValue());
    EXPECT_EQ(fract4, fract3);
    EXPECT_EQ(fract4.getDecimalValue(), fract3.getDecimalValue());
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
    EXPECT_EQ(fract2.getDecimalValue(), fract3.getDecimalValue());
    EXPECT_EQ(fract4, fract3);
    EXPECT_EQ(fract4.getDecimalValue(), fract3.getDecimalValue());
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

TEST(assignmentOperators, chainingFractionsIntegers)
{
    Fraction fract1{ "1/2" };
    Fraction fract2{ "4/5" };
    fract1 = fract2 = 4;
    EXPECT_EQ(fract1, fract2);
    EXPECT_EQ(fract2, "4/1");
}

TEST(assignmentOperators, chainingFractionsDecimals)
{
    Fraction fract1{ "1/2" };
    Fraction fract2{ "4/5" };
    fract1 = fract2 = 1.6;
    EXPECT_EQ(fract1, fract2);
    EXPECT_EQ(fract2, "8/5");
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

TEST(assignmentOperators, integers)
{
    Fraction fract1{ "4/1" };
    Fraction fract2{ "2/3" };
    fract2 = 4;
    EXPECT_EQ(fract1, fract2);
}

TEST(assignmentOperators, decimals)
{
    Fraction fract1{ "8/5" };
    Fraction fract2{ "2/3" };
    fract2 = 1.6;
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
