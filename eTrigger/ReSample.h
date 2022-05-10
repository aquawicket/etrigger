//// ReSample.h ///////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef RESAMPLE_H
#define RESAMPLE_H

#ifdef LIBRESAMPLE
#include "libresample.h"
#endif //LIBRESAMPLE

#ifdef LIBSAMPLERATE
#include "samplerate.h"
#endif //LIBSAMPLERATE

#include "../lib/libsndfile/Win32/sndfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class ReSample
{
public:

	ReSample(int channels, int ratio);
	~ReSample();

#ifdef LIBRESAMPLE
	int   libresample(double ratio, float* in, int channels, int& startSample, int frames, float* out, long outLength);
	void **handle;
	int chans;
#endif //LIBRESAMPLE

#ifdef LIBSAMPLERATE
	int libsamplerate(double ratio, float* in, int channels, int& startSample, int frames, float* out, long outLength);
	int error ;
	int converter;
	SRC_STATE  *src_state ;
	SRC_DATA   src_data;
#endif //LIBSAMPLERATE
};


#endif //RESAMPLE_H
