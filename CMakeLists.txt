cmake_minimum_required(VERSION 3.11)
project(board)

set(CMAKE_CXX_STANDARD 14)

##root
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS RIO Net)
include(${ROOT_USE_FILE})


ROOT_GENERATE_DICTIONARY(G__board Channel.h LINKDEF)
add_library(boardROOT SHARED Channel.cxx Channel_cxx_ACLiC_dict_rdict.pcm)
target_link_libraries(boardROOT ${ROOT_LIBRARIES})




include_directories(
        .
        ~/root/include/
)



add_executable(board
        Channel.cxx
        AnalysisManager.cxx
        AnalysisManager.h
        Parameters.h)

target_link_libraries(board boardROOT)
