# Install script for directory: /Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/lib/libassimp.a")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.a")
    EXECUTE_PROCESS(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.a")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264-dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/anim.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/ai_assert.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/camera.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/color4.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/color4.inl"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/config.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/defs.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/cfileio.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/light.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/material.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/material.inl"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/matrix3x3.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/matrix3x3.inl"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/matrix4x4.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/matrix4x4.inl"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/mesh.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/postprocess.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/quaternion.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/quaternion.inl"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/scene.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/texture.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/types.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/vector2.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/vector2.inl"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/vector3.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/vector3.inl"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/version.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/cimport.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/importerdesc.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/Importer.hpp"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/DefaultLogger.hpp"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/ProgressHandler.hpp"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/IOStream.hpp"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/IOSystem.hpp"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/Logger.hpp"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/LogStream.hpp"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/NullLogger.hpp"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/cexport.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/Exporter.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264-dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264-dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/Compiler/pushpack1.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/../include/assimp/Compiler/poppack1.h"
    "/Users/pp/projects/eoe/code/assimp--3.0.1270-source-only/code/pstdint.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264-dev")

