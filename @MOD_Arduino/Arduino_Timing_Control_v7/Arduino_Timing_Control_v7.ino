// About the program
  #define programVersion 7 // Max: 255
  
// Includes
  #include <avr/interrupt.h>

// Serial input to the program
  #define inputArrayMaxSize 500
  byte inputArray[inputArrayMaxSize]; // an array of integers to hold incoming data
  word inputArraySize = 0; // Current size of the input array
  boolean bufferOverflow = false; // Flag for input array buffer overflow
  boolean flagFirstEndByte = false; // Flag for the first 255 bit
  boolean inputComplete = false;  // whether the string is complete

// Define Functions
  // Static Functions
    #define fnECHO 0 //
    #define fnVERSION 1 //
    #define fnSET_CONTINUOUS 2 // Sets the continuous function
    #define fnSET_INT0_INTERRUPT 3 // Sets the timer interrupt
    #define fnCLEAR_INT0_INTERRUPT 4 // Clears the clock interrupt
    #define fnSET_INT0_INTERRUPT_PINS 5 // Sets what to do on an interrupt
    #define fnTIMING_SEQUENCE 50 // Runs the camera timing sequence
    #define fnONE_IMAGE 52 // Acquires one image
    #define fnSHUTTER_AND_IMAGES 51 // Opens the shutter, acquires two images, closes it
  // Continuous Functions

// Define pins
  // B Bank: outputs
  #define qswitchPin 10
  #define ledPin 13
  #define lampPin 12
  #define cameraPin 9
  #define shutterPin 11
  // D Bank: Inputs
  // Trigger pin is set to 2, necessary for interrupt to work

// Continuous acquire
#define lampDivide 5000 // Sets the devision factor for the lamp (from the external clock signal), must be int multiple of cameraDivide
#define cameraDivide 200
word cameraPulseCounter = cameraDivide - 1;
word lampPulseCounter = lampDivide - 1;
word qswitchCounter;
unsigned int PORTB_buffer = 0;
bool cameraINT0triggerON = false;
bool lampINT0triggerON = true;
bool qswitchINT0triggerON = false;

// Continuous function variables
word continuousFunction = 0; // Function to run when not running another function
byte continuousFunctionParamsArray[inputArrayMaxSize];         // an array of integers to hold incoming data
word continuousFunctionParamsArraySize = 0;

// Laser lamp variables
      word lampCounter;

// Variables for case 50
      byte EIMSK_OLD;
      // Define various parameters
      word delayMilliseconds;
      word divisionFactor;
      word numImages;
      word pulseDelay;

      // Set the excimer pulse stuff
      word totalNumberExcimerPulsesRemaining;
      word excimerPulseNumber;
      word nextExcimerPulsePointer;
      
// Notes:
//  High byte should be sent first

// One-time Functions
//   2  - Set the continuous function. Bytes should be (uint8 representation)
//        [0][02][a1][a2][c1][c2][c3]...[cn][\end1][\end2], where
//        a = (uint16) Continuous function number. 0 means do nothing each loop
//        c = array of 16 bit unsigned integers to pass the
//        \end = 0xFFFF, end of input.
//   50 - run the excimer program. Bytes should be (uint8 representation)
//        [0][50][a1][a2][b1][b2][c1][c2][d1][d2][d3]...[dn][\end1][\end2], where
//        a = (uint16) TTL input division factor
//        b = (uint16) number of images to acquire
//        c = (uint16) cycles to wait (/4) after input trigger, before cam trigger
//        d[] = array of 16 bit unsigned integers telling when the excimer
//              pulses should occur. 0 means that the excimer will be triggered
//              concurrently with the first image acquisition. 1 on the second, etc.
//              This array should be ordered sequentially or pulses will be missed.
//        \end = 0xFFFF, end of input.

// Continuous Functions
//   50 - Fire the camera with an incoming pulse. Command to set the function is (uint8 representation)
//        [0][02][0][50][a1][a2][\end1][\end2], where
//        a = (uint16) Continuous function number. 0 means do nothing each loop
//        \end = 0xFFFF, end of input.

