# CMakeList.txt: j2nodejs-12 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("j2nodejs-12")

add_library(j2nodejs-12 SHARED "j2nodejs-12.cpp" "j2nodejs-12.h" "node_code_cache_stub.cc" "node_snapshot_stub.cc")

# TODO: 如有需要，请添加测试并安装目标。
include_directories("${JDK_DIR}/include/")

message("${NODE_DIR}")

include_directories("${NODE_DIR}/deps/v8/include")

include_directories("${NODE_DIR}/deps/uv/include")
include_directories("${NODE_DIR}/deps/uv/src")
include_directories("${NODE_DIR}/src")
include_directories("${NODE_DIR}/deps/histogram/src")
include_directories("${NODE_DIR}/deps/uvwasi/src")
include_directories("${NODE_DIR}/deps/icu-small/source/i18n")
include_directories("${NODE_DIR}/deps/icu-small/source/common")
include_directories("${NODE_DIR}/deps/zlib")
include_directories("${NODE_DIR}/deps/llhttp/include")
include_directories("${NODE_DIR}/deps/cares/include")
include_directories("${NODE_DIR}/deps/nghttp2/lib/includes")
include_directories("${NODE_DIR}/deps/brotli/c/include")
include_directories("${NODE_DIR}/deps/openssl/openssl/include")
include_directories("${NODE_DIR}/deps/ngtcp2")
include_directories("${NODE_DIR}/deps/ngtcp2/ngtcp2/lib/includes")
include_directories("${NODE_DIR}/deps/ngtcp2/ngtcp2/crypto/includes")
include_directories("${NODE_DIR}/deps/ngtcp2/nghttp3/lib/includes")


# 将源代码添加到此项目的可执行文件。
#add_executable (j2nodejs-12 "j2nodejs-12.cpp" "j2nodejs-12.h" "node_code_cache_stub.cc" "node_snapshot_stub.cc")
#add_executable (j2nodejs-12 "embedtest.cc" "node_code_cache_stub.cc" "node_snapshot_stub.cc")
# TODO: 如有需要，请添加测试并安装目标。
IF(${IS_WINDOWS})
	message("windows")
	set(CMAKE_CXX_FLAGS_RELEASE "/MT")
	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

	include_directories("${JDK_DIR}/include/win32")
	include_directories("${NODE_DIR}/deps/v8/src")

	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/brotli.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/cares.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/histogram.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/http_parser.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/icudata.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/icui18n.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/icustubdata.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/icutools.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/icuucx.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/libnode.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/libuv.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/llhttp.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/nghttp2.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/openssl.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/torque_base.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/uvwasi.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/v8_base_without_compiler.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/v8_compiler.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/v8_init.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/v8_initializers.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/v8_libbase.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/v8_libplatform.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/v8_libsampler.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/v8_nosnapshot.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/v8_snapshot.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/lib/zlib.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/torque.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/bytecode_builtins_list_generator.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "Dbghelp.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "winmm.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "Ws2_32.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "iphlpapi.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "psapi.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "shell32.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "userenv.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "AdvAPI32.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "User32.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "ws2_32.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "gdi32.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "advapi32.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "crypt32.lib")
	target_link_libraries(j2nodejs-12 PUBLIC "user32.lib")

else()

	message("linux")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--start-group -ldl -pthread")
	add_definitions(-std=c++14)

	include_directories("${JDK_DIR}/include/linux")
	include_directories("${NODE_DIR}/out/Release/obj/gen/generate-bytecode-output-root")
	include_directories("${NODE_DIR}/out/Release/obj/gen/inspector-generated-output-root")
	include_directories("${NODE_DIR}/out/Release/obj/gen/torque-output-root")
	include_directories("${NODE_DIR}/out/Release/obj/gen")
	include_directories("${NODE_DIR}/deps/v8")
	include_directories("/usr/include")

	#target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/deps/zlib/libzlib.a")

	#target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/deps/uv/libuv.a")

	#target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/v8_gypfiles/libv8_snapshot.a")

	#target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/deps/openssl/libopenssl.a")
	
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/libnode.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/deps/histogram/libhistogram.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/deps/uvwasi/libuvwasi.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/v8_gypfiles/libv8_libplatform.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/icu/libicui18n.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/deps/zlib/libzlib.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/deps/http_parser/libhttp_parser.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/deps/llhttp/libllhttp.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/deps/cares/libcares.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/deps/uv/libuv.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/deps/nghttp2/libnghttp2.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/deps/brotli/libbrotli.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/deps/openssl/libopenssl.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/v8_gypfiles/libv8_base_without_compiler.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/icu/libicuucx.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/icu/libicudata.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/icu/libicustubdata.a")

	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/v8_gypfiles/libv8_libbase.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/v8_gypfiles/libv8_libsampler.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/v8_gypfiles/libv8_compiler.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/v8_gypfiles/libv8_snapshot.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/v8_gypfiles/libv8_initializers.a")

	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/libnode_text_start.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/v8_gypfiles/libv8_nosnapshot.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/v8_gypfiles/libv8_init.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.target/tools/v8_gypfiles/libtorque_base.a")
	target_link_libraries(j2nodejs-12 PUBLIC "${NODE_DIR}/out/Release/obj.host/tools/icu/libicutools.a")

	
endif()