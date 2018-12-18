/*Assign PWMs, analog, and digital inputs to pins */

volatile int pulse1 = 3; //PWM input at board pin 5, only PWM with interupt on 328 board
int volt1 = A0; //Analog input at board pin 23, referenced to board pin 21
int state1 = 12; // Digital input at board pin 18

/*Assign data variables*/

const int pulses_per_gallon = 450;
int data_Array [] = {0,0,0,0,0};
String buffer = ",";


/* setup */

void setup()
{
  Serial.begin(9600);

  pinMode(pulse1, INPUT);
  attachInterrupt(0, count_pulse1, RISING);
  
}

void loop()
{
  interrupts();
  delay(1000);
  noInterrupts();
  data_Array[0] = pulse1*pulses_per_gallon;
  data_Array[3] = analogRead(volt1)*15;
  data_Array[4] = digitalRead(state1);
  String buffer = String(data_Array[0]) + "," + data_Array[1] + "," + data_Array[2] + "," + data_Array[3]+ "," + data_Array[4] + "\0";
  
  Serial.println(buffer);
}

void count_pulse1()
{
  pulse1++;
}
