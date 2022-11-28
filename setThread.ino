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
void set_thread()
{
  // Scrive sul LCD
  strcpy(txtA, msgSetThread1);
  strcpy(txtB, msgSetThread2);
  strcpy(txtC, msgNull);
  strcpy(txtD, msgMm);
  lcdForceWrite = 1;
  lcdWrite();

  ////////////////////////////////////////////////////////////
  /// LOOP FEED                                           ////
  ////////////////////////////////////////////////////////////
  do
  {
    // GESTIONE MENU
    menu();
    // Tasto 3
    if(menuCheck == 2)
    {
      lenght = lenght - 0.5;
      if(lenght<1){lenght=1;}
      menuCheck = 0;
    }
    // Tasto 4
    if(menuCheck == 3)
    {
      lenght = lenght + 0.5;
      menuCheck = 0;
    }

    // Scrive sul LCD
    dtostrf(lenght, 5, 2, txtC);
    lcdWrite();
  }
  while(menuCheck != 1);
}
