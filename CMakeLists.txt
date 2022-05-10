#################################
####       eTrigger          ####
#################################

###### Supported Compilers ######
#
# Visual Studio 8 2005
# Visual Studio 9 2008
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

PROJECT( Aquawicket )

INCLUDE_DIRECTORIES( ${Aquawicket_SOURCE_DIR} ${wxWidgets_INCLUDE_DIRS} )


##-------------------------------------
##  eTrigger.exe
##-------------------------------------  
SET(eTrigger_SRCS
eTrigger/eTrigger.txt
eTrigger/app.rc
eTrigger/app.ico
eTrigger/App.h 
eTrigger/App.cpp 
#eTrigger/Main.h
#eTrigger/Main.cpp
eTrigger/MainFrame.h 
eTrigger/MainFrame.cpp
eTrigger/Err.h
eTrigger/Tracks.h 
eTrigger/Tracks.cpp
eTrigger/Trigger.h 
eTrigger/Trigger.cpp
eTrigger/TriggerDialog.h 
eTrigger/TriggerDialog.cpp  
eTrigger/MidiCC.h 
eTrigger/MidiCC.cpp
eTrigger/MidiCCDialog.h 
eTrigger/MidiCCDialog.cpp 
eTrigger/Process.h 
eTrigger/Process.cpp
eTrigger/Midi.h
eTrigger/Midi.cpp
eTrigger/MidiDialog.h 
eTrigger/MidiDialog.cpp
eTrigger/MenuPanel.h
eTrigger/MenuPanel.cpp
eTrigger/Audio.h 
eTrigger/Audio.cpp 
eTrigger/AudioDialog.h 
eTrigger/AudioDialog.cpp
eTrigger/Joystick.h 
eTrigger/Joystick.cpp 
eTrigger/JoystickDialog.h 
eTrigger/JoystickDialog.cpp
eTrigger/OptionsDialog.h 
eTrigger/OptionsDialog.cpp 
eTrigger/StatusDialog.h
eTrigger/StatusDialog.cpp
eTrigger/Wizard.h 
eTrigger/Wizard.cpp 
eTrigger/KeyToString.h
eTrigger/AboutDialog.h
eTrigger/AboutDialog.cpp
eTrigger/joystickEx.h
eTrigger/joystickEx.cpp
eTrigger/Network.h
eTrigger/Network.cpp
eTrigger/AdminDialog.h
eTrigger/AdminDialog.cpp
eTrigger/stdwx.h
eTrigger/stdwx.cpp
eTrigger/Timer.h
eTrigger/Timer.cpp
eTrigger/Security.h
eTrigger/Security.cpp
eTrigger/diskid32.h
eTrigger/diskid32.cpp
eTrigger/MidiMonitor.h
eTrigger/MidiMonitor.cpp
eTrigger/NotesDialog.h
eTrigger/NotesDialog.cpp
eTrigger/DebugDialog.h
eTrigger/DebugDialog.cpp
eTrigger/PianoDialog.h
eTrigger/PianoDialog.cpp
eTrigger/VelocityDialog.h
eTrigger/VelocityDialog.cpp
eTrigger/Tray.h
eTrigger/Tray.cpp
eTrigger/SoundController.h
eTrigger/SoundCOntroller.cpp
eTrigger/ReSample.h
eTrigger/ReSample.cpp
eTrigger/Samples.h
eTrigger/Samples.cpp
eTrigger/SampleDialog.h
eTrigger/SampleDialog.cpp
eTrigger/CpuUsage.h
eTrigger/CpuUsage.cpp
eTrigger/Details.h
eTrigger/Details.cpp
eTrigger/MainPanel.h
eTrigger/MainPanel.cpp
eTrigger/VelToPosAvgDlg.h
eTrigger/VelToPosAvgDlg.cpp
eTrigger/SequencerDialog.h
eTrigger/SequencerDialog.cpp
eTrigger/SequencePlayer.h
eTrigger/SequencePlayer.cpp
eTrigger/EtmFile.h
eTrigger/EtmFile.cpp
eTrigger/EtmEditorDialog2.h
eTrigger/EtmEditorDialog2.cpp
eTrigger/EtmPlayerDialog.h
eTrigger/EtmPlayerDialog.cpp
eTrigger/EtmPlayerOptions.h
eTrigger/EtmPlayerOptions.cpp
eTrigger/Waveform.h
eTrigger/Waveform.cpp
eTrigger/Midiform.h
eTrigger/Midiform.cpp
eTrigger/DrumTypeCodes.h
)

##-------------------------------------
##  eTrigger.dll
##-------------------------------------  
# Add the source files  
SET(eTriggerVST_SRCS
eTriggerVST/eTriggerVST.txt
eTriggerVST/wxVST.cpp
eTriggerVST/wxVST.h
eTriggerVST/eTriggerVST.h
eTriggerVST/eTriggerVST.cpp
#eTrigger/Main.h
#eTrigger/Main.cpp
eTrigger/MainPanel.h
eTrigger/MainPanel.cpp
eTrigger/app.rc
eTrigger/app.ico
eTrigger/Err.h
eTrigger/Tracks.h 
eTrigger/Tracks.cpp
eTrigger/Trigger.h 
eTrigger/Trigger.cpp
eTrigger/TriggerDialog.h 
eTrigger/TriggerDialog.cpp  
eTrigger/MidiCC.h 
eTrigger/MidiCC.cpp
eTrigger/MidiCCDialog.h 
eTrigger/MidiCCDialog.cpp 
eTrigger/Process.h 
eTrigger/Process.cpp
eTrigger/Midi.h
eTrigger/Midi.cpp
eTrigger/MidiDialog.h 
eTrigger/MidiDialog.cpp
eTrigger/MenuPanel.h
eTrigger/MenuPanel.cpp
eTrigger/Audio.h 
eTrigger/Audio.cpp 
eTrigger/AudioDialog.h 
eTrigger/AudioDialog.cpp
eTrigger/Joystick.h 
eTrigger/Joystick.cpp 
eTrigger/JoystickDialog.h 
eTrigger/JoystickDialog.cpp
eTrigger/OptionsDialog.h 
eTrigger/OptionsDialog.cpp 
eTrigger/StatusDialog.h
eTrigger/StatusDialog.cpp
eTrigger/Wizard.h 
eTrigger/Wizard.cpp 
eTrigger/KeyToString.h
eTrigger/AboutDialog.h
eTrigger/AboutDialog.cpp
eTrigger/joystickEx.h
eTrigger/joystickEx.cpp
eTrigger/Network.h
eTrigger/Network.cpp
eTrigger/AdminDialog.h
eTrigger/AdminDialog.cpp
eTrigger/stdwx.h
eTrigger/stdwx.cpp
eTrigger/Timer.h
eTrigger/Timer.cpp
eTrigger/Security.h
eTrigger/Security.cpp
eTrigger/diskid32.h
eTrigger/diskid32.cpp
eTrigger/MidiMonitor.h
eTrigger/MidiMonitor.cpp
eTrigger/NotesDialog.h
eTrigger/NotesDialog.cpp
eTrigger/DebugDialog.h
eTrigger/DebugDialog.cpp
eTrigger/PianoDialog.h
eTrigger/PianoDialog.cpp
eTrigger/VelocityDialog.h
eTrigger/VelocityDialog.cpp
eTrigger/Tray.h
eTrigger/Tray.cpp
eTrigger/SoundController.h
eTrigger/SoundController.cpp
eTrigger/ReSample.h
eTrigger/ReSample.cpp
eTrigger/Samples.h
eTrigger/Samples.cpp
eTrigger/SampleDialog.h
eTrigger/SampleDialog.cpp
eTrigger/CpuUsage.h
eTrigger/CpuUsage.cpp
eTrigger/Details.h
eTrigger/Details.cpp
eTrigger/VelToPosAvgDlg.h
eTrigger/VelToPosAvgDlg.cpp
eTrigger/SequencerDialog.h
eTrigger/SequencerDialog.cpp
eTrigger/EtmFile.h
eTrigger/EtmFile.cpp
eTrigger/EtmPlayerDialog.h
eTrigger/EtmPlayerDialog.cpp
eTrigger/EtmPlayerOptions.h
eTrigger/EtmPlayerOptions.cpp
eTrigger/Waveform.h
eTrigger/Waveform.cpp
eTrigger/Midiform.h
eTrigger/Midiform.cpp
eTrigger/DrumTypeCodes.h
)

