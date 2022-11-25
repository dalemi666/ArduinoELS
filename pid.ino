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
  digitalWrite(10, DIR);
  analogWrite (11, abs(output));
  lastErr = error;
  lastTime = now;
  
  // Comunications
  serialComm();
}
