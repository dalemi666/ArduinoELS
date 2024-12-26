/* E. D'Alessandro - GPL3 licence - @2022 */
////////////////////////////////////////////////////////////
/// P I D                                               ////
////////////////////////////////////////////////////////////
void pid()
{
  now = micros();
  timeChange = now - lastTime;
  error = pidSP - pidVal;
  //errSum += (error * timeChange);
  dErr = (error - lastErr) / timeChange;
  output = kp * error + kd * dErr;           // Ho tolto la parte >Integrale che non uso : ki * errSum + kd * dErr;
  if(output > 255){output = 255;}
  if(output < -255){output = -255;}
  if(output >= 0){DIR = 1;}else{DIR = 0;}

  // Dual PWM mode. La versione base usa un pin PWM ed un pin DIR, questa versione usa due uscite PWM che girano il motore
  // vero destra o verso sinistra
  if(DIR == 1) {
    analogWrite (10, abs(output));
    analogWrite (11, 0);
  } else {
    analogWrite (10, 0);
    analogWrite (11, abs(output));
  }
  // digitalWrite(10, DIR);
  // analogWrite (11, abs(output));
  
  lastErr = error;
  lastTime = now;
  
  // Comunications
  serialComm();
}
