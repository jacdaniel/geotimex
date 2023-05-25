# CMakeList.txt : projet CMake pour geotimex, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



set (TOOL_CHAIN_PATH "d:/JACK2/TOOLCHAIN")
set (FFTW3_PATH ${TOOL_CHAIN_PATH}/fftw3)

set (FFTW3_INCLUDE ${FFTW3_PATH}/include/)
set (FFTW3_LIBRARIES ${FFTW3_PATH}/lib64/)
SET(FFTW3_FULLLIBS ${FFTW3_LIBRARIES}/libfftw3-3.lib)
SET(FFTW3_LIBS libfftw3-3.lib)

MESSAGE("ok")
MESSAGE( ${TOOL_CHAIN_PATH})
MESSAGE (${FFTW3_INCLUDE})
project ("geotimex")

#find_package(OpenMP)
#if(OpenMP_CXX_FOUND)
    #target_link_libraries(geotimex PUBLIC OpenMP::OpenMP_CXX)
#endif()



# find_package(OpenMP REQUIRED)
# # target_link_libraries(geotimex PRIVATE OpenMP::OpenMP_CXX)
# # set(OpenMP_CXX_FLAGS "-Xclang -fopenmp" CACHE STRING "" FORCE)
# # set(OpenMP_C_FLAGS "-Xclang -fopenmp" CACHE STRING "" FORCE)
# set(OpenMP_LIBRARY_DIR "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/lib/x64")
# set(OpenMP_CXX_FLAGS "-Xclang -openmp" CACHE STRING "" FORCE)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
# link_directories(${OpenMP_LIBRARY_DIR})

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set(OpenMP_CXX_FLAGS "-openmp" CACHE STRING "" FORCE) # comment to set default
    message(STATUS "----------------")
    message(STATUS "OPENMP CXX_FLAGS:\n" ${OpenMP_CXX_FLAGS})
    message(STATUS "OPENMP CMAKE_EXE_LINKER_FLAGS:\n" ${OpenMP_EXE_LINKER_FLAGS})
    message(STATUS "----------------")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else(OPENMP_FOUND)
    message(FATAL_ERROR "Please set OPENMP_FOUND.")
endif(OPENMP_FOUND)



set(GEOTIMEX_INCLUDES 
			${CMAKE_CURRENT_SOURCE_DIR}/src/geotimeUtil
			${CMAKE_CURRENT_SOURCE_DIR}/src/dataUtil
			${CMAKE_CURRENT_SOURCE_DIR}/src/solver
			${CMAKE_CURRENT_SOURCE_DIR}/src/solver/poisson
			${CMAKE_CURRENT_SOURCE_DIR}/src/solver/poisson/fftPoisson
			${CMAKE_CURRENT_SOURCE_DIR}/src/solver/conjugateGradient
			${CMAKE_CURRENT_SOURCE_DIR}/src/solver/gradientDescent
			${CMAKE_CURRENT_SOURCE_DIR}/src/surfaceReconstruction
			${CMAKE_CURRENT_SOURCE_DIR}/src/dipManager
			${CMAKE_CURRENT_SOURCE_DIR}/src/operators
			${CMAKE_CURRENT_SOURCE_DIR}/src/rgtVolumic
			${CMAKE_CURRENT_SOURCE_DIR}/src/signal
			${CMAKE_CURRENT_SOURCE_DIR}/src/signal/leakyIntegration
			${CMAKE_CURRENT_SOURCE_DIR}/src/dataio
			${CMAKE_CURRENT_SOURCE_DIR}/src/dataio/xt
			${CMAKE_CURRENT_SOURCE_DIR}/src/util
			

			${CMAKE_CURRENT_SOURCE_DIR}/src/debugIO
			${CMAKE_CURRENT_SOURCE_DIR}/test/src
			${CMAKE_CURRENT_SOURCE_DIR}/test/src/laplacian
			${CMAKE_CURRENT_SOURCE_DIR}/test/src/geotime
			${CMAKE_CURRENT_SOURCE_DIR}/test/src/geotime/reconstruction
			${CMAKE_CURRENT_SOURCE_DIR}/test/src/utest
			 )

# set (FFTW3_INCLUDE "d:/JACK2/TOOLCHAIN/fftw3/include/)



