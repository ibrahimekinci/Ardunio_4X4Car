// motor sürücüsüne bağlanacak INPUT ve ENABLE pinleri
//ileri 8-13 aynı zamanda enable
//geri 9-12
//sağ 9-13
//sol 8-12
const int backEnable = 8;
const int rightBack = 9;
const int rightSpeed = 10;
const int frontEnable = 13;
const int leftBack = 12;
const int leftSpeed = 11;
const int lights = 3;
const int park = 4;
const int horn = 5;
byte speed = 0, speedNext = 0, speedPrev = 255, speedNextSlow = 0, speedPrevSlow = 255;
//int sensorDegeri;
//const int dortlu = 6;

void speedReset()
{
  speedNext = 0;
  speedNextSlow = 0;
  speedPrev = 255;
  speedPrevSlow = 255;

}
void stop()
{
  digitalWrite(backEnable, LOW);
  digitalWrite(rightBack, LOW);
  digitalWrite(frontEnable, LOW);
  digitalWrite(leftBack, LOW);
  digitalWrite(leftSpeed, LOW);
  digitalWrite(rightSpeed, LOW);
}
void reset()
{
  //backEnable,rightBack,frontEnable,leftBack,leftSpeed,rightSpeed,lights,park,horn,speed,slowSpeed
  stop();
  digitalWrite(lights, LOW);
  digitalWrite(park, LOW);
  digitalWrite(horn, LOW);
  speedReset();
}
void setSpeed(int newSpeed)
{
  speed = newSpeed;
  switch (speed)
  {
    case 1:
      speedNext = 25;
      speedPrev = 230;
      speedNextSlow = speedNext;
      speedPrevSlow = speedPrev;
      break;
    case 2:
      speedNext = 50;
      speedPrev = 205;
      speedNextSlow = 25;
      speedPrevSlow = 230;
      break;
    case 3:
      speedNext = 75;
      speedPrev = 180;
      speedNextSlow = 50;
      speedPrevSlow = 205;
      break;
    case 4:
      speedNext = 100;
      speedPrev = 155;
      speedNextSlow = 50;
      speedPrevSlow = 205;
      break;
    case 5:
      speedNext = 125;
      speedPrev = 130;
      speedNextSlow = 75;
      speedPrevSlow = 180;
      break;
    case 6:
      speedNext = 150;
      speedPrev = 105;
      speedNext = 75;
      speedPrev = 180;
      break;
    case 7:
      speedNext = 175;
      speedPrev = 80;
      speedNextSlow = 100;
      speedPrevSlow = 155;
      break;
    case 8:
      speedNext = 200;
      speedNextSlow = 125;
      speedPrev = 55;
      speedPrevSlow = 130;
    case 9:
      speedNext = 225;
      speedNextSlow = 150;
      speedPrev = 55;
      speedPrevSlow = 130;
      break;
    case 10:
      digitalWrite(speedNext, HIGH);
      speedNextSlow = 175;
      speedPrev = 55;
      speedPrevSlow = 130;
      break;
    default:
      speedReset();
      break;
  }
}
void ileri() {
  analogWrite(rightSpeed, speedNext);
  analogWrite(leftSpeed, speedNext);
  digitalWrite(backEnable, HIGH);
  digitalWrite(rightBack, LOW);
  digitalWrite(frontEnable, HIGH);
  digitalWrite(leftBack, LOW);
}

void sagaDon() {
  analogWrite(rightSpeed, speedNext);
  analogWrite(leftSpeed, speedNext);
  digitalWrite(backEnable, HIGH);
  digitalWrite(rightBack, LOW);
  digitalWrite(frontEnable, LOW);
  digitalWrite(leftBack, LOW);
}
void solaDon() {
  analogWrite(rightSpeed, speedNext);
  analogWrite(leftSpeed, speedNext);
  digitalWrite(backEnable, LOW);
  digitalWrite(rightBack, LOW);
  digitalWrite(frontEnable, HIGH);
  digitalWrite(leftBack, LOW);
}

