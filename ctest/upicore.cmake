#
# This file is part of upicore.
#
# upicore is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# upicore is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with upicore.  If not, see <https://www.gnu.org/licenses/>.
#

##
## PROJECT LAYOUT
##

set( PRJ_NAME "upicore" )

set( PRJ_ROOT_DIR "$ENV{HOME}/shared/dev" )

set( PRJ_SOURCE_DIR "${PRJ_ROOT_DIR}/source" )
set( PRJ_BUILD_DIR "${PRJ_ROOT_DIR}/build" )
set( PRJ_INSTALL_DIR "${PRJ_ROOT_DIR}/install" )

##
## BUILD CONFIGURATION.
##

set( PARALLEL_LEVEL 4 )

set( CTEST_BUILD_CONFIGURATION "Debug")
# set( CTEST_BUILD_CONFIGURATION "RelWithDebInfo")
# set( CTEST_BUILD_CONFIGURATION "Release")

set( BUILD_SUFFIX "" )
# set( BUILD_SUFFIX "-gcc" )
# set( BUILD_SUFFIX "-clang" )

set( CTEST_CMAKE_GENERATOR  "Unix Makefiles" )
set( CTEST_CMAKE_COMMAND "cmake" )
set( CTEST_BUILD_COMMAND "/usr/bin/make -j4 -k install" )
set( CTEST_SITE "tux-family" )
set( CTEST_BUILD_NAME "Debian-10.3_x86_64_${CTEST_BUILD_CONFIGURATION}${BUILD_SUFFIX}")

# set( CTEST_GIT_COMMAND "/usr/bin/git")
# set( CTEST_GIT_UPDATE_OPTIONS "")

set( CTEST_SOURCE_DIRECTORY "${PRJ_SOURCE_DIR}/${PRJ_NAME}")
set( CTEST_BINARY_DIRECTORY "${PRJ_BUILD_DIR}/${PRJ_NAME}-${CTEST_BUILD_CONFIGURATION}${BUILD_SUFFIX}")

# set( CTEST_USE_LAUNCHERS ON )
set( CTEST_USE_LAUNCHERS OFF )

set( PRJ_INSTALL_PREFIX "{PRJ_INSTALL_DIR}/${PRJ_NAME}-${CTEST_BUILD_CONFIGURATION}${BUILD_SUFFIX}")

set( PRJ_INITIAL_CACHE "
BUILDNAME:STRING=${CTEST_BUILD_NAME}
SITE:STRING=${CTEST_SITE}

CMAKE_BUILD_TYPE:STRING=${CTEST_BUILD_CONFIGURATION}

CMAKE_C_FLAGS:STRING+= -Wall -Wextra -Wshadow
CMAKE_CXX_FLAGS:STRING+= -Wall -Wextra -Wshadow

# CMAKE_C_COMPILER=/usr/bin/gcc-7
# CMAKE_CXX_COMPILER=/usr/bin/g++-7

# CMAKE_C_COMPILER=/usr/bin/clang
# CMAKE_CXX_COMPILER=/usr/bin/clang++

# Instrumentation
# CMAKE_C_FLAGS_RELWITHDEBINFO:STRING+= -fsanitize=address,undefined -fno-omit-frame-pointer
# CMAKE_CXX_FLAGS_RELWITHDEBINFO:STRING+=  -fsanitize=address,undefined -fno-omit-frame-pointer

CMAKE_INSTALL_PREFIX:STRING=${PRJ_INSTALL_PREFIX}
")

set( CTEST_NOTES_FILES
  ${CTEST_SCRIPT_DIRECTORY}/${CTEST_SCRIPT_NAME}
  ${CTEST_BINARY_DIRECTORY}/CMakeCache.txt
)

execute_process( COMMAND ${CTEST_CMAKE_COMMAND} -E remove_directory ${PRJ_INSTALL_PREFIX} )
execute_process( COMMAND ${CTEST_CMAKE_COMMAND} -E make_directory ${PRJ_INSTALL_PREFIX} )
ctest_empty_binary_directory( ${CTEST_BINARY_DIRECTORY} )

ctest_start( Experimental )
# ctest_update(SOURCE "${CTEST_SOURCE_DIRECTORY}")
file( WRITE "${CTEST_BINARY_DIRECTORY}/CMakeCache.txt" ${PRJ_INITIAL_CACHE} )
ctest_configure( BUILD "${CTEST_BINARY_DIRECTORY}" )
ctest_read_custom_files( ${CTEST_BINARY_DIRECTORY} )
ctest_build( BUILD "${CTEST_BINARY_DIRECTORY}" )
ctest_test( BUILD "${CTEST_BINARY_DIRECTORY}" PARALLEL_LEVEL ${PARALLEL_LEVEL} )
# ctest_submit()
