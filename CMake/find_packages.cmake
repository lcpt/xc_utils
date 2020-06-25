MESSAGE(STATUS "************* find packages begins ****************")
find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(MySQL REQUIRED)
find_package(VTK REQUIRED)
find_package(GTK2 REQUIRED)
find_package(CGAL REQUIRED COMPONENTS Qt5 Core)
find_package(GNUGTS REQUIRED)
find_package(CImg REQUIRED)
find_package(Plot REQUIRED)
find_package(GLIB2 REQUIRED)
find_package(Python COMPONENTS Interpreter Development)
# find_package(PythonInterp)
# find_package(PythonLibs REQUIRED)
# find_package(PythonInterp REQUIRED)
find_package(Boost 1.62 REQUIRED)
if(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
  SET(Boost_USE_STATIC_LIBS OFF)
  SET(Boost_USE_MULTITHREADED ON)
  SET(Boost_USE_STATIC_RUNTIME OFF)
  SET(Boost_DETAILED_FAILURE_MSG ON)
  if (PYTHON_VERSION_MAJOR EQUAL 3)
     find_package(Boost COMPONENTS python${PYTHON_VERSION_SUFFIX})
     find_package(PythonInterp 3)
     find_package(PythonLibs 3 REQUIRED)
  else()
     find_package(Boost COMPONENTS python)
     find_package(PythonInterp)
     find_package(PythonLibs REQUIRED)
  endif()
  set(XC_UTILS_BOOST_PYTHON_LIBRARIES ${Boost_LIBRARIES})
  find_package(Boost COMPONENTS system regex filesystem thread math_c99 math_c99f math_c99l math_tr1 math_tr1f math_tr1l REQUIRED)
elseif(NOT Boost_FOUND)
  MESSAGE(FATAL_ERROR "Unable to find correct Boost version. Did you set BOOST_ROOT?")
endif()
message(STATUS "PYTHON_LIBRARIES = ${PYTHON_LIBRARIES}")
message(STATUS "PYTHON_EXECUTABLE = ${PYTHON_EXECUTABLE}")
message(STATUS "PYTHON_INCLUDE_DIRS = ${PYTHON_INCLUDE_DIRS}")
find_package(Gnuplot REQUIRED)
find_package(MPFR)
find_package(GMP)
find_package(SQLITE3 REQUIRED)
find_package(ExecInfo)
find_package(MPI REQUIRED)
find_package(OpenMP REQUIRED)
MESSAGE(STATUS "************* find packages ends ****************")


