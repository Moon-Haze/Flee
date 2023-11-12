cmake_minimum_required(VERSION 3.5.0)
project(flee VERSION 0.2.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

include(CTest)
enable_testing()

add_compile_options(-std=c++17 -pthread)

find_package(OpenSSL REQUIRED)
find_package(Protobuf REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost COMPONENTS system filesystem iostreams locale json REQUIRED)

include(cmake/ProtobufBuildCpp.cmake)

set(REQUIRED_LIBS_QUALIFIED
        ${PROTOBUF_LIBRARIES} ${PROTOBUF_PROTOC_LIBRARIES}
        spdlog::spdlog  OpenSSL::SSL)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    list(APPEND REQUIRED_LIBS_QUALIFIED ${Boost_LIBRARIES})
endif()

include_directories(include/core)
include_directories(include/exception)
include_directories(include/handler)
include_directories(include/packet)
include_directories(include/util)
include_directories(proto)
include_directories(${OPENSSL_INCLUDE_DIR})

include_directories(${PROTOBUF_INCLUDE_DIRS})

file(GLOB_RECURSE All_CPP_FILES src/*.cpp src/*.c include/*.h)

# 生成 ***.proto 文件的 C++ 源代码
protobuf_generate_cpp_to(PROTO_SRCS PROTO_HDRS proto)

# message("${PROTO_SRCS} ${PROTO_HDRS}")

# 链接所有代码
add_library(${PROJECT_NAME} SHARED ${All_CPP_FILES} ${PROTO_SRCS} ${PROTO_HDRS})

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
add_executable(flee_client ./test/Flee_client.cpp)
target_link_libraries(flee_client
        ${REQUIRED_LIBS_QUALIFIED}
        ${PROJECT_NAME}
)
ADD_TEST(NAME Flee_Client COMMAND flee_client)

#Client测试
add_executable(flee_png ./test/Flee_png.cpp)
target_link_libraries(flee_png
        ${REQUIRED_LIBS_QUALIFIED}
        ${PROJECT_NAME}
)
ADD_TEST(NAME Flee_PNG COMMAND flee_png)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)