#include "helper.h"

void sleep_milli(int milliseconds) {
    long seconds = milliseconds/1000;
    long microseconds = (milliseconds%1000)*1000;
    if ( seconds > 0 ) {
        sleep(seconds);
    }
    if ( microseconds > 0 ) {
        usleep(microseconds);
    }
}