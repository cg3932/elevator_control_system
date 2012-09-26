#ifndef Scheduler_h
#define Scheduler_h
#include "Elevator.h"
#include "WProgram.h"
class Scheduler {

	String input;
	String systemStatus;
	String userType;
	int elevatorID;
	int opCode;
	int floor;
	Elevator  elevator[3];
	public:
	 Scheduler();
	 void Invoke(String binaryInput);
	 void Invoke2(int user,int id,int op,int floor);
     void InsertDestination(int floor,int elevatorID) ;
	 void Update();
	 void Operator();
	 void Passenger();
	 void Reset();
	private:
     void ScheduleCalls(int floor,String callDirection);
	 bool CheckIfCallExists(int floor,String callDirection) ;
	 void CancelCalls(int floor, int elevatorID);
     void OpenDoor(int elevatorID);
     void CloseDoor(int elevatorID);
     void Alarm(int elevatorID) ;
     String FindElevatorMovementDirection(int i);
     void Tokenize(String binaryInput);
     void InsertIntoQueue(int elevatorID,int floor);
	 int  convertToInt(String);
	 int findPow(int x,int e);
};

#endif