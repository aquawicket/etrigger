#################################
####       LibResample       ####
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

PROJECT( LibResample )

INCLUDE_DIRECTORIES( ${LibResample_SOURCE_DIR})

##-------------------------------------------------
## libresample.lib
##-------------------------------------------------
SET(libresample_SRCS 
include/libresample.h
src/configtemplate.h
src/filterkit.c
src/filterkit.h
src/resample.c
src/resample_defs.h
src/resamplesubs.c
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

   	SET(EXECUTABLE_OUTPUT_PATH ${LibResample_SOURCE_DIR}/../../_WIN32
            CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${LibResample_SOURCE_DIR}/../../_WIN32
            CACHE PATH "Single output directory for building all libraries.")

	ADD_DEFINITIONS(-DWIN32)
	
	INCLUDE_DIRECTORIES(${LibResample_SOURCE_DIR}/include )
	INCLUDE_DIRECTORIES(${LibResample_SOURCE_DIR}/src )
	
	##-------- libresample ----------------------------------------------------------------
	ADD_LIBRARY(lib-resample STATIC ${libresample_SRCS})
	SET_TARGET_PROPERTIES(lib-resample PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME libresample DEBUG_OUTPUT_NAME libresample_d)  
	##---------------------------------------------------------------------------------

ENDIF(WIN32)
##--------------------------------------------

    


##----------------------------------------
##        ##### MAC #####
##----------------------------------------
IF (APPLE)

	MESSAGE("Detected MAC environment")

	SET(EXECUTABLE_OUTPUT_PATH ${LibResample_SOURCE_DIR}/../../_MAC
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${LibResample_SOURCE_DIR}/../../_MAC
		CACHE PATH "Single output directory for building all libraries.")

	ADD_DEFINITIONS(-DMAC)

	INCLUDE_DIRECTORIES(${LibResample_SOURCE_DIR}/include )
	INCLUDE_DIRECTORIES(${LibResample_SOURCE_DIR}/src )
	
	##-------- libresample ----------------------------------------------------------------
	ADD_LIBRARY(lib-resample STATIC ${libresample_SRCS})
	SET_TARGET_PROPERTIES(lib-resample PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME libresample DEBUG_OUTPUT_NAME libresample_d)  
	##-------------------------------------------------------------------------------------

ENDIF (APPLE)
##--------------------------------------------





##----------------------------------------
##        ##### LINUX #####
##----------------------------------------
IF (UNIX)
IF (!APPLE)

	MESSAGE("Detected LINUX environment")

	SET(EXECUTABLE_OUTPUT_PATH ${LibResample_SOURCE_DIR}/../../_LINUX
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${LibResample_SOURCE_DIR}/../../_LINUX
		CACHE PATH "Single output directory for building all libraries.")

	ADD_DEFINITIONS(-DLINUX)

	INCLUDE_DIRECTORIES(${LibResample_SOURCE_DIR}/include )
	INCLUDE_DIRECTORIES(${LibResample_SOURCE_DIR}/src )
	
	##-------- libresample ----------------------------------------------------------------
	ADD_LIBRARY(lib-resample STATIC ${libresample_SRCS})
	SET_TARGET_PROPERTIES(lib-resample PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME libresample DEBUG_OUTPUT_NAME libresample_d)  
	##-------------------------------------------------------------------------------------

ENDIF (!APPLE)
ENDIF (UNIX)
##--------------------------------------------