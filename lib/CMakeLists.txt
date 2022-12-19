add_library(file_list FileList.cpp)
target_include_directories(file_list PUBLIC
                          "${PROJECT_SOURCE_DIR}/lib/include")