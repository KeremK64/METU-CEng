#include <iostream>
#include "WriteOutput.h"
#include "helper.h"
#include "monitor.h"

#include <vector>
#include <string>
#include <pthread.h>
#include <queue>


using namespace std;



class NarrowBridge : public Monitor{
    public:
        int travelTime;
        int maxWait;
        int count0 = 0;
        int count1 = 0;
        int active = 0;
        Condition timedwait;
        Condition road0;
        Condition road1;
        int cars = 0;
        int cars1 = 0;
        Condition delay;
        Condition roadSwitch;
        Condition waitToFinish;
        bool isPassing = false;
        bool isWait = false;
        queue<int> Q1 = queue<int>();
        queue<int> Q2 = queue<int>();
        Condition qWait1;
        Condition qWait2;

        NarrowBridge(int a, int b): travelTime(a), maxWait(b), timedwait(this), road0(this), road1(this), 
        delay(this), roadSwitch(this), waitToFinish(this), qWait1(this), qWait2(this){}
        
        /*struct timespec ts1;
        struct timeval time_val1;
        gettimeofday(&time_val1,NULL);
        ts1.tv_sec = time_val1.tv_sec + (PASS_DELAY/1000);
        ts1.tv_nsec= (time_val1.tv_usec + 1000UL *(PASS_DELAY % 1000)) * 1000UL; 
        if (ts1.tv_nsec>=1000000000UL)
        {
            ts1.tv_nsec-=1000000000;
            ts1.tv_sec++;
        }
        timedwait.timedwait(&ts1);*/

