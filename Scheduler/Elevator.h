#ifndef Elevator_H
#define Elevator_H

#include "WProgram.h"
#include <Door.h>

class Elevator { 
	
	
	//Variables
    // constants
    int floorTravelTime ; // the time in seconds it takes the elevator to travel from one floor to another
    
    // global variables
    int currentFloor; // the current floor the Elevator is at
    String direction; // the current direction of the Elevator
    int floorQueue[25]; // List of floors for the elevator to visit
    int floorSize; // Size of floorQueue
    String elevatorMovementStatus; // the current movement status of the Elevator
    boolean alarmON; // the current status of the elevator alarm
    
    
    //Added by Nagappan
    String callStatus; //purpose: To determine if the elevator is busy under some other call
    int elevatorID;

	public:
	boolean operatorAlarm;
	Elevator();
	Elevator(int startingFloor,int id);
	
	~Elevator();
	
	// Door Class
    Door door;

	void update();
	
    int getCurrentFloor();
    
	void setCurrentFloor(int floor);
	
	String getDirection();
	
	void setDirection(String newDirection);
	
	void add(int floor);
	
	void add(int index, int floor);
	
	boolean remove(int floor);
	
	int size();
	
	int get(int index);
	
	bool contains(int floor);
	
	void addDoorCommand(int command);
	String getDoorStatus();
	
	String getElevatorMovementStatus();
	
	void setElevatorMovementStatus(String newMovementStatus);
	
	boolean getAlarmStatus();
	
	void setAlarmStatus(boolean newAlarmStatus);
	
	String getCallStatus();
	
	void setCallStatus(String newCallStatus);
	
	void removeAll();
};

#endif