##-------------------------------------
##  eTriggerKeyGenerator.exe
##-------------------------------------
SET(eTriggerKeyGenerator_SRCS
eTriggerKeyGenerator/KeyGenerator.txt
eTriggerKeyGenerator/App.h
eTriggerKeyGenerator/App.cpp
eTriggerKeyGenerator/KeyGen.h
eTriggerKeyGenerator/KeyGen.cpp
)

##-------------------------------------
##  eTriggerServer.exe
##-------------------------------------  
SET(eTriggerServer_SRCS
eTriggerServer/eTriggerServer.txt
eTriggerServer/app.rc
eTriggerServer/app.ico
eTriggerServer/App.h
eTriggerServer/App.cpp
eTriggerServer/server.h
eTriggerServer/server.cpp
eTriggerServer/UserData.cpp
eTriggerServer/UserData.h
eTriggerServer/tray.h
eTriggerServer/tray.cpp
)

##-------------------------------------
##  eTriggerUpdater.exe
##-------------------------------------  
SET(eTriggerUpdater_SRCS
eTriggerUpdater/eTriggerUpdater.txt
eTriggerUpdater/App.h
eTriggerUpdater/App.cpp
)

##------------------------------------------------
##  portaudio.lib
##------------------------------------------------
SET(portaudio_SRCS
lib-src/portaudio/include/pa_asio.h
lib-src/portaudio/include/pa_win_ds.h
lib-src/portaudio/include/pa_win_wasapi.h
lib-src/portaudio/include/pa_win_waveformat.h
lib-src/portaudio/include/pa_win_wmme.h
lib-src/portaudio/include/portaudio.h
lib-src/portaudio/build/msvc/portaudio.def
lib-src/portaudio/src/common/pa_allocation.c
lib-src/portaudio/src/common/pa_converters.c
lib-src/portaudio/src/common/pa_cpuload.c
lib-src/portaudio/src/common/pa_debugprint.c
lib-src/portaudio/src/common/pa_dither.c
lib-src/portaudio/src/common/pa_front.c
lib-src/portaudio/src/hostapi/skeleton/pa_hostapi_skeleton.c
lib-src/portaudio/src/common/pa_process.c
lib-src/portaudio/src/common/pa_ringbuffer.c
lib-src/portaudio/src/common/pa_stream.c
lib-src/portaudio/src/common/pa_trace.c
lib-src/portaudio/src/hostapi/asio/ASIOSDK/common/asio.cpp
lib-src/portaudio/src/hostapi/asio/ASIOSDK/host/asiodrivers.cpp
lib-src/portaudio/src/hostapi/asio/ASIOSDK/host/pc/asiolist.cpp
lib-src/portaudio/src/hostapi/asio/pa_asio.cpp
lib-src/portaudio/src/hostapi/dsound/pa_win_ds.c
lib-src/portaudio/src/hostapi/dsound/pa_win_ds_dynlink.c
lib-src/portaudio/src/hostapi/wasapi/pa_win_wasapi.c
lib-src/portaudio/src/hostapi/wdmks/pa_win_wdmks.c
lib-src/portaudio/src/hostapi/wmme/pa_win_wmme.c
lib-src/portaudio/src/os/win/pa_win_coinitialize.c
lib-src/portaudio/src/os/win/pa_win_hostapis.c
lib-src/portaudio/src/os/win/pa_win_util.c
lib-src/portaudio/src/os/win/pa_win_waveformat.c
lib-src/portaudio/src/os/win/pa_win_wdmks_utils.c
lib-src/portaudio/src/os/win/pa_x86_plain_converters.c
)

SOURCE_GROUP("Resource Files" FILES
lib-src/portaudio/build/msvc/portaudio.def
)
	
SOURCE_GROUP("Source Files\\common" FILES
lib-src/portaudio/src/common/pa_allocation.c
lib-src/portaudio/src/common/pa_converters.c
lib-src/portaudio/src/common/pa_cpuload.c
lib-src/portaudio/src/common/pa_debugprint.c
lib-src/portaudio/src/common/pa_dither.c
lib-src/portaudio/src/common/pa_front.c
lib-src/portaudio/src/hostapi/skeleton/pa_hostapi_skeleton.c
lib-src/portaudio/src/common/pa_process.c
lib-src/portaudio/src/common/pa_ringbuffer.c
lib-src/portaudio/src/common/pa_stream.c
lib-src/portaudio/src/common/pa_trace.c
)
	
SOURCE_GROUP("Source Files\\hostapi\\ASIO" FILES
lib-src/portaudio/src/hostapi/asio/pa_asio.cpp
)

SOURCE_GROUP("Source Files\\hostapi\\ASIO\\ASIOSDK" FILES
lib-src/portaudio/src/hostapi/asio/ASIOSDK/common/asio.cpp
lib-src/portaudio/src/hostapi/asio/ASIOSDK/host/asiodrivers.cpp
lib-src/portaudio/src/hostapi/asio/ASIOSDK/host/pc/asiolist.cpp
)

SOURCE_GROUP("Source Files\\hostapi\\dsound" FILES
lib-src/portaudio/src/hostapi/dsound/pa_win_ds.c
lib-src/portaudio/src/hostapi/dsound/pa_win_ds_dynlink.c
)

SOURCE_GROUP("Source Files\\hostapi\\wasapi" FILES
lib-src/portaudio/src/hostapi/wasapi/pa_win_wasapi.c
)

SOURCE_GROUP("Source Files\\hostapi\\wdmks" FILES
lib-src/portaudio/src/hostapi/wdmks/pa_win_wdmks.c
)
	
SOURCE_GROUP("Source Files\\hostapi\\wmme" FILES
lib-src/portaudio/src/hostapi/wmme/pa_win_wmme.c
)
	
SOURCE_GROUP("Source Files\\os\\win" FILES
lib-src/portaudio/src/os/win/pa_win_coinitialize.c
lib-src/portaudio/src/os/win/pa_win_hostapis.c
lib-src/portaudio/src/os/win/pa_win_util.c
lib-src/portaudio/src/os/win/pa_win_waveformat.c
lib-src/portaudio/src/os/win/pa_win_wdmks_utils.c
lib-src/portaudio/src/os/win/pa_x86_plain_converters.c
)

##------------------------------------------------
##  portmidi.lib
##------------------------------------------------
SET(portmidi_SRCS
lib-src/portmidi/pm_common/pminternal.h
lib-src/portmidi/pm_common/pmutil.h
lib-src/portmidi/pm_win/pmwinmm.h
lib-src/portmidi/pm_common/portmidi.h
lib-src/portmidi/pm_common/pmutil.c
lib-src/portmidi/pm_win/pmwin.c
lib-src/portmidi/pm_win/pmwinmm.c
lib-src/portmidi/pm_common/portmidi.c
)

##------------------------------------------------
##  RtMidi.lib
##------------------------------------------------
SET(RtMidi_SRCS
lib-src/RtMidi/RtError.h 
lib-src/RtMidi/RtMidi.cpp 
lib-src/RtMidi/RtMidi.h 
)


##------------------------------------------------
##  RtAudio.lib
##------------------------------------------------
SET(RtAudio_SRCS
lib-src/RtAudio/RtError.h 
lib-src/RtAudio/RtAudio.cpp 
lib-src/RtAudio/RtAudio.h 
)


##------------------------------------------------
##  GWidgets.lib
##------------------------------------------------
SET(GWidgets_SRCS
lib-src/Gwidgets/GImage/GImage.h 
lib-src/Gwidgets/GImage/GImage.cpp 
lib-src/Gwidgets/GButton/GButton.h 
lib-src/Gwidgets/GButton/GButton.cpp 
lib-src/Gwidgets/GText/GText.h 
lib-src/Gwidgets/GText/GText.cpp 
lib-src/Gwidgets/GMeter/GMeter.h 
lib-src/Gwidgets/GMeter/GMeter.cpp 
lib-src/Gwidgets/GSlider/GSlider.h 
lib-src/Gwidgets/GSlider/GSlider.cpp 
lib-src/Gwidgets/GKnob/GKnob.h 
lib-src/Gwidgets/GKnob/GKnob.cpp 
lib-src/Gwidgets/GScrollBar/GScrollBar.h 
lib-src/Gwidgets/GScrollBar/GScrollBar.cpp 
lib-src/Gwidgets/GToggle/GToggle.h
lib-src/Gwidgets/GToggle/GToggle.cpp
lib-src/Gwidgets/GNumberBox/GNumberBox.h
lib-src/Gwidgets/GNumberBox/GNumberBox.cpp
lib-src/Gwidgets/GCurve/GCurve.h
lib-src/Gwidgets/GCurve/GCurve.cpp
lib-src/Gwidgets/GImageSelector/GImageSelector.h
lib-src/Gwidgets/GImageSelector/GImageSelector.cpp
lib-src/Gwidgets/GHelper/GHelper.h
lib-src/Gwidgets/GHelper/GHelper.cpp
lib-src/Gwidgets/GLFont/glfont2.h
lib-src/Gwidgets/GLFont/glfont2.cpp
lib-src/Gwidgets/GLImage/GLImage.h
lib-src/Gwidgets/GLImage/GLImage.cpp
)

