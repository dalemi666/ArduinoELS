/* E. D'Alessandro - MIT licence - @2022 */
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
void manualMove()
{
  // Scrive sul LCD
  strcpy(txtA, msgManualMove1);
  strcpy(txtB, msgManualMove2);
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
      moveDist = 1;
      moveTool();
      menuCheck = 0;
    }
    // Tasto 4
    if(menuCheck == 3)
    {
      moveDist = -1;
      moveTool();
      menuCheck = 0;
    }
  }
  while(menuCheck != 1);
}
