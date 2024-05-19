#ifndef HOMEWORK2_WRITEOUTPUT_H
#define HOMEWORK2_WRITEOUTPUT_H

#include <stdio.h>

#include <pthread.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum Action {
    TRAVEL,
    ARRIVE,
    START_PASSING,
    FINISH_PASSING
}Action;

void InitWriteOutput();
unsigned long long GetTimestamp();
void PrintThreadId();

/**
 *
 * @param carID
 * @param connector_type should be between 'N', 'F', 'C'
 * @param connectorID
 * @param action
 */
void WriteOutputf(FILE *f, int carID, char connector_type, int connectorID, Action action);
void WriteOutput(int carID, char connector_type, int connectorID, Action action);
#ifdef __cplusplus
}
#endif
#endif //HOMEWORK2_WRITEOUTPUT_H
