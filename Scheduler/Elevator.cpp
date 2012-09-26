#include "Elevator.h" //include the declaration for this class




Elevator::Elevator()
{
}

/**
 * Constructor for the Elevator class. Creates an instance of the
 * Elevator class and runs a continuous loop to check the floorQueue
 * and update the system variables accordingly.
 * 
 * @param startingFloor : value for the starting floor of the Elevator
 */
Elevator::Elevator(int startingFloor,int id){
		
	door = Door("CLOSED"); // the current door instance for the Elevator	
	currentFloor = startingFloor;
	direction = "NOT MOVING";
	elevatorMovementStatus = "Initialized on Floor " + String(startingFloor);
	alarmON = false;
	elevatorID = id;
	callStatus="NONE";
	floorSize = 0;
	floorTravelTime = 3;
	
	// initialize floors to 0
	int i;
	for (i = 0; i < 25; i = i + 1) {
		floorQueue[i] = -1;
	}

}

//<<destructor>>
Elevator::~Elevator(){/*nothing to destruct*/}

/**
 * update the movement of the elevator
 */
void Elevator::update() {
    //Update the doors
	door.update();
	
	// check that the alarm isn't on
	if (!alarmON) {
		
    	// check if there any floors to go to
    	if (floorQueue[0] != -1) {
    		
    		// the door is closed and there is a floor in the queue to go to
    		if (door.getDoorStatus().equals("CLOSED")) {
            
    			// if the floor to go to is above the current floor then go up 1 floor
		    	if (currentFloor < floorQueue[0]) {
		    		currentFloor ++;
		    		direction = "UP";
		    		door.setDoorStatus("CLOSED");
		    		elevatorMovementStatus = "MOVING UP TO FLOOR " + String(floorQueue[0]);
		    	
		    	// if the floor to go to is below the current floor then go down 1 floor
		    	} else if (currentFloor > floorQueue[0]) {
		    		currentFloor --;
		    		direction = "DOWN";
		    		door.setDoorStatus("CLOSED");
		    		elevatorMovementStatus = "MOVING DOWN TO FLOOR " + String(floorQueue[0]);
		    	
		    	// if the floor to go to is equal to the current floor  the we have arrived
		    	// open the door and then remove the current floor from the floor queue
		    	} else if (currentFloor == floorQueue[0]) {
		    		
		    		// REMOVE ELEMENT 0 FROM THE FLOOR QUEUE
		    		int j;
		    		for (j = 0; j < 24; j = j + 1) {
		    			floorQueue[j] = floorQueue[j+1];
		    		}
		    		floorQueue[24] = 0;
		    		floorSize --;
		    		
		    		direction = "NOT MOVING";
		    		door.add(1);
		    		elevatorMovementStatus = "ARRIVED AT FLOOR " + String(floorQueue[0]);
		    	}
		    
		    // if the door is open, opening, or closing and there is a floor to go to then close the door so that
		    // in the next iteration we can proceed to that floor
    		} else {
    			direction = "NOT MOVING";
	    		elevatorMovementStatus = door.getDoorStatus() + " DOOR AT FLOOR " + String(currentFloor);
    		}
    		
    	// there are no floors to go to
    	} else {
    		

			//Free up the elevator if it was busy previously
			callStatus="NONE";
    		
    		// if the door is closed then wait at the floor since there are no floors to go to
    		if (door.getDoorStatus().equals("CLOSED")) {
	    		direction = "NOT MOVING";
	    		elevatorMovementStatus = "WAITING AT FLOOR " + currentFloor;
	    	
	    	// if the door is open, the close the door and then wait since there are no floors to go to
    		} else if (door.getDoorStatus().equals("OPEN")){
    			direction = "NOT MOVING";
	    		elevatorMovementStatus = "WAITING AT FLOOR " + String(currentFloor);
    		}
    	}
    	
    // the alarm is on, do not move the elevator and update the elevatorMovementStatus
	} else {
		direction = "NOT MOVING";
		elevatorMovementStatus = "ALARM SOUNDING! WAITING AT FLOOR " + String(currentFloor);
	}
}

/**
 * Add a floor to the floorQueue
 */
