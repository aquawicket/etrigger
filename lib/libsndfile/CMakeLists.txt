#################################
####        libsndfile       ####
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

PROJECT( LibSndFile )

INCLUDE_DIRECTORIES( ${LibSndFile_SOURCE_DIR})

##-------------------------------------------------
## LibSndFile.lib
##-------------------------------------------------
SET(LibSndFile_SRCS 
Win32/config.h
Win32/sndfile.h
src/sndfile.c
src/flac.c
src/file_io.c
src/dwvw.c
src/dwd.c
src/double64.c
src/dither.c
src/common.c
src/command.c
src/caf.c
src/broadcast.c
src/avr.c
src/au.c
src/alaw.c
src/aiff.c
src/GSM610/table.c
src/GSM610/short_term.c
src/GSM610/rpe.c
src/GSM610/preprocess.c
src/GSM610/lpc.c
src/GSM610/long_term.c
src/GSM610/gsm_option.c
src/GSM610/gsm_encode.c
src/GSM610/gsm_destroy.c
src/GSM610/gsm_decode.c
src/GSM610/gsm_create.c
src/GSM610/decode.c
src/GSM610/code.c
src/GSM610/add.c
src/G72x/g72x.c
src/G72x/g723_40.c
src/G72x/g723_24.c
src/G72x/g723_16.c
src/G72x/g721.c
src/xi.c
src/wve.c
src/wav_w64.c
src/wav.c
src/w64.c
src/vox_adpcm.c
src/voc.c
src/ulaw.c
src/txw.c
src/svx.c
src/strings.c
src/sndfile.c
src/sds.c
src/sd2.c
src/rx2.c
src/raw.c
src/pvf.c
src/pcm.c
src/paf.c
src/ogg.c
src/nist.c
src/ms_adpcm.c
src/mat5.c
src/mat4.c
src/ircam.c
src/ima_adpcm.c
src/htk.c
src/gsm610.c
src/float32.c
src/g72x.c
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
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 8 2005")

	##### Microsoft Visual Studio 2008 options #####
	IF(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")
        	SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
        	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od /EHsc")
        	SET(CMAKE_CXX_FLAGS_RELEASE "/MT /Z7 /DEBUG /O2 /EHsc /bigobj")
       		SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2 /EHsc")
       		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od /EHsc")

		### Use precompiled Headers ###
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")

	##### Microsoft Visual Studio 2010 options #####
	IF(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
        	SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
        	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od /EHsc")
        	SET(CMAKE_CXX_FLAGS_RELEASE "/MT /Z7 /DEBUG /O2 /EHsc /bigobj")
       		SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2 /EHsc")
       		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od /EHsc")

		### Use precompiled Headers ###
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
	
	ENDIF(CMAKE_CXX_COMPILER MATCHES cl)

   	SET(EXECUTABLE_OUTPUT_PATH ${LibSndFile_SOURCE_DIR}/../../_WIN32
            CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${LibSndFile_SOURCE_DIR}/../../_WIN32
            CACHE PATH "Single output directory for building all libraries.")

	ADD_DEFINITIONS(-DWIN32)
	
	INCLUDE_DIRECTORIES(${LibSndFile_SOURCE_DIR}/src )
	INCLUDE_DIRECTORIES(${LibSndFile_SOURCE_DIR}/Win32 )
	
	##-------- LibSndFile ----------------------------------------------------------------
	ADD_LIBRARY(lib-SndFile STATIC ${LibSndFile_SRCS})
	SET_TARGET_PROPERTIES(lib-SndFile PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME LibSndFile DEBUG_OUTPUT_NAME LibSndFile_d)  
	##---------------------------------------------------------------------------------

ENDIF(WIN32)
##--------------------------------------------

    


##----------------------------------------
##        ##### MAC #####
##----------------------------------------
IF (APPLE)

	MESSAGE("Detected MAC environment")

	SET(EXECUTABLE_OUTPUT_PATH ${LibSndFile_SOURCE_DIR}/../../_MAC
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${LibSndFile_SOURCE_DIR}/../../_MAC
		CACHE PATH "Single output directory for building all libraries.")

	ADD_DEFINITIONS(-DMAC)

	INCLUDE_DIRECTORIES(${LibSndFile_SOURCE_DIR}/include )
	INCLUDE_DIRECTORIES(${LibSndFile_SOURCE_DIR}/src )
	
	##-------- LibSndFile ----------------------------------------------------------------
	ADD_LIBRARY(lib-SndFile STATIC ${LibSndFile_SRCS})
	SET_TARGET_PROPERTIES(lib-SndFile PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME LibSndFile DEBUG_OUTPUT_NAME LibSndFile_d)  
	##-------------------------------------------------------------------------------------

ENDIF (APPLE)
##--------------------------------------------





##----------------------------------------
##        ##### LINUX #####
##----------------------------------------
IF (UNIX)
IF (!APPLE)

	MESSAGE("Detected LINUX environment")

	SET(EXECUTABLE_OUTPUT_PATH ${LibSndFile_SOURCE_DIR}/../../_LINUX
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${LibSndFile_SOURCE_DIR}/../../_LINUX
		CACHE PATH "Single output directory for building all libraries.")

	ADD_DEFINITIONS(-DLINUX)

	INCLUDE_DIRECTORIES(${LibSndFile_SOURCE_DIR}/include )
	INCLUDE_DIRECTORIES(${LibSndFile_SOURCE_DIR}/src )
	
	##-------- LibSndFile ----------------------------------------------------------------
	ADD_LIBRARY(lib-SndFile STATIC ${LibSndFile_SRCS})
	SET_TARGET_PROPERTIES(lib-SndFile PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME LibSndFile DEBUG_OUTPUT_NAME LibSndFile_d)  
	##-------------------------------------------------------------------------------------

ENDIF (!APPLE)
ENDIF (UNIX)
##--------------------------------------------