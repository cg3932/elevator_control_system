#include "Door.h" //include the declaration for this class

// CONSTANTS
	// the time it takes for the elevator door to open
	int openingTime = 3;
	
	// the time the elevator door should be open for
	int openTime = 2;
	
	// the time it takes for the elevator door to close
	int  closingTime = 2;
	
	Door::Door()
	{
	  int i;
	  for (i = 0; i < 10; i = i + 1) {
		doorCommandQueue[i] = -1;
	  }
	  openingCount = 0;
	  openCount = 0;
	  closingCount = 0;
	  doorSize = 0;
	}
/**
 * Constructor for the Elevator class.
 * 
 * @param startingFloor : value for the starting floor of the Elevator
 */
Door::Door(String status){
	doorStatus = status;
	
	// initialize doorCommandQueue
	int i;
	for (i = 0; i < 10; i = i + 1) {
		doorCommandQueue[i] = -1;
	}
	
	doorSize = 0;
	openingCount = 0;
	openCount = 0;
	closingCount = 0;
}

//<<destructor>>
Door::~Door(){/*nothing to destruct*/}

/**
 * update the movement of the door
 */
void Door::update() {
	// Check if any new door commands have been added to the queue
	if (doorCommandQueue[0]!=-1) {
		
		// A Door OPEN command has been requested, initiate door OPEN sequence
		if (doorCommandQueue[0]==1) {
			
    		// REMOVE ELEMENT 0 FROM THE DOOR QUEUE
    		int j;
    		for (j = 0; j < 9; j = j + 1) {
    			doorCommandQueue[j] = doorCommandQueue[j+1];
    		}
    		doorCommandQueue[9] = -1;
    		doorSize--;
			
			doorStatus = "OPENING";
			openingCount = 0;
		
		// A Door CLOSE command has been requested, initiate door CLOSE sequence
		} else if (doorCommandQueue[0]==0) {
			
    		// REMOVE ELEMENT 0 FROM THE DOOR QUEUE
    		int j;
    		for (j = 0; j < 9; j = j + 1) {
    			doorCommandQueue[j] = doorCommandQueue[j+1];
    		}
    		doorCommandQueue[9] = -1;
    		doorSize--;
    		
			doorStatus = "CLOSING";
			closingCount = 0;
		}
		
	}
	
	// Update the door status based on the commands given
	if (doorStatus.equals("OPENING")) {
		
		// If the openingCount is equal to the time that the elevator should take to open the door (i.e. the openingTime)
		// then set the doorStatus to the next stage of leaving the door open. Otherwise, increment the openingCount
		if (openingCount == openingTime) {
			openingCount = 0;
			doorStatus = "OPEN";
		} else {
			openingCount++;
		}
	
		// If the openCount is equal to the time that the elevator door should be open (i.e. the openTime)
		// then set the doorStatus to the next stage of closing the door. Otherwise, increment the openCount
	} else if (doorStatus.equals("OPEN")) {
		if (openCount == openTime) {
			openCount = 0;
			doorStatus = "CLOSING";
		} else {
			openCount++;
		}
		
		// If the closingCount is equal to the time that the elevator door should take to close the door (i.e. the closingTime)
		// then set the doorStatus to the next stage of the door being closed. Otherwise, increment the closingCount
	} else if (doorStatus.equals("CLOSING")) {
		if (closingCount == closingTime) {
			closingCount = 0;
			doorStatus = "CLOSED";
		} else {
			closingCount++;
		}
		
		// The door is closed, continously reset the status counts as a cleanup measure
	} else if (doorStatus.equals("CLOSED")) {
		openingCount = 0;
		openCount = 0;
		closingCount = 0;
	}
}

/**
 * @return current door status
 */
String Door::getDoorStatus() {

	return doorStatus;
}

/**
 * @param status: set the current status for the door
 */
void Door::setDoorStatus(String status) {
	doorStatus = status;
}

/**
 * @param status: add command to doorCommandQueue
 */
void Door::add(int command) {
 
	// check that the command to add isn't already in the door queue
	boolean validCommand = true;
	int j;
	for (j = 0; j < 10; j = j + 1) {
		if (doorCommandQueue[j]==command) {
			validCommand = false;
			break;
		}
	}
	
	// the command doesn't currently exist, add the command to the door queue
	if (validCommand) {
		int i;
		for (i = 0; i < 10; i = i + 1) {
			if (doorCommandQueue[i]==-1) {
				doorCommandQueue[i] = command;
				break;
			}
		}
		doorSize++;
	}
}

/**
 * @return doorCommandQueue
 */
int Door::get(int index) {
	if (index < 10) {
		return doorCommandQueue[index];
	} else {
		return -1;
	}
}

/**
 * @return the size of doorCommandQueue
 */
 int Door::size() {
 	return doorSize;
 }
