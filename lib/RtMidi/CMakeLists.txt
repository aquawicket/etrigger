#################################
####       RtMidi           ####
#################################

cmake_minimum_required(VERSION 2.4)

SET(CMAKE_FIND_LIBRARY_PREFIXES "")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")

SET(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )

PROJECT( RtMidi )

INCLUDE_DIRECTORIES( ${RtMidi_SOURCE_DIR} )



##------------------------------------------------
##  RtMidi           .lib
##------------------------------------------------
SET(RtMidi_SRCS
RtError.h 
RtMidi.cpp 
RtMidi.h 
)




# If we build for windows systems, we also include the resource file
# containing the manifest, icon and other resources
   
##----------------------------------------
##       ###### WINDOWS ######
##----------------------------------------

IF(WIN32)
    
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

	SET(EXECUTABLE_OUTPUT_PATH ${RtMidi_SOURCE_DIR}../../../_WIN32
            CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${RtMidi_SOURCE_DIR}../../../_WIN32
            CACHE PATH "Single output directory for building all libraries.")

	      
	ADD_DEFINITIONS(-DWIN32)
	ADD_DEFINITIONS(-D__WINDOWS_MM__)


	##------ RtMidi ---------------------------------------------------------
	ADD_LIBRARY(lib-RtMidi STATIC ${RtMidi_SRCS})
        SET_TARGET_PROPERTIES(lib-RtMidi PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME RtMidi DEBUG_OUTPUT_NAME RtMidi_d)  
        ##---------------------------------------------------------------------------

ENDIF(WIN32)

    


##----------------------------------------
##        ##### MAC #####
##----------------------------------------
    
IF (APPLE)

	SET(EXECUTABLE_OUTPUT_PATH ${RtMidi_SOURCE_DIR}/../../_MAC
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${RtMidi_SOURCE_DIR}/../../_MAC
		CACHE PATH "Single output directory for building all libraries.")

	FIND_LIBRARY(COREMIDI_LIBRARY CoreMidi)
	##FIND_LIBRARY(COREAUDIO_LIBRARY CoreAudio)
	##FIND_LIBRARY(COREFOUNDATION_LIBRARY CoreFoundation )

	ADD_DEFINITIONS(-DMAC)
	ADD_DEFINITIONS(-D__MACOSX_CORE__)

	##-------- RtMidi ---------------------------------------------------------
	ADD_LIBRARY(lib-RtMidi STATIC ${RtMidi_SRCS})
	SET_TARGET_PROPERTIES(lib-RtMidi PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME RtMidi DEBUG_OUTPUT_NAME RtMidi_d)  
	##------------------------------------------------------------------------
ENDIF (APPLE)
