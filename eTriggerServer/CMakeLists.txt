#################################
####    eTrigger Server      ####
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

PROJECT( eTriggerServer )

INCLUDE_DIRECTORIES( ${eTriggerServer_SOURCE_DIR} ${wxWidgets_INCLUDE_DIRS} )


##-------------------------------------
##  eTriggerServer.exe
##-------------------------------------  
SET(eTriggerServer_SRCS
eTriggerServer.txt
App.h
App.cpp
server.h
server.cpp
UserData.cpp
UserData.h
tray.h
tray.cpp
)


# If we build for windows systems, we also include the resource file
# containing the manifest, icon and other resources
   
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

   	SET(EXECUTABLE_OUTPUT_PATH ${eTriggerServer_SOURCE_DIR}/../win_bin
            CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${eTriggerServer_SOURCE_DIR}/../win_lib
            CACHE PATH "Single output directory for building all libraries.")

	INCLUDE_DIRECTORIES(${eTriggerServer_SOURCE_DIR}/../lib-src/Gwidgets/GHelper )

	ADD_DEFINITIONS(-DWIN32)

	##------ Find Debug Libraries ---------------------------------------
	FIND_LIBRARY(GWidgetsd    GWidgets_d    ${eTriggerServer_SOURCE_DIR}/../win_lib/debug)
 
	##------ Find Release Libraries ---------------------------------------
	FIND_LIBRARY(GWidgets    GWidgets    ${eTriggerServer_SOURCE_DIR}/../win_lib/release)



	##----- eTriggerServer -------------------------------------------------------------------------------------
	ADD_EXECUTABLE(eTriggerServer WIN32 ${eTriggerServer_SRCS})
	TARGET_LINK_LIBRARIES(eTriggerServer ${wxWidgets_LIBRARIES} 
						debug ${WX_netd}
						debug ${WX_advd}
						debug ${GWidgetsd}
						optimized ${WX_net}
						optimized ${WX_adv}
						optimized ${GWidgets}
						)
	##-----------------------------------------------------------------------------------------------------------


ENDIF(WIN32)
##--------------------------------------------

    


##----------------------------------------
##        ##### MAC #####
##----------------------------------------
IF (APPLE)

	MESSAGE("Detected MAC environment")

	SET(EXECUTABLE_OUTPUT_PATH ${eTriggerServer_SOURCE_DIR}/../osx_bin
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${eTriggerServer_SOURCE_DIR}/../osx_lib
		CACHE PATH "Single output directory for building all libraries.")

	INCLUDE_DIRECTORIES(${eTriggerServer_SOURCE_DIR}/../lib-src/Gwidgets/GHelper )		

	##------ Find Debug Libraries ---------------------------------------
	FIND_LIBRARY(GWidgetsd libGWidgets_d.a ${eTriggerServer_SOURCE_DIR}/../osx_lib/debug)
	
	##------ Find Release Libraries ---------------------------------------
	FIND_LIBRARY(GWidgets libGWidgets.a ${eTriggerServer_SOURCE_DIR}/../osx_lib/release)

	ADD_DEFINITIONS(-DMAC)

	##----- eTriggerServer ------------------------------------------------------
	ADD_EXECUTABLE(eTriggerServer MACOSX_BUNDLE ${eTriggerServer_SRCS})
	TARGET_LINK_LIBRARIES(eTriggerServer ${wxWidgets_LIBRARIES}
						debug ${WX_netd}
						debug ${WX_advd}
						debug ${GWidgetsd}
						optimized ${WX_net}
						optimized ${WX_adv}
						optimized ${GWidgets}
						)
	##---------------------------------------------------------------------------





ENDIF (APPLE)
##--------------------------------------------





##----------------------------------------
##        ##### LINUX #####
##----------------------------------------
IF (UNIX)
IF (!APPLE)

	MESSAGE("Detected LINUX environment")

	SET(EXECUTABLE_OUTPUT_PATH ${eTriggerServer_SOURCE_DIR}/../linux_bin
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${eTriggerServer_SOURCE_DIR}/../linux_lib
		CACHE PATH "Single output directory for building all libraries.")

	INCLUDE_DIRECTORIES(${eTriggerServer_SOURCE_DIR}/../lib-src/Gwidgets/GHelper )

	
	##------ Find Libraries ---------------------------------------
	FIND_LIBRARY(GWidgetsd libGWidgets_d.a ${eTriggerServer_SOURCE_DIR}/../linux_lib)

	FIND_LIBRARY(GWidgets libGWidgets.a ${eTriggerServer_SOURCE_DIR}/../linux_lib)

	ADD_DEFINITIONS(-DLINUX)
	ADD_DEFINITIONS(-D__WXGTK__)


	##----- eTriggerServer -----------------------------------------------------
	ADD_EXECUTABLE(eTriggerServer ${eTriggerServer_SRCS})
	TARGET_LINK_LIBRARIES(eTriggerServer ${wxWidgets_LIBRARIES} 
						debug ${WX_netd}
						debug ${WX_advd}
						debug ${GWidgetsd}
						optimized ${WX_net}
						optimized ${WX_adv}
						optimized ${GWidgets}
						)
	##--------------------------------------------------------------------------

ENDIF (!APPLE)
ENDIF (UNIX)
##--------------------------------------------


ELSE(wxWidgets_FOUND)
    
MESSAGE("wxWidgets not found!")

ENDIF(wxWidgets_FOUND)
