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
void menu()
{
  button = lcd.readButtons();
  switch (button) 
  {
    // Tasto 1
    case 14:
      mode--;
      if(mode < 0){mode = 0;}
      menuCheck = 1;
      break;
      
    // Tasto 2
    case 13:
      mode++;
      if(mode > 6){mode = 6;}
      menuCheck = 1;
      break;

    // Tasto 3
    case 11:
      menuCheck = 2;
      break;

    // Tasto 4
    case 7:
      menuCheck = 3;
      break;
      
    // Tasto 1+2 ' Avvia la pagina di configurazione del sistema.
    case 77:
      mode = 99;
      menuCheck = 1;
      break;
  }
}
