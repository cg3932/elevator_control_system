#include "Scheduler.h"

//Constructor
	Scheduler::Scheduler()
	{
		// Initializing 
		Serial.println("Constructor Invoked. Hi!");
			elevator[0] = Elevator(0,0);
	    	elevator[1] = Elevator(0,1);
	    	elevator[2] = Elevator(0,2);
	}
	
//This function responds to the user commands	
	 void Scheduler::Invoke(String binaryInput)
	 {
	         Tokenize(binaryInput);
			 if(elevatorID==3)      //special code for toggling userType (shortage of input pins)
			 return;
			 
	         if(userType == "Operator")
			  {Operator();return;}
			 else
			  {Passenger();return;}
	  	  
	 }
	void Scheduler::Passenger()
    {
	  
	  Serial.print("----- Passenger Command ");
	     switch(opCode){
	    
	     case 0:   break;
	     case 1:   ScheduleCalls(floor,"UP");
	 	           Serial.print(" op: Hall Call Up");
	 			   Serial.print("\tFloor : "+String(floor)+"-----\n");
	 			   break;
	     case 2:   ScheduleCalls(floor,"DOWN");
	 	           Serial.print(" op: Hall Call Down");
	 			   Serial.print("\tFloor : "+String(floor)+"-----\n");
	 			   break;
	     case 3:   InsertDestination(floor,elevatorID);
	 	           Serial.print(" op:Insert Destination for Elevator "+String(elevatorID+1));
	 	           Serial.print("\tFloor : "+String(floor)+"-----\n");
	 	           break;
	     case 4:   OpenDoor(elevatorID);
	 	           Serial.print(" op: Open Door for Elevator "+String(elevatorID+1));
	 	           Serial.print("-----\n");
	 	           break;
	     case 5:   CloseDoor(elevatorID);
	 	           Serial.print(" op: Close Door for Elevator "+String(elevatorID+1));
	 	           Serial.print("-----\n");
	 	           break;
	     case 6:   CancelCalls(floor,elevatorID);
	 			   Serial.print(" op: Cancel floor for Elevator "+String(elevatorID+1));
	 			   Serial.print("\tFloor : "+String(floor)+"-----\n");
	 			   break;
	     case 7:   Serial.print(" op: Alarm status:");
	 			   Alarm(elevatorID);
	 			   Serial.print(" for Elevator "+String(elevatorID+1));
	 			   Serial.print("-----\n");
	 			   break;
	     default : break;
	 }
    }	
	void Scheduler::Operator()
	{
	    Serial.print("----- Operator Command");
	     switch(opCode){
	     case 0:   Reset();
		           Serial.print(" op: System Reset ");
		           Serial.print("-----\n");
				   break;
	     case 3:   InsertDestination(floor,elevatorID);
		           Serial.print(" op:Insert Destination for Elevator "+String(elevatorID+1));
		           Serial.print("\tFloor : "+String(floor)+"-----\n");
		           break;
	     case 4:   OpenDoor(elevatorID);
		           Serial.print(" op: Open Door for Elevator "+String(elevatorID+1));
		           Serial.print("-----\n");
		           break;
	     case 5:   CloseDoor(elevatorID);
		           Serial.print(" op: Close Door for Elevator "+String(elevatorID+1));
		           Serial.print("-----\n");
		           break;
	     case 7:   Serial.print(" op: Alarm status:");
				   Alarm(elevatorID);
				   Serial.print(" for Elevator "+String(elevatorID+1));
				   Serial.print("-----\n");
				   break;
	     default : break;
	 }
	 
	}
	
	void Scheduler::Reset()
	{
	   int i;
	   for(i=0;i<3;++i)
	    {
		 elevator[i].removeAll();
		 elevator[i].add(0,0);
		}
	}
//This function periodically sends output to the serial Monitor to show the current status of the elevators
	void Scheduler::Update()
	 {
	   int i;
	   for(i =0;i<3;++i)
	   {
	    elevator[i].update();
		//for indentation purposes
		int blankLen = 8-elevator[i].getDoorStatus().length();
		String blank="";
		int j;
		for(j=0;j<blankLen;++j)
		blank+=" ";
		//Output
		Serial.print(String(elevator[i].getCurrentFloor())+" "+String(elevator[i].getDoorStatus())+blank+"\t");
	   }
	   Serial.print("\n");
	   
	 }

