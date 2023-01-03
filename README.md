# Fractions
A class of rational numbers

Warning! Do not use in business/safety/other critical systems (including production servers etc). I will take no responsibility for any damage that might occur whatsoever.

The FractionLib folder contains the actual source code (library) for the class while the other one (FractionTests) contains the unit tests.

The unit tests have been written using the Google Test platform.

There are two branches:
- master: contains the up-to-date version of the code (minimum required C++ version is currently C++20)
- LegacyCode: an older version that doesn't require C++20 to build (minimum required is C++11)

Notes:
- the fractions library is built as shared (dynamic) library for Linux and MacOS and statically for Windows. This may obviously be changed by modifying the CMakeLists.txt file.
- use the older code whenever building with C++20 is not an option
- for the test case referring to the file stream operators please change the path and name of the file according to your requirements.

