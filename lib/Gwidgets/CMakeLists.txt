#################################
####       GWidgets          ####
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

# Find wxWidgets Libraries
FIND_PACKAGE(wxWidgets)

##---------------------------------------------------
## Actual config file starts here
##---------------------------------------------------

# Did we find wxWidgets ? This condition will fail
# for as long as the internal vars do not point to
# the proper wxWidgets configuration

IF(wxWidgets_FOUND)
    
# Include wxWidgets macros
    
INCLUDE(${wxWidgets_USE_FILE})

SET(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )

SET (wxWidgets_WXCONFIG_OPTS "--debug=yes --static=yes --version=2.8")

#SET(wxWidgets_USE_LIBS base core qa xml net adv gl)

PROJECT( GWidgets )

INCLUDE_DIRECTORIES( ${GWidgets_SOURCE_DIR} ${wxWidgets_INCLUDE_DIRS} )

##------------------------------------------------
##  GWidgets.lib
##------------------------------------------------
SET(GWidgets_SRCS
GImage/GImage.h 
GImage/GImage.cpp 
GButton/GButton.h 
GButton/GButton.cpp 
GText/GText.h 
GText/GText.cpp 
GMeter/GMeter.h 
GMeter/GMeter.cpp 
GSlider/GSlider.h 
GSlider/GSlider.cpp 
GKnob/GKnob.h 
GKnob/GKnob.cpp 
GScrollBar/GScrollBar.h 
GScrollBar/GScrollBar.cpp 
GToggle/GToggle.h
GToggle/GToggle.cpp
GNumberBox/GNumberBox.h
GNumberBox/GNumberBox.cpp
GCurve/GCurve.h
GCurve/GCurve.cpp
GImageSelector/GImageSelector.h
GImageSelector/GImageSelector.cpp
GHelper/GHelper.h
GHelper/GHelper.cpp
GLFont/glfont2.h
GLFont/glfont2.cpp
GLImage/GLImage.h
GLImage/GLImage.cpp
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
		#SET_SOURCE_FILES_PROPERTIES(eTrigger/stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 8 2005")

	##### Microsoft Visual Studio 2008 options #####
	IF(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")
        	SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
        	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od /EHsc")
        	SET(CMAKE_CXX_FLAGS_RELEASE "/MT /Z7 /DEBUG /O2 /EHsc /bigobj")
       		SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2 /EHsc")
       		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od /EHsc")

		### Use precompiled Headers ###
		#SET_SOURCE_FILES_PROPERTIES(eTrigger/stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")

	##### Microsoft Visual Studio 2010 options #####
	IF(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
        	SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
        	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od /EHsc")
        	SET(CMAKE_CXX_FLAGS_RELEASE "/MT /Z7 /DEBUG /O2 /EHsc /bigobj")
       		SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2 /EHsc")
       		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od /EHsc")

		### Use precompiled Headers ###
		#SET_SOURCE_FILES_PROPERTIES(eTrigger/stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
	
	ENDIF(CMAKE_CXX_COMPILER MATCHES cl)

   	SET(EXECUTABLE_OUTPUT_PATH ${GWidgets_SOURCE_DIR}/../../_WIN32
            CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${GWidgets_SOURCE_DIR}/../../_WIN32
            CACHE PATH "Single output directory for building all libraries.")

	ADD_DEFINITIONS(-DWIN32)

	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GImage )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GButton )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GCheckBox )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GMeter )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GScrollBar )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GSlider )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GKnob )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GText )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GNumberBox )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GCurve )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GImageSelector )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GHelper )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GLFont )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GLImage )

	##-------- GWidgets ----------------------------------------------------------------------
	ADD_LIBRARY(lib-GWidgets STATIC ${GWidgets_SRCS})
	SET_TARGET_PROPERTIES(lib-GWidgets PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME GWidgets DEBUG_OUTPUT_NAME GWidgets_d)  
	##--------------------------------------------------------------------------------------------

ENDIF(WIN32)
##--------------------------------------------

    


##----------------------------------------
##        ##### MAC #####
##----------------------------------------
IF (APPLE)

	MESSAGE("Detected MAC environment")

	SET(EXECUTABLE_OUTPUT_PATH ${GWidgets_SOURCE_DIR}/../../_MAC
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${GWidgets_SOURCE_DIR}/../../_MAC
		CACHE PATH "Single output directory for building all libraries.")

	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GImage )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GButton )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GCheckBox )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GMeter )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GGScrollBar )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GSlider )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GKnob )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GText )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GNumberBox )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GCurve )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GImageSelector )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GHelper )		
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GLFont )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GLImage )

	ADD_DEFINITIONS(-DMAC)

	##-------- GWidgets ---------------------------------------------------------
	ADD_LIBRARY(lib-GWidgets STATIC ${GWidgets_SRCS})
	SET_TARGET_PROPERTIES(lib-GWidgets PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME GWidgets DEBUG_OUTPUT_NAME GWidgets_d)  
	##------------------------------------------------------------------------

ENDIF (APPLE)
##--------------------------------------------





##----------------------------------------
##        ##### LINUX #####
##----------------------------------------
IF (UNIX)
IF (!APPLE)

	MESSAGE("Detected LINUX environment")

	SET(EXECUTABLE_OUTPUT_PATH ${GWidgets_SOURCE_DIR}/../../_LINUX
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${GWidgets_SOURCE_DIR}/../../_LINUX
		CACHE PATH "Single output directory for building all libraries.")

	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GImage )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GButton )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GCheckBox )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GMeter )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GGScrollBar )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GSlider )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GKnob )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GText )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GNumberBox )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GCurve )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GImageSelector )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GHelper )		
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GLFont )
	INCLUDE_DIRECTORIES(${GWidgets_SOURCE_DIR}/GLImage )
	
	ADD_DEFINITIONS(-DLINUX)
	ADD_DEFINITIONS(-D__WXGTK__)


	##-------- GWidgets ---------------------------------------------------------
	ADD_LIBRARY(lib-GWidgets STATIC ${GWidgets_SRCS})
	SET_TARGET_PROPERTIES(lib-GWidgets PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME GWidgets DEBUG_OUTPUT_NAME GWidgets_d)  
	##-------------------------------------------------------------------------

ENDIF (!APPLE)
ENDIF (UNIX)
##--------------------------------------------


ELSE(wxWidgets_FOUND)
    
MESSAGE("wxWidgets not found!")

ENDIF(wxWidgets_FOUND)
