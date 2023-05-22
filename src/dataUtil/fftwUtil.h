
#ifndef __FFTWUTIL__
#define __FFTWUTIL__

#define FFTW_DESTROY_PLAN(x) if ( x != nullptr ) { fftw_destroy_plan(x); x = nullptr; }

#define FFTW_FREE(x) if ( x!= nullptr ) { fftw_free(x); x = nullptr; }




#endif