/* E. D'Alessandro - GPL3 licence - @2022 */
////////////////////////////////////////////////////////////
/// TASTI                                               ////
////////////////////////////////////////////////////////////
//   _______________________
//  |                       |
//  |        LCD 16x2       |
//  |_______________________|
//    X      X      X      X
//   14     13      11     7
////////////////////////////////////////////////////////////

// ENCODER
#include <Encoder.h>
Encoder latheEnc(2, 4);
Encoder servoEnc(3, 5);

// LCD
#include <LCD16x2.h>
#include <Wire.h>
LCD16x2 lcd;

// USER PARAMETERS
double latheEncRes    = 2048;     // My lathe encoder resolution is 512 ppr --> Library read 4x --> 2048 --> lathe spindle/encoder ratio = 1/1 --> 2048 STEP/REV of lathe spindle
double servoEncRes    = 4300.8;   // My servo encoder resolution is 256 ppr --> Library read 4x --> 1024 --> motor encoder/lead screw ratio = 4.2/1 --> 4300.8 STEP/REV of lead screw
double distOneRev     = 1.04;     // Movement of lathe tool for 1 revolution of lead screw

// working vars
double passo          = 0.1;
double rapporto       = 0;
double TPI            = 0;

// setFeed, feed, setThread, thread
int    mode           = 0;
int    button         = 0;
double lenght         = 15;
double pidSP          = 0;
double pidVal         = 0;
int    menuCheck      = 0;
double moveDist       = 0;
double endThread      = 0;
int    screwDir       = 1;
double alternateCut   = servoEncRes * (0.1 / distOneRev);  // E' lo spostamneto Dx alternato in aventi ed in dietro dell'utensile durante la filettatura. 4300.8 corripsonde ad un giro della vite madre, quindi 1.04 mm

// serialComm
long   currentMicros  = 0;
int    j              = 0;
byte   b[4];
long   currentMicros2 = 0;
long   loopTime       = 0;
double turns          = 0;

// PID
double lastTime       = 0;
double now            = 0;
double timeChange     = 0;
double output         = 0;
int    DIR            = 0;
double error          = 0;
double errSum         = 0;
double dErr           = 0;
double lastErr        = 0;
double kp             = 10;
double ki             = 0;
double kd             = 10000;

// LCD
char txtA[17];
char txtB[17];
char txtC[17];
char txtD[17];
char oldTxtA[17];
char oldTxtB[17];
char oldTxtC[17];   
char oldTxtD[17];
int  i                = 0;
int  lcdForceWrite    = 0;

// Menu text EN
char msgBoot1[17]            = "<E.L.S. Control>";
char msgBoot2[17]            = "< Version 3.0 >";
char msgBoot3[17]            = "<  emi.dale@  > ";
char msgBoot4[17]            = "<  gmail.com  >";
char msgNull[17]             = "";
char msgFeed[17]             = "Feed = ";
char msgMm[17]               = " mm";
char msgSetFeed1[17]         = "Set Feed   (OFF)";
char msgFeed1[17]            = "Turning    ( ON)";
char msgSetThread1[17]       = "Set Thread (OFF)";
char msgSetThread2[17]       = "Dist = ";
char msgThread1[17]          = "Threading  ( ON)";
char msgManualMove1[17]      = "Manual Move( ON)";
char msgManualMove2[17]      = " < -  Push  + >";
char msgScrewDirection1[17]  = "screwDir   (OFF)";
char msgScrewDirection2[17]  = "Dir  = ";
char msgScrewType1[17]       = "Set Feed as TPI ";
char msgScrewType2[17]       = "TPI  = ";
char msgScrewType3[17]       = "TPI";

/////////////////////////////////////////////////////////////////
// S E T U P
/////////////////////////////////////////////////////////////////
void setup() 
{
  // delay avvio CPU
  delay(2000);

  Serial.begin(115200);
  Wire.begin();
  lcd.lcdSetBlacklight(255);
  lcd.lcdClear();
  
  // Messaggio di benvenuto
  strcpy(txtA, msgBoot1);
  strcpy(txtB, msgBoot2);
  strcpy(txtC, msgNull);
  strcpy(txtD, msgNull);
  lcdForceWrite = 1;
  lcdWrite();
  delay(2000);
  strcpy(txtA, msgBoot3);
  strcpy(txtB, msgBoot4);
  strcpy(txtC, msgNull);
  strcpy(txtD, msgNull);
  lcdForceWrite = 1;
  lcdWrite();
  delay(2000);
  
  pinMode(2, INPUT);       // Encoder pins PullUp OFF
  pinMode(3, INPUT);       // ...
  pinMode(4, INPUT);       // ..
  pinMode(5, INPUT);       // .
  
  pinMode(8,OUTPUT);       // LOOP speed measurements
  pinMode(9, OUTPUT);      // Segnala asincronia
  pinMode(10,OUTPUT);      // DIR
  pinMode(11,OUTPUT);      // PWM

  digitalWrite(8, LOW);    // LOOP speed measurements
  digitalWrite(9, LOW);    // Segnala asincronia
  analogWrite(10, 0);      // Motore fermo (SX)
  analogWrite(11, 0);      // Motore fermo (DX)

  // FREQUENZA PWM on pins 3,11
  TCCR2B = TCCR2B & 0b11111000 | 0x01;    // PWM on port 3,11 Frequecy = 31250 Hz

  // Frequenza PWM on pins 10 
  TCCR1A = (1 << WGM11);                  // Enable Fast PWM mode, leave duty cycle for analogWrite()
  TCCR1B = (TCCR1B & 0b11111000) | 0x01;  // Set prescaler to 1
  ICR1 = 500;                             // Set TOP value for ~32 kHz frequency
}

/////////////////////////////////////////////////////////////////
// M A I N    L O O P
/////////////////////////////////////////////////////////////////
void loop() 
{
  //////////////////////////////////////////////////////////////////////////////////////////////////
  // menuCheck:
  // i valori sono : 0 = nessun tasto, 1 = tasto menu (uno dei due), 2 = valore - , 3 = valore +
  // Reimposto ogni volta il check del menu a zero, ovvero nessun tasto premuto.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  menuCheck = 0;
  switch (mode)
  {
    case 0:
      setFeed();
      break;
    case 1:
      feed();
      break;
    case 2:
      set_thread();
      break;
    case 3:
      manualMove();
      break;
    case 4:
      thread();
      break;
    case 5:
      screwDirection();
      break;
    case 6:
      screwType();
      break;
    case 99:
      systemConfig();
      break;
  }
  ////////////////////////////////////////////////////////////
  // Update the ratio every loop
  ////////////////////////////////////////////////////////////
  // When the lathe spindle rotate for exactly 1 turn (2048 steps) 
  // and the lead screw rotate exactly 1 turn (4300.8 steps) the 
  // movement of the lathe tool is in my case exactly 1.04 mm, 
  // measured using a digital caliper..
  rapporto = (latheEncRes / servoEncRes) * distOneRev / passo;
}
