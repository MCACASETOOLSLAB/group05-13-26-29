//------------------------------------------------------------------------
// Filename: 
//    roller-coaster.cpp
// PROGRAM DESCRIPTION
//    Implementation of passenger threads and car thread
//------------------------------------------------------------------------

#include <iostream>

#include "roller-coaster.h"

// static data variables

static int On_board_passenger_ID[MAX_CAPACITY];   // IDs of on board passengers  
static int On_board_passenger_counter = 0;        // number of passengers on board

// static semaphores

static Semaphore Queue("WaitingQueue", 0);   // passenger waiting for a ride
static Semaphore CheckIn("CheckIn", 1);      // check in counter 
static Semaphore Boarding("Boarding", 0);    // controls the boarding process
static Semaphore Riding("Riding", 0);        // keep passengers on the car so 
static Semaphore Unloading("Unloading", 0);  // controlling the unloading process


// ------------------------------------------------------------------- 
// FUNCTION  Filler():                                              
//    This function fills a strstream with spaces.                 
// ------------------------------------------------------------------- 

strstream *Filler(int n)
{
     int  i;
     strstream *Space;

     Space = new strstream;
     for (i = 0; i < n; i++)
          (*Space) << ' ';
     (*Space) << '\0';
     return Space;
}

//------------------------------------------------------------------------
// PassengerThread::PassengerThread()
//      constructor for PassengerThread class
//------------------------------------------------------------------------

PassengerThread::PassengerThread(int Number,  int capacity)
{
     passenger_Id = Number;
     Capacity = capacity;
     ThreadName.seekp(0, ios::beg);
     ThreadName << "Passenger" << passenger_Id << '\0';
}

//------------------------------------------------------------------------
// PassengerThread::TakeRide()
//      passenger takes ride in the car
//------------------------------------------------------------------------

void PassengerThread::TakeRide()
{
     strstream *Space;

     Space = Filler(3);       // build leading spaces
     
     Queue.Wait();            // join the queue for a ride
     CheckIn.Wait();          // time to check in

     // save my name and increase the counter
     On_board_passenger_ID[On_board_passenger_counter] = passenger_Id;
     On_board_passenger_counter++;
     cout << Space->str() << ThreadName.str() 
          <<" is on board the car" << endl;

     // if I am the last one to be on board, boarding completes and the car is full
     if (On_board_passenger_counter == Capacity)  
          Boarding.Signal();   
     CheckIn.Signal();        // allow next passenger to check in
     Riding.Wait();           // I am riding in the car
     Unloading.Signal();      // get off the car
}

// ---------------------------------------------------------------------    
// FUNCTION PassengerThread::ThreadFunc()
//    The thread body of PassengerThread.                  
// --------------------------------------------------------------------- 

void PassengerThread::ThreadFunc() 
{
     Thread::ThreadFunc();

     while (1) {        
          Delay();       // wandering for a while
          TakeRide();    // take a ride
     }
     Exit();
}

//------------------------------------------------------------------------
// CarThread::CarThread()
//      constructor for CarThread class
//------------------------------------------------------------------------

CarThread::CarThread(char *Name, int capacity, int noOfRides)
          : Thread(Name)
{
     Capacity = capacity;
     No_of_rides = noOfRides;
}

// ---------------------------------------------------------------------    
// FUNCTION CarThr::ThreadFunc()
//    The function implement a car thread.                  
// --------------------------------------------------------------------- 

void CarThread::ThreadFunc()
{
     Thread::ThreadFunc();
     int i, j;

     for (i = 1; i <= No_of_rides; i++) {               
          for (j = 1; j <= Capacity; j++)  
               Queue.Signal();          // allow CAPACITY passengers to check in
          Boarding.Wait();              // wait for boarding to complete

          // print on boarding passenger names
          cout << "The car is running for the " << i 
               << " time with passengers ";
          for (j = 0; j < Capacity; j++) 
               cout << " " << On_board_passenger_ID[j];
          cout << endl;
          Delay();                      // ride for a while

          On_board_passenger_counter = 0;  // start unloading passengers            
          for (j = 1; j <= Capacity; j++) {
               Riding.Signal();         // release a passenger
               Unloading.Wait();        // wait until this passenger is done
          }
          // definitely, the car is empty and goes for the next run
     }
     // done here and show messages
     cout << "The car is shot-off for maintenance" << endl;
     
     Exit();
}

// end of roller-coaster.h
