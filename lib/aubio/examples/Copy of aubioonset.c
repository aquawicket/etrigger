

  ibuf      = new_fvec(overlap_size, channels);
  obuf      = new_fvec(overlap_size, channels);
  fftgrain  = new_cvec(buffer_size, channels);


  /* phase vocoder */
  pv = new_aubio_pvoc(buffer_size, overlap_size, channels);
  /* onsets */
  parms = new_aubio_peakpicker(threshold);
  o = new_aubio_onsetdetection(type_onset,buffer_size,channels);
  onset = new_fvec(1, channels);

}


void examples_common_process(aubio_process_func_t process_func, aubio_print_func_t print ){



    jack_setup = new_aubio_jack(channels, channels,
          (aubio_process_func_t)process_func);
   



    /* phasevoc */
    debug("Processing ...\n");

    frames = 0;

    while ((signed)overlap_size == aubio_sndfile_read(file, overlap_size, ibuf))
    {
      isonset=0;
      process_func(ibuf->data, obuf->data, overlap_size);

      frames++;
    }

//////////////////////////////////////////////////////////////////////////////////////


unsigned int pos = 0; /*frames%dspblocksize*/

int aubio_process(float **input, float **output, int nframes) {
  unsigned int i;       /*channels*/
  unsigned int j;       /*frames*/
  for (j=0;j<(unsigned)nframes;j++) {
	  //if(usejack) {
      //for (i=0;i<channels;i++) {
      //  /* write input to datanew */
      //  fvec_write_sample(ibuf, input[i][j], i, pos);
      //  /* put synthnew in output */
      //  output[i][j] = fvec_read_sample(obuf, i, pos);
      //}
      //}
    /*time for fft*/
    if (pos == overlap_size-1) {         
      /* block loop */
      aubio_pvoc_do (pv,ibuf, fftgrain);
      aubio_onsetdetection(o,fftgrain, onset);
      //if (usedoubled) {
      //  aubio_onsetdetection(o2,fftgrain, onset2);
      //  onset->data[0][0] *= onset2->data[0][0];
      //}
      isonset = aubio_peakpick_pimrt(onset,parms);
      if (isonset) {
          for (pos = 0; pos < overlap_size; pos++){
            obuf->data[0][pos] = woodblock->data[0][pos];
          }
      } else {
        for (pos = 0; pos < overlap_size; pos++)
          obuf->data[0][pos] = 0.;
      }
      /* end of block loop */
      pos = -1; /* so it will be zero next j loop */
    }
    pos++;
  }
  return 1;
}
