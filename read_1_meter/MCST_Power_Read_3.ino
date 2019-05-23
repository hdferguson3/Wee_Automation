// Program to count pulses from power meter and send via serial to host
// Doug Ferguson
// April 2019
// Adafruit Metro Mini 328 Unno Board

//Number of pulses, used to measure energy.
long pulseCount = 0;

//power and energy
float elapsedWh = 0.000;

//Serial request character
int c = 0;

void setup()
{
    Serial.begin(115200); // Configure serial baud rate

    //Configure input pin and assign to interrupt
    pinMode(2,INPUT_PULLUP); // Set pin to be used and confire pullup resistor
    attachInterrupt(0, onPulse, FALLING); // Interrupt attached to IRQ 0 = pin2
}

void loop() // Main loop
{
if (Serial.available()){ // Check for serial request
   int c = Serial.read();
   if (c=='?'){  // Send available data
    Serial.print(elapsedWh,3);
   }
   if (c=='r'){  // Reset counter
    pulseCount=0;
   }
}
      

else { //Find wh elapsed
elapsedWh = (pulseCount*1.25); //convert pulses to wh
interrupts(); //Enable interrupt to count pulses
delay(10); 
noInterrupts(); //Disable interrupts to reset counter if called
}
}


// The interrupt routine
void onPulse()
{
    //pulseCounter
    pulseCount++;
}