// Pin interrupt routine
ISR(INT0_vect) {
  PORTB_buffer = 0;
// Trigger the camera
  if (cameraPulseCounter == 0) {
    if (cameraINT0triggerON == true) {
      PORTB_buffer = PORTB_buffer | (1 << (cameraPin - 8));
    }
    cameraPulseCounter = cameraDivide;
  }
  cameraPulseCounter -= 1;
  
  // Trigger the lamp and/or qswitch
  if (lampPulseCounter == 0) {
    if (lampINT0triggerON == true) {
      PORTB_buffer = PORTB_buffer | (1 << (lampPin - 8));
    }
    if (qswitchINT0triggerON == true) {
      PORTB_buffer = PORTB_buffer | (1 << (qswitchPin - 8));
    }
    lampPulseCounter = lampDivide;
  }
  lampPulseCounter -= 1;
  
  // Trigger the entire port, keeping other pins intact
  PORTB |= PORTB_buffer;
  delayMicroseconds(1);
  PORTB &= ~PORTB_buffer;
}

void setup() {
  /* Make sure all pins are put in high impedence state and 
     that their registers are set as low before doing anything.
     This puts the board in a known (and harmless) state     */
  int i;
  for (i=0;i<20;i++) {
    pinMode(i,INPUT);
    digitalWrite(i,0);
  }
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,0);
  // initialize serial:
  Serial.begin(115200,SERIAL_8N1);
  
  // Initialization Code
  // DDRD = DDRD | B11111000;  // sets pins 3 to 7 as outputs, 2 input without changing the value of pins 0 & 1, which are RX & TX 
  DDRB = B11111110; // sets B bank to outputs, except for pin 8
  
  // Set Pin 2 as input
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);    // Enable pullup resistor
  
  
  EICRA |= (1 << ISC00);    // | (1 << ISC01);    // Trigger INT0 on rising edge
  EICRA |= (1 << ISC01);

  // SET INT0 Interrupt
  EIMSK |= (1 << INT0);
}

//ISR(INT0_vect) {
//  PORTB = B00000010;
//  //EIMSK &= ~(1 << INT0);     // Disable external interrupt INT0
//  PORTB = B00000000;
//}

