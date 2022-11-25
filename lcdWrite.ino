/* E. D'Alessandro - MIT licence - @2022 */
////////////////////////////////////////////////////////////
/// Testo L C D                                              ////
////////////////////////////////////////////////////////////
//   __________________________________________
//  |[1..............txtA...................16]|
//  |[1...txtB...7][8..txtC..12][13 ..txtD..15]|
//  |__________________________________________|
//    X      X      X      X
//   14     13      11     7
////////////////////////////////////////////////////////////
void lcdWrite()
{
  //lcd.lcdClear();
  if(strcmp(txtA, oldTxtA) != 0 || lcdForceWrite == 1)
  {
    lcd.lcdGoToXY(1,1);
    lcd.lcdWrite(txtA);
    strcpy(oldTxtA, txtA); // strcpy(destination, source);
  }
  if(strcmp(txtB, oldTxtB) != 0 || lcdForceWrite == 1)
  {
    lcd.lcdGoToXY(1,2);
    lcd.lcdWrite(txtB);
    strcpy(oldTxtB, txtB);
  }
  if(strcmp(txtC, oldTxtC) != 0 || lcdForceWrite == 1)
  {
    lcd.lcdGoToXY(8,2);
    lcd.lcdWrite(txtC);
    strcpy(oldTxtC, txtC);
  }
  if(strcmp(txtD, oldTxtD) != 0 || lcdForceWrite == 1)
  {
    lcd.lcdGoToXY(13,2);
    lcd.lcdWrite(txtD);
    strcpy(oldTxtD, txtD);
  }
  // cencello il flag di scrittura forzata
  lcdForceWrite = 0;
}
