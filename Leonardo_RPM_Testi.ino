#define Enc 7         // Interrupt pini   (Encoder )
#define hallsens1  2 // Interrupt pini (Sens1) 
#define hallsens2  3   // Interrupt pini (Sens2) 
#define Tach 1


long previousMillis1 = 0;
long currentMillis1 = 0;

float rpm_encoder = 0;
float rpm_sens1 = 0;
float rpm_sens2 = 0;
float rpm_tachometer = 0;


volatile long Tachometer;
volatile long  EncoderValue;
volatile long HallEffectValue1 = 0;
volatile long HallEffectValue2 = 0;

void updateTach()
{
    Tachometer++;

}
void updateSens1()
{
  HallEffectValue1++;
}
void updateSens2()
{
  HallEffectValue2++;
}

void updateEncoder()
{
  EncoderValue++;
}


void  Rpm_Sens1()    //RPM FUNCTİON

{
  currentMillis1 = millis();
    if (currentMillis1 - previousMillis1 == 1000)
     {
      previousMillis1 = currentMillis1;

      rpm_sens1 = HallEffectValue1 * 60 /80;       //SENSÖR1 RPM MEASUREMENT
      Serial.print(rpm_sens1);
      Serial.print(",");
      HallEffectValue1 = 0;

      rpm_sens2 = HallEffectValue2 * 60/80;        //SENSÖR2 RPM MEASUREMENT
      Serial.print(rpm_sens2);
      Serial.print(",");
      HallEffectValue2 = 0;


      rpm_encoder = EncoderValue * 60 /2000;        //ENCODER RPM MEASUREMENT 
      Serial.print(rpm_encoder);
      Serial.print(",");
      EncoderValue = 0;

      rpm_tachometer = Tachometer*60 /2000;         //TACHOMETER RPM MEASUREMENT
      Serial.print(rpm_tachometer);
      Serial.println(",");
      Tachometer = 0;

}
}


void setup() {
 
    pinMode(Enc, INPUT_PULLUP);
    pinMode(hallsens1, INPUT_PULLUP);
    pinMode(hallsens2, INPUT_PULLUP);
    pinMode(Tach,INPUT_PULLUP);
    Serial.begin(9600);
    
    attachInterrupt(digitalPinToInterrupt(Enc), updateEncoder, RISING);
    attachInterrupt(digitalPinToInterrupt(hallsens1), updateSens1, RISING);
    attachInterrupt(digitalPinToInterrupt(hallsens2), updateSens2, RISING);
    attachInterrupt(digitalPinToInterrupt(Tach), updateTach, RISING);


}

void loop() {

  Rpm_Sens1();

}
