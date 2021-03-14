#include <Arduino_FreeRTOS.h>
#include <Keypad.h>

#include "MyTimer.h"

#define configUSE_16_BIT_TICKS   0     // 16 bits means like two minutes max delays

const byte LED_OUPUT = 12;

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char ptrTaskList[250];

void TaskNotify( void *pvParameters );
void TaskKeypadRead( void *pvParameters );
void TaskSystemReport( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  
  Serial.begin(9600);  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  pinMode(LED_OUPUT, OUTPUT);
  digitalWrite(LED_OUPUT, HIGH);
  
  pinMode(LED_BUILTIN, OUTPUT);   
  digitalWrite(LED_BUILTIN, LOW);   // I turn it off, so it doesn't distract me

  xTaskCreate(
    TaskKeypadRead,
    "KeypadRead",
    128,  // Stack size
    NULL,
    1,    // Priority
    NULL );

  xTaskCreate(
    TaskSystemReport,
    "SystemReport",
    128,  // Stack size
    NULL,
    1,    // Priority
    NULL );
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/



void TaskNotify(void *pvParameters)
{
  // (void) pvParameters;  
  // unsigned long duration = ((TaskNotifyArgs*) pvParameters)->duration;
  TaskNotifyArgs* args = (TaskNotifyArgs*) pvParameters;
  
  // there was a bug that looked like an integer overflow, when twenty minute vTaskDelay triggered every time after two and a half minutes, but I couldn't figure out why
  // but anyway we don't just convert ms to ticks, because this function is imprecise, it added like 30 secs for each 6 minutes with a certain configuration
  // so it just checks every once in a while if time if up 

  unsigned long start = millis();
  for(;;) {
    if( millis() - start > args->duration ) {
      break;
    } else {
      vTaskDelay( pdMS_TO_TICKS(1000UL) );    // TODO: magic number
//      vTaskDelay( pdMS_TO_TICKS(200UL) ); 
    }
  }

  digitalWrite(args->pin, HIGH);

  vTaskSuspend(NULL);    // https://www.freertos.org/implementing-a-FreeRTOS-task.html
}

void TaskKeypadRead(void *pvParameters) {
  (void) pvParameters;
  TaskHandle_t taskHandle_Notify = NULL;

  static TaskNotifyArgs taskNotifyArgs;   // strictly speaking, static is not needed here, but we leave it here to draw attention that we use this chunk as shared memory between threads

  for (;;)
  {
   char key = keypad.getKey();
  
   if (key){
      Serial.println(key);
      taskNotifyArgs = keyToDuration(key);

      digitalWrite(taskNotifyArgs.pin, LOW);
      if(taskHandle_Notify) {
        // TODO: check if it's not deleted already, otherwise the os crashes
        // right now the notify thread suspends itself instead of deleting itself
        // because if you try to delete it a second time, it hangs or crashes
        vTaskDelete(taskHandle_Notify);
      }

      
      xTaskCreate(
        TaskNotify,
        "Notify",
        128,  // This stack size can be checked & adjusted by reading the Stack Highwater
        (void*) &taskNotifyArgs,
        2,  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        &taskHandle_Notify );
      } 
  
      vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskSystemReport(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    // BOOKMARK
    // TODO: print amount of free memory
    // Serial.println("report: ");

    // TODO: stress test the current thing with timers in threads by emulating a lot of keypresses
  
    vTaskDelay(pdMS_TO_TICKS(10 * 1000UL));
  }
}

TaskNotifyArgs keyToDuration(char key) {
  // TODO: assign meaningful delays or use toInt
  switch (key) {   // yes, I'm aware of the break statement, it's not needed here
    case '*':
      return TaskNotifyArgs(LED_OUPUT,        3 * 1000UL);
    case '1':
      return TaskNotifyArgs(LED_OUPUT,  20 * 60 * 1000UL);
    case '2':
      return TaskNotifyArgs(LED_OUPUT,  40 * 60 * 1000UL);
    case '3':
      return TaskNotifyArgs(LED_OUPUT,  60 * 60 * 1000UL);
    case '4':
      return TaskNotifyArgs(LED_OUPUT,  80 * 60 * 1000UL);
    case '5':
      return TaskNotifyArgs(LED_OUPUT, 100 * 60 * 1000UL);
    case '6':
      return TaskNotifyArgs(LED_OUPUT, 120 * 60 * 1000UL);
    case '7':
      return TaskNotifyArgs(LED_OUPUT, 140 * 60 * 1000UL);
    case '8':
      return TaskNotifyArgs(LED_OUPUT, 160 * 60 * 1000UL);
    case '9':
      return TaskNotifyArgs(LED_OUPUT, 180 * 60 * 1000UL);
    default:
      return TaskNotifyArgs(LED_OUPUT, 200UL);
  }
}
