#ifndef __MYTIMER_H__
#define __MYTIMER_H__

// we pass arguments using an instance of this struct in memory
class TaskNotifyArgs {
public:
  int pin = 0;
  unsigned long duration = 0;

  TaskNotifyArgs() {}
  TaskNotifyArgs(int pin, unsigned long duration) : pin(pin), duration(duration) {}
};

#endif // __MYTIMER_H__
