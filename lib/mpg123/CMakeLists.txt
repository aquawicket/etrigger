#################################
####         Mpg123          ####
#################################

###### Supported Compilers ######
#
# Visual Studio 8 2005
# Visual Studio 9 2008
# Visual Studio 10 2010
# Xcode
# KDevelop 3.5


cmake_minimum_required(VERSION 2.4)

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

SET(CMAKE_FIND_LIBRARY_PREFIXES "")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
SET(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )

PROJECT( Mpg123 )

INCLUDE_DIRECTORIES( ${Mpg123_SOURCE_DIR} )

##-------------------------------------------------
##  libmpg123.lib
##-------------------------------------------------
SET(mpg123_SRCS
ports/MSVC++/config.h
ports/MSVC++/mpg123.h
ports/MSVC++/msvc.c
src/libmpg123/compat.c
src/libmpg123/compat.h
src/libmpg123/dct36_3dnow.S
src/libmpg123/dct36_3dnowext.S
src/libmpg123/dct64.c
src/libmpg123/dct64_3dnow.S
src/libmpg123/dct64_3dnowext.S
src/libmpg123/dct64_mmx.S
src/libmpg123/dct64_sse.S
src/libmpg123/dct64_sse_float.S
src/libmpg123/dct64_x86_64.S
src/libmpg123/dct64_x86_64_float.S
src/libmpg123/debug.h
src/libmpg123/decode.h
src/libmpg123/equalizer.c
src/libmpg123/equalizer_3dnow.S
src/libmpg123/format.c
src/libmpg123/frame.c
src/libmpg123/frame.h
src/libmpg123/getbits.h
src/libmpg123/getcpuflags.h
src/libmpg123/getcpuflags.S
src/libmpg123/huffman.h
src/libmpg123/icy.c
src/libmpg123/icy.h
src/libmpg123/icy2utf8.c
src/libmpg123/icy2utf8.h
src/libmpg123/id3.c
src/libmpg123/id3.h
src/libmpg123/index.c
src/libmpg123/index.h
src/libmpg123/l2tables.h
src/libmpg123/layer1.c
src/libmpg123/layer2.c
src/libmpg123/layer3.c
src/libmpg123/libmpg123.c
src/libmpg123/mangle.h
src/libmpg123/mpg123.h.in
src/libmpg123/mpg123lib_intern.h
src/libmpg123/ntom.c
src/libmpg123/optimize.c
src/libmpg123/optimize.h
src/libmpg123/parse.c
src/libmpg123/parse.h
src/libmpg123/reader.h
src/libmpg123/readers.c
src/libmpg123/sample.h
src/libmpg123/stringbuf.c
src/libmpg123/synth.c
src/libmpg123/synth.h
src/libmpg123/synth_3dnow.S
src/libmpg123/synth_3dnowext.S
src/libmpg123/synth_8bit.c
src/libmpg123/synth_i586.S
src/libmpg123/synth_i586_dither.S
src/libmpg123/synth_mmx.S
src/libmpg123/synth_real.c
src/libmpg123/synth_s32.c
src/libmpg123/synth_sse.S
src/libmpg123/synth_sse_accurate.S
src/libmpg123/synth_sse_float.S
src/libmpg123/synth_sse_s32.S
src/libmpg123/synth_stereo_sse_accurate.S
src/libmpg123/synth_stereo_sse_float.S
src/libmpg123/synth_stereo_sse_s32.S
src/libmpg123/synth_stereo_x86_64.S
src/libmpg123/synth_stereo_x86_64_accurate.S
src/libmpg123/synth_stereo_x86_64_float.S
src/libmpg123/synth_stereo_x86_64_s32.S
src/libmpg123/synth_x86_64.S
src/libmpg123/synth_x86_64_accurate.S
src/libmpg123/synth_x86_64_float.S
src/libmpg123/synth_x86_64_s32.S
src/libmpg123/tabinit.c
src/libmpg123/tabinit_mmx.S
src/libmpg123/true.h
)
   