        void passNB(int carId, int conId, int from, int to){
            __synchronized__;

            WriteOutput(carId, 'N', conId, Action::ARRIVE);

            if(from == 0){
                if(count1 == 0 && count0 == 0){
                    active = 0;
                    count0++;

                    WriteOutput(carId, 'N', conId, Action::START_PASSING);
                    isPassing = true;

                    struct timespec ts;
                    struct timeval time_val;
                    gettimeofday(&time_val,NULL);
                    ts.tv_sec = time_val.tv_sec + (travelTime/1000);
                    ts.tv_nsec= (time_val.tv_usec + 1000UL *(travelTime % 1000)) * 1000UL; 
                    if (ts.tv_nsec>=1000000000UL)
                    {
                        ts.tv_nsec-=1000000000;
                        ts.tv_sec++;
                    }
                    timedwait.timedwait(&ts);
                    
                    count0--;
                    if(count0 == 0){
                        roadSwitch.notify();
                    }
                    WriteOutput(carId, 'N', conId, Action::FINISH_PASSING);
                    if(count0 == 0){
                        isPassing = false;
                    }
                    
                    if(isWait){
                        waitToFinish.notify();
                    }

                }
                else if(count1 != 0 && count0 == 0 && active){
                    count0++;

                    struct timespec ts2;
                    struct timeval time_val2;
                    gettimeofday(&time_val2,NULL);
                    ts2.tv_sec = time_val2.tv_sec + (maxWait/1000);
                    ts2.tv_nsec= (time_val2.tv_usec + 1000UL *(maxWait % 1000)) * 1000UL; 
                    if (ts2.tv_nsec>=1000000000UL)
                    {
                        ts2.tv_nsec-=1000000000;
                        ts2.tv_sec++;
                    }
                    roadSwitch.timedwait(&ts2);
                    active = 0;
                    isWait = true;

                    while(isPassing){
                        waitToFinish.wait();
                    }
                    
                    isPassing = false;

                    WriteOutput(carId, 'N', conId, Action::START_PASSING);
                    isPassing = true;
                    road0.notifyAll();

                    struct timespec ts;
                    struct timeval time_val;
                    gettimeofday(&time_val,NULL);
                    ts.tv_sec = time_val.tv_sec + (travelTime/1000);
                    ts.tv_nsec= (time_val.tv_usec + 1000UL *(travelTime % 1000)) * 1000UL; 
                    if (ts.tv_nsec>=1000000000UL)
                    {
                        ts.tv_nsec-=1000000000;
                        ts.tv_sec++;
                    }
                    timedwait.timedwait(&ts);

                    count0--;
                    if(count0 == 0){
                        roadSwitch.notify();
                    }
                    WriteOutput(carId, 'N', conId, Action::FINISH_PASSING);
                    if(count0 == 0){
                        isPassing = false;
                    }
                    if(isWait){
                        waitToFinish.notify();
                        isWait = false;
                    }

                }
                else if(count0 != 0 && !active){
                    count0++;
                    Q1.push(carId);
                    while(Q1.front() != carId){
                        qWait1.wait();
                    }
                    
                    while(cars){
                        delay.wait();
                    }
                    cars++;
                    struct timespec ts1;
                    struct timeval time_val1;
                    gettimeofday(&time_val1,NULL);
                    ts1.tv_sec = time_val1.tv_sec + (PASS_DELAY/1000);
                    ts1.tv_nsec= (time_val1.tv_usec + 1000UL *(PASS_DELAY % 1000)) * 1000UL; 
                    if (ts1.tv_nsec>=1000000000UL)
                    {
                        ts1.tv_nsec-=1000000000;
                        ts1.tv_sec++;
                    }
                    timedwait.timedwait(&ts1);
                    cars--;
                    delay.notify();
                    WriteOutput(carId, 'N', conId, Action::START_PASSING);
                    Q1.pop();
                    qWait1.notifyAll();
                    isPassing = true;

                    struct timespec ts;
                    struct timeval time_val;
                    gettimeofday(&time_val,NULL);
                    ts.tv_sec = time_val.tv_sec + (travelTime/1000);
                    ts.tv_nsec= (time_val.tv_usec + 1000UL *(travelTime % 1000)) * 1000UL; 
                    if (ts.tv_nsec>=1000000000UL)
                    {
                        ts.tv_nsec-=1000000000;
                        ts.tv_sec++;
                    }
                    timedwait.timedwait(&ts);

                    count0--;
                    if(count0 == 0){
                        roadSwitch.notify();
                    }
                    WriteOutput(carId, 'N', conId, Action::FINISH_PASSING);
                    if(count0 == 0){
                        isPassing = false;
                    }
                    if(isWait){
                        waitToFinish.notify();
                    }
                }
                else{
                    count0++;
                    Q1.push(carId);
                    while(Q1.front() != carId){
                        qWait1.wait();
                    }
                    
                    road0.wait();

                    if(count0 != 1){
                        while(cars){
                            delay.wait();
                        }
                        cars++;
                        struct timespec ts;
                        struct timeval time_val;
                        gettimeofday(&time_val,NULL);
                        ts.tv_sec = time_val.tv_sec + (PASS_DELAY/1000);
                        ts.tv_nsec= (time_val.tv_usec + 1000UL *(PASS_DELAY % 1000)) * 1000UL; 
                        if (ts.tv_nsec>=1000000000UL)
                        {
                            ts.tv_nsec-=1000000000;
                            ts.tv_sec++;
                        }
                        timedwait.timedwait(&ts);
                        cars--;
                        delay.notify();
                    }


                    WriteOutput(carId, 'N', conId, Action::START_PASSING);
                    Q1.pop();
                    qWait1.notifyAll();
                    isPassing = true;


                    struct timespec ts1;
                    struct timeval time_val1;
                    gettimeofday(&time_val1,NULL);
                    ts1.tv_sec = time_val1.tv_sec + (travelTime/1000);
                    ts1.tv_nsec= (time_val1.tv_usec + 1000UL *(travelTime % 1000)) * 1000UL; 
                    if (ts1.tv_nsec>=1000000000UL)
                    {
                        ts1.tv_nsec-=1000000000;
                        ts1.tv_sec++;
                    }
                    timedwait.timedwait(&ts1);
                    
                    count0--;
                    if(count0 == 0){
                        roadSwitch.notify();
                    }
                    WriteOutput(carId, 'N', conId, Action::FINISH_PASSING);
                    if(count0 == 0){
                        isPassing = false;
                    }
                    if(isWait){
                        waitToFinish.notify();
                    }
                }
            }
            else{
                if(count0 == 0 && count1 == 0){
                    active = 1;
                    count1++;
                    WriteOutput(carId, 'N', conId, Action::START_PASSING);
                    isPassing = true;

                    struct timespec ts;
                    struct timeval time_val;
                    gettimeofday(&time_val,NULL);
                    ts.tv_sec = time_val.tv_sec + (travelTime/1000);
                    ts.tv_nsec= (time_val.tv_usec + 1000UL *(travelTime % 1000)) * 1000UL; 
                    if (ts.tv_nsec>=1000000000UL)
                    {
                        ts.tv_nsec-=1000000000;
                        ts.tv_sec++;
                    }
                    timedwait.timedwait(&ts);
                    
                    count1--;
                    if(count1 == 0){
                        roadSwitch.notify();
                    }
                    WriteOutput(carId, 'N', conId, Action::FINISH_PASSING);
                    if(count1 == 0){
                        isPassing = false;
                    }
                    if(isWait){
                        waitToFinish.notify();
                    }

                }
                else if(count0 != 0 && count1 == 0 && !active){
                    count1++;

                    struct timespec ts1;
                    struct timeval time_val1;
                    gettimeofday(&time_val1,NULL);
                    ts1.tv_sec = time_val1.tv_sec + (maxWait/1000);
                    ts1.tv_nsec= (time_val1.tv_usec + 1000UL *(maxWait % 1000)) * 1000UL; 
                    if (ts1.tv_nsec>=1000000000UL)
                    {
                        ts1.tv_nsec-=1000000000;
                        ts1.tv_sec++;
                    }
                    roadSwitch.timedwait(&ts1);
                    active = 1;
                    isWait = true;

                    while(isPassing){
                        waitToFinish.wait();
                    }
                    
                    active = 1;
                    isPassing = false;


                    WriteOutput(carId, 'N', conId, Action::START_PASSING);
                    isPassing = true;
                    road1.notifyAll();

                    struct timespec ts2;
                    struct timeval time_val2;
                    gettimeofday(&time_val2,NULL);
                    ts2.tv_sec = time_val2.tv_sec + (travelTime/1000);
                    ts2.tv_nsec= (time_val2.tv_usec + 1000UL *(travelTime % 1000)) * 1000UL; 
                    if (ts2.tv_nsec>=1000000000UL)
                    {
                        ts2.tv_nsec-=1000000000;
                        ts2.tv_sec++;
                    }
                    timedwait.timedwait(&ts2);

                    count1--;
                    if(count1 == 0){
                        roadSwitch.notify();
                    }
                    WriteOutput(carId, 'N', conId, Action::FINISH_PASSING);
                    if(count1 == 0){
                        isPassing = false;
                    }
                    if(isWait){
                        waitToFinish.notify();
                    }

                }
                else if(count1 != 0 && active){
                    count1++;
                    Q2.push(carId);
                    while(Q2.front() != carId){
                        qWait2.wait();
                    }
                    
                    while(cars){
                        delay.wait();
                    }
                    cars1++;
                    struct timespec ts1;
                    struct timeval time_val1;
                    gettimeofday(&time_val1,NULL);
                    ts1.tv_sec = time_val1.tv_sec + (PASS_DELAY/1000);
                    ts1.tv_nsec= (time_val1.tv_usec + 1000UL *(PASS_DELAY % 1000)) * 1000UL; 
                    if (ts1.tv_nsec>=1000000000UL)
                    {
                        ts1.tv_nsec-=1000000000;
                        ts1.tv_sec++;
                    }
                    timedwait.timedwait(&ts1);
                    cars1--;
                    delay.notify();
                    WriteOutput(carId, 'N', conId, Action::START_PASSING);
                    Q2.pop();
                    qWait2.notifyAll();
                    isPassing = true;

                    struct timespec ts;
                    struct timeval time_val;
                    gettimeofday(&time_val,NULL);
                    ts.tv_sec = time_val.tv_sec + (travelTime/1000);
                    ts.tv_nsec= (time_val.tv_usec + 1000UL *(travelTime % 1000)) * 1000UL; 
                    if (ts.tv_nsec>=1000000000UL)
                    {
                        ts.tv_nsec-=1000000000;
                        ts.tv_sec++;
                    }
                    timedwait.timedwait(&ts);

                    count1--;
                    if(count1 == 0){
                        roadSwitch.notify();
                    }
                    WriteOutput(carId, 'N', conId, Action::FINISH_PASSING);
                    if(count1 == 0){
                        isPassing = false;
                    }
                    if(isWait){
                        waitToFinish.notify();
                    }
                }
                else{
                    count1++;
                    Q2.push(carId);
                    while(Q2.front() != carId){
                        qWait2.wait();
                    }
                    
                    road1.wait();

                    if(count1 != 1){
                        while(cars){
                            delay.wait();
                        }
                        cars++;
                        struct timespec ts;
                        struct timeval time_val;
                        gettimeofday(&time_val,NULL);
                        ts.tv_sec = time_val.tv_sec + (PASS_DELAY/1000);
                        ts.tv_nsec= (time_val.tv_usec + 1000UL *(PASS_DELAY % 1000)) * 1000UL; 
                        if (ts.tv_nsec>=1000000000UL)
                        {
                            ts.tv_nsec-=1000000000;
                            ts.tv_sec++;
                        }
                        timedwait.timedwait(&ts);
                        cars--;
                        delay.notify();
                    }

                    WriteOutput(carId, 'N', conId, Action::START_PASSING);
                    Q2.pop();
                    qWait2.notifyAll();
                    isPassing = true;

                    struct timespec ts1;
                    struct timeval time_val1;
                    gettimeofday(&time_val1,NULL);
                    ts1.tv_sec = time_val1.tv_sec + (travelTime/1000);
                    ts1.tv_nsec= (time_val1.tv_usec + 1000UL *(travelTime % 1000)) * 1000UL; 
                    if (ts1.tv_nsec>=1000000000UL)
                    {
                        ts1.tv_nsec-=1000000000;
                        ts1.tv_sec++;
                    }
                    timedwait.timedwait(&ts1);
                    
                    count1--;
                    if(count1 == 0){
                        roadSwitch.notify();
                    }
                    WriteOutput(carId, 'N', conId, Action::FINISH_PASSING);
                    if(count1 == 0){
                        isPassing = false;
                    }
                    if(isWait){
                        waitToFinish.notify();
                    }
                    
                }
            }

            

        }
};

