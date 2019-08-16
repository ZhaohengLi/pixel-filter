cmake_minimum_required(VERSION 3.13)
project(CVProjectV1_0)

set(CMAKE_CXX_STANDARD 14)


find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(CVProjectV1_0 main.cpp rectBlur.cpp rectBlur.h faceDetect.cpp faceDetect.h facedetectcnn-floatdata.cpp facedetectcnn.h facedetectcnn-int8data.cpp facedetectcnn-model.cpp facedetectcnn.cpp)

target_link_libraries(CVProjectV1_0  ${OpenCV_LIBS})
