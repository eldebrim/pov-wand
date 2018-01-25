/*
 * For ECE 341
 * Team 1
 * POV wand project
 */

// letters
int a[] = {1, 6, 26, 6, 1};
int b[] = {31, 21, 21, 10, 0};
int c2[] = {14, 17, 17, 10, 0};
int d[] = {31, 17, 17, 14, 0};
int e[] = {31, 21, 21, 17, 0};
int f[] = {31, 20, 20, 16, 0};
int g[] = {14, 17, 19, 10, 0};
int h[] = {31, 4, 4, 4, 31};
int i[] = {0, 17, 31, 17, 0};
int j[] = {0, 17, 30, 16, 0};
int k[] = {31, 4, 10, 17, 0};
int l[] = {31, 1, 1, 1, 0};
int m[] = {31, 12, 3, 12, 31};
int n[] = {31, 12, 3, 31, 0};
int o[] = {14, 17, 17, 14, 0};
int p[] = {31, 20, 20, 8, 0};
int q[] = {14, 17, 19, 14, 2};
int r[] = {31, 20, 22, 9, 0};
int s[] = {8, 21, 21, 2, 0};
int t[] = {16, 16, 31, 16, 16};
int u[] = {30, 1, 1, 30, 0};
int v[] = {24, 6, 1, 6, 24};
int w[] = {28, 3, 12, 3, 28};
int x[] = {17, 10, 4, 10, 17};
int y[] = {17, 10, 4, 8, 16};
int z[] = {19, 21, 21, 25, 0};

// Variables to dictate pin headers
const int accX = A0;
const int accY = A1;
const int accZ = A2;
const int noPixels  = 10;   // the number of LEDs in our display
const int LEDpinmap[noPixels] = {2,3,4,5,6,7,8,9,10,11};  // maps the LEDs to the corresponding o/p pins
// pin 2 is the top led

// POV variables
int delayTime = 10;
int currentRate = 0;
int setRate = 0;
int charBreak = 2;

void setup() 
{
  // initialize serial
  Serial.begin(115200);
  delay(4);

  // initalize the pins
  for (int i=0; i < noPixels; i++)
  {
    pinMode(LEDpinmap[i], OUTPUT); 
  } 
  
  pinMode(accX, INPUT);
  pinMode(accY, INPUT);
  pinMode(accZ, INPUT);

  //intialize the acceleromiter values
  setRate = analogRead(accX) + analogRead(accY);
  //delayTime += setRate;
}

void loop() 
{
  // reference the external voltage reference, in order to make the median V 3.3
  analogReference(EXTERNAL);
  
  // change the word to be displayed here
  displayString("hi");
}

// function that acceps an interger containing the hight of a specific row of a character and maps it into LED's
void displayLine(int line)
{
  int myline;
  myline = line;
  //if (myline>=16) {digitalWrite(LEDpinmap[0], HIGH); myline-=16;} else {digitalWrite(LEDpinmap[0], LOW);}
  //if (myline>=8)  {digitalWrite(LEDpinmap[1], HIGH); myline-=8;}  else {digitalWrite(LEDpinmap[1], LOW);}
  //if (myline>=4)  {digitalWrite(LEDpinmap[2], HIGH); myline-=4;}  else {digitalWrite(LEDpinmap[2], LOW);}
  //if (myline>=2)  {digitalWrite(LEDpinmap[3], HIGH); myline-=2;}  else {digitalWrite(LEDpinmap[3], LOW);}
  //if (myline>=1)  {digitalWrite(LEDpinmap[4], HIGH); myline-=1;}  else {digitalWrite(LEDpinmap[4], LOW);}
  if (myline>=16)
  {
    digitalWrite(LEDpinmap[0], HIGH); 
    digitalWrite(LEDpinmap[1], HIGH);
    myline-=16;
  }
  else 
  {
    digitalWrite(LEDpinmap[0], LOW);
    digitalWrite(LEDpinmap[1], LOW);
  }
  if (myline>=8)
  {
    digitalWrite(LEDpinmap[2], HIGH); 
    digitalWrite(LEDpinmap[3], HIGH);
    myline-=8;
  }
  else 
  {
    digitalWrite(LEDpinmap[2], LOW);
    digitalWrite(LEDpinmap[3], LOW);
  }
  if (myline>=4)
  {
    digitalWrite(LEDpinmap[4], HIGH); 
    digitalWrite(LEDpinmap[5], HIGH);
    myline-=4;
  }
  else 
  {
    digitalWrite(LEDpinmap[4], LOW);
    digitalWrite(LEDpinmap[5], LOW);
  }
  if (myline>=2)
  {
    digitalWrite(LEDpinmap[6], HIGH); 
    digitalWrite(LEDpinmap[7], HIGH);
    myline-=2;
  }
  else 
  {
    digitalWrite(LEDpinmap[6], LOW);
    digitalWrite(LEDpinmap[7], LOW);
  }
  if (myline>=1)
  {
    digitalWrite(LEDpinmap[8], HIGH); 
    digitalWrite(LEDpinmap[9], HIGH);
    myline-=1;
  }
  else 
  {
    digitalWrite(LEDpinmap[8], LOW);
    digitalWrite(LEDpinmap[9], LOW);
  }

  // testing for finding the "normal" acc values
  Serial.print(analogRead(accX));
  Serial.print("\t");
  Serial.print(analogRead(accY));
  Serial.print("\t");
  Serial.print(analogRead(accZ));
  Serial.print("\t");
  Serial.print(delayTime);
  Serial.print("\n");
  //delay(10);

  //sample code for the adjustment of the speed
  currentRate = analogRead(accX) + analogRead(accY);
  if(currentRate < setRate)
  {
    if(delayTime + (setRate-currentRate) < 50)
    {
      delayTime = delayTime + (setRate-currentRate);
    }
    else
    {
      delayTime = 50;
    }
  }
  if(currentRate > setRate)
  {
    if(delayTime - (currentRate-setRate) > 0)
    {
      delayTime = delayTime - (currentRate-setRate);
    }
    else
    {
      delayTime = 1;
    }
  }
  setRate = currentRate;
}

