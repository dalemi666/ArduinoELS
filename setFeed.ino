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
void setFeed()
{
  // Scrive sul LCD
  strcpy(txtA, msgSetFeed1);
  strcpy(txtB, msgFeed);
  strcpy(txtC, msgNull);
  strcpy(txtD, msgMm);
  lcdForceWrite = 1;
  lcdWrite();

  ////////////////////////////////////////////////////////////
  /// LOOP FEED                                           ////
  ////////////////////////////////////////////////////////////
  do
  {
    menu();
    // Tasto 3
    if(menuCheck == 2)
    {
      passo = passo - 0.01;
      if(passo<0.01){passo=0.01;}
      menuCheck = 0;
    }
    // Tasto 4
    if(menuCheck == 3)
    {
      passo = passo + 0.01;
      menuCheck = 0;
    }
    
    // Scrive sul LCD
    dtostrf(passo, 5, 3, txtC);
    lcdWrite();
  }
  while(menuCheck != 1);
}
  