# Ajoutez une source à l'exécutable de ce projet.
add_executable (geotimex 
"geotimex.cpp" 
"src/solver/solver.cpp" "src/solver/solver.h" 
"src/geotimeUtil/geotimeFlags.h"
"src/solver/poisson/fftPoisson/fftPoissonSolverCPU.cpp"  
"src/geotimeUtil/returnFlags.h"  
"src/dataUtil/dataUtil.cpp" "src/dataUtil/dataUtil.h"
"src/dataUtil/memUtil.h" 
"src/dataUtil/fftwUtil.h" "src/dataUtil/ioUtil.h" "src/dataUtil/ioUtil.cpp" 
"src/solver/poisson/fftPoisson/fftLaplacian.cpp" "src/solver/poisson/fftPoisson/fftLaplacian.h" "src/dataUtil/dataFormat.h" 
  "test/src/laplacian/testLaplacian1D.cpp" "test/src/laplacian/testLaplacian1d.h" 
 "src/debugIO/debugIO.cpp" 
 "src/operators/operatorNabla.cpp" "src/operators/operatorNabla.h" 
 "src/operators/oparatorExtract.cpp" "src/operators/operatorExtract.h" "src/operators/operatorNabla.hpp"
 "test/src/test.cpp"
 "test/src/geotime/reconstruction/testReconstruction1d.cpp" 
 "src/operators/operatorNablaT.cpp" "src/operators/operatorNablaT.h" "src/operators/operatorNablaT.hpp" 
 "src/debugIO/debugIO.hpp" "src/solver/solverUtil.h" "src/dataUtil/flagUtil.h" 
 "src/solver/poisson/poissonSolver.cpp" 
 "src/solver/poisson/poissonSolver.h" 
 "src/solver/poisson/fftPoisson/fftPoissonSolver.cpp" 
 "src/solver/poisson/fftPoisson/fftPoissonSolverCPU.h"
 "src/operators/operatorNablaT.cpp" "src/operators/operatorNablaT.h" "src/operators/operatorNablaT.hpp"  
 "src/debugIO/debugIO.hpp" "src/solver/solverUtil.h" "src/dataUtil/flagUtil.h" "src/solver/poisson/poissonSolver.cpp" 
 "src/solver/poisson/poissonSolver.h" "src/solver/poisson/fftPoisson/fftPoissonSolver.cpp"
 "src/solver/poisson/fftPoisson/fftPoissonSolverCPU.h"
 
 "test/src/utest/utConjugateGradient.cpp"
 "test/src/utest/utConjugateGradient.h" "test/src/utest/utConjugateGradientCallBack.hpp" "test/src/utest/utConjugateGradientCallBack.h" 
 "src/solver/gradientDescent/gradientDescent.h" "src/solver/gradientDescent/gradientDescent.hpp" "test/src/utest/utGradientDescent.cpp" 
 "src/solver/gradientDescent/gradientDescentCallBack.h" "test/src/utest/utGradientDescentCallBack.hpp" "test/src/utest/utGradientDescentCallBack.h"
 "test/src/geotime/reconstruction/testReconstruction2d.cpp" "src/surfaceReconstruction/surfaceReconstruction.cpp" "src/surfaceReconstruction/surfaceReconstruction.h" 
 "test/src/utest/utSurfaceReconstruction.cpp" "src/dipManager/dipManager.cpp" "src/dipManager/dipManager.h" "src/rgtVolumic/rgtVolumic.cpp" 
 "src/rgtVolumic/rgtVolumic.hpp" "src/rgtVolumic/rgtVolumicConjugateGradientCallBack.h" "src/rgtVolumic/rgtVolumicConjugateGradientCallBack.hpp" 
 "test/src/utest/utRgtVolumic3d.h" "test/src/utest/utRgtVolumic3d.cpp"
 "src/signal/leakyIntegration/leakyIntegration.h" "src/operators/operatorInsert.cpp" "src/dataio/xt/xt.cpp" "src/dataio/xt/xt.h" "test/src/utest/utXt.cpp" "test/src/utest/utXt.h" "test/src/utest/utRgtVolumic2d.cpp" "test/src/utest/utRgtVolumic2d.h" "src/solver/solverCallback.h" "src/solver/solverCallBack.hpp"   "src/signal/dataThreshold.hpp" "src/util/stringUtil.h" "src/util/stringUtil.cpp" "src/util/voxel.cpp" "src/util/voxel.h" "src/util/constraint.h" "src/util/constraint.cpp")


MESSAGE("ok2")
MESSAGE(${FFTW3_LIBRARIES})
MESSAGE(${FFTW3_FULLLIBS})

target_include_directories("geotimex" PRIVATE ${GEOTIMEX_INCLUDES} ${FFTW3_INCLUDE} )
link_directories(${FFTW3_LIBRARIES})
target_link_libraries("geotimex" PRIVATE ${FFTW3_FULLLIBS}  )
# target_link_libraries("geotimex" ${FFTW3_FULLLIBS} )



# TODO: Ajoutez des tests et installez des cibles si nécessaire.


