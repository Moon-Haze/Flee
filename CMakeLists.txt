cmake_minimum_required(VERSION 3.0.0)
project(flee VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/module ${CMAKE_MODULE_PATH})

include(CTest)
enable_testing()

find_package(CryptoPP REQUIRED)
find_package(Protobuf REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(spdlog REQUIRED)

include(cmake/ProtobufBuildCpp.cmake)

set(REQUIRED_LIBS_QUALIFIED
        ${PROTOBUF_LIBRARIES} ${PROTOBUF_PROTOC_LIBRARIES}
        ${CryptoPP_LIBRARIES} jsoncpp_lib spdlog::spdlog)

include_directories(include/code)
include_directories(include/exception)
include_directories(include/util)
include_directories(proto)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${JSON_INC_PATH})
# include_directories(${CryptoPP_INCLUDE_DIRS})

aux_source_directory(src/code CODE_CPP_FILE)
aux_source_directory(src/util UTIL_CPP_FILE)

# 生成 ***.proto 文件的 C++ 源代码
protobuf_generate_cpp_to(PROTO_SRCS PROTO_HDRS proto)

message("${PROTO_SRCS} ${PROTO_HDRS}")

set(All_CPP_FILES ${CODE_CPP_FILE} ${UTIL_CPP_FILE} ${PROTO_SRCS})
# 链接所有代码
add_library(${PROJECT_NAME} SHARED ${All_CPP_FILES})

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

# 设置测试文件
aux_source_directory(./test TEST_FILE)
add_executable(flee_test ${TEST_FILE})
target_link_libraries(flee_test
        ${REQUIRED_LIBS_QUALIFIED}
        ${PROJECT_NAME}
)
ADD_TEST(NAME flee_test_0_1 COMMAND flee_test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)