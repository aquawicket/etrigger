#################################
####       CryptoPP          ####
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

PROJECT( CryptoPP )

INCLUDE_DIRECTORIES( ${CryptoPP_SOURCE_DIR} )

##-------------------------------------------------
##  crypto.lib
##-------------------------------------------------
SET(crypto_SRCS
3way.h
adler32.h
aes.h
algebra.h
algparam.h
arc4.h
argnames.h
asn.h
base32.h
base64.h
basecode.h
blowfish.h
blumshub.h
camellia.h
cast.h
cbcmac.h
channels.h
config.h
cpu.h
crc.h
cryptlib.h
default.h
des.h
dh.h
dh2.h
dmac.h
dsa.h
ec2n.h
eccrypto.h
ecp.h
elgamal.h
emsa2.h
eprecomp.h
esign.h
files.h
filters.h
fips140.h
fltrimpl.h
gf256.h
gf2_32.h
gf2n.h
gfpcrypt.h
gost.h
gzip.h
hex.h
hmac.h
hrtimer.h
ida.h
idea.h
integer.h
iterhash.h
lubyrack.h
luc.h
mars.h
md2.h
md4.h
md5.h
mdc.h
misc.h
modarith.h
modes.h
modexppc.h
mqueue.h
mqv.h
nbtheory.h
network.h
nr.h
oaep.h
oids.h
osrng.h
panama.h
pch.h
pkcspad.h
polynomi.h
pssr.h
pubkey.h
pwdbased.h
queue.h
rabin.h
randpool.h
rc2.h
rc5.h
rc6.h
rijndael.h
ripemd.h
rng.h
rsa.h
rw.h
safer.h
salsa.h
seal.h
secblock.h
seckey.h
serpent.h
sha.h
shacal2.h
shark.h
simple.h
skipjack.h
smartptr.h
socketft.h
sosemanuk.h
square.h
strciphr.h
tea.h
tiger.h
trdlocal.h
trunhash.h
ttmac.h
twofish.h
vmac.h
wait.h
wake.h
whrlpool.h
winpipes.h
words.h
xtr.h
xtrcrypt.h
zdeflate.h
zinflate.h
zlib.h
3way.cpp
adler32.cpp
algebra.cpp
algparam.cpp
arc4.cpp
asn.cpp
base32.cpp
base64.cpp
basecode.cpp
bfinit.cpp
blowfish.cpp
blumshub.cpp
camellia.cpp
cast.cpp
casts.cpp
cbcmac.cpp
channels.cpp
cpu.cpp
crc.cpp
cryptlib.cpp
default.cpp
des.cpp
dessp.cpp
dh.cpp
dh2.cpp
dll.cpp
dsa.cpp
ec2n.cpp
eccrypto.cpp
ecp.cpp
elgamal.cpp
emsa2.cpp
eprecomp.cpp
esign.cpp
files.cpp
filters.cpp
fips140.cpp
fipstest.cpp
gf256.cpp
gf2_32.cpp
gf2n.cpp
gfpcrypt.cpp
gost.cpp
gzip.cpp
hex.cpp
hmac.cpp
hrtimer.cpp
ida.cpp
idea.cpp
integer.cpp
iterhash.cpp
luc.cpp
mars.cpp
marss.cpp
md2.cpp
md4.cpp
md5.cpp
misc.cpp
modes.cpp
mqueue.cpp
mqv.cpp
nbtheory.cpp
network.cpp
oaep.cpp
osrng.cpp
panama.cpp
pch.cpp
pkcspad.cpp
polynomi.cpp
pssr.cpp
pubkey.cpp
queue.cpp
rabin.cpp
randpool.cpp
rc2.cpp
rc5.cpp
rc6.cpp
rdtables.cpp
rijndael.cpp
ripemd.cpp
rng.cpp
rsa.cpp
rw.cpp
safer.cpp
salsa.cpp
seal.cpp
serpent.cpp
sha.cpp
shacal2.cpp
shark.cpp
sharkbox.cpp
simple.cpp
skipjack.cpp
socketft.cpp
sosemanuk.cpp
square.cpp
squaretb.cpp
strciphr.cpp
tea.cpp
tftables.cpp
tiger.cpp
tigertab.cpp
trdlocal.cpp
ttmac.cpp
twofish.cpp
vmac.cpp
wait.cpp
wake.cpp
whrlpool.cpp
winpipes.cpp
xtr.cpp
xtrcrypt.cpp
zdeflate.cpp
zinflate.cpp
zlib.cpp
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

   	SET(EXECUTABLE_OUTPUT_PATH ${CryptoPP_SOURCE_DIR}/../../_WIN32
            CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${CryptoPP_SOURCE_DIR}/../../_WIN32
            CACHE PATH "Single output directory for building all libraries.")

	ADD_DEFINITIONS(-DWIN32)
	ADD_DEFINITIONS(-DOPT_GENERIC)
	ADD_DEFINITIONS(-DACCURATE_ROUNDING)
	ADD_DEFINITIONS(-DIEEE_FLOAT)

	INCLUDE_DIRECTORIES(${CryptoPP_SOURCE_DIR})
	
	##-------- crypto -------------------------------------------------------------------
	ADD_LIBRARY(lib-crypto STATIC ${crypto_SRCS})
	SET_TARGET_PROPERTIES(lib-crypto PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME crypto DEBUG_OUTPUT_NAME crypto_d)  
	SET_TARGET_PROPERTIES(lib-crypto PROPERTIES COMPILE_FLAGS "/Oi")
	##-------------------------------------------------------------------------------------
	
ENDIF(WIN32)
##--------------------------------------------

    


##----------------------------------------
##        ##### MAC #####
##----------------------------------------
IF (APPLE)

	MESSAGE("Detected MAC environment")

	SET(EXECUTABLE_OUTPUT_PATH ${CryptoPP_SOURCE_DIR}/../../_MAC
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${CryptoPP_SOURCE_DIR}/../../_MAC
		CACHE PATH "Single output directory for building all libraries.")

	INCLUDE_DIRECTORIES(${CryptoPP_SOURCE_DIR})

	ADD_DEFINITIONS(-DMAC)

	##-------- crypto -------------------------------------------------------------------
	ADD_LIBRARY(lib-crypto STATIC ${crypto_SRCS})
	SET_TARGET_PROPERTIES(lib-crypto PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME crypto DEBUG_OUTPUT_NAME crypto_d)  
	##-------------------------------------------------------------------------------------

ENDIF (APPLE)
##--------------------------------------------





##----------------------------------------
##        ##### LINUX #####
##----------------------------------------
IF (UNIX)
IF (!APPLE)

	MESSAGE("Detected LINUX environment")

	SET(EXECUTABLE_OUTPUT_PATH ${CryptoPP_SOURCE_DIR}/../../_LINUX
		CACHE PATH "Single output directory for building all executables.")
	SET(LIBRARY_OUTPUT_PATH ${CryptoPP_SOURCE_DIR}/../../_LINUX
		CACHE PATH "Single output directory for building all libraries.")

	INCLUDE_DIRECTORIES(${CryptoPP_SOURCE_DIR} )

	ADD_DEFINITIONS(-DLINUX)
	ADD_DEFINITIONS(-D__WXGTK__)

	##-------- crypto -------------------------------------------------------------------
	ADD_LIBRARY(lib-crypto STATIC ${crypto_SRCS})
	SET_TARGET_PROPERTIES(lib-crypto PROPERTIES LINKER_LANGUAGE CXX OUTPUT_NAME crypto DEBUG_OUTPUT_NAME crypto_d)  
	##-------------------------------------------------------------------------------------

ENDIF (!APPLE)
ENDIF (UNIX)
##--------------------------------------------