// function that accepts one character from the provided word and calls display line for each of the 5 preset lines of a char
void displayChar(char c)
{
  if (c == 'a'){for (int i = 0; i <5; i++){displayLine(a[i]);delay(delayTime);}displayLine(0);}
  if (c == 'b'){for (int i = 0; i <5; i++){displayLine(b[i]);delay(delayTime);}displayLine(0);}
  if (c == 'c'){for (int i = 0; i <5; i++){displayLine(c2[i]);delay(delayTime);}displayLine(0);}
  if (c == 'd'){for (int i = 0; i <5; i++){displayLine(d[i]);delay(delayTime);}displayLine(0);}
  if (c == 'e'){for (int i = 0; i <5; i++){displayLine(e[i]);delay(delayTime);}displayLine(0);}
  if (c == 'f'){for (int i = 0; i <5; i++){displayLine(f[i]);delay(delayTime);}displayLine(0);}
  if (c == 'g'){for (int i = 0; i <5; i++){displayLine(g[i]);delay(delayTime);}displayLine(0);}
  if (c == 'h'){for (int i = 0; i <5; i++){displayLine(h[i]);delay(delayTime);}displayLine(0);}
  if (c == 'i'){for (int it = 0; it <5; it++){displayLine(i[it]);delay(delayTime);}displayLine(0);}
  if (c == 'j'){for (int i = 0; i <5; i++){displayLine(j[i]);delay(delayTime);}displayLine(0);}
  if (c == 'k'){for (int i = 0; i <5; i++){displayLine(k[i]);delay(delayTime);}displayLine(0);}
  if (c == 'l'){for (int i = 0; i <5; i++){displayLine(l[i]);delay(delayTime);}displayLine(0);}
  if (c == 'm'){for (int i = 0; i <5; i++){displayLine(m[i]);delay(delayTime);}displayLine(0);}
  if (c == 'n'){for (int i = 0; i <5; i++){displayLine(n[i]);delay(delayTime);}displayLine(0);}
  if (c == 'o'){for (int i = 0; i <5; i++){displayLine(o[i]);delay(delayTime);}displayLine(0);}
  if (c == 'p'){for (int i = 0; i <5; i++){displayLine(p[i]);delay(delayTime);}displayLine(0);}
  if (c == 'q'){for (int i = 0; i <5; i++){displayLine(q[i]);delay(delayTime);}displayLine(0);}
  if (c == 'r'){for (int i = 0; i <5; i++){displayLine(r[i]);delay(delayTime);}displayLine(0);}
  if (c == 's'){for (int i = 0; i <5; i++){displayLine(s[i]);delay(delayTime);}displayLine(0);}
  if (c == 't'){for (int i = 0; i <5; i++){displayLine(t[i]);delay(delayTime);}displayLine(0);}
  if (c == 'u'){for (int i = 0; i <5; i++){displayLine(u[i]);delay(delayTime);}displayLine(0);}
  if (c == 'v'){for (int i = 0; i <5; i++){displayLine(v[i]);delay(delayTime);}displayLine(0);}
  if (c == 'w'){for (int i = 0; i <5; i++){displayLine(w[i]);delay(delayTime);}displayLine(0);}
  if (c == 'x'){for (int i = 0; i <5; i++){displayLine(x[i]);delay(delayTime);}displayLine(0);}
  if (c == 'y'){for (int i = 0; i <5; i++){displayLine(y[i]);delay(delayTime);}displayLine(0);}
  if (c == 'z'){for (int i = 0; i <5; i++){displayLine(z[i]);delay(delayTime);}displayLine(0);}

  // add in the preset character spacing
  delay(charBreak);
}

// takes the given string and calls displayChar for each character of the string
void displayString(char* s)
{
  for (int i = 0; i<=strlen(s); i++)
  {
    displayChar(s[i]);
   }
}  

//Parts of the code are donated from: https://diyhacking.com/arduino-pov-display/
