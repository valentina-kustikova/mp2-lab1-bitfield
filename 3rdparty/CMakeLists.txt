set(target "gtest")

FILE(GLOB hdrs "gtest/*.h")
FILE(GLOB srcs "gtest/*.cc")

ADD_LIBRARY(${target} STATIC ${srcs})

if((${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") AND
    (${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
    set(pthread "-pthread")
endif()
TARGET_LINK_LIBRARIES(${target} ${pthread})
