#ifndef __MYTIMER_H__
#define __MYTIMER_H__

// arduino's compiler is quirky and requires a struct to be in a header if we want to use it as a return value


// we pass arguments using an instance of this struct in memory
class TaskNotifyArgs {
public:
  String taskName;
  int pin;
  unsigned long duration = 0;
  TaskHandle_t taskHandle = NULL;
  void (*func_ptr)(void *pvParameters);    // TODO: is it possible to make it static and pass it directly, instead of having a pointer to a function, which we assign somewhere

  TaskNotifyArgs(String taskName, int pin, void (*func_ptr)(void *pvParameters)) : taskName(taskName), pin(pin), func_ptr(func_ptr) {  }
  
  void restart(unsigned long duration);

  // static void TaskNotifyArgs::TaskNotify(void *pvParameters);
};


#endif // __MYTIMER_H__
