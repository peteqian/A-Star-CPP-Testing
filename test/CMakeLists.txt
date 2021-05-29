cmake_minimum_required(VERSION 3.8)

set(This SimTests)

set(Headers TestOracle.h)

set(Sources Data.cpp Graph.cpp VerifyData.cpp MissingData.cpp TestOracle.cpp SimTests.cpp)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    Simulation
)

add_test(
    NAME ${This}
    COMMAND ${This}
)