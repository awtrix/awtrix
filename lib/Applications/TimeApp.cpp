#include <TimeApp.h>
#include <stdio.h>
unsigned long previousMillis = 0; 
unsigned long interval = 1000; 
bool TD;
const char * monname[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};


void TimeApp::render(DisplayManager& display) {

    if (TD || SLEEP_MODE){
        char t[14];
        sprintf_P(t, PSTR("%02d:%02d:%02d"), hour(), minute(),second()); 
        display.drawText(t, {1, 0}, true,!BIG_TIME,true);
        if ((millis() - previousMillis > interval) &  BIG_TIME ) {
        previousMillis = millis(); 
        blink = !blink;
    }

    if (blink & BIG_TIME){
        display.fillRect(14,0,5,6,{0,0,0});
    }
   
 
    }else{
        char  d[14];
        sprintf_P(d, PSTR("%02d. %s"), day(), monname[month()-1]); 
        display.drawText(d , {3, 0}, true,true,true);
        }
    
   if (SHOW_WEEKDAY && !SLEEP_MODE){
        long day = now() / 86400L;
        int day_of_the_week = (day+3) % 7;
        display.drawWeekday(day_of_the_week);
    }


  display.show();
  ++loopCounter;
}

void TimeApp::enable() {
    loopCounter=0;
    TD=!TD;
}


