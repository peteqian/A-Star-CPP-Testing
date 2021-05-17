# CSIT314
CSIT314 - Unit Testing

The program can be executed using VSCode using Windows 10.
In order to execute test cases, you must install the following pre-requisites:

1. CMake and CMake tools via VSCode
2. C/C++ (VSCode Extension)

If you encounter errors with CMake path. Ensure your settings are correct, check main page of CMake via VSCode. 
Or, alternatively download from https://cmake.org/ and install into directory you can locate.

## Build set-up.

1. Configure CMake with a C/C++ compiler. This may be mwing/Visual Studio 2019 x86/x64 architecture.
2. Press F7 to build.

If you encounter errors with building. My only solution so far is to reconfigure your compiler with another C/C++ compiler.

Create TestCases within ../test/SimTests.cpp

Documentation of test case creation can be found [here](https://google.github.io/googletest/).


## Running your tests
1. Firstly, ensure the file you're working must include in the headers:
> #include "../ass3-refactor.h"
> 
> #include <gtest/gtest.h>
2. Do not re-declare, as compiler will complain. Technically, this shouldn't need to be be declared at all. It is automatically generated within the libraries.
> int main(int argc, char **argv)
4. If you're working VSCode, there is a play button on the bottom.
5. Will update for other environments if needed.

## Making changes to the source code.
For the actual program, the source code is located in ass3-refactor.cpp and ass3-refactor.h.
As for the test cases. You can either separate your test cases into a new file in the home/test/ directory or work in an existing file. Preferably separate test case for cod readability.

# Notes:
1. The executable of the test program is built in build/test. Any files you create in your test code will be located in this directory.
2. The files in the home directory are just for static test data to remove annoying randomness involved in generating the test data for debugging the test case functionality. This should not be tested in the final production.
