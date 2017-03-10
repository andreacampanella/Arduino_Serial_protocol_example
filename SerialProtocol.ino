/*
	A simple serial communication protocol example. 
 	By Andrea "emuboy" Campanella
 	emuboy85@gmail.com
 	
	the communication packet will be something like this 
	
	0xAC 0x02 0xDE 0xAD 0x39

	0xAC is the header of out packet , this , with the checksum , will help the communication se-sync in case of error.
	0x01 is the leght of the payload (zero based, 1 is two bytes)
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
	if (Serial.available() > 0) {
		// get incoming byte:
		inByte = Serial.read();
		if (inByte == packet_header)    	
		{
		  #ifdef DEBUG
      Serial.print("Found header\n");      
      #endif
      
			//first byte found. 
			packet_lenght = Serial.read();

			if (packet_lenght > 0)    		
			{
      
    #ifdef DEBUG
        Serial.print("Lenght is ");
        Serial.print(packet_lenght,HEX);
        Serial.print("\n");
	#endif
				//if the lenght of the data is at least 1 bit long, we have valid data.
				//if not, well, why are you transmitting empty packets anyway???
				//start to collect as much bytes as leght says.
				for (int i = 0; i < packet_lenght; ++i)
				{
					packet_data[i] = Serial.read();
				}
				//let's read the checksum
				packet_checksum = Serial.read() ;
				
				int sum = packet_lenght;
   				
   				for (int i = 0; i < packet_lenght; i++) {
       				sum += packet_data[i];
   				}
   				if (sum = packet_checksum)
   				{
   					//here you can do something with the data the best would be a switch case with packet_data[0] as ID 
   					//and the rest as payload eg : analogWrite(packet_data[0],packet_data[1])
            #ifdef DEBUG
            Serial.print("Checksum valid\n");      
            #endif         
   				}
    		}
	}
  }
}