pthread_cond_t allHere = PTHREAD_COND_INITIALIZER;
pthread_cond_t timeIsUp = PTHREAD_COND_INITIALIZER;


class Ferry : public Monitor{
    public:
        int travelTime;
        int maxWait;
        int capacity;
        Condition allHere;
        Condition allHere1;
        Condition waiting;
        Condition timeIsUp;
        Condition waiting1;
        Condition timeIsUp1;
        Condition full;
        Condition full1;
        int count0 = 0;
        int count1 = 0;

        Ferry(int a, int b, int c): travelTime(a), maxWait(b), capacity(c),
        allHere(this), timeIsUp(this), waiting(this), allHere1(this),
        waiting1(this), timeIsUp1(this), full(this), full1(this){}

        void passFerry(int carId, int conId, int from, int to){
            

            __synchronized__;
            WriteOutput(carId, 'F', conId, Action::ARRIVE);


            
            
            if(from == 0){
                while(count0 == capacity){
                    full1.wait();
                }
                if (count0 == capacity - 1)
                {   
                    count0++;
                    WriteOutput(carId, 'F', conId, Action::START_PASSING);
                    allHere.notifyAll();
                    waiting.notifyAll();
                    struct timespec ts1;
                    struct timeval time_val1;
                    gettimeofday(&time_val1,NULL);
                    ts1.tv_sec = time_val1.tv_sec + (travelTime/1000);
                    ts1.tv_nsec= (time_val1.tv_usec + 1000UL *(travelTime % 1000)) * 1000UL; 
                    if (ts1.tv_nsec>=1000000000UL)
                    {
                        ts1.tv_nsec-=1000000000;
                        ts1.tv_sec++;
                    }
                    timeIsUp.timedwait(&ts1);
                    WriteOutput(carId, 'F', conId, Action::FINISH_PASSING);
                    full1.notifyAll();
                    return;
                }
                else if (count0 == 0)
                {   
                    count0++;
                    struct timespec ts1;
                    struct timeval time_val1;
                    gettimeofday(&time_val1,NULL);
                    ts1.tv_sec = time_val1.tv_sec + (maxWait/1000);
                    ts1.tv_nsec= (time_val1.tv_usec + 1000UL *(maxWait % 1000)) * 1000UL; 
                    if (ts1.tv_nsec>=1000000000UL)
                    {
                        ts1.tv_nsec-=1000000000;
                        ts1.tv_sec++;
                    }
                    waiting.timedwait(&ts1);
                    if(count0 == capacity){
                        full1.notifyAll();
                    }
                    WriteOutput(carId, 'F', conId, Action::START_PASSING);
                    allHere.notifyAll();
                    count0 = 0;
                }
                else
                {   
                    count0++;
                    allHere.wait();
                    WriteOutput(carId, 'F', conId, Action::START_PASSING);
                }
                

                struct timespec ts;
                struct timeval time_val;
                gettimeofday(&time_val,NULL);
                ts.tv_sec = time_val.tv_sec + (travelTime/1000);
                ts.tv_nsec= (time_val.tv_usec + 1000UL *(travelTime % 1000)) * 1000UL; 
                if (ts.tv_nsec>=1000000000UL)
                {
                    ts.tv_nsec-=1000000000;
                    ts.tv_sec++;
                }
                timeIsUp.timedwait(&ts);
                WriteOutput(carId, 'F', conId, Action::FINISH_PASSING);
            }
            else{
                while(count1 == capacity){
                    full.wait();
                }
                if (count1 == capacity - 1)
                {   
                    count1++;
                    WriteOutput(carId, 'F', conId, Action::START_PASSING);
                    allHere1.notifyAll();
                    waiting1.notifyAll();
                    struct timespec ts;
                    struct timeval time_val;
                    gettimeofday(&time_val,NULL);
                    ts.tv_sec = time_val.tv_sec + (travelTime/1000);
                    ts.tv_nsec= (time_val.tv_usec + 1000UL *(travelTime % 1000)) * 1000UL; 
                    if (ts.tv_nsec>=1000000000UL)
                    {
                        ts.tv_nsec-=1000000000;
                        ts.tv_sec++;
                    }
                    timeIsUp.timedwait(&ts);
                    WriteOutput(carId, 'F', conId, Action::FINISH_PASSING);
                    full.notifyAll();
                    return;
                }
                else if (count1 == 0)
                {   
                    count1++;
                    struct timespec ts;
                    struct timeval time_val;
                    int t= maxWait; 
                    gettimeofday(&time_val,NULL);
                    ts.tv_sec= time_val.tv_sec+ t/1000;
                    ts.tv_nsec= (time_val.tv_usec+1000UL*((t%1000)))*1000UL;
                    if (ts.tv_nsec>=1000000000UL)
                    {
                        ts.tv_nsec-=1000000000;
                        ts.tv_sec+=1;
                    }
                    waiting1.timedwait(&ts);
                    if(count1 == capacity){
                        full.notifyAll();
                    }
                    WriteOutput(carId, 'F', conId, Action::START_PASSING);
                    allHere1.notifyAll();
                    count1 = 0;
                }
                else
                {
                    count1++;
                    allHere1.wait();
                    WriteOutput(carId, 'F', conId, Action::START_PASSING);
                }
                

                struct timespec ts;
                struct timeval time_val;
                gettimeofday(&time_val,NULL);
                ts.tv_sec = time_val.tv_sec + (travelTime/1000);
                ts.tv_nsec= (time_val.tv_usec + 1000UL *(travelTime % 1000)) * 1000UL; 
                if (ts.tv_nsec>=1000000000UL)
                {
                    ts.tv_nsec-=1000000000;
                    ts.tv_sec++;
                }
                timeIsUp1.timedwait(&ts);
                WriteOutput(carId, 'F', conId, Action::FINISH_PASSING);
            }
            
            
        }
        
        
};