##-------------------------------------------------
## libresample.lib
##-------------------------------------------------
SET(libresample_SRCS 
lib-src/libresample/include/libresample.h
lib-src/libresample/src/configtemplate.h
lib-src/libresample/src/filterkit.c
lib-src/libresample/src/filterkit.h
lib-src/libresample/src/resample.c
lib-src/libresample/src/resample_defs.h
lib-src/libresample/src/resamplesubs.c
)


##-------------------------------------------------
## VstSDK.lib
##-------------------------------------------------
SET(vstsdk_SRCS 
lib-src/VstSDK/source/common/AEffect.h
lib-src/VstSDK/source/common/aeffectx.h
lib-src/VstSDK/source/common/AEffEditor.hpp
lib-src/VstSDK/source/common/aeffguieditor.cpp
lib-src/VstSDK/source/common/aeffguieditor.h
lib-src/VstSDK/source/common/AudioEffect.cpp
lib-src/VstSDK/source/common/AudioEffect.hpp
lib-src/VstSDK/source/common/audioeffectx.cpp
lib-src/VstSDK/source/common/audioeffectx.h
#lib-src/VstSDK/source/common/vstcontrols.cpp
#lib-src/VstSDK/source/common/vstcontrols.h
lib-src/VstSDK/source/common/vstfxstore.h
#lib-src/VstSDK/source/common/vstgui.cpp
#lib-src/VstSDK/source/common/vstgui.h
#lib-src/VstSDK/source/common/vstplugscarbon.h
#lib-src/VstSDK/source/common/vstplugsmac.h
#lib-src/VstSDK/source/common/vstplugsmacho.h
)

##-------------------------------------------------
##  libmpg123.lib
##-------------------------------------------------
SET(mpg123_SRCS
lib-src/mpg123/ports/MSVC++/config.h
lib-src/mpg123/ports/MSVC++/mpg123.h
lib-src/mpg123/ports/MSVC++/msvc.c
lib-src/mpg123/src/libmpg123/compat.c
lib-src/mpg123/src/libmpg123/compat.h
lib-src/mpg123/src/libmpg123/dct36_3dnow.S
lib-src/mpg123/src/libmpg123/dct36_3dnowext.S
lib-src/mpg123/src/libmpg123/dct64.c
lib-src/mpg123/src/libmpg123/dct64_3dnow.S
lib-src/mpg123/src/libmpg123/dct64_3dnowext.S
lib-src/mpg123/src/libmpg123/dct64_mmx.S
lib-src/mpg123/src/libmpg123/dct64_sse.S
lib-src/mpg123/src/libmpg123/dct64_sse_float.S
lib-src/mpg123/src/libmpg123/dct64_x86_64.S
lib-src/mpg123/src/libmpg123/dct64_x86_64_float.S
lib-src/mpg123/src/libmpg123/debug.h
lib-src/mpg123/src/libmpg123/decode.h
lib-src/mpg123/src/libmpg123/equalizer.c
lib-src/mpg123/src/libmpg123/equalizer_3dnow.S
lib-src/mpg123/src/libmpg123/format.c
lib-src/mpg123/src/libmpg123/frame.c
lib-src/mpg123/src/libmpg123/frame.h
lib-src/mpg123/src/libmpg123/getbits.h
lib-src/mpg123/src/libmpg123/getcpuflags.h
lib-src/mpg123/src/libmpg123/getcpuflags.S
lib-src/mpg123/src/libmpg123/huffman.h
lib-src/mpg123/src/libmpg123/icy.c
lib-src/mpg123/src/libmpg123/icy.h
lib-src/mpg123/src/libmpg123/icy2utf8.c
lib-src/mpg123/src/libmpg123/icy2utf8.h
lib-src/mpg123/src/libmpg123/id3.c
lib-src/mpg123/src/libmpg123/id3.h
lib-src/mpg123/src/libmpg123/index.c
lib-src/mpg123/src/libmpg123/index.h
lib-src/mpg123/src/libmpg123/l2tables.h
lib-src/mpg123/src/libmpg123/layer1.c
lib-src/mpg123/src/libmpg123/layer2.c
lib-src/mpg123/src/libmpg123/layer3.c
lib-src/mpg123/src/libmpg123/libmpg123.c
lib-src/mpg123/src/libmpg123/mangle.h
lib-src/mpg123/src/libmpg123/mpg123.h.in
lib-src/mpg123/src/libmpg123/mpg123lib_intern.h
lib-src/mpg123/src/libmpg123/ntom.c
lib-src/mpg123/src/libmpg123/optimize.c
lib-src/mpg123/src/libmpg123/optimize.h
lib-src/mpg123/src/libmpg123/parse.c
lib-src/mpg123/src/libmpg123/parse.h
lib-src/mpg123/src/libmpg123/reader.h
lib-src/mpg123/src/libmpg123/readers.c
lib-src/mpg123/src/libmpg123/sample.h
lib-src/mpg123/src/libmpg123/stringbuf.c
lib-src/mpg123/src/libmpg123/synth.c
lib-src/mpg123/src/libmpg123/synth.h
lib-src/mpg123/src/libmpg123/synth_3dnow.S
lib-src/mpg123/src/libmpg123/synth_3dnowext.S
lib-src/mpg123/src/libmpg123/synth_8bit.c
lib-src/mpg123/src/libmpg123/synth_i586.S
lib-src/mpg123/src/libmpg123/synth_i586_dither.S
lib-src/mpg123/src/libmpg123/synth_mmx.S
lib-src/mpg123/src/libmpg123/synth_real.c
lib-src/mpg123/src/libmpg123/synth_s32.c
lib-src/mpg123/src/libmpg123/synth_sse.S
lib-src/mpg123/src/libmpg123/synth_sse_accurate.S
lib-src/mpg123/src/libmpg123/synth_sse_float.S
lib-src/mpg123/src/libmpg123/synth_sse_s32.S
lib-src/mpg123/src/libmpg123/synth_stereo_sse_accurate.S
lib-src/mpg123/src/libmpg123/synth_stereo_sse_float.S
lib-src/mpg123/src/libmpg123/synth_stereo_sse_s32.S
lib-src/mpg123/src/libmpg123/synth_stereo_x86_64.S
lib-src/mpg123/src/libmpg123/synth_stereo_x86_64_accurate.S
lib-src/mpg123/src/libmpg123/synth_stereo_x86_64_float.S
lib-src/mpg123/src/libmpg123/synth_stereo_x86_64_s32.S
lib-src/mpg123/src/libmpg123/synth_x86_64.S
lib-src/mpg123/src/libmpg123/synth_x86_64_accurate.S
lib-src/mpg123/src/libmpg123/synth_x86_64_float.S
lib-src/mpg123/src/libmpg123/synth_x86_64_s32.S
lib-src/mpg123/src/libmpg123/tabinit.c
lib-src/mpg123/src/libmpg123/tabinit_mmx.S
lib-src/mpg123/src/libmpg123/true.h
)

