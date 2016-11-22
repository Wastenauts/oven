#define THERMO_PIN A1		//input pin for thermocouple after amplification
#define THERMO_DELAY 300	//delay for analogRead of thermocouple
#define THERMO_RANGE 5.0	//voltage range of amplified thermocouple reading = 0V to 5V
#define ADC_RES	1023		//adc resolution
#define THERMO_OFFSET -0.02	//-20mV offset on thermocouple reading
#define T_V_RATIO 81.3  // degrees per volt; (41uV/degree)^-1 / 300 amplifier gain

#define POT_PIN A0 //input pin for setpoint from potentiometer

#define RELAY1 9
#define RELAY2 10
#define OFF 1 //relays are passive conducting, only when a signal is applied do they turn off.
#define ON 0

float temp = 0;
int setT = 0;  //to be set during use via user interface (i.e. potentiometer)

void setup() {
  Serial.begin(9600);
  //Serial.println("Ready: ");

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY1, OFF);
  digitalWrite(RELAY2, OFF);
}

void loop() {
 	setT = 60 + (255-60) * (float)analogRead(POT_PIN) / 1023;		//for control range from 60 to 255.
	temp = getTemp();
  

  //switch on or off relay to control oven element
  if(temp > setT) {2']45]['/  digitalWrite(RELAY1, OFF);
    digitalWrite(RELAY2, OFF);
    Serial.println("\nRelays OFF\n");
  }
  else {
    digitalWrite(RELAY1, ON);
    digitalWrite(RELAY2, ON);
    Serial.println("\nRelays ON\n");
  }
}

float getTemp() {
  // read the value from the sensor:
  
  int thermoVal = analogRead(THERMO_PIN);
  delay(THERMO_DELAY);  //give time for the analog read

  
  float voltage = ( (float)thermoVal * THERMO_RANGE / ADC_RES ) + 0.02; //voltage across thermocouple
  float delta_temp = voltage * T_V_RATIO;                               //temperature difference across thermocouple

  Serial.print("thermo_V = ");    Serial.print(voltage);
  Serial.print("\t\tdelta T = "); Serial.print(delta_temp);
  Serial.print("\tT = ");         Serial.print(23 + delta_temp);
  Serial.print("\tSet =");        Serial.println(setT);
  return 23.0 + delta_temp; //add cold junction value, to be read from IC sensor.
} 