void loop() {

  if (inputComplete) {
    // Check for a buffer overflow
    if (bufferOverflow | inputArraySize < 2) {
      // clear the string and set necessary parameters
      inputArraySize = 0;
      flagFirstEndByte = false;
      inputComplete = false;
      bufferOverflow = false;
      return;
    }

    // Switch on the first character of the string
    switch (makeWord(inputArray[0],inputArray[1])) {
      
     //////////////////////////////////////////////////////////
     // Case 0 - Echo the input                              //
     //////////////////////////////////////////////////////////
     case fnECHO:
      for (word j=0;j<inputArraySize;j++) {
        Serial.write(inputArray[j]);
      }
      Serial.write(255);
      Serial.write(255);
      break;
      
     //////////////////////////////////////////////////////////
     // Case fnVERSION - Echo the version                            //
     //////////////////////////////////////////////////////////
     case fnVERSION:
      digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(200);               // wait for 200 ms
      digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
      Serial.write(0);
      Serial.write(0);
      Serial.write(0);
      Serial.write(programVersion);
      Serial.write(255);
      Serial.write(255);
      break;
      
     //////////////////////////////////////////////////////////
     // fnSET_CONTINUOUS - Set the continuous function       //
     //////////////////////////////////////////////////////////
     case fnSET_CONTINUOUS:
      // Check for required input parameters
      if (inputArraySize < 4) {break;}
	  
	  continuousFunction = makeWord(inputArray[2],inputArray[3]);
	  memcpy(inputArray,continuousFunctionParamsArray,inputArrayMaxSize);
	  continuousFunctionParamsArraySize = inputArraySize;

     //////////////////////////////////////////////////////////
     // fnSET_INT0_INTERRUPT - Sets the INT0 interrupt       //
     //////////////////////////////////////////////////////////
     case fnSET_INT0_INTERRUPT:
       EIMSK |= (1 << INT0);
       break;

     //////////////////////////////////////////////////////////
     // fnCLEAR_INT0_INTERRUPT - Clears the INT0 interrupt   //
     //////////////////////////////////////////////////////////
     case fnCLEAR_INT0_INTERRUPT:
       EIMSK &= ~(1 << INT0);
       break;
       
     //////////////////////////////////////////////////////////
     // fnSET_INT0_INTERRUPT_PINS - Sets which things happen on INT0 interrupt   //
     //////////////////////////////////////////////////////////
     case fnSET_INT0_INTERRUPT_PINS:
        // Check for required input parameters
        if (inputArraySize < 2) {break;}
        
        // Set some values from the input
        //  bit 1 = camera, bit 2 = lamp, bit 3 = qswitch
        if ((inputArray[3] & (1 << 0)) == 0) {cameraINT0triggerON = false;} else {cameraINT0triggerON = true;}
        if ((inputArray[3] & (1 << 1)) == 0) {lampINT0triggerON = false;} else {lampINT0triggerON = true;}
        if ((inputArray[3] & (1 << 2)) == 0) {qswitchINT0triggerON = false;} else {qswitchINT0triggerON = true;}
       break;
       
     //////////////////////////////////////////////////////////
     // Case 50 - run the excimer/camera timing sequence     //
     //////////////////////////////////////////////////////////
     case fnTIMING_SEQUENCE:
        // Hard-coded values
        //   PORTB is pins 8 to 13. The last two bits (B000000XX) are for the crystal and are unused
        //   The numbering scheme is 13,12,11,10,9,8,xtal,xtal for the 8 pins in the PORTB register.
        //   Pin 8 has been defined as the TTL input trigger pin
        //   Pin 9 has been defined as the camera trigger output pin
        //   Pin 10 has been defined as the excimer trigger output pin
        
        // Check for required input parameters
        if (inputArraySize < 10) {break;}
        
        // Define various parameters
        delayMilliseconds = makeWord(inputArray[2],inputArray[3]);
        divisionFactor = makeWord(inputArray[4],inputArray[5]);
        numImages = makeWord(inputArray[6],inputArray[7]);
        pulseDelay = makeWord(inputArray[8],inputArray[9]);
  
        // Set the excimer pulse stuff
        totalNumberExcimerPulsesRemaining = floor((inputArraySize - 10)/2);
        excimerPulseNumber = 65535; // WORD_MAX
        nextExcimerPulsePointer = 10;
        if (totalNumberExcimerPulsesRemaining > 0) {
          totalNumberExcimerPulsesRemaining -= 1;
          excimerPulseNumber = makeWord(inputArray[nextExcimerPulsePointer],inputArray[nextExcimerPulsePointer+1]);
          nextExcimerPulsePointer += 2;
        }
        
        // Wait half a second
        delay(delayMilliseconds);
        
        // Stop the interrupt - we want full control here
        EIMSK_OLD = EIMSK;
        EIMSK &= ~(1 << INT0);
        PORTB = 0;
        
        // Wait for the next lamp fire
        while(lampPulseCounter > 0) {
             // Wait for pin LOW
             while (PIND & (1<<2)) {}
             
             // Wait for pin HIGH
             while (!(PIND & (1<<2))) {}
             lampPulseCounter -= 1;
        }
        lampPulseCounter = 0;
        PORTB = 0;
        
        for (word j=0;j<300;j++)
        {
           
           if (j == 100) {
                 // Wait for pin LOW
                 while (PIND & (1<<2)) {}
                 
                 PORTB = 0;
                 
                 // Wait for pin HIGH
                 while (!(PIND & (1<<2))) {}
                 PORTB = (1 << (cameraPin - 8)) | (1 << (lampPin - 8)) | (1 << (qswitchPin - 8));
               
            } else if ((j % (lampDivide/cameraDivide)) == 0) {
                 // Wait for pin LOW
                 while (PIND & (1<<2)) {}
                 PORTB = 0;
                 // Wait for pin HIGH
                 while (!(PIND & (1<<2))) {}
                 PORTB = (1 << (cameraPin - 8)) | (1 << (lampPin - 8));
            } else {
                 // Wait for pin LOW
                 while (PIND & (1<<2)) {}
                 PORTB = 0;
                 // Wait for pin HIGH
                 while (!(PIND & (1<<2))) {}
                 PORTB = (1 << (cameraPin - 8));
            }
            
           // Wait for the remaining pulses 
           for (int i = 0; i < (cameraDivide - 1); i++) {
                 // Wait for pin LOW
                 while (PIND & (1<<2)) {}
                 
                 // Wait for pin HIGH
                 while (!(PIND & (1<<2))) {}
           }
        }
        
         // Wait for pin LOW
         while (PIND & (1<<2)) {}
         PORTB = 0;
         
         // Turn the interrupt back on
         lampPulseCounter = 0;
         EIMSK = EIMSK_OLD;
          
         // Write to serial
         // Serial.write("DONE");
         break;
     //////////////////////////////////////////////////////////
     // Case fnSHUTTER_AND_IMAGE - run the shutter/camera program             //
     //////////////////////////////////////////////////////////
     case fnSHUTTER_AND_IMAGES: 
     
      // Set the shutter open
      PORTB = (1 << (shutterPin - 8));
      
      // Wait for the shutter to open
      delay(1000);
      
       // Wait for pin LOW
       while (PIND & (1<<2)) {}
       PORTB = (1 << (shutterPin - 8));
       // Wait for pin HIGH
       while (!(PIND & (1<<2))) {}
       PORTB = (1 << (shutterPin - 8)) | (1 << (cameraPin - 8));
      
       // Wait for the remaining pulses 
       for (int i = 0; i < (cameraDivide - 1); i++) {
             // Wait for pin LOW
             while (PIND & (1<<2)) {}
             PORTB = (1 << (shutterPin - 8));
             
             // Wait for pin HIGH
             while (!(PIND & (1<<2))) {}
       }
      
       // Wait for pin LOW
       while (PIND & (1<<2)) {}
       PORTB = (1 << (shutterPin - 8));
       // Wait for pin HIGH
       while (!(PIND & (1<<2))) {}
       PORTB = (1 << (shutterPin - 8)) | (1 << (cameraPin - 8));
       
       // Wait for the remaining pulses 
       for (int i = 0; i < (cameraDivide - 1); i++) {
             // Wait for pin LOW
             while (PIND & (1<<2)) {}
             PORTB = (1 << (shutterPin - 8));
             
             // Wait for pin HIGH
             while (!(PIND & (1<<2))) {}
       }
      
       // Wait for pin LOW
       while (PIND & (1<<2)) {}
       PORTB = (1 << (shutterPin - 8));
       // Wait for pin HIGH
       while (!(PIND & (1<<2))) {}
       PORTB = (1 << (shutterPin - 8)) | (1 << (cameraPin - 8));
      
      // Wait for the image to be captured
      delay(100);
      
      // Close the shutter
      PORTB = 0;
      
       break;

     //////////////////////////////////////////////////////////
     // Case fnONE_IMAGE - acquire one image                 //
     //////////////////////////////////////////////////////////
     case fnONE_IMAGE: 

      // Pause for the camera
      delay(500);

      // Acquire an image
       // Wait for pin LOW
       while (PIND & (1<<2)) {}
       PORTB = 0;
       // Wait for pin HIGH
       while (!(PIND & (1<<2))) {}
       PORTB = (1 << (cameraPin - 8));
       // Wait for pin LOW
       while (PIND & (1<<2)) {}
       PORTB = 0;
      
      break;
        
    } // End Switch Structure
    
    // clear the string and set necessary parameters
    inputArraySize = 0;
    flagFirstEndByte = false;
    inputComplete = false;
    bufferOverflow = false;
  } else {
      switch (continuousFunction) {
        case 0:
          break;
        case 50:
          break;
      }
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    byte inByte = (char)Serial.read(); 
    // if the incoming character is null, set a flag for
    // the main loop
    if (inByte == 255 & flagFirstEndByte) {
      // The last bit was also 255, so we need to flag the end of
      // the input
      inputComplete = true;
    } else if (inByte == 255) {
      // This is possibly the first end byte in the sequence,
      // so we should flag it
      flagFirstEndByte = true;
    } else {
      if (flagFirstEndByte) {
       // Since this bit is not 255, we are not at the end of the
       // input. We need to add 255 to the end of the input array
       // before we move on.
       flagFirstEndByte = false;
       if (inputArraySize < inputArrayMaxSize) {
        inputArray[inputArraySize] = 255;
        inputArraySize += 1;
       } else {bufferOverflow = true;}
      }
      
      // Also add the new bit to the input array
      if (inputArraySize < inputArrayMaxSize) {
       inputArray[inputArraySize] = inByte;
       inputArraySize += 1;
      } else {bufferOverflow = true;}
    }
  }
}