##-------------------------------------------------
##  crypto.lib
##-------------------------------------------------
SET(crypto_SRCS
lib-src/cryptopp/3way.h
lib-src/cryptopp/adler32.h
lib-src/cryptopp/aes.h
lib-src/cryptopp/algebra.h
lib-src/cryptopp/algparam.h
lib-src/cryptopp/arc4.h
lib-src/cryptopp/argnames.h
lib-src/cryptopp/asn.h
lib-src/cryptopp/base32.h
lib-src/cryptopp/base64.h
lib-src/cryptopp/basecode.h
lib-src/cryptopp/blowfish.h
lib-src/cryptopp/blumshub.h
lib-src/cryptopp/camellia.h
lib-src/cryptopp/cast.h
lib-src/cryptopp/cbcmac.h
lib-src/cryptopp/channels.h
lib-src/cryptopp/config.h
lib-src/cryptopp/cpu.h
lib-src/cryptopp/crc.h
lib-src/cryptopp/cryptlib.h
lib-src/cryptopp/default.h
lib-src/cryptopp/des.h
lib-src/cryptopp/dh.h
lib-src/cryptopp/dh2.h
lib-src/cryptopp/dmac.h
lib-src/cryptopp/dsa.h
lib-src/cryptopp/ec2n.h
lib-src/cryptopp/eccrypto.h
lib-src/cryptopp/ecp.h
lib-src/cryptopp/elgamal.h
lib-src/cryptopp/emsa2.h
lib-src/cryptopp/eprecomp.h
lib-src/cryptopp/esign.h
lib-src/cryptopp/files.h
lib-src/cryptopp/filters.h
lib-src/cryptopp/fips140.h
lib-src/cryptopp/fltrimpl.h
lib-src/cryptopp/gf256.h
lib-src/cryptopp/gf2_32.h
lib-src/cryptopp/gf2n.h
lib-src/cryptopp/gfpcrypt.h
lib-src/cryptopp/gost.h
lib-src/cryptopp/gzip.h
lib-src/cryptopp/hex.h
lib-src/cryptopp/hmac.h
lib-src/cryptopp/hrtimer.h
lib-src/cryptopp/ida.h
lib-src/cryptopp/idea.h
lib-src/cryptopp/integer.h
lib-src/cryptopp/iterhash.h
lib-src/cryptopp/lubyrack.h
lib-src/cryptopp/luc.h
lib-src/cryptopp/mars.h
lib-src/cryptopp/md2.h
lib-src/cryptopp/md4.h
lib-src/cryptopp/md5.h
lib-src/cryptopp/mdc.h
lib-src/cryptopp/misc.h
lib-src/cryptopp/modarith.h
lib-src/cryptopp/modes.h
lib-src/cryptopp/modexppc.h
lib-src/cryptopp/mqueue.h
lib-src/cryptopp/mqv.h
lib-src/cryptopp/nbtheory.h
lib-src/cryptopp/network.h
lib-src/cryptopp/nr.h
lib-src/cryptopp/oaep.h
lib-src/cryptopp/oids.h
lib-src/cryptopp/osrng.h
lib-src/cryptopp/panama.h
lib-src/cryptopp/pch.h
lib-src/cryptopp/pkcspad.h
lib-src/cryptopp/polynomi.h
lib-src/cryptopp/pssr.h
lib-src/cryptopp/pubkey.h
lib-src/cryptopp/pwdbased.h
lib-src/cryptopp/queue.h
lib-src/cryptopp/rabin.h
lib-src/cryptopp/randpool.h
lib-src/cryptopp/rc2.h
lib-src/cryptopp/rc5.h
lib-src/cryptopp/rc6.h
lib-src/cryptopp/rijndael.h
lib-src/cryptopp/ripemd.h
lib-src/cryptopp/rng.h
lib-src/cryptopp/rsa.h
lib-src/cryptopp/rw.h
lib-src/cryptopp/safer.h
lib-src/cryptopp/salsa.h
lib-src/cryptopp/seal.h
lib-src/cryptopp/secblock.h
lib-src/cryptopp/seckey.h
lib-src/cryptopp/serpent.h
lib-src/cryptopp/sha.h
lib-src/cryptopp/shacal2.h
lib-src/cryptopp/shark.h
lib-src/cryptopp/simple.h
lib-src/cryptopp/skipjack.h
lib-src/cryptopp/smartptr.h
lib-src/cryptopp/socketft.h
lib-src/cryptopp/sosemanuk.h
lib-src/cryptopp/square.h
lib-src/cryptopp/strciphr.h
lib-src/cryptopp/tea.h
lib-src/cryptopp/tiger.h
lib-src/cryptopp/trdlocal.h
lib-src/cryptopp/trunhash.h
lib-src/cryptopp/ttmac.h
lib-src/cryptopp/twofish.h
lib-src/cryptopp/vmac.h
lib-src/cryptopp/wait.h
lib-src/cryptopp/wake.h
lib-src/cryptopp/whrlpool.h
lib-src/cryptopp/winpipes.h
lib-src/cryptopp/words.h
lib-src/cryptopp/xtr.h
lib-src/cryptopp/xtrcrypt.h
lib-src/cryptopp/zdeflate.h
lib-src/cryptopp/zinflate.h
lib-src/cryptopp/zlib.h
lib-src/cryptopp/3way.cpp
lib-src/cryptopp/adler32.cpp
lib-src/cryptopp/algebra.cpp
lib-src/cryptopp/algparam.cpp
lib-src/cryptopp/arc4.cpp
lib-src/cryptopp/asn.cpp
lib-src/cryptopp/base32.cpp
lib-src/cryptopp/base64.cpp
lib-src/cryptopp/basecode.cpp
lib-src/cryptopp/bfinit.cpp
lib-src/cryptopp/blowfish.cpp
lib-src/cryptopp/blumshub.cpp
lib-src/cryptopp/camellia.cpp
lib-src/cryptopp/cast.cpp
lib-src/cryptopp/casts.cpp
lib-src/cryptopp/cbcmac.cpp
lib-src/cryptopp/channels.cpp
lib-src/cryptopp/cpu.cpp
lib-src/cryptopp/crc.cpp
lib-src/cryptopp/cryptlib.cpp
lib-src/cryptopp/default.cpp
lib-src/cryptopp/des.cpp
lib-src/cryptopp/dessp.cpp
lib-src/cryptopp/dh.cpp
lib-src/cryptopp/dh2.cpp
lib-src/cryptopp/dll.cpp
lib-src/cryptopp/dsa.cpp
lib-src/cryptopp/ec2n.cpp
lib-src/cryptopp/eccrypto.cpp
lib-src/cryptopp/ecp.cpp
lib-src/cryptopp/elgamal.cpp
lib-src/cryptopp/emsa2.cpp
lib-src/cryptopp/eprecomp.cpp
lib-src/cryptopp/esign.cpp
lib-src/cryptopp/files.cpp
lib-src/cryptopp/filters.cpp
lib-src/cryptopp/fips140.cpp
lib-src/cryptopp/fipstest.cpp
lib-src/cryptopp/gf256.cpp
lib-src/cryptopp/gf2_32.cpp
lib-src/cryptopp/gf2n.cpp
lib-src/cryptopp/gfpcrypt.cpp
lib-src/cryptopp/gost.cpp
lib-src/cryptopp/gzip.cpp
lib-src/cryptopp/hex.cpp
lib-src/cryptopp/hmac.cpp
lib-src/cryptopp/hrtimer.cpp
lib-src/cryptopp/ida.cpp
lib-src/cryptopp/idea.cpp
lib-src/cryptopp/integer.cpp
lib-src/cryptopp/iterhash.cpp
lib-src/cryptopp/luc.cpp
lib-src/cryptopp/mars.cpp
lib-src/cryptopp/marss.cpp
lib-src/cryptopp/md2.cpp
lib-src/cryptopp/md4.cpp
lib-src/cryptopp/md5.cpp
lib-src/cryptopp/misc.cpp
lib-src/cryptopp/modes.cpp
lib-src/cryptopp/mqueue.cpp
lib-src/cryptopp/mqv.cpp
lib-src/cryptopp/nbtheory.cpp
lib-src/cryptopp/network.cpp
lib-src/cryptopp/oaep.cpp
lib-src/cryptopp/osrng.cpp
lib-src/cryptopp/panama.cpp
lib-src/cryptopp/pch.cpp
lib-src/cryptopp/pkcspad.cpp
lib-src/cryptopp/polynomi.cpp
lib-src/cryptopp/pssr.cpp
lib-src/cryptopp/pubkey.cpp
lib-src/cryptopp/queue.cpp
lib-src/cryptopp/rabin.cpp
lib-src/cryptopp/randpool.cpp
lib-src/cryptopp/rc2.cpp
lib-src/cryptopp/rc5.cpp
lib-src/cryptopp/rc6.cpp
lib-src/cryptopp/rdtables.cpp
lib-src/cryptopp/rijndael.cpp
lib-src/cryptopp/ripemd.cpp
lib-src/cryptopp/rng.cpp
lib-src/cryptopp/rsa.cpp
lib-src/cryptopp/rw.cpp
lib-src/cryptopp/safer.cpp
lib-src/cryptopp/salsa.cpp
lib-src/cryptopp/seal.cpp
lib-src/cryptopp/serpent.cpp
lib-src/cryptopp/sha.cpp
lib-src/cryptopp/shacal2.cpp
lib-src/cryptopp/shark.cpp
lib-src/cryptopp/sharkbox.cpp
lib-src/cryptopp/simple.cpp
lib-src/cryptopp/skipjack.cpp
lib-src/cryptopp/socketft.cpp
lib-src/cryptopp/sosemanuk.cpp
lib-src/cryptopp/square.cpp
lib-src/cryptopp/squaretb.cpp
lib-src/cryptopp/strciphr.cpp
lib-src/cryptopp/tea.cpp
lib-src/cryptopp/tftables.cpp
lib-src/cryptopp/tiger.cpp
lib-src/cryptopp/tigertab.cpp
lib-src/cryptopp/trdlocal.cpp
lib-src/cryptopp/ttmac.cpp
lib-src/cryptopp/twofish.cpp
lib-src/cryptopp/vmac.cpp
lib-src/cryptopp/wait.cpp
lib-src/cryptopp/wake.cpp
lib-src/cryptopp/whrlpool.cpp
lib-src/cryptopp/winpipes.cpp
lib-src/cryptopp/xtr.cpp
lib-src/cryptopp/xtrcrypt.cpp
lib-src/cryptopp/zdeflate.cpp
lib-src/cryptopp/zinflate.cpp
lib-src/cryptopp/zlib.cpp
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
		SET_SOURCE_FILES_PROPERTIES(eTrigger/stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/App.cpp  PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTriggerVST/eTriggerVST.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Main.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MainFrame.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Tracks.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Trigger.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/TriggerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MidiCC.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MidiCCDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Process.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Midi.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MidiDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Audio.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/AudioDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Joystick.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/JoystickDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/OptionsDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/StatusDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Wizard.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/AboutDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/joystickEx.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Network.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/AdminDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Timer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Security.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/diskid32.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MidiMonitor.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/NotesDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/DebugDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/PianoDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/VelocityDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Tray.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/SoundController.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/ReSample.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Samples.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/SampleDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/CpuUsage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Details.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MenuPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/VelToPosAvgDlg.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/SequencerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/EtmFile.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/EtmPlayerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/EtmPlayerOptions.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/EtmEditorDialog2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Waveform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Midiform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/SequencePlayer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/GLImage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/glfont2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 8 2005")

	##### Microsoft Visual Studio 2008 options #####
	IF(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")
        	SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
        	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od /EHsc")
        	SET(CMAKE_CXX_FLAGS_RELEASE "/MT /Z7 /DEBUG /O2 /EHsc /bigobj")
       		SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2 /EHsc")
       		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od /EHsc")

		### Use precompiled Headers ###
		SET_SOURCE_FILES_PROPERTIES(eTrigger/stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/App.cpp  PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTriggerVST/eTriggerVST.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Main.cpp  PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MainFrame.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Tracks.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Trigger.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/TriggerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MidiCC.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MidiCCDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Process.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Midi.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MidiDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Audio.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/AudioDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Joystick.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/JoystickDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/OptionsDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/StatusDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Wizard.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/AboutDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/joystickEx.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Network.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/AdminDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Timer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Security.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/diskid32.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MidiMonitor.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/NotesDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/DebugDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/PianoDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/VelocityDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Tray.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/SoundController.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/ReSample.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Samples.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/SampleDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/CpuUsage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Details.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MainPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MenuPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/VelToPosAvgDlg.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/SequencerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/EtmFile.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/EtmPlayerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/EtmPlayerOptions.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/EtmEditorDialog2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Waveform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Midiform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/SequencePlayer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/GLImage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/glfont2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")

	##### Microsoft Visual Studio 2010 options #####
	IF(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
        	SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
        	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od /EHsc")
        	SET(CMAKE_CXX_FLAGS_RELEASE "/MT /Z7 /DEBUG /O2 /EHsc /bigobj")
       		SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2 /EHsc")
       		SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od /EHsc")

		### Use precompiled Headers ###
		SET_SOURCE_FILES_PROPERTIES(eTrigger/stdwx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/App.cpp  PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTriggerVST/eTriggerVST.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Main.cpp  PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MainFrame.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Tracks.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Trigger.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/TriggerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MidiCC.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MidiCCDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Process.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Midi.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MidiDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Audio.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/AudioDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Joystick.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/JoystickDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/OptionsDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/StatusDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Wizard.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h") 
		SET_SOURCE_FILES_PROPERTIES(eTrigger/AboutDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/joystickEx.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Network.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/AdminDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Timer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Security.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/diskid32.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MidiMonitor.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/NotesDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/DebugDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/PianoDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/VelocityDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Tray.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/SoundController.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/ReSample.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Samples.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/SampleDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/CpuUsage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Details.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MainPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/MenuPanel.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/VelToPosAvgDlg.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/SequencerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/EtmFile.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/EtmPlayerDialog.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/EtmPlayerOptions.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/EtmEditorDialog2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Waveform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/Midiform.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/SequencePlayer.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/GLImage.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
		SET_SOURCE_FILES_PROPERTIES(eTrigger/glfont2.cpp PROPERTIES COMPILE_FLAGS "/Yustdwx.h")
	ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 10")	
	
	ENDIF(CMAKE_CXX_COMPILER MATCHES cl)

   	SET(EXECUTABLE_OUTPUT_PATH ${Aquawicket_SOURCE_DIR}/--==Windows==--
            CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${Aquawicket_SOURCE_DIR}/--==Windows==--
            CACHE PATH "Single output directory for building all libraries.")

	
	##------ Find Debug Libraries ---------------------------------------
	FIND_LIBRARY(dsound       dsound        $ENV{DXSDK_DIR}/Lib/x86 )
	FIND_LIBRARY(RtAudiod     RtAudio_d     ${Aquawicket_SOURCE_DIR}/--==Windows==--/debug)
	FIND_LIBRARY(portaudiod   portaudio_d   ${Aquawicket_SOURCE_DIR}/--==Windows==--/debug)
	FIND_LIBRARY(portmidid    portmidi_d    ${Aquawicket_SOURCE_DIR}/--==Windows==--/debug)
	FIND_LIBRARY(GWidgetsd    GWidgets_d    ${Aquawicket_SOURCE_DIR}/--==Windows==--/debug)
	FIND_LIBRARY(RtMidid      RtMidi_d      ${Aquawicket_SOURCE_DIR}/--==Windows==--/debug)	
	FIND_LIBRARY(cryptod      crypto_d      ${Aquawicket_SOURCE_DIR}/--==Windows==--/debug)
	FIND_LIBRARY(libsndfiled  sndfile_d     ${Aquawicket_SOURCE_DIR}/--==Windows==--/debug)
	FIND_LIBRARY(libresampled libresample_d ${Aquawicket_SOURCE_DIR}/--==Windows==--/debug)
	FIND_LIBRARY(libvstd      libvst_d      ${Aquawicket_SOURCE_DIR}/--==Windows==--/debug)
	FIND_LIBRARY(libmpg123d    libmpg123_d   ${Aquawicket_SOURCE_DIR}/--==Windows==--/debug)
	 
	##------ Find Release Libraries ---------------------------------------
	FIND_LIBRARY(RtAudio     RtAudio     ${Aquawicket_SOURCE_DIR}/--==Windows==--/release)	
	FIND_LIBRARY(portaudio   portaudio   ${Aquawicket_SOURCE_DIR}/--==Windows==--/release)
	FIND_LIBRARY(portmidi    portmidi    ${Aquawicket_SOURCE_DIR}/--==Windows==--/release)
	FIND_LIBRARY(GWidgets    GWidgets    ${Aquawicket_SOURCE_DIR}/--==Windows==--/release)
	FIND_LIBRARY(RtMidi      RtMidi      ${Aquawicket_SOURCE_DIR}/--==Windows==--/release)
	FIND_LIBRARY(crypto      crypto      ${Aquawicket_SOURCE_DIR}/--==Windows==--/release)
	FIND_LIBRARY(libsndfile  sndfile     ${Aquawicket_SOURCE_DIR}/--==Windows==--/release)
	FIND_LIBRARY(libresample libresample ${Aquawicket_SOURCE_DIR}/--==Windows==--/release)
	FIND_LIBRARY(libvst      libvst      ${Aquawicket_SOURCE_DIR}/--==Windows==--/release)
	FIND_LIBRARY(libmpg123   libmpg123   ${Aquawicket_SOURCE_DIR}/--==Windows==--/release)

	##------ portaudio -----------------------------------------------------------------------------
	INCLUDE_DIRECTORIES($ENV{DXSDK_DIR}/Include )
	#INCLUDE_DIRECTORIES($ENV{DXSDK_DIR}/Lib/x86 )
	#INCLUDE_DIRECTORIES($ENV{WINSDK}/Include )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio/include )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio/src/common )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio/src/os/win )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio/src/hostapi/asio/ASIOSDK/common )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio/src/hostapi/asio/ASIOSDK/host )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio/src/hostapi/asio/ASIOSDK/host/pc )
	ADD_LIBRARY(lib-portaudio STATIC ${portaudio_SRCS})
	SET_TARGET_PROPERTIES(lib-portaudio PROPERTIES STATIC_LIBRARY_FLAGS ksguid.lib)


	SET_TARGET_PROPERTIES(lib-portaudio PROPERTIES LINKER_LANGUAGE CXX)
	SET_TARGET_PROPERTIES(lib-portaudio PROPERTIES OUTPUT_NAME portaudio) 
	SET_TARGET_PROPERTIES(lib-portaudio PROPERTIES DEBUG_OUTPUT_NAME portaudio_d)
	SET_TARGET_PROPERTIES(lib-portaudio PROPERTIES COMPILE_DEFINITIONS WIN32,PA_ENABLE_DEBUG_OUTPUT,_CRT_SECURE_NO_DEPRECATE,PAWIN_USE_WDMKS_DEVICE_INFO,PA_USE_ASIO=1,PA_USE_DS=1,PA_USE_WMME=1,PA_USE_WASAPI=1,PA_USE_WDMKS=1)
	##-------------------------------------------------------------------------------------------------
	
	##------ portmidi -----------------------------------------------------------------------------
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portmidi/pm_common )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portmidi/pm_win )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portmidi/porttime )
	ADD_LIBRARY(lib-portmidi STATIC ${portmidi_SRCS})
	SET_TARGET_PROPERTIES(lib-portmidi PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME portmidi DEBUG_OUTPUT_NAME portmidi_d) 
	SET_TARGET_PROPERTIES(lib-portmidi PROPERTIES COMPILE_DEFINITIONS WIN32)
	##-------------------------------------------------------------------------------------------------

	##------ RtAudio --------------------------------------------------------------------
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/RtAudio )
	ADD_LIBRARY(lib-RtAudio STATIC ${RtAudio_SRCS})
	SET_TARGET_PROPERTIES(lib-RtAudio PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME RtAudio DEBUG_OUTPUT_NAME RtAudio_d)
	SET_TARGET_PROPERTIES(lib-RtAudio PROPERTIES COMPILE_DEFINITIONS WIN32)  
	##------------------------------------------------------------------------------------

	##------ RtMidi --------------------------------------------------------------------
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/RtMidi )
	ADD_LIBRARY(lib-RtMidi STATIC ${RtMidi_SRCS})
	SET_TARGET_PROPERTIES(lib-RtMidi PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME RtMidi DEBUG_OUTPUT_NAME RtMidi_d) 
	SET_TARGET_PROPERTIES(lib-RtMidi PROPERTIES COMPILE_DEFINITIONS WIN32,__WINDOWS_MM__) 
	##------------------------------------------------------------------------------------
	
	##-------- GWidgets ----------------------------------------------------------------------
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GImage )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GButton )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GCheckBox )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GMeter )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GScrollBar )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GSlider )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GKnob )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GText )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GNumberBox )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GCurve )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GImageSelector )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GHelper )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GLFont )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GLImage )
	ADD_LIBRARY(lib-GWidgets STATIC ${GWidgets_SRCS})
	SET_TARGET_PROPERTIES(lib-GWidgets PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME GWidgets DEBUG_OUTPUT_NAME GWidgets_d)
	SET_TARGET_PROPERTIES(lib-GWidgets PROPERTIES COMPILE_DEFINITIONS WIN32)
	##--------------------------------------------------------------------------------------------

	##-------- crypto -------------------------------------------------------------------
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/cryptopp )
	ADD_LIBRARY(lib-crypto STATIC ${crypto_SRCS})
	SET_TARGET_PROPERTIES(lib-crypto PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME crypto DEBUG_OUTPUT_NAME crypto_d)  
	SET_TARGET_PROPERTIES(lib-crypto PROPERTIES COMPILE_FLAGS "/Oi")
	SET_TARGET_PROPERTIES(lib-crypto PROPERTIES COMPILE_DEFINITIONS WIN32,ACCURATE_ROUNDING,IEEE_FLOAT)
	##-------------------------------------------------------------------------------------
	
	##-------- libresample ----------------------------------------------------------------
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/libresample/include )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/libresample/src )
	ADD_LIBRARY(lib-resample STATIC ${libresample_SRCS})
	SET_TARGET_PROPERTIES(lib-resample PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME libresample DEBUG_OUTPUT_NAME libresample_d)
	SET_TARGET_PROPERTIES(lib-resample PROPERTIES COMPILE_DEFINITIONS WIN32)
	##---------------------------------------------------------------------------------
 	
        ##-------- VsTSDK ----------------------------------------------------------------
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/VstSDK/source/common )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/VstSDK/source/ADelay )
	ADD_LIBRARY(lib-vstsdk STATIC ${vstsdk_SRCS})
	SET_TARGET_PROPERTIES(lib-vstsdk PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME libvst DEBUG_OUTPUT_NAME libvst_d)
	SET_TARGET_PROPERTIES(lib-vstsdk PROPERTIES COMPILE_DEFINITIONS WIN32)
	##---------------------------------------------------------------------------------

	##-------- mpg123 -------------------------------------------------------------------
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/mpg123/src/libmpg123 )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/mpg123/ports/MSVC++ )
	ADD_LIBRARY(lib-mpg123 STATIC ${mpg123_SRCS})
	SET_TARGET_PROPERTIES(lib-mpg123 PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME libmpg123 DEBUG_OUTPUT_NAME libmpg123_d)
	SET_TARGET_PROPERTIES(lib-mpg123 PROPERTIES COMPILE_DEFINITIONS WIN32,OPT_GENERIC)
	##-------------------------------------------------------------------------------------

	##----- eTriggerServer -------------------------------------------------------------------------------------
	ADD_EXECUTABLE(eTriggerServer WIN32 ${eTriggerServer_SRCS})
	TARGET_LINK_LIBRARIES(eTriggerServer ${wxWidgets_LIBRARIES} 
						debug ${WX_netd}
						debug ${WX_advd}
						debug ${GWidgetsd}
						optimized ${WX_net}
						optimized ${WX_adv}
						optimized ${GWidgets})
	SET_TARGET_PROPERTIES(eTriggerServer PROPERTIES COMPILE_DEFINITIONS WIN32)
	##-----------------------------------------------------------------------------------------------------------

	##----- eTriggerUpdater --------------------------------------------------------------------------------------
	ADD_EXECUTABLE(eTriggerUpdater WIN32 ${eTriggerUpdater_SRCS})
	TARGET_LINK_LIBRARIES(eTriggerUpdater ${wxWidgets_LIBRARIES})
	SET_TARGET_PROPERTIES(eTriggerUpdater PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME Updater)
	SET_TARGET_PROPERTIES(eTriggerUpdater PROPERTIES COMPILE_DEFINITIONS WIN32)
	##------------------------------------------------------------------------------------------------------------
	
	##----- eTriggerKeyGenerator ---------------------------------------------------------------------------------
	ADD_EXECUTABLE(eTriggerKeyGenerator WIN32 ${eTriggerKeyGenerator_SRCS})
	TARGET_LINK_LIBRARIES(eTriggerKeyGenerator ${wxWidgets_LIBRARIES}
						debug ${GWidgetsd}
						debug ${cryptod}
						optimized ${GWidgets}
						optimized ${crypto}
						)
	SET_TARGET_PROPERTIES(eTriggerKeyGenerator PROPERTIES LINKER_LANGUAGE CXX 
							      OUTPUT_NAME eTriggerKeyGenerator
							      COMPILE_DEFINITIONS WIN32) 
	##---------------------------------------------------------------------------------------------------------


	##----- eTrigger.exe------------------------------------------------------------------------------------------
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/libsndfile/Win32 )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/eTrigger )
	GET_TARGET_PROPERTY(MyExecutable_PATH Aquawicket LOCATION)
	ADD_EXECUTABLE(eTrigger WIN32 ${eTrigger_SRCS})
	TARGET_LINK_LIBRARIES(eTrigger ${wxWidgets_LIBRARIES}
						debug ${WX_qad}
						debug ${WX_xmld}
						debug ${WX_netd}
						debug ${WX_advd}
						debug ${WX_gld}
						debug winmm.lib
						#debug ksuser.lib
						debug opengl32.lib
						debug ${cryptod}
						debug ${GWidgetsd}
						debug ${RtMidid}
						debug ${libsndfiled} 
						debug ${libresampled}
						#debug ${dsound}
						debug ${portaudiod}
						debug ${portmidid}
						debug ${libmpg123d}
						#debug ${RtAudiod}	
						optimized ${WX_qa}
						optimized ${WX_xml}
						optimized ${WX_net}
						optimized ${WX_adv}
						optimized ${WX_gl}
						optimized winmm.lib
						#optimized ksuser.lib
						optimized opengl32.lib
						optimized ${crypto}
						optimized ${GWidgets}
						optimized ${RtMidi}
						optimized ${libsndfile}
						optimized ${libresample}
						#optimized ${dsound}
						optimized ${portaudio}
						optimized ${portmidi}
						optimized ${libmpg123}
						#optimized ${RtAudio}
						)

	SET_TARGET_PROPERTIES(eTrigger PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:libc.lib" 
						  LINK_FLAGS_DEBUG "/MANIFESTUAC:NO" 
						  LINK_FLAGS "/NODEFAULTLIB:libc.lib"
						  LINK_FLAGS "/MANIFESTUAC:NO"
						  COMPILE_DEFINITIONS WIN32,PORTAUDIO)
	##--------------------------------------------------------------------------


	##----- eTrigger.dll------------------------------------------------------------------------------------------
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/eTriggerVST )
	#GET_TARGET_PROPERTY(MyExecutable_PATH Aquawicket LOCATION)
	ADD_LIBRARY(eTriggerVST SHARED ${eTriggerVST_SRCS})
	TARGET_LINK_LIBRARIES(eTriggerVST ${wxWidgets_LIBRARIES}
						debug ${WX_qad}
						debug ${WX_xmld}
						debug ${WX_netd}
						debug ${WX_advd}
						debug ${WX_gld}
						debug winmm.lib
						#debug ksuser.lib
						debug opengl32.lib
						debug ${libvstd}
						debug ${cryptod}
						debug ${GWidgetsd}
						debug ${RtMidid}
						debug ${libsndfiled} 
						debug ${libresampled}
						debug ${dsound}						
						debug ${portaudiod}
						debug ${libmpg123d}
						#debug ${RtAudiod}
						optimized ${WX_qa}
						optimized ${WX_xml}
						optimized ${WX_net}
						optimized ${WX_adv}
						optimized ${WX_gl}
						optimized winmm.lib
						#optimized ksuser.lib
						optimized opengl32.lib
						optimized ${libvst}
						optimized ${crypto}
						optimized ${GWidgets}
						optimized ${RtMidi}
						optimized ${libsndfile}
						optimized ${libresample}
						optimized ${dsound}
						optimized ${portaudio}
						optimized ${libmpg123}
						#optimized ${RtAudio}
						)

	SET_TARGET_PROPERTIES(eTriggerVST PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:libc.lib" 
						     LINK_FLAGS "/NODEFAULTLIB:libc.lib"
						     LINKER_LANGUAGE CXX 
						     COMPILE_DEFINITIONS WIN32,VST)
	##--------------------------------------------------------------------------

