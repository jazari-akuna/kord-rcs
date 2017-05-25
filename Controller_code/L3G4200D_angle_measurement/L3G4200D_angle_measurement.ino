#include <Wire.h>
#include <L3G4200D.h>

long int x, y, z, px, py, pz, tempo, t1, t, Tsampling, xini, yini, zini, i, value90;
float Anglex, Angley, Anglez;
L3G4200D gyro;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  gyro.enableDefault();
}

//void loop(int *(position)[4]) {
void loop() {
  gyro.read();
//  int position[4];
  //Measurment of data + Settings
  x = gyro.g.x;
  y = gyro.g.y;
  //z = gyro.g.z;

  value90 = 2800;
  
  // t = millis();

  //Initialisation of data + transformation of speed into position
    if (tempo != 1)
    {
      x = 0;
      y = 0;
      px = 0;
      py = 0;
    }

    xini = x * 0.01;
    yini = y * 0.01;
    
  //if values are saved
    x = 0.01 * x + px;
    y = 0.01 * y + py;

  //if not saved
//  x = x * 0.01;
//  y = y * 0.01;
  //  z = z * 0.01;

  //Transformation of values into angles
   Anglex = 90 * x ;
   Anglex = Anglex / 5000;
   Angley = 90 * y ;
   Angley = Angley / 5000;
  // Anglez = 90 * z / value90;

  //Print values
  //  Serial.print("G ");

    Serial.print("X: ");
  //Serial.print((int)gyro.g.x);
    Serial.print("  ");
    Serial.print(x);
    Serial.print(" ");
   Serial.print(Anglex);

   Serial.print(" Y: ");
  //Serial.print((int)gyro.g.y);
    Serial.print("  ");
    Serial.print(y);
    Serial.print(" ");
   Serial.print(Angley);

//    Serial.print(" Z: ");
//    Serial.println((int)gyro.g.z);
//    Serial.print("  ");
//    Serial.print(z);
//    Serial.print(" ");
//    Serial.print(Anglez);

  Serial.println(" ");

  //Save for next loop
    px = x;
    py = y;
    tempo = 1;
  

  delay(10);

}
