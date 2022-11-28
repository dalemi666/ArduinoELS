/* E. D'Alessandro - GPL3 licence - @2022 */
////////////////////////////////////////////////////////////
/// Comunications                                       ////
////////////////////////////////////////////////////////////
void serialComm()
{
  // Loop speed measurements
  if(digitalRead(8) == 1){digitalWrite(8, 0);}else{digitalWrite(8, 1);}
  
  // segnala mancanza di sicronia pari al 2% !!
  if(abs(error) >= 40.96){digitalWrite(9, HIGH);}else{digitalWrite(9, LOW);}
  
  // Dati seriali
  //binData();
  //asciiData();
  //contaGiri();
}

////////////////////////////////////////////////////////////
/// invio dati ASCII                                    ////
////////////////////////////////////////////////////////////
void asciiData()
{
    Serial.print("< ");
    Serial.print(latheEnc.read());
    Serial.print(";");
    Serial.print(servoEnc.read());
    Serial.println(" >");
}

////////////////////////////////////////////////////////////
/// invio dati BINARY                                   ////
////////////////////////////////////////////////////////////
void binData()
{
  // loop time
  loopTime = micros() - currentMicros2;
  currentMicros2 = micros();
  // Comunicazione seriale
  if(loopTime > 0 && loopTime < 100000)
  {
    Serial.write("<");
    IntegerToBytes((long)(latheEnc.read()), b);
    for (int j=0; j<4; ++j){Serial.write((int)b[j]);};
    IntegerToBytes((long)(servoEnc.read()), b);
    for (int j=0; j<4; ++j){Serial.write((int)b[j]);};
    IntegerToBytes((long)(output), b);
    for (int j=0; j<4; ++j){Serial.write((int)b[j]);};
    IntegerToBytes(loopTime, b);
    for (int j=0; j<4; ++j){Serial.write((int)b[j]);};
    Serial.write(">");
  }
}

////////////////////////////////////////////////////////////
/// Conversione LONG --> 4 byte                         ////
////////////////////////////////////////////////////////////
void IntegerToBytes(long val, byte b[4]) 
{
  b[0] = (byte )((val >> 24) & 0xff);
  b[1] = (byte )((val >> 16) & 0xff);
  b[2] = (byte )((val >> 8) & 0xff);
  b[3] = (byte )(val & 0xff);
}

////////////////////////////////////////////////////////////
/// Conteggio giri mandrino                             ////
////////////////////////////////////////////////////////////
void contaGiri()
{
  Serial.println((long)(latheEnc.read()/latheEncRes));
}