##--------------------------------------------------
##       ###### WINDOWS ######
##--------------------------------------------------
IF(WIN32)
   	
	MESSAGE("Detected WINDOWS environment")

	IF(CMAKE_CXX_COMPILER MATCHES cl)

	##### Microsoft Visual Studio 2005 options #####
	IF(CMAKE_GENERATOR STREQUAL "Visual Studio 8 2005")
		SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy /Wp64")
		SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od /EHsc /Wp64")
		SET(CMAKE_CXX_FLAGS_RELEASE "/MT /Z7 /DEBUG /O2 /EHsc /bigobj /Wp64")
		SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2 /EHsc /Wp64")
		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od /EHsc /Wp64")
			
		### Use precompiled Headers ###
		#SET_SOURCE_FILES_PROPERTIES(stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 8 2005")

	##### Microsoft Visual Studio 2008 options #####
	IF(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")
        	SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
        	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od /EHsc")
        	SET(CMAKE_CXX_FLAGS_RELEASE "/MT /Z7 /DEBUG /O2 /EHsc /bigobj")
       		SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2 /EHsc")
       		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od /EHsc")

		### Use precompiled Headers ###
		#SET_SOURCE_FILES_PROPERTIES(stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")

	##### Microsoft Visual Studio 2010 options #####
	IF(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
        	SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
        	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od /EHsc")
        	SET(CMAKE_CXX_FLAGS_RELEASE "/MT /Z7 /DEBUG /O2 /EHsc /bigobj")
       		SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2 /EHsc")
       		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od /EHsc")

		### Use precompiled Headers ###
		#SET_SOURCE_FILES_PROPERTIES(stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
	
	ENDIF(CMAKE_CXX_COMPILER MATCHES cl)

   	SET(EXECUTABLE_OUTPUT_PATH ${Mpg123_SOURCE_DIR}/../../_WIN32
            CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${Mpg123_SOURCE_DIR}/../../_WIN32
            CACHE PATH "Single output directory for building all libraries.")

	ADD_DEFINITIONS(-DWIN32)
	ADD_DEFINITIONS(-DACCURATE_ROUNDING)
	ADD_DEFINITIONS(-DIEEE_FLOAT)
	ADD_DEFINITIONS(-DOPT_GENERIC)

	INCLUDE_DIRECTORIES(${Mpg123_SOURCE_DIR}/src/libmpg123 )
	INCLUDE_DIRECTORIES(${Mpg123_SOURCE_DIR}/ports/MSVC++ )

	##-------- mpg123 -------------------------------------------------------------------
	ADD_LIBRARY(lib-mpg123 STATIC ${mpg123_SRCS})
	SET_TARGET_PROPERTIES(lib-mpg123 PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME libmpg123 DEBUG_OUTPUT_NAME libmpg123_d)  
	##-------------------------------------------------------------------------------------

ENDIF(WIN32)
##--------------------------------------------

    


##----------------------------------------
##        ##### MAC #####
##----------------------------------------
IF (APPLE)

	MESSAGE("Detected MAC environment")

	SET(EXECUTABLE_OUTPUT_PATH ${Mpg123_SOURCE_DIR}/../../_MAC
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${Mpg123_SOURCE_DIR}/../../_MAC
		CACHE PATH "Single output directory for building all libraries.")

	ADD_DEFINITIONS(-DMAC)
	ADD_DEFINITIONS(-DACCURATE_ROUNDING)
	ADD_DEFINITIONS(-DIEEE_FLOAT)
	ADD_DEFINITIONS(-DOPT_GENERIC)

	INCLUDE_DIRECTORIES(${Mpg123_SOURCE_DIR}/src/libmpg123 )
	
	##-------- mpg123 -------------------------------------------------------------------
	ADD_LIBRARY(lib-mpg123 STATIC ${mpg123_SRCS})
	SET_TARGET_PROPERTIES(lib-mpg123 PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME libmpg123 DEBUG_OUTPUT_NAME libmpg123_d)  
	##-------------------------------------------------------------------------------------

ENDIF (APPLE)
##--------------------------------------------





##----------------------------------------
##        ##### LINUX #####
##----------------------------------------
IF (UNIX)
IF (!APPLE)

	MESSAGE("Detected LINUX environment")

	SET(EXECUTABLE_OUTPUT_PATH ${Mpg123_SOURCE_DIR}/../../_LINUX
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${Mpg123_SOURCE_DIR}/../../_LINUX
		CACHE PATH "Single output directory for building all libraries.")

	ADD_DEFINITIONS(-DLINUX)

	INCLUDE_DIRECTORIES(${Mpg123_SOURCE_DIR}/src/libmpg123 )
	
	##-------- mpg123 -------------------------------------------------------------------
	ADD_LIBRARY(lib-mpg123 STATIC ${mpg123_SRCS})
	SET_TARGET_PROPERTIES(lib-mpg123 PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME libmpg123 DEBUG_OUTPUT_NAME libmpg123_d)  
	##-------------------------------------------------------------------------------------
	
ENDIF (!APPLE)
ENDIF (UNIX)
##--------------------------------------------
