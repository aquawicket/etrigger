#################################
####   eTriggerKeyGenerator  ####
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

IF(wxWidgets_FOUND)
    
INCLUDE(${wxWidgets_USE_FILE})

SET(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )
SET (wxWidgets_WXCONFIG_OPTS "--debug=yes --static=yes --version=2.8")

PROJECT( eTriggerKeyGenerator )

INCLUDE_DIRECTORIES( ${eTriggerKeyGenerator_SOURCE_DIR} ${wxWidgets_INCLUDE_DIRS} )

##-------------------------------------
##  KeyGenerator.exe
##-------------------------------------
SET(KeyGenerator_SRCS
KeyGenerator.txt
App.h
App.cpp
KeyGen.h
KeyGen.cpp
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

   	SET(EXECUTABLE_OUTPUT_PATH ${eTriggerKeyGenerator_SOURCE_DIR}/../win_bin
            CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${eTriggerKeyGenerator_SOURCE_DIR}/../win_lib
            CACHE PATH "Single output directory for building all libraries.")

	
	##------ Find Libraries ---------------------------------------	
	FIND_LIBRARY(cryptod   crypto_d   ${eTriggerKeyGenerator_SOURCE_DIR}/../win_lib/debug)
	FIND_LIBRARY(crypto    crypto     ${eTriggerKeyGenerator_SOURCE_DIR}/../win_lib/release)
	FIND_LIBRARY(GWidgetsd GWidgets_d ${eTriggerKeyGenerator_SOURCE_DIR}/../win_lib/debug)
	FIND_LIBRARY(GWidgets  GWidgets   ${eTriggerKeyGenerator_SOURCE_DIR}/../win_lib/release)

	ADD_DEFINITIONS(-DWIN32)
	
	INCLUDE_DIRECTORIES(${eTriggerKeyGenerator_SOURCE_DIR}/../lib-src/GWidgets/GButton )
	INCLUDE_DIRECTORIES(${eTriggerKeyGenerator_SOURCE_DIR}/../lib-src/GWidgets/GHelper )
	INCLUDE_DIRECTORIES(${eTriggerKeyGenerator_SOURCE_DIR}/../lib-src/cryptopp )
	
	##----- KeyGenerator --------------------------------------------------------------------------------------
	ADD_EXECUTABLE(KeyGenerator WIN32 ${KeyGenerator_SRCS})
	TARGET_LINK_LIBRARIES(KeyGenerator ${wxWidgets_LIBRARIES}
						debug ${GWidgetsd}
						debug ${cryptod}
						optimized ${GWidgets}
						optimized ${crypto}
						)
	SET_TARGET_PROPERTIES(KeyGenerator PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME KeyGenerator)  
	##---------------------------------------------------------------------------------------------------------

ENDIF(WIN32)
##--------------------------------------------

    


##----------------------------------------
##        ##### MAC #####
##----------------------------------------
IF (APPLE)

	MESSAGE("Detected MAC environment")

	SET(EXECUTABLE_OUTPUT_PATH ${eTriggerKeyGenerator_SOURCE_DIR}/../osx_bin
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${eTriggerKeyGenerator_SOURCE_DIR}/../osx_lib
		CACHE PATH "Single output directory for building all libraries.")

	##------ Find Libraries ---------------------------------------
	FIND_LIBRARY(cryptod   libcryptopp_d.a     ${eTriggerKeyGenerator_SOURCE_DIR}/../osx_lib/debug)
	FIND_LIBRARY(crypto    libcryptopp.a       ${eTriggerKeyGenerator_SOURCE_DIR}/../osx_lib/release)
	FIND_LIBRARY(GWidgetsd libGWidgets_d.a     ${eTriggerKeyGenerator_SOURCE_DIR}/../osx_lib/debug)
	FIND_LIBRARY(GWidgets  libGWidgets.a       ${eTriggerKeyGenerator_SOURCE_DIR}/../osx_lib/release)

        ######### CMake Fix for Universal Builds ###########
	set(Apple_wxWidgets_LIBRARIES)
		foreach(LIB ${wxWidgets_LIBRARIES})
		if(${LIB} MATCHES "-arch")
			#message(STATUS "Skipping ${LIB}")
		else()
			#message(STATUS "Added ${LIB}")
			list(APPEND Apple_wxWidgets_LIBRARIES ${LIB})
		endif()
		endforeach()
	set(wxWidgets_LIBRARIES ${Apple_wxWidgets_LIBRARIES})
	#####################################################
	
	ADD_DEFINITIONS(-DMAC)
	ADD_DEFINITIONS(-DCRYPTOPP_DISABLE_ASM)  #NOTE: If we build on ppc machine, we might need to remove this
	
	INCLUDE_DIRECTORIES(${eTriggerKeyGenerator_SOURCE_DIR}/../lib-src/GWidgets/GButton )
	INCLUDE_DIRECTORIES(${eTriggerKeyGenerator_SOURCE_DIR}/../lib-src/GWidgets/GHelper )
	INCLUDE_DIRECTORIES(${eTriggerKeyGenerator_SOURCE_DIR}/../lib-src/cryptopp )

	##----- KeyGenerator --------------------------------------------------------------------------------------
	ADD_EXECUTABLE(KeyGenerator MACOSX_BUNDLE ${KeyGenerator_SRCS})
	TARGET_LINK_LIBRARIES(KeyGenerator ${wxWidgets_LIBRARIES}
						debug ${GWidgetsd}
						debug ${cryptod}
						optimized ${GWidgets}
						optimized ${crypto}
						)
	SET_TARGET_PROPERTIES(KeyGenerator PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME KeyGenerator)  
	##---------------------------------------------------------------------------------------------------------

ENDIF (APPLE)
##--------------------------------------------





##----------------------------------------
##        ##### LINUX #####
##----------------------------------------
IF (UNIX)
IF (!APPLE)

	MESSAGE("Detected LINUX environment")

	SET(EXECUTABLE_OUTPUT_PATH ${eTriggerKeyGenerator_SOURCE_DIR}/../linux_bin
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${eTriggerKeyGenerator_SOURCE_DIR}/../linux_lib
		CACHE PATH "Single output directory for building all libraries.")
	
	##------ Find Libraries ---------------------------------------
	FIND_LIBRARY(cryptod   libcrypto_d   ${eTriggerKeyGenerator_SOURCE_DIR}/../linux_lib/debug)
	FIND_LIBRARY(crypto    libcrypto     ${eTriggerKeyGenerator_SOURCE_DIR}/../linux_lib/release)
	FIND_LIBRARY(GWidgetsd GWidgets_d ${eTriggerKeyGenerator_SOURCE_DIR}/../linux_lib/debug)
	FIND_LIBRARY(GWidgets  GWidgets   ${eTriggerKeyGenerator_SOURCE_DIR}/../linux_lib/release)	

	ADD_DEFINITIONS(-DLINUX)
	
	INCLUDE_DIRECTORIES(${eTriggerKeyGenerator_SOURCE_DIR}/../lib-src/GWidgets/GButton )
	INCLUDE_DIRECTORIES(${eTriggerKeyGenerator_SOURCE_DIR}/../lib-src/GWidgets/GHelper )
	INCLUDE_DIRECTORIES(${eTriggerKeyGenerator_SOURCE_DIR}/../lib-src/cryptopp )
	
	##----- eTriggerUpdater -----------------------------------------------------
	ADD_EXECUTABLE(KeyGenerator ${KeyGenerator_SRCS})
	TARGET_LINK_LIBRARIES(KeyGenerator ${wxWidgets_LIBRARIES}
						debug ${GWidgetsd}
						debug ${cryptod}
						optimized ${GWidgets}
						optimized ${crypto}
						)
	SET_TARGET_PROPERTIES(KeyGenerator PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME KeyGenerator)
	##--------------------------------------------------------------------------

ENDIF (!APPLE)
ENDIF (UNIX)
##--------------------------------------------


ELSE(wxWidgets_FOUND) 
MESSAGE("wxWidgets not found!")
ENDIF(wxWidgets_FOUND)
