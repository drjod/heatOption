#ifndef TIMER_89_H
#define TIMER_89_H

#include <time.h>

struct Timer
{
  typedef clock_t Ticks;
  Ticks t_;

  static Ticks get_ticks ()
  {
	 return clock();
  }

  static double ms (Ticks ticks)
  {
	 return ticks * 1.e6 / CLOCKS_PER_SEC;
  }

  Timer (bool start_now = false) : t_(start_now ? get_ticks() : 0)  {  }

  Ticks start ()  {  return t_ = get_ticks();  }
  Ticks stop ()   {  return t_ = get_ticks() - t_;  }
  double ms () const {  return ms(t_);   }
};


#endif
