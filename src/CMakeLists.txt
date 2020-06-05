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

set( SOURCES
  main.cpp
  cxx/memory.cpp
  cxx/trace.cpp
  cxx/tuple.cpp
  pipeline/data.cpp
  pipeline/input.cpp
  pipeline/output.cpp
  pipeline/port.cpp
  pipeline/process.cpp
  pipeline.cpp
  )

add_executable( ${PROJECT_NAME} ${SOURCES} )

message( "CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}" )

target_include_directories( ${PROJECT_NAME}
  PUBLIC ${CMAKE_SOURCE_DIR}/src )

# target_include_directories( ${PROJECT_NAME}
#   PUBLIC ${PROJECT_BINARY_DIR}/src
#   )
