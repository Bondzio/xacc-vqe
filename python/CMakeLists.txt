find_package(PythonLibs)

if(PythonLibs_FOUND)
include_directories(${CMAKE_SOURCE_DIR}/tpls/pybind11/include)
include_directories(${PYTHON_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/task/tasks)

link_directories(${XACC_LIBRARY_DIR})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -O2 -g -pipe -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wformat -fexceptions -fstack-protector-strong --param=ssp-buffer-size=4 -grecord-gcc-switches -m64 -mtune=generic -D_GNU_SOURCE -fPIC -fwrapv")

if(APPLE)
   set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
endif(APPLE)

add_library(pyxaccvqe SHARED xacc-vqe-py.cpp)
SET_TARGET_PROPERTIES(pyxaccvqe PROPERTIES PREFIX "")
# do not mess with the ordering of libraries here!
target_link_libraries(pyxaccvqe ${PYTHON_LIBRARY} xacc-vqe-tasks ${XACC_LIBRARIES} ${Boost_LIBRARIES})
install(TARGETS pyxaccvqe DESTINATION ${XACC_ROOT}/lib/python)
endif()

