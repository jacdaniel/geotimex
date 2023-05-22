# CMakeList.txt : projet CMake pour geotimex, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

set (TOOL_CHAIN_PATH "d:/JACK2/TOOLCHAIN")
set (FFTW3_PATH ${TOOL_CHAIN_PATH}/fftw3)

set (FFTW3_INCLUDE ${FFTW3_PATH}/include/)
set (FFTW3_LIBRARIES ${FFTW3_PATH}/lib64/)
SET(FFTW3_FULLLIBS ${FFTW3_LIBRARIES}/libfftw3-3.lib)
SET(FFTW3_LIBS libfftw3-3.lib)




set(GEOTIMEX_INCLUDES 
			${CMAKE_CURRENT_SOURCE_DIR}/src/geotimeUtil
			${CMAKE_CURRENT_SOURCE_DIR}/src/dataUtil
			${CMAKE_CURRENT_SOURCE_DIR}/src/solver
			${CMAKE_CURRENT_SOURCE_DIR}/src/solver/poisson
			${CMAKE_CURRENT_SOURCE_DIR}/src/solver/poisson/fftPoisson

			${CMAKE_CURRENT_SOURCE_DIR}/src/operators

			${CMAKE_CURRENT_SOURCE_DIR}/src/debugIO
			${CMAKE_CURRENT_SOURCE_DIR}/test/src
			${CMAKE_CURRENT_SOURCE_DIR}/test/src/laplacian
			${CMAKE_CURRENT_SOURCE_DIR}/test/src/geotime
			${CMAKE_CURRENT_SOURCE_DIR}/test/src/geotime/reconstruction
			 )

# set (FFTW3_INCLUDE "d:/JACK2/TOOLCHAIN/fftw3/include/)



MESSAGE("ok")
MESSAGE( ${TOOL_CHAIN_PATH})
MESSAGE (${FFTW3_INCLUDE})


project ("geotimex")

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
 "src/operators/operatorNablaT.cpp" "src/operators/operatorNablaT.h" "src/operators/operatorNablaT.hpp"  "src/debugIO/debugIO.hpp" "src/solver/solverUtil.h" "src/dataUtil/flagUtil.h" "src/solver/poisson/poissonSolver.cpp" "src/solver/poisson/poissonSolver.h" "src/solver/poisson/fftPoisson/fftPoissonSolver.cpp" "src/solver/poisson/fftPoisson/fftPoissonSolverCPU.h")


MESSAGE("ok2")
MESSAGE(${FFTW3_LIBRARIES})
MESSAGE(${FFTW3_FULLLIBS})

target_include_directories("geotimex" PRIVATE ${GEOTIMEX_INCLUDES} ${FFTW3_INCLUDE} )
link_directories(${FFTW3_LIBRARIES})
target_link_libraries("geotimex" PRIVATE ${FFTW3_FULLLIBS} )
# target_link_libraries("geotimex" ${FFTW3_FULLLIBS} )



# TODO: Ajoutez des tests et installez des cibles si nécessaire.


