/*
	A simple serial communication protocol example. 
 	By Andrea "emuboy" Campanella
 	emuboy85@gmail.com
 	
	the communication packet will be something like this 
	
	0xAC 0x02 0xDE 0xAD 0x39

	0xAC is the header of out packet , this , with the checksum , will help the communication se-sync in case of error.
	0x02 is the leght of the payload 
	0xDE first byte of the payload
	0xAD second byte of the payload
	0x39 is the truckated (to 8 bit) checksum excluding header and checksum bytes
*/

#define packet_header 0xAC //the start of the packet

int packet_lenght = 0   ;
int packet_data[10] = {} ;
int packet_checksum = 0 ;

int inByte = 0 ; //a temporary variable to store our incoming byte

void setup() {  
  // start serial port at 115200 bps:
  Serial.begin(115200);
  Serial.print("Start\n");
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }  
}

void loop() {
	/*
		Data collection phase:
		in this phase you will collect the data form the serial port , 
		check if is valid and do something useful with it .
	*/
	if (Serial.available() > 3) {
	    /*
	    The Arduino is not fast enought to handle a context switch between the serial port and the 
	    code, we will have to collect the data in the serial port and analise it later.
	    */
	    delay(1); //let the UART collect all the packages
	    int i = 0;

	    while ((Serial.available() > 0) ){   
	      packet_data[i] = Serial.read();
	      i++;
	    }
	  
	    int total_packet_len = packet_data[1]+2 ; //this is useful only to keep the code tidy.

	    //check if the header is right.
		if (packet_data[0] == packet_header){
      		//Check if the lenght is valid.
      		if (packet_data[1] > 0){
				/*Let's read the checksum*/					
				long sum = 0 ; 	        
        		//Sum every element in the packet until you reach the checksum
				for (i = 0; i < total_packet_len; i++) {
					sum += packet_data[i];
				}
        		sum = sum & 0xFF ;	   				
   				if ( sum  == packet_data[total_packet_len] ){
   					//here you can do something with the data the best would be a switch case with packet_data[0] as ID 
   					//and the rest as payload eg : analogWrite(packet_data[0],packet_data[1])
   					
            		Serial.printf("checksum valid , Data is : 0x%x \t 0x%x \n",packet_data[2],packet_data[3]);      
              

   				}
	    	}
    	}
	}
}


