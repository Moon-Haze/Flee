function(protobuf_generate_cpp_to CPP_SRCS INC_HDRS DST_DIR)
  set(OUT_DIR ${CMAKE_SOURCE_DIR}/${DST_DIR})
  set(CPP_FILES "")
  set(INC_FILES "")
  #设置protoc的搜索路径
  LIST(APPEND PROTO_FLAGS -I${OUT_DIR})
  #获取需要编译的proto文件
  file(GLOB_RECURSE PROTO_FILES ${OUT_DIR}/*.proto)
  foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(FIL_WE ${PROTO_FILE} NAME_WE)
    list(APPEND CPP_FILES "${OUT_DIR}/${FIL_WE}.pb.cc")
    list(APPEND INC_FILES "${OUT_DIR}/${FIL_WE}.pb.h")
    # 使用自定义命令
    add_custom_command(
      OUTPUT "${OUT_DIR}/${FIL_WE}.pb.cc" "${OUT_DIR}/${FIL_WE}.pb.h"
      COMMAND
        ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTO_FLAGS} --cpp_out=${OUT_DIR} ${PROTO_FILE}
      DEPENDS ${PROTO_FILE}
      COMMENT "Running C++ protocol buffer compiler on ${FIL_WE}"
      VERBATIM
    )
  endforeach()
  # 添加自定义target
  add_custom_target(generate_message ALL
                  DEPENDS ${CPP_FILES} ${INC_FILES}
                  COMMENT "generate message target."
                  VERBATIM
                  )
  set(${CPP_SRCS} ${CPP_FILES} PARENT_SCOPE)
  set(${INC_HDRS} ${INC_FILES} PARENT_SCOPE)
endfunction(protobuf_generate_cpp_to)
