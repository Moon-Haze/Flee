cmake_minimum_required(VERSION 3.0.0)
project(flee VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

include(CTest)
enable_testing()

add_compile_options(-std=c++17 -pthread)

find_package(CryptoPP REQUIRED)
find_package(Protobuf REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost COMPONENTS system filesystem iostreams log log_setup  REQUIRED)

include(cmake/ProtobufBuildCpp.cmake)

set(REQUIRED_LIBS_QUALIFIED  ws2_32
        ${PROTOBUF_LIBRARIES} ${PROTOBUF_PROTOC_LIBRARIES}
        cryptopp-static jsoncpp_lib spdlog::spdlog)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    list(APPEND REQUIRED_LIBS_QUALIFIED ${Boost_LIBRARIES})
endif()

include_directories(include/code)
include_directories(include/exception)
include_directories(include/util)
include_directories(proto)
include_directories(${OPENSSL_INCLUDE_DIR})

include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${JSON_INC_PATH})
# include_directories(${CryptoPP_INCLUDE_DIRS})

aux_source_directory(src/code CODE_CPP_FILE)
aux_source_directory(src/util UTIL_CPP_FILE)
aux_source_directory(src/exception EXCEPTION_CPP_FILE)

# 生成 ***.proto 文件的 C++ 源代码
protobuf_generate_cpp_to(PROTO_SRCS PROTO_HDRS proto)

# message("${PROTO_SRCS} ${PROTO_HDRS}")

set(All_CPP_FILES ${CODE_CPP_FILE} ${UTIL_CPP_FILE} ${EXCEPTION_CPP_FILE} ${PROTO_SRCS})
# 链接所有代码
add_library(${PROJECT_NAME} SHARED ${All_CPP_FILES})

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

# 设置测试文件
# 一般测试
add_executable(flee_test ./test/Flee_test.cpp)
target_link_libraries(flee_test
        ${REQUIRED_LIBS_QUALIFIED}
        ${PROJECT_NAME}
)
ADD_TEST(NAME Flee_Test COMMAND flee_test)

# 网络测试
add_executable(flee_net ./test/Flee_net.cpp)
target_link_libraries(flee_net
        ${REQUIRED_LIBS_QUALIFIED}
        ${PROJECT_NAME}
)
ADD_TEST(NAME Flee_Net COMMAND flee_net)

#Client测试
add_executable(flee_client ./test/flee_client.cpp)
target_link_libraries(flee_client
        ${REQUIRED_LIBS_QUALIFIED}
        ${PROJECT_NAME}
)
ADD_TEST(NAME Flee_Client COMMAND flee_client)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)