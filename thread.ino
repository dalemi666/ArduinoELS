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
void thread()
{
    // Scrive sul LCD
  strcpy(txtA, msgThread1);
  strcpy(txtB, msgFeed);
  dtostrf(passo, 5, 3, txtC);
  strcpy(txtD, msgMm);
  lcdForceWrite = 1;
  lcdWrite();

  ////////////////////////////////////////////////////////////
  /// LOOP THREAD                                         ////
  ////////////////////////////////////////////////////////////
  do
  {
    // GESTIONE MENU
    menu();
    // Tasto 3
    if(menuCheck == 2)
    {
      ////////////////////////////////////////////////////////////
      /// LOOP THREAD                                         ////
      ////////////////////////////////////////////////////////////
      // (A) Attesa sincronia: 
      // Divido la posizione attuale per 4096 step (ovvero latheEncRes) e prendo la parte intera, gli sommmo 1 ( 1 giro completo) e lo moltiplico per 4096, ottengo una posizione futura 
      // che è esattamente un multiplo di 4096
      // IMPORTANTE !! l'encoder per filettature destre normali ruota verso valori positivi !!!
      // Questo è l'unico loop dal quale non si può uscire !! perchè non leggo menu(); la frequenza di polling e 33 kHz !
      turns = ((long)(latheEnc.read() / latheEncRes) + 1) * latheEncRes;
      do
      {
        //menu();
        serialComm();
      }
      while(latheEnc.read() < turns);

      // (B) Tornitura:
      // Per prima cosa imposto il valore dell'encoder del servo come se fosse in sincronia
      // screwDir cambia il segno
      servoEnc.write(latheEnc.read()/rapporto * screwDir);  
      endThread = servoEnc.read() + (lenght * servoEncRes / distOneRev) * screwDir;
      // alternateDir cambia la direzione dello spostamento dell'utensile ad ogni passata di +- 0.2 mm
      alternateCut = alternateCut * -1;
      if(screwDir == 1)
      {
        do
        {
          menu();
          pidSP  = (latheEnc.read() / rapporto * screwDir) + alternateCut;
          pidVal = servoEnc.read();
          pid();
        }
        while(servoEnc.read() < endThread && menuCheck != 1);
      }
      else
      {
        do
        {
          menu();
          pidSP  = (latheEnc.read() / rapporto * screwDir) + alternateCut;
          pidVal = servoEnc.read();
          pid();
        }
        while(servoEnc.read() > endThread && menuCheck != 1);
      }
      digitalWrite(10, 0); 
      analogWrite (11, 0);

      // Mi assicuro che la posizione sia raggiunta eseguendo il pid sulla posizione finale per 0.2 secondi
      currentMicros = micros();
      do
      {
        pidSP  = endThread;
        pidVal = servoEnc.read();
        pid();
      }
      while(micros() <= currentMicros + 200000 && menuCheck != 1);
      // Azzero l'uscita in tensione.
      digitalWrite(10, 0); 
      analogWrite (11, 0);

      // cancello il flag del check
      menuCheck = 0;
    }
      
    // Tasto 4
    if(menuCheck == 3)
    {
      // (C) Posiziono l'utensile 4 mm oltre la partenza
      // screwDir decide se invertire o meno il segno per viti destre o sinistre
      moveDist = -(lenght + 4) * screwDir;
      moveTool();
      
      // (D) Elimino gioco muovendo verso sinistra di 4 mm
      // screwDir decide se invertire o meno il segno per viti destre o sinistre
      moveDist = 4 * screwDir;
      moveTool();
      
      // cancello il flag del check
      menuCheck = 0;
    }
  }
  while(menuCheck != 1);
}
