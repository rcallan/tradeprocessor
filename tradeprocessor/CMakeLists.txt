cmake_minimum_required(VERSION 3.16)

add_subdirectory(../lib lib)

include_directories(${SHARED_LIB_INCLUDE_DIR})

set(SRCS TradeProcessor.cpp)
add_executable(arith ${SRCS})
target_link_libraries(arith lib)

install (TARGETS arith DESTINATION "${PROJECT_SOURCE_DIR}/bin/")