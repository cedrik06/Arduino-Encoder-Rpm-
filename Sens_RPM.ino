#define Enc 18        // Interrupt pini   (Encoder )
#define hallsens1  2  // Interrupt pini (Sens1) 
#define hallsens2  3   // Interrupt pini (Sens2)
#define TachA 19
#define TachB 20



long previousMillis1 = 0;
long currentMillis1 = 0;

float rpm_encoder = 0;
float rpm_sens1 = 0;
float rpm_sens2 = 0;



volatile long  EncoderValue;
volatile long HallEffectValue1 = 0;
volatile long HallEffectValue2 = 0;


unsigned long currenttime1;
unsigned long currenttime2;
unsigned long LastTimeA = 0;
unsigned long LastTimeB = 0;

unsigned long TD = 0;                    //Time Difference
double PD = 0;                          //Phase Difference

double periodA = 0;                     // A sinyalinin periyodu 
double periodB = 0;                     //B sinyalinin periyodu 

volatile long counterA = 0;
volatile long counterB = 0;

float rpm_tachA = 0;
float rpm_tachB = 0;
int Tach_Ref = 88;




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

void Int1()
{
 counterA ++;
 currenttime1= micros(); 
 periodA =currenttime1 - LastTimeA; 
 LastTimeA = currenttime1; 
 
}
void Int2()
{
 counterB++;
 currenttime2 = micros();
 periodB = currenttime2 - LastTimeB ;
 LastTimeB =currenttime2;
}




void  Rpm_Sens1()    // Tüm  Rpm değerlerinin okunduğu tek fonksiyon
{


  currentMillis1 = millis();
    if (currentMillis1 - previousMillis1 == 1000)
     {
      previousMillis1 = currentMillis1;
      TD = abs(currenttime1 - currenttime2);                 // iki sinyal arasındaki zaman farkını alıyor 
      PD = (TD *360.0/((periodA + periodB)/2.0))*10000000;               //zaman farkını 360 ile çarpıp daha sonra frekans ile çarpıyoruz 
      rpm_sens1 = HallEffectValue1 * 60 /80;       //SENSÖR1 RPM HESAPLAMASI YAPIP EKRANA YAZDIRIR  
      Serial.print(rpm_sens1);
      Serial.print(",");
      HallEffectValue1 = 0;

      rpm_sens2 = HallEffectValue2 * 60/80;        //SENSÖR2 RPM HESAPLAMASI YAPIP EKRANA YAZDIRIR  
      Serial.print(rpm_sens2);
      Serial.print(",");
      HallEffectValue2 = 0;


      rpm_encoder = EncoderValue * 60/2000;        //ENCODER RPM HESAPLAMASI YAPIP EKRANA YAZDIRIR  
      Serial.print(rpm_encoder);
      Serial.print(",");
      EncoderValue = 0;

      rpm_tachA = counterA*60/88;
  
      Serial.print(rpm_tachA);
      Serial.print(",");
      counterA = 0;
 
      rpm_tachB = counterB*60/88;
      Serial.print(rpm_tachB);
      Serial.print(",");
      counterB = 0; 

      Serial.print(PD);
      Serial.println(",");
      
      if (currenttime1>currenttime2){
        Serial.print(0);
      }
      else
        Serial.print(1);
      }
 
}

void setup() {
 

    Serial.begin(9600);
    
    pinMode(Enc, INPUT_PULLUP);
    pinMode(hallsens1, INPUT_PULLUP);
    pinMode(hallsens2, INPUT_PULLUP);
    pinMode(TachA, INPUT_PULLUP);
    pinMode(TachB, INPUT_PULLUP);



    attachInterrupt(digitalPinToInterrupt(Enc), updateEncoder, RISING);
    attachInterrupt(digitalPinToInterrupt(hallsens1), updateSens1, RISING);
    attachInterrupt(digitalPinToInterrupt(hallsens2), updateSens2, RISING);
    attachInterrupt(digitalPinToInterrupt(TachA), Int1, RISING);
    attachInterrupt(digitalPinToInterrupt(TachB), Int2, RISING);



}

void loop() {


  Rpm_Sens1();

}

