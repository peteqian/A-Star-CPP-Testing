# CSIT314
CSIT314 - Unit Testing

The program can be executed using VSCode using Windows 10.
In order to execute test cases, you must install the following pre-requisites:

1. CMake and CMake tools via VSCode
2. C/C++ (VSCode Extension)

If you encounter errors with CMake path. Ensure your settings are correct, check main page of CMake via VSCode. 
Or, alternatively download from https://cmake.org/ and install into directory you can locate.

# Build set-up.
## Windows

1. Configure CMake with a C/C++ compiler. This may be mwing/Visual Studio 2019 x86/x64 architecture.
2. Press F7 to build.

If you encounter errors with building. My only solution so far is to reconfigure your compiler with another C/C++ compiler.

Create TestCases within ../test/SimTests.cpp

Documentation of test case creation can be found [here](https://google.github.io/googletest/).

## Unix (Mac OSX, Ubuntu)
1. Download and install CMake
2. Once you've downloaded CSIT314 Folder from the repos
3. Create a build directory 
> mkdir build
4. Change to build
> cmake ../
> make

# Running your tests
1. Firstly, ensure the file you're working must include in the headers:
> #include "../ass3-refactor.h"
> 
> #include <gtest/gtest.h>
2. Do not re-declare, as compiler will complain. Technically, this shouldn't need to be be declared at all. It is automatically generated within the libraries.
> int main(int argc, char **argv)

## Windows
1. If you're working VSCode, there is a play button on the bottom.

## Unix
1. Ensure you have saved your source code files.
2. Run the make command in the build directory
> $ cd ./build && make
3. Then run the program
> ./build/test/SimTests

## Making changes to the source code.
For the actual program, the source code is located in ass3-refactor.cpp and ass3-refactor.h.
As for the test cases. You can either separate your test cases into a new file in the home/test/ directory or work in an existing file. Preferably separate test case for code readability.

When creating a separate file for tests. You must:
1. Edit the CMakeLists.txt located in the test folder 
> CSIT314/test/CMakeLists.txt
2. Then edit on line 5 to add your new file:
> set(Sources SimTests.cpp Data.cpp >insert_your_new_file_here<)


# Notes:
1. The executable of the test program is built in build/test. Any files you create in your test code will be located in this directory.
2. The files in the home directory are just for static test data to remove annoying randomness involved in generating the test data for debugging the test case functionality. This should not be tested in the final production.