void ilerisag() {
  analogWrite(rightSpeed, speedNext);
  analogWrite(leftSpeed, speedNextSlow);
  digitalWrite(backEnable, HIGH);
  digitalWrite(rightBack, LOW);
  digitalWrite(frontEnable, HIGH);
  digitalWrite(leftBack, LOW);
}
void ilerisol () {
  analogWrite(rightSpeed, speedNextSlow);
  analogWrite(leftSpeed, speedNext);
  digitalWrite(backEnable, HIGH);
  digitalWrite(rightBack, LOW);
  digitalWrite(frontEnable, HIGH);
  digitalWrite(leftBack, LOW);
}

void geri() {
  analogWrite(rightSpeed, speedPrev);
  analogWrite(leftSpeed, speedPrev);
  digitalWrite(backEnable, HIGH);
  digitalWrite(rightBack, HIGH);
  digitalWrite(frontEnable, HIGH);
  digitalWrite(leftBack, HIGH);
}

void gerisag() {
  analogWrite(rightSpeed, speedPrevSlow);
  analogWrite(leftSpeed, speedPrev);
  digitalWrite(backEnable, HIGH);
  digitalWrite(rightBack, HIGH);
  digitalWrite(frontEnable, HIGH);
  digitalWrite(leftBack, HIGH);
}

void gerisol() {
  analogWrite(rightSpeed, speedPrev);
  analogWrite(leftSpeed, speedPrevSlow);
  digitalWrite(backEnable, HIGH);
  digitalWrite(rightBack, HIGH);
  digitalWrite(frontEnable, HIGH);
  digitalWrite(leftBack, HIGH);
}

void setup() {
  // Bluetooth için port açılıyor
  Serial.begin(9600);
  // motorları kontrol eden pinler ve lights park horn pinleri çıkış olarak ayarlanıyor
  pinMode(backEnable, OUTPUT);
  pinMode(rightBack, OUTPUT);
  pinMode(frontEnable, OUTPUT);
  pinMode(leftBack, OUTPUT);
  pinMode(rightSpeed, OUTPUT);
  pinMode(leftSpeed, OUTPUT);
  pinMode(lights, OUTPUT);
  pinMode(park, OUTPUT);
  pinMode(horn, OUTPUT);
  //pinMode(A0, INPUT);
}
void loop() {

  if (Serial.available() > 0) {   //Bluetooth’tan veri bekliyoruz.
    char tus = (char)Serial.read();
    if ( tus == 'F' )
      ileri();
    else if ( tus == 'B' )
      geri();
    else if ( tus == 'L' )
      solaDon();
    else if ( tus == 'R' )
      //{ if(sensorDegeri<200)
      sagaDon();
    else if ( tus == 'G' )
      ilerisol();
    else if ( tus == 'I' )
      ilerisag();
    else if ( tus == 'H' )
      gerisol();
    else if ( tus == 'J' )
      gerisag();
    else if (tus == 'W')
      digitalWrite(lights, HIGH);

    else if (tus == 'w')
      digitalWrite(lights, LOW);

    else if (tus == 'V')
      digitalWrite(horn, HIGH);

    else if (tus == 'v')
      digitalWrite(horn, LOW);

    else if (tus == 'U')
      digitalWrite(park, HIGH);

    else if (tus == 'u')
      digitalWrite(park, LOW);

    else if (tus == '0') {
      stop();
      setSpeed(0);
    }
    else if ( tus == 'D' )
      reset();
    else if (tus == '1') {
      setSpeed(1);
    }
    else if (tus == '2') {
      setSpeed(2);
    }
    else if (tus == '3') {
      setSpeed(3);
    }
    else if (tus == '4') {
      setSpeed(4);
    }
    else if (tus == '5') {
      setSpeed(5);
    }
    else if (tus == '6') {
      setSpeed(6);
    }
    else if (tus == '7') {
      setSpeed(7);
    }
    else if (tus == '8') {
      setSpeed(8);
    }
    else if (tus == '9') {
      setSpeed(9);
    }
    else if (tus == 'q') {
      setSpeed(10);
    }
    else
    {
      stop();
    }
    //sensorDegeri = analogRead(A5);
    delay(1);
  }
}






