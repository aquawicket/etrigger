//// ReSample.cpp ///////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "ReSample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MIN(A, B) (A) < (B)? (A) : (B)

///////////////////////////////////////////
ReSample::ReSample(int channels, int ratio)
{
	//libsamplerate
#ifdef LIBSAMPLERATE
	converter = 2;
	if ((src_state = src_new (converter, 2, &error)) == NULL)
	{	wxMessageBox(wxT("Error : src_new() failed : %s."), ConvTowxString(src_strerror(error))) ;
		return;
	} 
#endif //LIBSAMPLERATE

#ifdef LIBRESAMPLE
	//libresample
	chans = channels;
	handle = (void **)malloc(chans * sizeof(void *));
	for(int c=0; c<chans; c++){
		handle[c] = resample_open(0, ratio, ratio);
	}
#endif //LIBRESAMPLE
}

/////////////////////
ReSample::~ReSample()
{
#ifdef LIBSAMPLERATE
	src_state = src_delete(src_state);
#endif //LIBSAMPLERATE

#ifdef LIBRESAMPLE
	//libresample
	for(int c=0; c<chans; c++){
		resample_close(handle[c]);
	}

	delete[] handle;
#endif //LIBRESAMPLE
}

//we want to get an outputBuffer filled with resampled data.

#ifdef LIBRESAMPLE
int ReSample::libresample(double ratio, float* in, int channels, int& startSample, int frames, float* out, long outLength)
{
	int srclen = outLength * ratio;
	float *src = new float[srclen];     //create a place to store non-interleaved input
	float *dst = new float[outLength];	//create a place to store non-interleaved output

	int pos = startSample / channels;
    int bufferpos = 0;
    int outcount = 0;
	
	while(outcount < outLength && pos < frames){ //fill until output Buffer is full
		int block = MIN(srclen-bufferpos, frames-pos);
		int lastFlag = (pos+block == frames);
		int inUsed, inUsed2=0, outUsed=0, outUsed2=0;

		block += bufferpos;

		for(int c=0; c<channels; c++) {
			for(int i=0; i<block; i++){
				src[i] = in[(pos+i)* channels+c];
			}

			inUsed = 0;
			outUsed = resample_process(handle[c], ratio, src,
				 block, lastFlag, &inUsed, dst, outLength - outcount);

			if (c==0) {
				inUsed2 = inUsed;
				outUsed2 = outUsed;
			}
			else {
				if (inUsed2 != inUsed || outUsed2 != outUsed) {
					wxMessageBox(wxT("Fatal error: channels out of sync!"));
					resample_close(handle);
					//delete srci;
					delete src;
					delete dst;
					return -1;
				}
			}
			
			for(int i=0; i<outUsed; i++){
				if(dst[i] <= -1)
					out[i * channels + c] = -1;
				else if(dst[i] >= 1)
					out[i * channels + c] = 1;
				else
					out[i * channels + c] += dst[i];
			}
		}

		bufferpos = block - inUsed;

		pos += inUsed;
		startSample = pos * channels;
		outcount += outUsed;
	}

	delete src;
	delete dst;
	return outcount; //return the number of output frames processed.
}
#endif //LIBRESAMPLE


#ifdef LIBSAMPLERATE
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ReSample::libsamplerate(double ratio, float* in, int channels, int& startSample, int frames, float* out, long outLength)
{	
	//FIXME:  we need to mix in the output.. not overwrite it!

	if(ratio == 1.0){ //samplerates the same, just do direct transfer
		for(int i=0; i<(outLength * channels); ++i){
			out[i] += in[i];
		}
	}

	double	   max = 0.0 ;
	int	       output_count = 0 ;
	
	src_data.end_of_input = 0; /* Set this later. */

	/* Start with zero to force load in while loop. */
	src_data.input_frames = frames - (startSample / channels);
	src_data.data_in = in;
	src_data.data_in += startSample;

	src_data.src_ratio = ratio;

	float *temp = new float[outLength * channels];
	src_data.data_out = temp;
	src_data.output_frames = outLength;// /channels ;

	while (1)
	{
		/* The last read will not be a full buffer, so snd_of_input. */
		if (src_data.input_frames < outLength){
				src_data.end_of_input = SF_TRUE;
		}

		if ((error = src_process (src_state, &src_data))){
			wxMessageBox(wxString::Format(wxT("Error : %s"), src_strerror (error)));
			return -1;
		};

		output_count += src_data.output_frames_gen;
		startSample += src_data.input_frames_used * channels;

		/* Terminate if done. */
		if (output_count >= outLength)
			break;

		if (src_data.end_of_input)// && src_data.output_frames_gen == 0)
			break ;
	}

	for(int i=0; i<(outLength * channels); ++i){
		out[i] += temp[i];
	}

	delete temp;
	return output_count;
}
#endif //LIBSAMPLERATE

