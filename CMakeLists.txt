cmake_minimum_required(VERSION 3.15)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(darknet)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})

set(CUDA_LIB_PATH "/usr/local/cuda/lib64")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread -L ${CUDA_LIB_PATH}")
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -gencode arch=compute_75,code=compute_75")
set(LIB_STATIC_NAME "${PROJECT_NAME}-static")
set(LIB_DYNAMIC_NAME "${PROJECT_NAME}-dynamic")

add_compile_definitions(GPU CUDNN)

find_package(CUDA REQUIRED)
set(CUDA_LIBS "${CUDA_LIBRARIES};cublas;cudnn;curand;cudart")

find_package(OpenSSL REQUIRED)

set(LIB_SOURCE_FILES
        src/activation_layer.c
        src/activations.c
        src/avgpool_layer.c
        src/batchnorm_layer.c
        src/blas.c
        src/box.c
        src/col2im.c
        src/connected_layer.c
        src/convolutional_layer.c
        src/cost_layer.c
        src/crnn_layer.c
        src/crop_layer.c
        src/cuda.c
        src/data.c
        src/deconvolutional_layer.c
        src/demo.c
        src/detection_layer.c
        src/dropout_layer.c
        src/gemm.c
        src/gru_layer.c
        src/im2col.c
        src/image.c
        src/image_opencv.cpp
        src/iseg_layer.c
        src/l2norm_layer.c
        src/layer.c
        src/list.c
        src/local_layer.c
        src/logistic_layer.c
        src/lstm_layer.c
        src/matrix.c
        src/maxpool_layer.c
        src/network.c
        src/normalization_layer.c
        src/option_list.c
        src/parser.c
        src/region_layer.c
        src/reorg_layer.c
        src/rnn_layer.c
        src/route_layer.c
        src/shortcut_layer.c
        src/softmax_layer.c
        src/tree.c
        src/upsample_layer.c
        src/utils.c
        src/yolo_layer.c
        )

set(EXE_SOURCE_FILES
        examples/art.c
        examples/captcha.c
        examples/cifar.c
        examples/classifier.c
        examples/coco.c
        examples/darknet.c
        examples/detector.c
        examples/go.c
        examples/instance-segmenter.c
        examples/lsd.c
        examples/nightmare.c
        examples/regressor.c
        examples/rnn.c
        examples/segmenter.c
        examples/super.c
        examples/tag.c
        examples/yolo.c)

set(CUDA_SOURCE_FILES
        src/activation_kernels.cu
        src/avgpool_layer_kernels.cu
        src/blas_kernels.cu
        src/col2im_kernels.cu
        src/convolutional_kernels.cu
        src/crop_layer_kernels.cu
        src/deconvolutional_kernels.cu
        src/dropout_layer_kernels.cu
        src/im2col_kernels.cu
        src/maxpool_layer_kernels.cu
        )

set(INCLUDE_DIRS include src /usr/local/cuda/include)
include_directories(${INCLUDE_DIRS})
cuda_include_directories(${INCLUDE_DIRS})

cuda_add_library(${LIB_STATIC_NAME} STATIC ${LIB_SOURCE_FILES} ${CUDA_SOURCE_FILES} OPTIONS ${CUDA_NVCC_FLAGS})
#cuda_add_library(${LIB_DYNAMIC_NAME} SHARED ${LIB_SOURCE_FILES} ${CUDA_SOURCE_FILES} OPTIONS ${CUDA_NVCC_FLAGS})

add_executable(${PROJECT_NAME} ${EXE_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LIB_STATIC_NAME} ${CUDA_LIBS})

add_executable(chkweights examples/check_weights.cpp)
target_link_libraries(chkweights ${LIB_STATIC_NAME} ${CUDA_LIBS} OpenSSL::SSL)
