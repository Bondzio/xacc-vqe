#find_package(MPI)
#if (MPI_FOUND) 
#   set(BOOST_ROOT ${XACC_ROOT})
#   find_package(Boost COMPONENTS filesystem program_options system mpi)
#   if (Boost_FOUND) 
#      message (STATUS "We have Boost with MPI Support")
#      include_directories(${MPI_CXX_INCLUDE_PATH})
#      add_subdirectory(boost-mpi)
#   endif()
#endif()
add_subdirectory(no-mpi)
install(FILES MPIProvider.hpp DESTINATION ${CMAKE_INSTALL_PREFIX}/include/vqe)