//inserts a destination floor to the floorQueue of the specified elevator.	 
     void Scheduler::InsertDestination(int floor,int elevatorID) 
	 {
	    InsertIntoQueue(elevatorID,floor);
	 }
	 
//Schedules hall calls 	 
     void Scheduler::ScheduleCalls(int floor,String callDirection)
	 {
	   int closest = -1;  // for closest lift 
		int elevatorID   = -1;  // elevator to send
        boolean concatenate = false;   //To indicate if the floor should be inserted or concatenated to the queue
		String userDirection;

         
		//Check if call already exists
		if(CheckIfCallExists(floor,callDirection))return;
			 
		//Continue travelling in the direction while there are remaining requests in the same direction.
		
		//Action : check which of the elevators are going in the same direction and assign the closest elevator.
		int i,distance,val;
		String nextDirection;
		for(i = 0 ; i<3;++i)
		{
		    
			nextDirection = FindElevatorMovementDirection(i);
			
			if(nextDirection == callDirection)
			{
				if(nextDirection== "UP" &&  floor>elevator[i].getCurrentFloor())
				{
				    val = floor - elevator[i].getCurrentFloor();
					distance  = abs(val);
				    if(elevator[i].getCallStatus()=="NONE" && (closest == -1 || closest>distance) ) { closest =distance; elevatorID = i; }
				}
				else if(nextDirection== "DOWN" &&  floor<elevator[i].getCurrentFloor())
				{
				    val = floor - elevator[i].getCurrentFloor();
					distance  = abs(val);
				    if(elevator[i].getCallStatus()=="NONE" && (closest == -1 || closest>distance) ) { closest =distance; elevatorID = i; }
				}
			}
					
		}
		
		//If no elevator has been allocated from the previous step, allocate the one which is idle and closest
		if(elevatorID==-1)
			for(i = 0 ; i<3;++i)
			{
				nextDirection = FindElevatorMovementDirection(i);
				
				if(nextDirection == "IDLE")
				{
				 val = floor - elevator[i].getCurrentFloor();
				 distance  = abs(val);
			    
				 if(closest == -1 || closest>distance){ closest =distance; elevatorID = i;}
				}
						
			}
		//Again, If no elevator has been allocated from the previous step, allocate the one which is moving in the opp direction 
		//and has the closest last floor on queue
		if(elevatorID==-1)
			for(i = 0 ; i<3;++i)
			{
				 int size = (int)elevator[i].size();
				 val = floor - elevator[i].get(size-1);
				 //distance from the last floor on queue
				 distance  = abs(val);
			    
				 if(closest == -1 || closest>distance){ 
				 closest =distance; 
				 elevatorID = i; 
				 concatenate=true;
				 }
						
			}

	      //Find out which direction the user is at 
		 if(floor > elevator[elevatorID].getCurrentFloor())
		 userDirection = "UP";
		 else
		 userDirection = "DOWN";
		 
        // TO make sure that the elevator reaches, without going further ,to the user who wants to go in the opposite direction 
        if(userDirection!=callDirection) 
	    elevator[elevatorID].setCallStatus(callDirection);
        
        if(concatenate==true)
        elevator[elevatorID].add(floor);
        else
        InsertIntoQueue(elevatorID,floor);
		
	 }
	 bool Scheduler::CheckIfCallExists(int floor,String callDirection) 
	 {
	    int i;
		for(i=0;i<3;++i)
		{
			if(elevator[i].contains(floor) && elevator[i].getCallStatus()==callDirection) 
			{
				return true;
			}
		}
	    return false;	
	 }
	 void Scheduler::CancelCalls(int floor, int elevatorID)
	 {
	   elevator[elevatorID].remove(floor);
	 }
     void Scheduler::OpenDoor(int elevatorID)
	 {
	    elevator[elevatorID].addDoorCommand(1);
	 }
     void Scheduler::CloseDoor(int elevatorID)
	 {
	   elevator[elevatorID].addDoorCommand(0);
	 }
     void Scheduler::Alarm(int elevatorID) 
	 {
	    //toggle alarm status
		bool alarmStatus = !elevator[elevatorID].getAlarmStatus();
	    if(alarmStatus == true)
		   {
		    elevator[elevatorID].setAlarmStatus( alarmStatus);
		    if(userType=="Operator" )
			  {
			   elevator[elevatorID].operatorAlarm = true;
			  }
		   }
		else
		  {
		    if(userType=="Operator" )
			  {
			   if(elevator[elevatorID].operatorAlarm ==true)
     		   {
			    elevator[elevatorID].setAlarmStatus( alarmStatus);
			    elevator[elevatorID].operatorAlarm = false;
			   }
			  }
			else
			  {
			   elevator[elevatorID].setAlarmStatus( alarmStatus);
			   elevator[elevatorID].operatorAlarm = false;
			  }
		  }		
		if(elevator[elevatorID].getAlarmStatus())
		Serial.print("ON");
		else
		Serial.print("OFF");
	 }
     String Scheduler::FindElevatorMovementDirection(int i)
	 {
	  String nextDirection;
    	if(elevator[i].size())
		{
			int nextFloor = elevator[i].get(0);
     		if(elevator[i].getCurrentFloor() < nextFloor)
	    		nextDirection = "UP";
     		else
     			nextDirection = "DOWN";
		}
		else
			nextDirection = "IDLE";
		
    	return nextDirection;
	 }
	 
	 //This function takes in the input binary string and extracts values and sets the global variables. 
     void Scheduler::Tokenize(String binaryInput)
	 {
	   String tokens[4];
		 
	     // Tokenize the input binary input
		 tokens[0]= binaryInput.substring(0, 1);	// 1 bit
		 tokens[1]= binaryInput.substring(1, 3);  // 2 bits
		 tokens[2]= binaryInput.substring(3, 6);  // 3 bits
		 tokens[3]= binaryInput.substring(6, 11); // 5 bits
		
/*		
		// Setting up appropriate variables based on the input
		 if(convertToInt(tokens[0]) == 0)
			 userType = "Passenger";
		 else 
			 userType = "Operator";
*/
			 
		 elevatorID = convertToInt(tokens[1]);
		 opCode = convertToInt(tokens[2]);
		 floor  = convertToInt(tokens[3]);
		 
		 if(elevatorID == 3)
			 {
			  if(userType == "Passenger")
			  {
			   userType = "Operator";
			   Serial.println("---- Operator Mode ----");
			  }
			  else
			  {
			   userType = "Passenger";
			   Serial.println("---- Passenger Mode ----");
			  }
			 }
		 
	 }
	 int Scheduler::convertToInt(String a)
	 {
	      int i,ret=0;
	      int len=a.length();
	       
	      for(i=0;i<len;++i)
	      {
	         int x= ((int)(a[i]-'0'));  
		     int coeff = findPow(2,len-i-1);	
		     ret+= x*coeff;
	      }
	       return ret;
	 }
	 int Scheduler::findPow(int x,int e)
	 {
	   int i,ret=1;
	   for(i=0;i<e;++i)
	   ret*=x;
	   
	   return ret;
	 }
     void Scheduler::InsertIntoQueue(int elevatorID,int floor)
	 {
	   
	     int i,flag=0;
         String direction  = FindElevatorMovementDirection(elevatorID); // direction in which the elevator is going
		
		
		  for(i = 0;i<elevator[elevatorID].size();++i)
         {
		 
    	    int comparedFloor = elevator[elevatorID].get(i);
   	       	if(direction == "UP" && floor < comparedFloor && floor>elevator[elevatorID].getCurrentFloor())
   	       		{elevator[elevatorID].add(i,floor);flag=1;break;}
   	       	else if(direction == "DOWN" && floor > comparedFloor && floor<elevator[elevatorID].getCurrentFloor())
   	        	    {elevator[elevatorID].add(i,floor);flag=1;break;}
         }
         
         if(flag==0)
		 {
          elevator[elevatorID].add(floor);
		 
		 }
	 }
