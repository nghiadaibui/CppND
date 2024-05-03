#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
 /*
  Data present by index of cpuStat
  [1]: user
  [2]: nice
  [3]: system
  [4]: idle
  [5]: iowait
  [6]: irq
  [7]: softirq
  [8]: steal
  [9]: guest
  [10]: guest_nice
*/
  typedef enum {
    CPU,  
    USER,
    NICE,
    SYSTEM,
    IDLE,
    IOWAIT,
    IRQ,
    SOFTIRQ,
    STEAL,
    GUEST,
    GUEST_NICE
  } index_t;

  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
};

#endif