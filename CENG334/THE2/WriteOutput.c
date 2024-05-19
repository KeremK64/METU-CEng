#include "WriteOutput.h"
pthread_mutex_t mutexWrite = PTHREAD_MUTEX_INITIALIZER;

struct timeval startTime;

void InitWriteOutput()
{
    gettimeofday(&startTime, NULL);
}

unsigned long long GetTimestamp()
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return (currentTime.tv_sec - startTime.tv_sec) * 1000 // second
           + (currentTime.tv_usec - startTime.tv_usec) / 1000; // micro second
}

void PrintThreadId(FILE *f)
{
    pthread_t tid = pthread_self();
    size_t i;
    fprintf(f, "ThreadID: ");
    for (i=0; i<sizeof(pthread_t); ++i)
        fprintf(f, "%02x", *(((unsigned char*)&tid) + i));
    fprintf(f, ", ");
}

void WriteOutputf(FILE *f, int carID, char connector_type, int connectorID, Action action) {
    unsigned long long time = GetTimestamp();
    pthread_mutex_lock(&mutexWrite);

    PrintThreadId(f);
    fprintf(f,"CarID: %d, Object: %c%d, time stamp: %llu, AID: %d ", carID, connector_type, connectorID, time, (int)action);
    switch (action) {
        case TRAVEL:
            fprintf(f, "traveling to connector.\n");
            break;
        case ARRIVE:
            fprintf(f, "arrived at connector.\n");
            break;
        case START_PASSING:
            fprintf(f, "started passing connector.\n");
            break;
        case FINISH_PASSING:
            fprintf(f, "finished passing connector.\n");
            break;
        default:
            fprintf(f, "Wrong argument format.\n");
            break;
    }
    pthread_mutex_unlock(&mutexWrite);
}

void WriteOutput(int carID, char connector_type, int connectorID, Action action) {
    WriteOutputf(stdout, carID, connector_type, connectorID, action);
}


