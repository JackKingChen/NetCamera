cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_STANDARD 14)

# now we use STATIC lib, so let's remove WEBRTC_EXPORT and WEBRTC_DLL
#if(WIN32)
#    add_definitions(-DWEBRTC_DLL)
#endif(WIN32)

include_directories(../src)
add_executable(test_vad_00 test_00/test_00.cpp)

if(WIN32)
        target_link_libraries(test_vad_00 vad)
else(WIN32)
        target_link_libraries(test_vad_00 vad pthread)
endif(WIN32)


