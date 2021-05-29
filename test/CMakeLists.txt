cmake_minimum_required(VERSION 3.8)

set(This SimTests)

<<<<<<< Updated upstream
set(Sources SimTests.cpp Data.cpp Graph.cpp)
=======
set(Headers TestOracle.h)

set(Sources SimTests.cpp Data.cpp Graph.cpp VerifyData.cpp MissingData.cpp TestOracle.cpp)
>>>>>>> Stashed changes

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    Simulation
)

add_test(
    NAME ${This}
    COMMAND ${This}
)