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
void screwType()
{
  // Scrive sul LCD
  strcpy(txtA, msgScrewType1);
  strcpy(txtB, msgScrewType2);
  strcpy(txtC, msgNull);
  strcpy(txtD, msgScrewType3);
  lcdForceWrite = 1;
  lcdWrite();

  // Imposta il TPI in base al Feed
  TPI = int(25.4 / passo);

  ////////////////////////////////////////////////////////////
  /// LOOP FEED                                           ////
  ////////////////////////////////////////////////////////////
  do
  {
    menu();
    // Tasto 3
    if(menuCheck == 2)
    {
      TPI = TPI - 1;
      if(TPI<1){TPI=1;}
      menuCheck = 0;
      passo = 25.4 / TPI;
    }
    // Tasto 4
    if(menuCheck == 3)
    {
      TPI = TPI + 1;
      menuCheck = 0;
      passo = 25.4 / TPI;
    }
    
    // Scrive sul LCD
    dtostrf(TPI, 3, 0, txtC);
    lcdWrite();
  }
  while(menuCheck != 1);
}
  

