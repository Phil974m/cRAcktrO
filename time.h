#include <windows.h>

class Timer
{
  LARGE_INTEGER startTime ;
  double fFreq ;

public:
  Timer() {
    LARGE_INTEGER freq ;
    QueryPerformanceFrequency( &freq ) ;
    fFreq = (double)freq.QuadPart ;
    reset();
  }

  void reset() {   QueryPerformanceCounter( &startTime ) ;  }

  // Gets the most up to date time.
  double getTime() const {
    LARGE_INTEGER endTime ;
    QueryPerformanceCounter( &endTime ) ;
    return ( endTime.QuadPart - startTime.QuadPart ) / fFreq ; // as double
  }
};