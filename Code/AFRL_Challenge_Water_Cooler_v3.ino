/*
AFRL Challenge Program v 3
By: Jackson Montgomery - Joshua Jablonowski
3-30-15

Peltier controller, temp status, Bluetooth connection.
*/

int pelt1 = 4; //Set of 2 peltiers
int pelt2 = 5; //Set of 2 peltiers
int pelt3 = 6; //Set of 4 peltiers
int fans= 3;
int thermistor1= 2;
int peltpwr=179;  // 0-255, 179 is approx 70% power, 255 is max power



void setup(){
 Serial.begin(9600);
 pinMode(pelt1,OUTPUT);
 pinMode(pelt2,OUTPUT);
 pinMode(pelt3,OUTPUT);
 pinMode(fans, OUTPUT);
 pinMode(thermistor1,INPUT);


 
 }
 
 int Thermistor(int RawADC) {  //Function to perform the fancy math of the Steinhart-Hart equation
 double Temp;
 int final;
 Temp = log(((10240000/RawADC) - 10000));
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;              // Convert Kelvin to Celsius
 Temp = (Temp * 9.0)/ 5.0 + 32.0; // Celsius to Fahrenheit - comment out this line if you need Celsius
 Temp = Temp-3; //calibration adjustment
 Temp = round(Temp);
 final=(int)Temp;
 return final;
}


void loop(){

  int therm1;
  int therm2;
  
  digitalWrite(fans, HIGH);
    
  while(1){
   
    therm1 = analogRead(thermistor1);
    therm2= Thermistor(therm1);                        //temp of thermistor in F
  

if (therm2>=70){        
            Serial.print("8 on :    Temp:");  //eight(all) peltiers on
            analogWrite(pelt1,peltpwr);
            analogWrite(pelt2,peltpwr);
            analogWrite(pelt3,peltpwr);
          }
if ((therm2>=60)&&(therm2<70)){
            Serial.print("6 on :    Temp:");    // six peltiers on
            analogWrite(pelt1,0);
            analogWrite(pelt2,peltpwr);
            analogWrite(pelt3,peltpwr);
}
if ((therm2>=50)&&(therm2<60)){          // four peltiers on
            Serial.print("4 on :    Temp:");
            analogWrite(pelt1,peltpwr);
            analogWrite(pelt2,peltpwr);
            analogWrite(pelt3,0);
          }
if ((therm2>=35)&&(therm2<50)){         
Serial.print("2 on :    Temp:");  // two peltiers on
            analogWrite(pelt1,peltpwr);
            analogWrite(pelt2,0);
            analogWrite(pelt3,0);
          }
if(therm2<35){                                  
            Serial.print("0 on :    Temp:");  //if almost freezing turn off
            analogWrite(pelt1,0);
            analogWrite(pelt2,0);
            analogWrite(pelt3,0);
}
 Serial.println(therm2);

 delay(1000);
}
}// end of void loop




  