class Crossroad : public Monitor{
    public:
        int travelTime;
        int maxWait;

        Crossroad(int a, int b): travelTime(a), maxWait(b){}

        void passCR(int carId, int conId, int from, int to){
            WriteOutput(carId, 'C', conId, Action::ARRIVE);
        }

};

enum class ConnectorType{
    NARROWBRIDGE,
    FERRY,
    CROSSROAD,
    NONE
};

class PathObject{
    public:
        ConnectorType connector;
        int connectorNum;
        int from;
        int to;

        PathObject(ConnectorType a, int b, int c, int d): connector(a), connectorNum(b), from(c), to(d){}
};

class Path{
    public:
        vector<PathObject> obj;
        int length;

        Path(vector<PathObject> a, int b): obj(a), length(b){}
};


class Car{
    public:
        int travelTime;
        int pathLen;
        Path path;

        Car(int a, int b, Path p): travelTime(a), pathLen(b), path(p){}
};

vector<NarrowBridge*> narrowBridgeParser(int len){
    std::vector<NarrowBridge*> arr;
    for(int i = 0; i < len; i++){
        int time, wait;
        cin >> time >> wait;
        NarrowBridge* temp = new NarrowBridge(time, wait);
        arr.push_back(temp);
    }
    return arr;
}

vector<Ferry*> ferryParser(int len){
    std::vector<Ferry*> arr;
    for(int i = 0; i < len; i++){
        int time, wait, capacity;
        cin >> time >> wait >> capacity;
        Ferry *temp = new Ferry(time, wait, capacity);
        arr.push_back(temp);
    }
    return arr;
}

