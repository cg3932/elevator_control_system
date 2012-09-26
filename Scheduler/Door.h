#ifndef Door_H
#define Door_H

#include "WProgram.h"

class Door { 
	

	
	public:
	Door();
	Door(String status);
	
	~Door();
	
	void update();
	
	String getDoorStatus();
	
	void setDoorStatus(String status);
	
	void add(int command);
	
	int size();
	
	int get(int index);
	
	private:
	
	
	// the time counting variable for the opening door status
	int openingCount ;
	
	// the time counting variable for the open door status
	int openCount;
	
	// the time counting variable for the closing door status
	int closingCount;
	
	// the size of the doorCommandQueue
	int doorSize ;
	
   // the door's opening and closing status
	String doorStatus;
	
	// The list of open/close commands for the Door
	int doorCommandQueue[10];
};

#endif
