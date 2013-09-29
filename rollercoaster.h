//------------------------------------------------------------------------
// Filename: 
//    roller-coaster.h
// PROGRAM DESCRIPTION
//    class definition file for the roller coaster program
//------------------------------------------------------------------------

#ifndef  _ROLLER_H
#define  _ROLLER_H

#include "ThreadClass.h"

#define MAX_PASSENGERS   20   // Maximum number of passengers 
#define MAX_CAPACITY     10   // Maximum capacity of the car  
#define MAX_NO_RIDES     10   // Maximum number of car rides

//------------------------------------------------------------------------
// PassengerThread class definition
//------------------------------------------------------------------------

class PassengerThread: public Thread 
{
     public:
          PassengerThread(int Number, int capacity);
          void TakeRide();
     private:
          int  passenger_Id;
          int  Capacity;      // capacity of the car  
          void ThreadFunc();
};

//------------------------------------------------------------------------
// CarThread class definition
//------------------------------------------------------------------------

class CarThread: public Thread 
{
     public:
          CarThread(char *Name, int capacity, int noOfRides);
     private:
          void ThreadFunc();
          int  Capacity;      // capcity of the car  
          int  No_of_rides;   // number of times the car rides
};

#endif
