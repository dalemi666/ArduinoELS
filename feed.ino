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
void feed()
{
  // Scrive sul LCD
  strcpy(txtA, msgFeed1);
  strcpy(txtB, msgFeed);
  dtostrf(passo, 5, 3, txtC);
  strcpy(txtD, msgMm);
  lcdForceWrite = 1;
  lcdWrite();

  ////////////////////////////////////////////////////////////
  /// Sincronizzo l'encoder servo con quello del mandrino ////
  ////////////////////////////////////////////////////////////
  servoEnc.write(latheEnc.read()/rapporto * screwDir);
  
  ////////////////////////////////////////////////////////////
  /// LOOP FEED                                           ////
  ////////////////////////////////////////////////////////////
  do
  {
    menu();
    // screwDir decide se invertire o meno il segno per viti destre o sinistre
    pidSP  = (latheEnc.read()/rapporto) * screwDir;
    pidVal = servoEnc.read();
    pid();
  }
  while(menuCheck != 1);
  // Spengo il motore 
  digitalWrite(10, 0); 
  analogWrite (11, 0);
}
