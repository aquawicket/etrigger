#################################
####       eTriggerVst       ####
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

PROJECT( eTriggerVst )

INCLUDE_DIRECTORIES( ${eTriggerVst_SOURCE_DIR} ${wxWidgets_INCLUDE_DIRS} )

##-------------------------------------
##  eTrigger.dll
##-------------------------------------  
# Add the source files  
SET(eTriggerVST_SRCS
eTriggerVST.txt
wxVST.cpp
wxVST.h
eTriggerVST.h
eTriggerVST.cpp
#eTrigger/Main.h
#eTrigger/Main.cpp
../eTrigger/MainPanel.h
../eTrigger/MainPanel.cpp
../eTrigger/icon.rc
../eTrigger/Err.h
../eTrigger/Tracks.h 
../eTrigger/Tracks.cpp
../eTrigger/Trigger.h 
../eTrigger/Trigger.cpp
../eTrigger/TriggerDialog.h 
../eTrigger/TriggerDialog.cpp  
../eTrigger/MidiCC.h 
../eTrigger/MidiCC.cpp
../eTrigger/MidiCCDialog.h 
../eTrigger/MidiCCDialog.cpp 
../eTrigger/Process.h 
../eTrigger/Process.cpp
../eTrigger/Midi.h
../eTrigger/Midi.cpp
../eTrigger/MidiDialog.h 
../eTrigger/MidiDialog.cpp
../eTrigger/MenuPanel.h
../eTrigger/MenuPanel.cpp
../eTrigger/Audio.h 
../eTrigger/Audio.cpp 
../eTrigger/AudioDialog.h 
../eTrigger/AudioDialog.cpp
../eTrigger/Joystick.h 
../eTrigger/Joystick.cpp 
../eTrigger/JoystickDialog.h 
../eTrigger/JoystickDialog.cpp
../eTrigger/OptionsDialog.h 
../eTrigger/OptionsDialog.cpp 
../eTrigger/StatusDialog.h
../eTrigger/StatusDialog.cpp
../eTrigger/Wizard.h 
../eTrigger/Wizard.cpp 
../eTrigger/KeyToString.h
../eTrigger/AboutDialog.h
../eTrigger/AboutDialog.cpp
../eTrigger/joystickEx.h
../eTrigger/joystickEx.cpp
../eTrigger/Network.h
../eTrigger/Network.cpp
../eTrigger/AdminDialog.h
../eTrigger/AdminDialog.cpp
../eTrigger/stdwx.h
../eTrigger/stdwx.cpp
../eTrigger/Timer.h
../eTrigger/Timer.cpp
../eTrigger/Security.h
../eTrigger/Security.cpp
../eTrigger/diskid32.h
../eTrigger/diskid32.cpp
../eTrigger/MidiMonitor.h
../eTrigger/MidiMonitor.cpp
../eTrigger/NotesDialog.h
../eTrigger/NotesDialog.cpp
../eTrigger/DebugDialog.h
../eTrigger/DebugDialog.cpp
../eTrigger/PianoDialog.h
../eTrigger/PianoDialog.cpp
../eTrigger/VelocityDialog.h
../eTrigger/VelocityDialog.cpp
../eTrigger/Tray.h
../eTrigger/Tray.cpp
../eTrigger/SoundController.h
../eTrigger/SoundController.cpp
../eTrigger/ReSample.h
../eTrigger/ReSample.cpp
../eTrigger/Samples.h
../eTrigger/Samples.cpp
../eTrigger/SampleDialog.h
../eTrigger/SampleDialog.cpp
../eTrigger/CpuUsage.h
../eTrigger/CpuUsage.cpp
../eTrigger/Details.h
../eTrigger/Details.cpp
../eTrigger/VelToPosAvgDlg.h
../eTrigger/VelToPosAvgDlg.cpp
../eTrigger/SequencerDialog.h
../eTrigger/SequencerDialog.cpp
../eTrigger/EtmFile.h
../eTrigger/EtmFile.cpp
../eTrigger/EtmEditorDialog.h
../eTrigger/EtmEditorDialog.cpp
../eTrigger/EtmPlayerDialog.h
../eTrigger/EtmPlayerDialog.cpp
../eTrigger/EtmPlayerOptions.h
../eTrigger/EtmPlayerOptions.cpp
../eTrigger/Waveform.h
../eTrigger/Waveform.cpp
../eTrigger/Midiform.h
../eTrigger/Midiform.cpp
../eTrigger/DrumTypeCodes.h
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
		SET_SOURCE_FILES_PROPERTIES(wxVST.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTriggerVST.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MainPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MainFrame.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Tracks.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Trigger.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/TriggerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MidiCC.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MidiCCDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Process.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Midi.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MidiDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Audio.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/AudioDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Joystick.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/JoystickDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/OptionsDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/StatusDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Wizard.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/AboutDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/joystickEx.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Network.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/AdminDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Timer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Security.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/diskid32.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MidiMonitor.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/NotesDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/DebugDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/PianoDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/VelocityDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Tray.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/SoundController.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/ReSample.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Samples.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/SampleDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/CpuUsage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Details.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MenuPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/VelToPosAvgDlg.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/SequencerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/EtmFile.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/EtmEditorDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/EtmPlayerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/EtmPlayerOptions.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Waveform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Midiform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/GLImage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/glfont2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 8 2005")

	##### Microsoft Visual Studio 2008 options #####
	IF(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")
        	SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
        	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od /EHsc")
        	SET(CMAKE_CXX_FLAGS_RELEASE "/MT /Z7 /DEBUG /O2 /EHsc /bigobj")
       		SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2 /EHsc")
       		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od /EHsc")

		### Use precompiled Headers ###
		SET_SOURCE_FILES_PROPERTIES(wxVST.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTriggerVST.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MainPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MainFrame.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Tracks.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Trigger.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/TriggerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MidiCC.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MidiCCDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Process.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Midi.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MidiDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Audio.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/AudioDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Joystick.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/JoystickDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/OptionsDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/StatusDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Wizard.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/AboutDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/joystickEx.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Network.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/AdminDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Timer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Security.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/diskid32.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MidiMonitor.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/NotesDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/DebugDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/PianoDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/VelocityDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Tray.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/SoundController.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/ReSample.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Samples.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/SampleDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/CpuUsage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Details.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MenuPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/VelToPosAvgDlg.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/SequencerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/EtmFile.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/EtmEditorDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/EtmPlayerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/EtmPlayerOptions.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Waveform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Midiform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/GLImage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/glfont2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")

	##### Microsoft Visual Studio 2010 options #####
	IF(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
        	SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
        	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od /EHsc")
        	SET(CMAKE_CXX_FLAGS_RELEASE "/MT /Z7 /DEBUG /O2 /EHsc /bigobj")
       		SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2 /EHsc")
       		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od /EHsc")

		### Use precompiled Headers ###
		SET_SOURCE_FILES_PROPERTIES(wxVST.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTriggerVST.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MainPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MainFrame.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Tracks.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Trigger.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/TriggerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MidiCC.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MidiCCDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Process.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Midi.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MidiDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Audio.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/AudioDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Joystick.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/JoystickDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/OptionsDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/StatusDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Wizard.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/AboutDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/joystickEx.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Network.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/AdminDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Timer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Security.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/diskid32.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MidiMonitor.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/NotesDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/DebugDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/PianoDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/VelocityDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Tray.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/SoundController.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/ReSample.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Samples.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/SampleDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/CpuUsage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Details.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/MenuPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/VelToPosAvgDlg.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/SequencerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/EtmFile.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/EtmEditorDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/EtmPlayerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/EtmPlayerOptions.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Waveform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/Midiform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/GLImage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(../eTrigger/glfont2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
	
	ENDIF(CMAKE_CXX_COMPILER MATCHES cl)

   	SET(EXECUTABLE_OUTPUT_PATH ${eTriggerVst_SOURCE_DIR}/../win_bin
            CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${eTriggerVst_SOURCE_DIR}/../win_lib
            CACHE PATH "Single output directory for building all libraries.")

	##------ Find Debug Libraries ---------------------------------------
	FIND_LIBRARY(dsound       dsound        $ENV{DXSDK_DIR}/Lib/x86 )
	FIND_LIBRARY(RtAudiod     RtAudio_d     ${eTriggerVst_SOURCE_DIR}/../win_lib/debug)
	FIND_LIBRARY(portaudiod   portaudio_d   ${eTriggerVst_SOURCE_DIR}/../win_lib/debug)
	FIND_LIBRARY(portmidid    portmidi_d    ${eTriggerVst_SOURCE_DIR}/../win_lib/debug)
	FIND_LIBRARY(GWidgetsd    GWidgets_d    ${eTriggerVst_SOURCE_DIR}/../win_lib/debug)
	FIND_LIBRARY(RtMidid      RtMidi_d      ${eTriggerVst_SOURCE_DIR}/../win_lib/debug)	
	FIND_LIBRARY(cryptod      crypto_d      ${eTriggerVst_SOURCE_DIR}/../win_lib/debug)
	FIND_LIBRARY(libsndfiled  sndfile_d     ${eTriggerVst_SOURCE_DIR}/../win_lib/debug)
	FIND_LIBRARY(libresampled libresample_d ${eTriggerVst_SOURCE_DIR}/../win_lib/debug)
	FIND_LIBRARY(libvstd      libvst_d      ${eTriggerVst_SOURCE_DIR}/../win_lib/debug)
	FIND_LIBRARY(libmpg123    libmpg123_d   ${eTriggerVst_SOURCE_DIR}/../win_lib/debug)
	 
	##------ Find Release Libraries ---------------------------------------
	FIND_LIBRARY(RtAudio     RtAudio     ${eTriggerVst_SOURCE_DIR}/../win_lib/release)	
	FIND_LIBRARY(portaudio   portaudio   ${eTriggerVst_SOURCE_DIR}/../win_lib/release)
	FIND_LIBRARY(portmidi    portmidi    ${eTriggerVst_SOURCE_DIR}/../win_lib/release)
	FIND_LIBRARY(GWidgets    GWidgets    ${eTriggerVst_SOURCE_DIR}/../win_lib/release)
	FIND_LIBRARY(RtMidi      RtMidi      ${eTriggerVst_SOURCE_DIR}/../win_lib/release)
	FIND_LIBRARY(crypto      crypto      ${eTriggerVst_SOURCE_DIR}/../win_lib/release)
	FIND_LIBRARY(libsndfile  sndfile     ${eTriggerVst_SOURCE_DIR}/../win_lib/release)
	FIND_LIBRARY(libresample libresample ${eTriggerVst_SOURCE_DIR}/../win_lib/release)
	FIND_LIBRARY(libvst      libvst      ${eTriggerVst_SOURCE_DIR}/../win_lib/release)
	FIND_LIBRARY(libmpg123   libmpg123   ${eTriggerVst_SOURCE_DIR}/../win_lib/release)

	ADD_DEFINITIONS(-DWIN32)
    ADD_DEFINITIONS(-DPAWIN_USE_WDMKS_DEVICE_INFO)
	ADD_DEFINITIONS(-DOPT_GENERIC)
	ADD_DEFINITIONS(-DACCURATE_ROUNDING)
	ADD_DEFINITIONS(-DIEEE_FLOAT)
	ADD_DEFINITIONS(-D__WINDOWS_MM__)
	ADD_DEFINITIONS(-DVST)

	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../eTrigger/ )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GImage )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GButton )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GCheckBox )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GMeter )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GScrollBar )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GSlider )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GKnob )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GText )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GNumberBox )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GCurve )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GImageSelector )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GHelper )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GLFont )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GLImage )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/libsndfile/Win32 )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/libresample/include )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/libresample/src )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/portaudio/include )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/portaudio/src/common )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/cryptopp )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/mpg123/src/libmpg123 )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/mpg123/ports/MSVC++ )

	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/RtMidi )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/VstSDK/source/common )

	##----- eTrigger.dll------------------------------------------------------------------------------------------
	ADD_LIBRARY(eTriggerVST SHARED ${eTriggerVST_SRCS})
	TARGET_LINK_LIBRARIES(eTriggerVST ${wxWidgets_LIBRARIES}
						debug ${WX_qad}
						debug ${WX_xmld}
						debug ${WX_netd}
						debug ${WX_advd}
						debug ${WX_gld}
						debug winmm.lib
						debug ksuser.lib
						debug opengl32.lib
						debug ${cryptod}
						debug ${GWidgetsd}
						debug ${RtMidid}
						debug ${libsndfiled} 
						debug ${libresampled}
						debug ${dsound}
						debug ${portaudiod}
						debug ${portmidid}
						debug ${libmpg123}
						debug ${libvstd}
						#debug ${RtAudiod}	
						optimized ${WX_qa}
						optimized ${WX_xml}
						optimized ${WX_net}
						optimized ${WX_adv}
						optimized ${WX_gl}
						optimized winmm.lib
						optimized ksuser.lib
						optimized opengl32.lib
						optimized ${crypto}
						optimized ${GWidgets}
						optimized ${RtMidi}
						optimized ${libsndfile}
						optimized ${libresample}
						optimized ${dsound}
						optimized ${portaudio}
						optimized ${portmidi}
						optimized ${libmpg123}
						optimized ${libvstd}
						#optimized ${RtAudio}
						)

	SET_TARGET_PROPERTIES(eTriggerVST PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:libc.lib" LINK_FLAGS "/NODEFAULTLIB:libc.lib")
	##--------------------------------------------------------------------------

ENDIF(WIN32)
##--------------------------------------------

    


##----------------------------------------
##        ##### MAC #####
##----------------------------------------
IF (APPLE)

	MESSAGE("Detected MAC environment")

	SET(EXECUTABLE_OUTPUT_PATH ${eTriggerVst_SOURCE_DIR}/../osx_bin
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${eTriggerVst_SOURCE_DIR}/../osx_lib
		CACHE PATH "Single output directory for building all libraries.")

	FIND_LIBRARY(COREMIDI_LIBRARY CoreMidi)
	FIND_LIBRARY(COREAUDIO_LIBRARY CoreAudio)
	FIND_LIBRARY(COREFOUNDATION_LIBRARY CoreFoundation )
	FIND_LIBRARY(AUDIOTOOLBOX_LIBRARY AudioToolbox )
	FIND_LIBRARY(AUDIOUNIT_LIBRARY AudioUnit )
	FIND_LIBRARY(CORESERVICES_LIBRARY CoreServices)
	FIND_LIBRARY(IOKIT_LIBRARY ioKit)

	ADD_DEFINITIONS(-DMAC)
	ADD_DEFINITIONS(-D__MACOSX_CORE__)
	ADD_DEFINITIONS(-DVST)

	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GImage )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GButton )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GCheckBox )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GMeter )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GScrollBar )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GSlider )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GKnob )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GText )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GNumberBox )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GCurve )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GImageSelector )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GHelper )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GLFont )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GLImage )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/libsndfile/Win32 )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/libresample/include )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/libresample/src )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/portaudio/include )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/portaudio/src/common )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/cryptopp )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/mpg123/src/libmpg123 )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/mpg123/ports/MSVC++ )

	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/RtMidi )

	##----- eTrigger.dll------------------------------------------------------------------------------------------
	ADD_LIBRARY(eTriggerVST SHARED ${eTriggerVST_SRCS})
	TARGET_LINK_LIBRARIES(eTriggerVST ${wxWidgets_LIBRARIES}
						debug ${WX_qad}
						debug ${WX_xmld}
						debug ${WX_netd}
						debug ${WX_advd}
						debug ${WX_gld}
						debug winmm.lib
						debug ksuser.lib
						debug opengl32.lib
						debug ${cryptod}
						debug ${GWidgetsd}
						debug ${RtMidid}
						debug ${libsndfiled} 
						debug ${libresampled}
						debug ${dsound}
						debug ${portaudiod}
						debug ${portmidid}
						debug ${libmpg123}
						#debug ${RtAudiod}	
						optimized ${WX_qa}
						optimized ${WX_xml}
						optimized ${WX_net}
						optimized ${WX_adv}
						optimized ${WX_gl}
						optimized winmm.lib
						optimized ksuser.lib
						optimized opengl32.lib
						optimized ${crypto}
						optimized ${GWidgets}
						optimized ${RtMidi}
						optimized ${libsndfile}
						optimized ${libresample}
						optimized ${dsound}
						optimized ${portaudio}
						optimized ${portmidi}
						optimized ${libmpg123}
						#optimized ${RtAudio}
						)

	SET_TARGET_PROPERTIES(eTriggerVST PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:libc.lib" LINK_FLAGS "/NODEFAULTLIB:libc.lib")
	##--------------------------------------------------------------------------

ENDIF (APPLE)
##--------------------------------------------





##----------------------------------------
##        ##### LINUX #####
##----------------------------------------
IF (UNIX)
IF (!APPLE)

	MESSAGE("Detected LINUX environment")

	SET(EXECUTABLE_OUTPUT_PATH ${eTriggerVst_SOURCE_DIR}/../linux_bin
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${eTriggerVst_SOURCE_DIR}/../linux_lib
		CACHE PATH "Single output directory for building all libraries.")

    FIND_LIBRARY(ASOUND_LIBRARY asound)
	
	ADD_DEFINITIONS(-DLINUX)
	ADD_DEFINITIONS(-D__WXGTK__)
	ADD_DEFINITIONS(-DCMAKE_BUILD_TYPE=debugfull)
	ADD_DEFINITIONS(-D__LINUX_ALSASEQ__)
	ADD_DEFINITIONS(-DVST)

	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GImage )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GButton )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GCheckBox )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GMeter )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GScrollBar )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GSlider )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GKnob )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GText )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GNumberBox )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GCurve )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GImageSelector )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GHelper )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GLFont )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/GWidgets/GLImage )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/libsndfile/Win32 )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/libresample/include )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/libresample/src )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/portaudio/include )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/portaudio/src/common )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/cryptopp )
	
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/mpg123/src/libmpg123 )
	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/mpg123/ports/MSVC++ )

	INCLUDE_DIRECTORIES(${eTriggerVst_SOURCE_DIR}/../lib-src/RtMidi )

	##----- eTrigger.dll------------------------------------------------------------------------------------------
	ADD_LIBRARY(eTriggerVST SHARED ${eTriggerVST_SRCS})
	TARGET_LINK_LIBRARIES(eTriggerVST ${wxWidgets_LIBRARIES}
						debug ${WX_qad}
						debug ${WX_xmld}
						debug ${WX_netd}
						debug ${WX_advd}
						debug ${WX_gld}
						debug winmm.lib
						debug ksuser.lib
						debug opengl32.lib
						debug ${cryptod}
						debug ${GWidgetsd}
						debug ${RtMidid}
						debug ${libsndfiled} 
						debug ${libresampled}
						debug ${dsound}
						debug ${portaudiod}
						debug ${portmidid}
						debug ${libmpg123}
						#debug ${RtAudiod}	
						optimized ${WX_qa}
						optimized ${WX_xml}
						optimized ${WX_net}
						optimized ${WX_adv}
						optimized ${WX_gl}
						optimized winmm.lib
						optimized ksuser.lib
						optimized opengl32.lib
						optimized ${crypto}
						optimized ${GWidgets}
						optimized ${RtMidi}
						optimized ${libsndfile}
						optimized ${libresample}
						optimized ${dsound}
						optimized ${portaudio}
						optimized ${portmidi}
						optimized ${libmpg123}
						#optimized ${RtAudio}
						)

	SET_TARGET_PROPERTIES(eTriggerVST PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:libc.lib" LINK_FLAGS "/NODEFAULTLIB:libc.lib")
	##--------------------------------------------------------------------------

ENDIF (!APPLE)
ENDIF (UNIX)
##--------------------------------------------


ELSE(wxWidgets_FOUND)    
MESSAGE("wxWidgets not found!")
ENDIF(wxWidgets_FOUND)
