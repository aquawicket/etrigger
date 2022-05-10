#################################
####         wxBlank         ####
#################################

###### Supported Compilers ######
#
# Visual Studio 9 2008



cmake_minimum_required(VERSION 2.4)

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

SET(CMAKE_FIND_LIBRARY_PREFIXES "")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")

FIND_PACKAGE(wxWidgets)
IF(wxWidgets_FOUND)

INCLUDE(${wxWidgets_USE_FILE})
sET(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )

PROJECT( wxBlank )
INCLUDE_DIRECTORIES( ${wxBlank_SOURCE_DIR} ${wxWidgets_INCLUDE_DIRS} )
 
##----------------------------------------
##  wxBlank.exe
##----------------------------------------  
SET(wxBlank_SRCS
app.ico
app.rc
app.icns
App.h
App.cpp
Main.h
Main.cpp
)



##----------------------------------------
##       ###### WINDOWS ######
##----------------------------------------
IF(WIN32)

	MESSAGE("Detected WINDOWS environment")

	SET(EXECUTABLE_OUTPUT_PATH ${wxBlank_SOURCE_DIR}/../--==Windows==--
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${wxBlank_SOURCE_DIR}/../--==Windows==-
		CACHE PATH "Single output directory for building all libraries.")
	
	IF(CMAKE_CXX_COMPILER MATCHES cl)
	##### Microsoft Visual Studio 2008 options #####
	IF(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")
        	SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
        	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od /EHsc")
        	SET(CMAKE_CXX_FLAGS_RELEASE "/MT /Z7 /DEBUG /O2 /EHsc /bigobj")
       		SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2 /EHsc")
       		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od /EHsc")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")
	ENDIF(CMAKE_CXX_COMPILER MATCHES cl)

	ADD_DEFINITIONS(-DWIN32)

	GET_TARGET_PROPERTY(MyExecutable_PATH wxBlank LOCATION)
	ADD_EXECUTABLE(wxBlank WIN32 ${wxBlank_SRCS})
	TARGET_LINK_LIBRARIES(wxBlank ${wxWidgets_LIBRARIES})	  
ENDIF(WIN32)
##----------------------------------------


##----------------------------------------
##        ##### MAC #####
##----------------------------------------
IF(APPLE)

	MESSAGE("Detected MAC environment")

	SET(EXECUTABLE_OUTPUT_PATH ${wxBlank_SOURCE_DIR}/../--==Mac==--
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${wxBlank_SOURCE_DIR}/../--==Mac==--
		CACHE PATH "Single output directory for building all libraries.")

	ADD_DEFINITIONS(-DMAC)
	ADD_DEFINITIONS(-D__MACOSX_CORE__)


	GET_TARGET_PROPERTY(MyExecutable_PATH wxBlank LOCATION)
	
	##SET( MACOSX_RESOURCE_FILES ${wxBlank_SOURCE_DIR}/app.icns )
			SET( MACOSX_BUNDLE_ICON_FILE app.icns)

	SET_SOURCE_FILES_PROPERTIES(${wxBlank_RESOURCES_DIR}/app.icns
                              PROPERTIES
                              MACOSX_PACKAGE_LOCATION Resources)
	ADD_EXECUTABLE(wxBlank MACOSX_BUNDLE ${wxBlank_SRCS})
	TARGET_LINK_LIBRARIES(wxBlank ${wxWidgets_LIBRARIES})

ENDIF(APPLE)
##----------------------------------------




##----------------------------------------
##        ##### LINUX #####
##----------------------------------------
IF (UNIX)
IF (!APPLE)
	MESSAGE("Detected LINUX environment")

	SET(EXECUTABLE_OUTPUT_PATH ${wxBlank_SOURCE_DIR}/../--==Linux==--
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${wxBlank_SOURCE_DIR}/../--==Linux==--
		CACHE PATH "Single output directory for building all libraries.")

	ADD_DEFINITIONS(-DLINUX)
	ADD_DEFINITIONS(-D__WXGTK__)

	GET_TARGET_PROPERTY(MyExecutable_PATH wxBlank LOCATION)
	ADD_EXECUTABLE(wxBlank ${wxBlank_SRCS})
	TARGET_LINK_LIBRARIES(wxBlank ${wxWidgets_LIBRARIES})

ENDIF (!APPLE)
ENDIF (UNIX)
##----------------------------------------



ELSE(wxWidgets_FOUND)
MESSAGE("wxWidgets not found!")
ENDIF(wxWidgets_FOUND)