float sum = 0;
float voltage = 0.0;
int z1 = 1000;
int z2 = 330;
float mult = 1.0/((float)z2/((float)z1+(float)z2));
void setup()
{
    pinMode(13,OUTPUT);
    digitalWrite(13,HIGH);
    Serial.begin(9600);
}

void loop()
{
    for (int i=0;i<400;i++)
    {
      sum = sum + analogRead(A1);
     // Serial.println(mult*analogRead(A1)/1023.0);
      delay(150);
    }
    voltage = 4.831169*mult*(sum/400.0)/ 1023.0;
    Serial.print(voltage);
    Serial.print("V");
    sum=0;
}