vector<Crossroad*> crossRoadParser(int len){
    std::vector<Crossroad*> arr;
    for(int i = 0; i < len; i++){
        int time, wait;
        cin >> time >> wait;
        Crossroad *temp = new Crossroad(time, wait);
        arr.push_back(temp);
    }
    return arr;
}

ConnectorType transformer(int c){
    switch(c){
        case 78:
            return ConnectorType::NARROWBRIDGE;
        case 70:
            return ConnectorType::FERRY;
        case 67:
            return ConnectorType::CROSSROAD;
        default:
            return ConnectorType::NONE;
    }
        
}


Path pathParser(int len){
    vector<PathObject> arr;
    for(int i = 0; i < len; i++){
        string connector;
        int from;
        int to;
        cin >> connector >> from >> to;
        PathObject temp(transformer(connector[0]), connector[1] - '0', from, to);
        arr.push_back(temp);
    }
    return Path(arr, len);
}


Car carParser(int time, int len){
    Path path = pathParser(len);
    Car temp(time, len, path);
    
    return temp;
}

vector<NarrowBridge*> narrowBridges;
vector<Ferry*> ferries;
vector<Crossroad*> crossRoads;
vector<Car> cars;

void* carRoutine(void* carID){
    int carId = *(int *) carID;
    vector<PathObject> arr = cars[carId].path.obj;

    for(int i = 0; i < arr.size(); i++){
        ConnectorType CT = arr[i].connector;
        int connectorNum = arr[i].connectorNum;
        char connectorChar;

        switch(CT){
            case ConnectorType::NARROWBRIDGE:
                connectorChar = 'N';
                break;
            case ConnectorType::FERRY:
                connectorChar = 'F';
                break;
            case ConnectorType::CROSSROAD:
                connectorChar = 'C';
                break;
        }
        WriteOutput(carId, connectorChar, connectorNum, Action::TRAVEL);
        sleep_milli(cars[carId].travelTime);
        
        switch(CT){
            case ConnectorType::NARROWBRIDGE:
                narrowBridges[connectorNum]->passNB(carId, connectorNum, arr[i].from, arr[i].to);
                break;
            case ConnectorType::FERRY:
                ferries[connectorNum]->passFerry(carId, connectorNum, arr[i].from, arr[i].to);
                break;
            case ConnectorType::CROSSROAD:
                crossRoads[connectorNum]->passCR(carId, connectorNum, arr[i].from, arr[i].to);
                break;
        }
        
    }
    return NULL;
}



pthread_t* threadArr;

int main(){
    

    int numOfNB;
    cin >> numOfNB;
    narrowBridges = narrowBridgeParser(numOfNB);

    int numOfFerry;
    cin >> numOfFerry;
    ferries = ferryParser(numOfFerry);

    int numOfCR;
    cin >> numOfCR;
    crossRoads = crossRoadParser(numOfCR);

    int numOfCars;
    cin >> numOfCars;
    
    for(int i = 0; i < numOfCars; i++){
        int travelTime, len;
        cin >> travelTime >> len;
        Car car = carParser(travelTime, len);
        cars.push_back(car);
    }


    
    InitWriteOutput();
    threadArr = new pthread_t[cars.size()];

    
    for(int i = 0; i < cars.size(); i++){
        int *temp = new int;
        *temp = i;
        pthread_create(threadArr + i, NULL, carRoutine, (void*) temp);
    }

    for(int i = 0; i < cars.size(); i++){
        pthread_join(threadArr[i], NULL);
    }

    return 0;
}