ENDIF(WIN32)
##--------------------------------------------

    


##----------------------------------------
##        ##### MAC #####
##----------------------------------------
IF (APPLE)

	MESSAGE("Detected MAC environment")

	SET(EXECUTABLE_OUTPUT_PATH ${Aquawicket_SOURCE_DIR}/--==Mac==--
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${Aquawicket_SOURCE_DIR}/--==Mac==--
		CACHE PATH "Single output directory for building all libraries.")

	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/Images )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GImage )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GButton )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GCheckBox )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GMeter )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GScrollBar )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GSlider )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GKnob )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GText )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GNumberBox )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GCurve )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GImageSelector )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GHelper )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GLFont )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GLImage )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/RtMidi )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio/include )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio/src/common )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio/src/hostapi/asio/ASIOSDK/common )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio/src/hostapi/asio/ASIOSDK/host )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio/src/hostapi/asio/ASIOSDK/host/pc )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/cryptopp )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/libsndfile/MacOS )
	#INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/libsamplerate/src )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/mpg123/src/libmpg123 )

	FIND_LIBRARY(COREMIDI_LIBRARY CoreMidi)
	FIND_LIBRARY(COREAUDIO_LIBRARY CoreAudio)
	FIND_LIBRARY(COREFOUNDATION_LIBRARY CoreFoundation )
	FIND_LIBRARY(AUDIOTOOLBOX_LIBRARY AudioToolbox )
	FIND_LIBRARY(AUDIOUNIT_LIBRARY AudioUnit )
	FIND_LIBRARY(CORESERVICES_LIBRARY CoreServices)
	FIND_LIBRARY(IOKIT_LIBRARY ioKit)
	FIND_LIBRARY(OPENGL OpenGl)

	##------ Find Debug Libraries ---------------------------------------
	FIND_LIBRARY(GWidgetsd libGWidgets_d.a ${Aquawicket_SOURCE_DIR}/--==Mac==--/debug)
	FIND_LIBRARY(RtMidid libRtMidi_d.a ${Aquawicket_SOURCE_DIR}/--==Mac==--/debug)
	FIND_LIBRARY(portaudiod libPortaudio_d.a ${Aquawicket_SOURCE_DIR}/--==Mac==--/debug)
	FIND_LIBRARY(cryptod libcryptopp_d.a ${Aquawicket_SOURCE_DIR}/--==Mac==--/debug)
	#FIND_LIBRARY(libsndfiled libSndfile_d.a ${Aquawicket_SOURCE_DIR}/--==Mac==--/debug)
	
	##------ Find Release Libraries ---------------------------------------
	FIND_LIBRARY(GWidgets libGWidgets.a ${Aquawicket_SOURCE_DIR}/--==Mac==--/release)
	FIND_LIBRARY(RtMidi libRtMidi.a ${Aquawicket_SOURCE_DIR}/--==Mac==--/release)
	FIND_LIBRARY(portaudio libPortaudio.a ${Aquawicket_SOURCE_DIR}/--==Mac==--/release)
	FIND_LIBRARY(crypto libcryptopp.a ${Aquawicket_SOURCE_DIR}/--==Mac==--/release)
	#FIND_LIBRARY(libsndfile libSndfile.a ${Aquawicket_SOURCE_DIR}/--==Mac==--/release)

	ADD_DEFINITIONS(-DMAC)
	ADD_DEFINITIONS(-D__MACOSX_CORE__)

	##------ portaudio ---------------------------------------------------------
	ADD_LIBRARY(lib-portaudio STATIC ${portaudio_SRCS})
	SET_TARGET_PROPERTIES(lib-portaudio PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME portaudio DEBUG_OUTPUT_NAME portaudio_d) 
	##---------------------------------------------------------------------------

	##------ RtMidi ---------------------------------------------------------
	ADD_LIBRARY(lib-RtMidi STATIC ${RtMidi_SRCS})
	SET_TARGET_PROPERTIES(lib-RtMidi PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME RtMidi DEBUG_OUTPUT_NAME RtMidi_d)  
	##---------------------------------------------------------------------------

	##-------- GWidgets ---------------------------------------------------------
	ADD_LIBRARY(lib-GWidgets STATIC ${GWidgets_SRCS})
	SET_TARGET_PROPERTIES(lib-GWidgets PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME GWidgets DEBUG_OUTPUT_NAME GWidgets_d)  
	##-------------------------------------------------------------------------
	
	##-------- crypto -------------------------------------------------------------------
	ADD_LIBRARY(lib-crypto STATIC ${crypto_SRCS})
	SET_TARGET_PROPERTIES(lib-crypto PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME crypto DEBUG_OUTPUT_NAME crypto_d)  
	##-------------------------------------------------------------------------------------

	##-------- mpg123 -------------------------------------------------------------------
	ADD_LIBRARY(lib-mpg123 STATIC ${mpg123_SRCS})
	SET_TARGET_PROPERTIES(lib-mpg123 PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME libmpg123 DEBUG_OUTPUT_NAME libmpg123_d)  
	##-------------------------------------------------------------------------------------

	##----- eTriggerServer ------------------------------------------------------
	##ADD_EXECUTABLE(eTriggerServer MACOSX_BUNDLE ${eTriggerServer_SRCS})
	##TARGET_LINK_LIBRARIES(eTriggerServer ${wxWidgets_LIBRARIES}
	##									debug ${WX_netd}
	##									optimized ${WX_net})
	##---------------------------------------------------------------------------


	##----- eTriggerUpdater -----------------------------------------------------
	ADD_EXECUTABLE(eTriggerUpdater MACOSX_BUNDLE ${eTriggerUpdater_SRCS})
	TARGET_LINK_LIBRARIES(eTriggerUpdater ${wxWidgets_LIBRARIES})
	##--------------------------------------------------------------------------

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

	##----- eTrigger ------------------------------------------------------
	GET_TARGET_PROPERTY(MyExecutable_PATH Aquawicket LOCATION)
	ADD_EXECUTABLE(eTrigger MACOSX_BUNDLE ${eTrigger_SRCS})
	TARGET_LINK_LIBRARIES(eTrigger ${wxWidgets_LIBRARIES}
					debug ${COREMIDI_LIBRARY}
					debug ${COREAUDIO_LIBRARY}
					debug ${COREFOUNDATION_LIBRARY}
					debug ${AUDIOTOOLBOX_LIBRARY}
					debug ${AUDIOUNIT_LIBRARY}
					debug ${CORESERVICES_LIBRARY}
					debug ${IOKIT_LIBRARY}	
					debug ${OPENGL}					
					debug ${portaudiod}
					debug ${GWidgetsd}
					debug ${RtMidid}
					debug ${cryptod}
					#debug ${WX_qad} 
					#debug ${WX_xmld} 
					#debug ${WX_netd} 
					#debug ${WX_advd} 
					#debug ${WX_gld}
					#debug ${libsndfiled}
					#debug ${libmpg123}
					optimized ${COREMIDI_LIBRARY}
					optimized ${COREAUDIO_LIBRARY}
					optimized ${COREFOUNDATION_LIBRARY}
					optimized ${AUDIOTOOLBOX_LIBRARY}
					optimized ${AUDIOUNIT_LIBRARY}
					optimized ${CORESERVICES_LIBRARY}
					optimized ${IOKIT_LIBRARY}
					optimized ${OPENGL}		
					optimized ${portaudio}
					optimized ${GWidgets}
					optimized ${RtMidi}
					optimized ${crypto}
					#optimized ${WX_qa}
					#optimized ${WX_xml} 
					#optimized ${WX_net} 
					#optimized ${WX_adv} 
					#optimized ${WX_gld}
					#optimized ${libsndfile} 
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

	SET(EXECUTABLE_OUTPUT_PATH ${Aquawicket_SOURCE_DIR}/--==Linux==--
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${Aquawicket_SOURCE_DIR}/--==Linux==--
		CACHE PATH "Single output directory for building all libraries.")

	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/Images )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GImage )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GButton )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GCheckBox )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GMeter )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GScrollBar )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GSlider )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GKnob )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GText )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GNumberBox )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GCurve )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GImageSelector )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/Gwidgets/GHelper )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/alsa/include )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/RtMidi )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio/include )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio/src/common )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/portaudio/src/os/unix)
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/cryptopp )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/libsndfile/src )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/libresample/include )
	INCLUDE_DIRECTORIES(${Aquawicket_SOURCE_DIR}/lib-src/libresample/src )
	
	##------ Find Libraries ---------------------------------------
	FIND_LIBRARY(GWidgetsd libGWidgets_d.a ${Aquawicket_SOURCE_DIR}/--==Linux==--)
	FIND_LIBRARY(RtMidid libRtMidi_d.a ${Aquawicket_SOURCE_DIR}--==Linux==--)
	FIND_LIBRARY(portaudiod libPortaudio_d.a ${Aquawicket_SOURCE_DIR}/--==Linux==--)
	FIND_LIBRARY(cryptod crypto_d.a ${Aquawicket_SOURCE_DIR}/--==Linux==--) 	
	FIND_LIBRARY(libsndfiled libSndfile_d.a ${Aquawicket_SOURCE_DIR}/--==Linux==--)
	FIND_LIBRARY(libresampled libresample_d.a ${Aquawicket_SOURCE_DIR}/--==Linux==--)

	FIND_LIBRARY(GWidgets libGWidgets.a ${Aquawicket_SOURCE_DIR}/--==Linux==--)
	FIND_LIBRARY(RtMidi libRtMidi.a ${Aquawicket_SOURCE_DIR}/--==Linux==--)
	FIND_LIBRARY(portaudio libPortaudio.a ${Aquawicket_SOURCE_DIR}/--==Linux==--)
	FIND_LIBRARY(crypto crypto ${Aquawicket_SOURCE_DIR}/--==Linux==--) 	
	FIND_LIBRARY(libsndfile libSndfile.a ${Aquawicket_SOURCE_DIR}/--==Linux==--)
	FIND_LIBRARY(libresample libresample.a ${Aquawicket_SOURCE_DIR}/--==Linux==--)

        FIND_LIBRARY(ASOUND_LIBRARY asound)
	
	ADD_DEFINITIONS(-DLINUX)
	ADD_DEFINITIONS(-D__WXGTK__)
	ADD_DEFINITIONS(-DCMAKE_BUILD_TYPE=debugfull)
	ADD_DEFINITIONS(-D__LINUX_ALSASEQ__)


	##------ portaudio ---------------------------------------------------------
	ADD_LIBRARY(lib-portaudio STATIC ${portaudio_SRCS})
	SET_TARGET_PROPERTIES(lib-portaudio PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME portaudio DEBUG_OUTPUT_NAME portaudio_d) 
	##---------------------------------------------------------------------------

	##------ RtMidi ---------------------------------------------------------
	ADD_LIBRARY(lib-RtMidi STATIC ${RtMidi_SRCS})
	SET_TARGET_PROPERTIES(lib-RtMidi PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME RtMidi DEBUG_OUTPUT_NAME RtMidi_d)  
	##---------------------------------------------------------------------------

	##-------- GWidgets ---------------------------------------------------------
	ADD_LIBRARY(lib-GWidgets STATIC ${GWidgets_SRCS})
	SET_TARGET_PROPERTIES(lib-GWidgets PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME GWidgets DEBUG_OUTPUT_NAME GWidgets_d)  
	##-------------------------------------------------------------------------

	##-------- crypto -------------------------------------------------------------------
	ADD_LIBRARY(lib-crypto STATIC ${crypto_SRCS})
	SET_TARGET_PROPERTIES(lib-crypto PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME crypto DEBUG_OUTPUT_NAME crypto_d)  
	##-------------------------------------------------------------------------------------


	##----- eTriggerServer -----------------------------------------------------
	ADD_EXECUTABLE(eTriggerServer ${eTriggerServer_SRCS})
	TARGET_LINK_LIBRARIES(eTriggerServer ${wxWidgets_LIBRARIES} )
						#debug ${WX_netd}
						#optimized ${WX_net})
	##--------------------------------------------------------------------------


	##----- eTriggerUpdater -----------------------------------------------------
	ADD_EXECUTABLE(eTriggerUpdater ${eTriggerUpdater_SRCS})
	TARGET_LINK_LIBRARIES(eTriggerUpdater ${wxWidgets_LIBRARIES})
	##--------------------------------------------------------------------------


	##----- eTrigger ------------------------------------------------------
	GET_TARGET_PROPERTY(MyExecutable_PATH Aquawicket LOCATION)
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