void Elevator::add(int floor) {
	 
	 // check that the floor to add is a valid floor and that it doesn't already exist
	 // check that the floor to add is a valid floor and that it doesn't already exist
	
	boolean validFloor = true;
	
	// check that the floor is a valid number
	if ((floor < 0) || (floor > 20)) {
		 validFloor = false;
	}
	// check that the floor isn't already in the floor queue
	int j;
	for (j = 0; j < 25; j = j + 1) {
		if (floorQueue[j] == floor) {
			validFloor = false;
				break;
		}
	}
	
	// if the floor is valid then add it
	if (validFloor) 
	{
		int i;
		for (i = 0; i < 25; i = i + 1) {
			if (floorQueue[i] == -1) {
				floorQueue[i] = floor;
				break;
			}
		}
		floorSize ++;
	}
	
}

/**
 * Add a floor to the floorQueue at a specified index
 */
void Elevator::add(int index, int floor) {
	
	// check that the floor to add is a valid floor and that it doesn't already exist
	boolean validFloor = true;
	
	// check that the floor is a valid number
	if ((floor < 0) || (floor > 20)) {
		validFloor = false;
	}
	
	// check that the floor isn't already in the floor queue
	int j;
	for (j = 0; j < 25; j = j + 1) {
		if (floorQueue[j] == floor) {
			validFloor = false;
			break;
		}
	}
	
	// if the floor is valid then add it
	if (validFloor) {
		int i;
		int temp[25];
		
		// create new temp array with added floor at specified index
		for (i = 0; i < 25; i = i + 1) {
			if (i<index) {
				temp[i] = floorQueue[i];
			} else if (i == index) {
				temp[i] = floor;
			} else {
				temp[i] = floorQueue[i-1];
			}
		}
		
		// copy over temp array
		int j;
		for (j = 0; j < 25; j = j + 1) {
			floorQueue[j] = temp[j];
		}
		
		floorSize ++;
	}
}

/**
 * Return the size of the floorQueue
 */
int Elevator::size() {
	return floorSize;
}

// checks if the floorQueue contains the given floor
bool Elevator::contains(int floor)
{
  int i;
  for (i = 0; i < 25; i++) 
		if(floorQueue[i] == floor)return true;
	
	return false;
}

/**
 * Return the floorQueue array
 */
int Elevator::get(int index) {
	if (index < 25) {
		return floorQueue[index];
	} else {
		return -1;
	}
}

/**
 * @return false if the selected floor was not in the queue
 * return true if the floor was successfully removed from the floorQueue
 */
boolean Elevator::remove(int floor) {
	int i;
	int removeIndex = -1;
	for (i = 0; i < 25; i = i + 1) {
		if (floorQueue[i] == floor) {
			removeIndex = i;
			break;
		}
	}
	
	// the specified floor was not found in the queue
	if (removeIndex == -1) {
		return false;
		
	// the specified floor was found, remove it
	} else {
		int i;
		for (i = removeIndex; i < 24; i = i + 1) {
			floorQueue[i] = floorQueue[i+1];
		}
		floorQueue[24] = 0;
		floorSize --;
		return true;
	}
}

void Elevator::removeAll()
{
    int i;
		for (i = 0; i < 25; i = i + 1)
			floorQueue[i] == -1;
	floorSize = 0;	
}
/**
 * @return current Floor of the Elevator
 */
int Elevator::getCurrentFloor() {
	return currentFloor;
}

/**
 * @param floor: set the current floor of the Elevator
 */
void Elevator::setCurrentFloor(int floor) {
	currentFloor = floor;
}

/**
 * @return current Direction of the Elevator
 */
String Elevator::getDirection() {
	return direction;
}

/**
 * @param newDirection: set the current direction of the Elevator
 */
void Elevator::setDirection(String newDirection) {
	direction = newDirection;
}

/**
 * @param newDoorCommandQueue: set the doorCommandQueue for the Elevator door
 */
void Elevator::addDoorCommand(int command) {
	door.add(command);
}

String Elevator::getDoorStatus()
{
 return door.getDoorStatus();
}
/**
 * @param newElevatorMovementStatus: set the ElevatorMovementStatus
 */
void Elevator::setElevatorMovementStatus(String newElevatorMovementStatus) {
	elevatorMovementStatus = newElevatorMovementStatus;
}

/**
 * @return the alarm status
 */
boolean Elevator::getAlarmStatus () {
	return alarmON;
}

/**
 * @param alarm: set the alarm status
 */
void Elevator::setAlarmStatus(boolean alarm) {
	alarmON = alarm;
}
/**
 * @return the alarm status
 */
String Elevator::getCallStatus(){
	return callStatus;
}
/**
 * @param status: set the isBusy status
 */
void Elevator::setCallStatus(String status){
	callStatus=status;
}
