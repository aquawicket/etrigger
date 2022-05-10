#################################
####       eTrigger          ####
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
FIND_PACKAGE(wxWidgets COMPONENTS core base gl net adv qa REQUIRED)
IF(wxWidgets_FOUND)
    
# Include wxWidgets macros
    
INCLUDE(${wxWidgets_USE_FILE})

SET(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )

##SET (wxWidgets_WXCONFIG_OPTS "--debug=yes --static=yes --version=2.8")

PROJECT( eTrigger )

INCLUDE_DIRECTORIES( ${eTrigger_SOURCE_DIR} ${wxWidgets_INCLUDE_DIRS} )

add_definitions(${wxWidgets_DEFINITIONS})

##-------------------------------------
##  eTrigger.exe
##-------------------------------------  
SET(eTrigger_SRCS
eTrigger.txt
icon.rc
App.h 
App.cpp 
#Main.h
#Main.cpp
MainFrame.h 
MainFrame.cpp
Err.h
Tracks.h 
Tracks.cpp
Trigger.h 
Trigger.cpp
TriggerDialog.h 
TriggerDialog.cpp  
MidiCC.h 
MidiCC.cpp
MidiCCDialog.h 
MidiCCDialog.cpp 
Process.h 
Process.cpp
Midi.h
Midi.cpp
MidiDialog.h 
MidiDialog.cpp
MenuPanel.h
MenuPanel.cpp
Audio.h 
Audio.cpp 
AudioDialog.h 
AudioDialog.cpp
Joystick.h 
Joystick.cpp 
JoystickDialog.h 
JoystickDialog.cpp
OptionsDialog.h 
OptionsDialog.cpp 
StatusDialog.h
StatusDialog.cpp
Wizard.h 
Wizard.cpp 
KeyToString.h
AboutDialog.h
AboutDialog.cpp
joystickEx.h
joystickEx.cpp
Network.h
Network.cpp
AdminDialog.h
AdminDialog.cpp
stdwx.h
stdwx.cpp
Timer.h
Timer.cpp
Security.h
Security.cpp
diskid32.h
diskid32.cpp
MidiMonitor.h
MidiMonitor.cpp
NotesDialog.h
NotesDialog.cpp
DebugDialog.h
DebugDialog.cpp
PianoDialog.h
PianoDialog.cpp
VelocityDialog.h
VelocityDialog.cpp
Tray.h
Tray.cpp
SoundController.h
SoundController.cpp
ReSample.h
ReSample.cpp
Samples.h
Samples.cpp
SampleDialog.h
SampleDialog.cpp
CpuUsage.h
CpuUsage.cpp
Details.h
Details.cpp
MainPanel.h
MainPanel.cpp
VelToPosAvgDlg.h
VelToPosAvgDlg.cpp
SequencerDialog.h
SequencerDialog.cpp
EtmFile.h
EtmFile.cpp
#EtmEditorDialog.h
#EtmEditorDialog.cpp
EtmEditorDialog2.h
EtmEditorDialog2.cpp
EtmPlayerDialog.h
EtmPlayerDialog.cpp
EtmPlayerOptions.h
EtmPlayerOptions.cpp
Waveform.h
Waveform.cpp
Midiform.h
Midiform.cpp
DrumTypeCodes.h
DirSearch.h
DirSearch.cpp
SequencePlayer.h
SequencePlayer.cpp
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
		SET_SOURCE_FILES_PROPERTIES(stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
		SET_SOURCE_FILES_PROPERTIES(App.cpp  PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(DirSearch.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")		
		SET_SOURCE_FILES_PROPERTIES(MainFrame.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MidiCC.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MidiCCDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(Process.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Midi.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MidiDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Audio.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(AudioDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Joystick.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(JoystickDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(OptionsDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(StatusDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Wizard.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(AboutDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(joystickEx.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Network.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(AdminDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Timer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Security.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(diskid32.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MidiMonitor.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(NotesDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(DebugDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(PianoDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(VelocityDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Tray.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(SoundController.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(ReSample.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Samples.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(SampleDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(CpuUsage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Details.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MenuPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(VelToPosAvgDlg.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(SequencerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(EtmFile.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(EtmEditorDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(EtmEditorDialog2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(EtmPlayerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(EtmPlayerOptions.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Waveform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Midiform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(GLImage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(glfont2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Tracks.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Trigger.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(TriggerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(SequencePlayer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 8 2005")

	##### Microsoft Visual Studio 2008 options #####
	IF(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")
        	SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
        	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od /EHsc")
        	SET(CMAKE_CXX_FLAGS_RELEASE "/MT /Z7 /DEBUG /O2 /EHsc /bigobj")
       		SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2 /EHsc")
       		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od /EHsc")

		### Use precompiled Headers ###
		SET_SOURCE_FILES_PROPERTIES(stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
		SET_SOURCE_FILES_PROPERTIES(App.cpp  PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MainFrame.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Tracks.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Trigger.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(TriggerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MidiCC.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MidiCCDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(Process.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Midi.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MidiDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Audio.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(AudioDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Joystick.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(JoystickDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(OptionsDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(StatusDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Wizard.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(AboutDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(joystickEx.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Network.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(AdminDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Timer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Security.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(diskid32.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MidiMonitor.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(NotesDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(DebugDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(PianoDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(VelocityDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Tray.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(SoundController.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(ReSample.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Samples.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(SampleDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(CpuUsage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Details.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MainPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MenuPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(VelToPosAvgDlg.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(SequencerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(EtmFile.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(EtmEditorDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(EtmEditorDialog2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")		
		SET_SOURCE_FILES_PROPERTIES(EtmPlayerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(EtmPlayerOptions.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Waveform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Midiform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(GLImage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(glfont2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(DirSearch.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(SequencePlayer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")

	##### Microsoft Visual Studio 2010 options #####
	IF(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
        	SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
        	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od /EHsc")
        	SET(CMAKE_CXX_FLAGS_RELEASE "/MT /Z7 /DEBUG /O2 /EHsc /bigobj")
       		SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2 /EHsc")
       		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od /EHsc")

		### Use precompiled Headers ###
		SET_SOURCE_FILES_PROPERTIES(stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
		SET_SOURCE_FILES_PROPERTIES(App.cpp  PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MainFrame.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Tracks.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Trigger.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(TriggerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MidiCC.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MidiCCDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(Process.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Midi.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MidiDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Audio.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(AudioDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Joystick.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(JoystickDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(OptionsDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(StatusDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Wizard.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(AboutDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(joystickEx.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Network.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(AdminDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Timer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Security.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(diskid32.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MidiMonitor.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(NotesDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(DebugDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(PianoDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(VelocityDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Tray.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(SoundController.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(ReSample.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Samples.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(SampleDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(CpuUsage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Details.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MainPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(MenuPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(VelToPosAvgDlg.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(SequencerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(EtmFile.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(EtmEditorDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(EtmEditorDialog2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")		
		SET_SOURCE_FILES_PROPERTIES(EtmPlayerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(EtmPlayerOptions.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Waveform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(Midiform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(GLImage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(glfont2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(DirSearch.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(SequencePlayer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
	
	ENDIF(CMAKE_CXX_COMPILER MATCHES cl)

   	SET(EXECUTABLE_OUTPUT_PATH ${eTrigger_SOURCE_DIR}/../_WIN32
            CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${eTrigger_SOURCE_DIR}/../_WIN32
            CACHE PATH "Single output directory for building all libraries.")

	##------ Find Debug Libraries --------------------------------------------------
	FIND_LIBRARY(dsound          dsound        ${eTrigger_SOURCE_DIR}/../_WIN32/Debug )
	FIND_LIBRARY(RtAudiod        RtAudio_d     ${eTrigger_SOURCE_DIR}/../_WIN32/Debug)
	FIND_LIBRARY(portaudiod      portaudio_d   ${eTrigger_SOURCE_DIR}/../_WIN32/Debug)
	FIND_LIBRARY(portmidid       portmidi_d    ${eTrigger_SOURCE_DIR}/../_WIN32/Debug)
	FIND_LIBRARY(GWidgetsd       GWidgets_d    ${eTrigger_SOURCE_DIR}/../_WIN32/Debug)
	FIND_LIBRARY(RtMidid         RtMidi_d      ${eTrigger_SOURCE_DIR}/../_WIN32/Debug)	
	FIND_LIBRARY(cryptod         crypto_d      ${eTrigger_SOURCE_DIR}/../_WIN32/Debug)
	FIND_LIBRARY(libsndfiled     sndfile_d     ${eTrigger_SOURCE_DIR}/../_WIN32/Debug)
	FIND_LIBRARY(libresampled    libresample_d ${eTrigger_SOURCE_DIR}/../_WIN32/Debug)
	FIND_LIBRARY(libsamplerate   libsamplerate_d ${eTrigger_SOURCE_DIR}/../_WIN32/Debug)
	FIND_LIBRARY(libmpg123       libmpg123_d   ${eTrigger_SOURCE_DIR}/../_WIN32/Debug)
	 
	##------ Find Release Libraries -----------------------------------------------
	FIND_LIBRARY(RtAudio     RtAudio         ${eTrigger_SOURCE_DIR}/../_WIN32/Release)	
	FIND_LIBRARY(portaudio   portaudio       ${eTrigger_SOURCE_DIR}/../_WIN32/Release)
	FIND_LIBRARY(portmidi    portmidi        ${eTrigger_SOURCE_DIR}/../_WIN32/Release)
	FIND_LIBRARY(GWidgets    GWidgets        ${eTrigger_SOURCE_DIR}/../_WIN32/Release)
	FIND_LIBRARY(RtMidi      RtMidi          ${eTrigger_SOURCE_DIR}/../_WIN32/Release)
	FIND_LIBRARY(crypto      crypto          ${eTrigger_SOURCE_DIR}/../_WIN32/Release)
	FIND_LIBRARY(libsndfile  sndfile         ${eTrigger_SOURCE_DIR}/../_WIN32/Release)
	FIND_LIBRARY(libresample libresample     ${eTrigger_SOURCE_DIR}/../_WIN32/Release)
	FIND_LIBRARY(libsamplerate libsamplerate ${eTrigger_SOURCE_DIR}/../_WIN32/Release)
	FIND_LIBRARY(libmpg123   libmpg123       ${eTrigger_SOURCE_DIR}/../_WIN32/Release)

	ADD_DEFINITIONS(-DWIN32)
    ADD_DEFINITIONS(-DPAWIN_USE_WDMKS_DEVICE_INFO)
	ADD_DEFINITIONS(-DOPT_GENERIC)
	ADD_DEFINITIONS(-DACCURATE_ROUNDING)
	ADD_DEFINITIONS(-DIEEE_FLOAT)
	ADD_DEFINITIONS(-D__WINDOWS_MM__)
	ADD_DEFINITIONS(-DLIBSNDFILE)

	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GImage )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GButton )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GCheckBox )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GMeter )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GScrollBar )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GSlider )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GKnob )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GText )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GNumberBox )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GCurve )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GImageSelector )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GHelper )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GLFont )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GLImage )
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/libsndfile/Win32 )
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/libresample/include )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/libresample/src )

	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/libsamplerate/src )
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/portaudio/include )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/portaudio/src/common )
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/cryptopp )
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/mpg123/src/libmpg123 )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/mpg123/ports/MSVC++ )

	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/RtMidi )
	
	##----- eTrigger.exe------------------------------------------------------------------------------------------
	GET_TARGET_PROPERTY(MyExecutable_PATH eTrigger LOCATION)
	ADD_EXECUTABLE(eTrigger WIN32 ${eTrigger_SRCS})
	TARGET_LINK_LIBRARIES(eTrigger ${wxWidgets_LIBRARIES}
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
						debug ${libsamplerate}
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
						optimized ${libsamplerate}
						optimized ${dsound}
						optimized ${portaudio}
						optimized ${portmidi}
						optimized ${libmpg123}
						#optimized ${RtAudio}
						)

	SET_TARGET_PROPERTIES(eTrigger PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:libc.lib" LINK_FLAGS "/NODEFAULTLIB:libc.lib")
	SET_TARGET_PROPERTIES(eTrigger PROPERTIES LINK_FLAGS_DEBUG "/MANIFESTUAC:NO" LINK_FLAGS "/MANIFESTUAC:NO")
	##--------------------------------------------------------------------------


ENDIF(WIN32)
##--------------------------------------------

    


##----------------------------------------
##        ##### MAC #####
##----------------------------------------
IF (APPLE)

	MESSAGE("Detected MAC environment")

	SET(EXECUTABLE_OUTPUT_PATH ${eTrigger_SOURCE_DIR}/../osx_bin
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${eTrigger_SOURCE_DIR}/../osx_lib
		CACHE PATH "Single output directory for building all libraries.")

	FIND_LIBRARY(COREMIDI_LIBRARY CoreMidi)
	FIND_LIBRARY(COREAUDIO_LIBRARY CoreAudio)
	FIND_LIBRARY(COREFOUNDATION_LIBRARY CoreFoundation )
	FIND_LIBRARY(AUDIOTOOLBOX_LIBRARY AudioToolbox )
	FIND_LIBRARY(AUDIOUNIT_LIBRARY AudioUnit )
	FIND_LIBRARY(CORESERVICES_LIBRARY CoreServices)
	FIND_LIBRARY(IOKIT_LIBRARY ioKit)
	FIND_LIBRARY(OPENGL_LIBRARY opengl)

	##------ Find Debug Libraries ---------------------------------------
	FIND_LIBRARY(GWidgetsd libGWidgets_d.a ${eTrigger_SOURCE_DIR}/../osx_lib/debug)
	FIND_LIBRARY(RtMidid libRtMidi_d.a ${eTrigger_SOURCE_DIR}/../osx_lib/debug)
	FIND_LIBRARY(portaudiod libPortaudio_d.a ${eTrigger_SOURCE_DIR}/../osx_lib/debug)
	FIND_LIBRARY(cryptod libcryptopp_d.a ${eTrigger_SOURCE_DIR}/../osx_lib/debug)
	FIND_LIBRARY(libsndfiled libsndfile_d.a ${eTrigger_SOURCE_DIR}/../osx_lib/debug)
	FIND_LIBRARY(liboggd libogg_d.a ${eTrigger_SOURCE_DIR}/../osx_lib/debug)
	FIND_LIBRARY(libvorbisd libvorbis_d.a ${eTrigger_SOURCE_DIR}/../osx_lib/debug)
	FIND_LIBRARY(libvorbisencd libvorbisenc_d.a ${eTrigger_SOURCE_DIR}/../osx_lib/debug)
	FIND_LIBRARY(libflacd libflac_d.a ${eTrigger_SOURCE_DIR}/../osx_lib/debug)
	FIND_LIBRARY(libresampled libresample_d.a ${eTrigger_SOURCE_DIR}/../osx_lib/debug)
	
	##------ Find Release Libraries ---------------------------------------
	FIND_LIBRARY(GWidgets libGWidgets.a ${eTrigger_SOURCE_DIR}/../osx_lib/release)
	FIND_LIBRARY(RtMidi libRtMidi.a ${eTrigger_SOURCE_DIR}/../osx_lib/release)
	FIND_LIBRARY(portaudio libPortaudio.a ${eTrigger_SOURCE_DIR}/../osx_lib/release)
	FIND_LIBRARY(crypto libcryptopp.a ${eTrigger_SOURCE_DIR}/../osx_lib/release)
	FIND_LIBRARY(libsndfile libsndfile.a ${eTrigger_SOURCE_DIR}/../osx_lib/release)
	FIND_LIBRARY(libogg libogg.a ${eTrigger_SOURCE_DIR}/../osx_lib/release)
	FIND_LIBRARY(libvorbis libvorbis.a ${eTrigger_SOURCE_DIR}/../osx_lib/release)
	FIND_LIBRARY(libvorbisenc libvorbisenc.a ${eTrigger_SOURCE_DIR}/../osx_lib/release)
	FIND_LIBRARY(libflac libflac.a ${eTrigger_SOURCE_DIR}/../osx_lib/release)
	FIND_LIBRARY(libresample libresample.a ${eTrigger_SOURCE_DIR}/../osx_lib/release)

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
	ADD_DEFINITIONS(-D__MACOSX_CORE__)
	ADD_DEFINITIONS(-DCRYPTOPP_DISABLE_ASM)  #NOTE: If we build on ppc machine, we might need to remove this
	ADD_DEFINITIONS(-DLIBRESAMPLE)
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GImage )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GButton )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GCheckBox )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GMeter )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GScrollBar )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GSlider )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GKnob )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GText )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GNumberBox )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GCurve )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GImageSelector )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GHelper )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GLFont )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/GWidgets/GLImage )
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/libsndfile/MacOS )

	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/libsamplerate/src )	
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/libresample/include )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/libresample/src )
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/portaudio/include )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/portaudio/src/common )
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/cryptopp )
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/mpg123/src/libmpg123 )

	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/RtMidi )

	##----- eTrigger ------------------------------------------------------
	GET_TARGET_PROPERTY(MyExecutable_PATH eTrigger LOCATION)
	ADD_EXECUTABLE(eTrigger MACOSX_BUNDLE ${eTrigger_SRCS})
	TARGET_LINK_LIBRARIES(eTrigger 	${wxWidgets_LIBRARIES}
					debug ${COREMIDI_LIBRARY}
					debug ${COREAUDIO_LIBRARY}
					debug ${COREFOUNDATION_LIBRARY}
					debug ${AUDIOTOOLBOX_LIBRARY}
					debug ${AUDIOUNIT_LIBRARY}
					debug ${CORESERVICES_LIBRARY}
					debug ${IOKIT_LIBRARY}	
					debug ${OPENGL_LIBRARY}
					debug ${portaudiod}
					debug ${GWidgetsd}
					debug ${RtMidid}
					debug ${cryptod}
					debug ${libvorbisd}
					debug ${libvorbisencd}
					debug ${liboggd}
					debug ${libflacd}
					debug ${libsndfiled}
					debug ${libresampled}			
					#debug ${libmpg123}
					optimized ${COREMIDI_LIBRARY}
					optimized ${COREAUDIO_LIBRARY}
					optimized ${COREFOUNDATION_LIBRARY}
					optimized ${AUDIOTOOLBOX_LIBRARY}
					optimized ${AUDIOUNIT_LIBRARY}
					optimized ${CORESERVICES_LIBRARY}
					optimized ${IOKIT_LIBRARY}
					optimized ${OPENGL_LIBRARY}	
					optimized ${portaudio}
					optimized ${GWidgets}
					optimized ${RtMidi}
					optimized ${crypto}
					optimized ${libvorbis}
					optimized ${libvorbisenc}
					optimized ${libogg}
					optimized ${libflac}
					optimized ${libsndfile}
					optimized ${libresample}
					#optimized ${libmpg123}
					)
	##-------------------------------------------------------------------------

ENDIF (APPLE)
##--------------------------------------------





##----------------------------------------
##        ##### LINUX #####
##----------------------------------------
IF (UNIX)
IF (!APPLE)

	MESSAGE("Detected LINUX environment")

	SET(EXECUTABLE_OUTPUT_PATH ${eTrigger_SOURCE_DIR}/../linux_bin
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${eTrigger_SOURCE_DIR}/../linux_lib
		CACHE PATH "Single output directory for building all libraries.")
	
	##------ Find Libraries ---------------------------------------
	FIND_LIBRARY(GWidgetsd libGWidgets_d.a ${eTrigger_SOURCE_DIR}/../linux_lib)
	FIND_LIBRARY(RtMidid libRtMidi_d.a ${eTrigger_SOURCE_DIR}/../linux_lib)
	FIND_LIBRARY(portaudiod libPortaudio_d.a ${eTrigger_SOURCE_DIR}/../linux_lib)
	FIND_LIBRARY(cryptod crypto_d.a ${eTrigger_SOURCE_DIR}/../linux_lib) 	
	FIND_LIBRARY(libsndfiled libSndfile_d.a ${eTrigger_SOURCE_DIR}/../linux_lib)
	FIND_LIBRARY(libresampled libresample_d.a ${eTrigger_SOURCE_DIR}/../linux_lib)

	FIND_LIBRARY(GWidgets libGWidgets.a ${eTrigger_SOURCE_DIR}/../linux_lib)
	FIND_LIBRARY(RtMidi libRtMidi.a ${eTrigger_SOURCE_DIR}/../linux_lib)
	FIND_LIBRARY(portaudio libPortaudio.a ${eTrigger_SOURCE_DIR}/../linux_lib)
	FIND_LIBRARY(crypto crypto ${eTrigger_SOURCE_DIR}/../linux_lib) 	
	FIND_LIBRARY(libsndfile libSndfile.a ${eTrigger_SOURCE_DIR}/../linux_lib)
	FIND_LIBRARY(libresample libresample.a ${eTrigger_SOURCE_DIR}/../linux_lib)

    FIND_LIBRARY(ASOUND_LIBRARY asound)
	
	ADD_DEFINITIONS(-DLINUX)
	ADD_DEFINITIONS(-D__WXGTK__)
	ADD_DEFINITIONS(-DCMAKE_BUILD_TYPE=debugfull)
	ADD_DEFINITIONS(-D__LINUX_ALSASEQ__)
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/libresample/include )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/libresample/src )
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/portaudio/include )
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/portaudio/src/common )
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/cryptopp )
	
	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/mpg123/src/libmpg123 )

	INCLUDE_DIRECTORIES(${eTrigger_SOURCE_DIR}/../lib/RtMidi )

	##----- eTrigger ------------------------------------------------------
	GET_TARGET_PROPERTY(MyExecutable_PATH eTrigger LOCATION)
	ADD_EXECUTABLE(eTrigger ${eTrigger_SRCS})
	TARGET_LINK_LIBRARIES(eTrigger  ${wxWidgets_LIBRARIES}
					debug ${portaudiod}
					debug ${GWidgetsd}
					debug ${RtMidid}
					debug ${ASOUND_LIBRARY}
					optimized ${portaudio}
					optimized ${GWidgets}
					optimized ${RtMidi}
					optimized ${ASOUND_LIBRARY}
					#optimized ${WX_qa} 
					#optimized ${WX_xml} 
					#optimized ${WX_net} 
					#optimized ${WX_adv} 
					#optimized ${libsndfile} 
					)
	##--------------------------------------------------------------------------

ENDIF (!APPLE)
ENDIF (UNIX)
##--------------------------------------------


ELSE(wxWidgets_FOUND)
MESSAGE("wxWidgets not found!")
ENDIF(wxWidgets_FOUND)
