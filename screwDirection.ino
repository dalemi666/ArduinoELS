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
void screwDirection()
{
  // Scrive sul LCD
  strcpy(txtA, msgScrewDirection1);
  strcpy(txtB, msgScrewDirection2);
  strcpy(txtC, msgNull);
  strcpy(txtD, msgNull);
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
      screwDir = 1;
      menuCheck = 0;
    }
    // Tasto 4
    if(menuCheck == 3)
    {
      screwDir = -1;
      menuCheck = 0;
    }
    
    // Scrive sul LCD
    if(screwDir == 1)
    {
      strcpy(txtC, "R       ");
      lcdWrite();
    }
    else
    {
      strcpy(txtC, "L       ");
      lcdWrite();
    }
  }
  while(menuCheck != 1);
}
