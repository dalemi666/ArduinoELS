////////////////////////////////////////////////////////////
/// moveTool                                            ////
////////////////////////////////////////////////////////////
void moveTool()
{
  // imposto il SP al valore attuale di servoEnc
  pidSP = servoEnc.read();
  moveDist = servoEnc.read() + moveDist * servoEncRes / 1.04;

  if(moveDist > servoEnc.read())
  {
    do
    {
      menu();
      pidSP = pidSP + 8;
      if(pidSP > moveDist){pidSP = moveDist;}
      pidVal = servoEnc.read();
      pid();
    }
    while(pidSP < moveDist && menuCheck != 1);
  }
  else
  {
    do
    {
      menu();
      pidSP = pidSP - 8;
      if(pidSP < moveDist){pidSP = moveDist;}
      pidVal = servoEnc.read();
      pid();
    }
    while(pidSP > moveDist && menuCheck != 1);
  }

  // Mi assicuro che la posizione sia raggiunta almeno come primo passaggio
  do
  {
    menu();
    pidSP  = moveDist;
    pidVal = servoEnc.read();
    pid();
  }
  while(abs(servoEnc.read() - moveDist) > 1 && menuCheck != 1);
  
  // Mi assicuro che la posizione sia raggiunta eseguendo il pid sulla posizione finale per 0.2 secondi
  currentMicros = micros();
  do
  {
    pidSP  = moveDist;
    pidVal = servoEnc.read();
    pid();
  }
  while(micros() <= currentMicros + 200000 && menuCheck != 1);
  
  // Azzero l'uscita in tensione.
  digitalWrite(10, 0); 
  analogWrite (11, 0);
}
