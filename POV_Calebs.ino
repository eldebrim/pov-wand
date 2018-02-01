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
int space[] = {0,0,0,0,0};

// Variables to dictate pin headers
const int accX = A0;
const int accY = A1;
const int accZ = A2;
const int noPixels  = 10;   // the number of LEDs in our display
const int LEDpinmap[noPixels] = {2,3,4,5,6,7,8,9,10,11};  // maps the LEDs to the corresponding o/p pins
// pin 2 is the top led

// POV variables
double delayTime = 10;
double charBreak = 10;
long tick = 0;
long tock = 0;
long currentSwing = 600;
int swingTime = 0;
int left = 0;
int right = 0;
int currentRate = 0;
int pattern = 0;
int pos_thresh;         // positive acceleration threshold
int neg_thresh;         // negatiive acceleration threshold
boolean swingLeft;        // decelleration flag
int dir;
long edgeTime;

// Stuff for the accelerometer part
int xdata;
int ydata;
int deltax;
int deltay;
int oldx;
int oldy;
int magnitude_accelerometer;
int mag_movement = 10; //  The minimum value of magnitude accelerometer that means there has been movement

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
}

void loop() 
{
  // reference the external voltage reference, in order to make the median V 3.3
  analogReference(EXTERNAL);
  displayString("working"); // change here
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

  // call the function that adjusts the speed of the display
  adjustSpeed();
}

// function that accepts one character from the provided word and calls display line for each of the 5 preset lines of a char
void displayCharL(char c)
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
  if (c == ' '){for (int i = 0; i <5; i++){displayLine(space[i]);delay(delayTime);}displayLine(0);}

  // add in the preset character spacing
  delay(charBreak);
}

// function that accepts one character from the provided word and calls display line for each of the 5 preset lines of a char
void displayCharR(char c)
{
  /*if (c == 'a'){for (int i = 5; i > 0; i--){displayLine(a[i]);delay(delayTime);}displayLine(0);}
  if (c == 'b'){for (int i = 5; i > 0; i--){displayLine(b[i]);delay(delayTime);}displayLine(0);}
  if (c == 'c'){for (int i = 5; i > 0; i--){displayLine(c2[i]);delay(delayTime);}displayLine(0);}
  if (c == 'd'){for (int i = 5; i > 0; i--){displayLine(d[i]);delay(delayTime);}displayLine(0);}
  if (c == 'e'){for (int i = 5; i > 0; i--){displayLine(e[i]);delay(delayTime);}displayLine(0);}
  if (c == 'f'){for (int i = 5; i > 0; i--){displayLine(f[i]);delay(delayTime);}displayLine(0);}
  if (c == 'g'){for (int i = 5; i > 0; i--){displayLine(g[i]);delay(delayTime);}displayLine(0);}
  if (c == 'h'){for (int i = 5; i > 0; i--){displayLine(h[i]);delay(delayTime);}displayLine(0);}
  if (c == 'i'){for (int it = 5; it > 0; it--){displayLine(i[it]);delay(delayTime);}displayLine(0);}
  if (c == 'j'){for (int i = 5; i > 0; i--){displayLine(j[i]);delay(delayTime);}displayLine(0);}
  if (c == 'k'){for (int i = 5; i > 0; i--){displayLine(k[i]);delay(delayTime);}displayLine(0);}
  if (c == 'l'){for (int i = 5; i > 0; i--){displayLine(l[i]);delay(delayTime);}displayLine(0);}
  if (c == 'm'){for (int i = 5; i > 0; i--){displayLine(m[i]);delay(delayTime);}displayLine(0);}
  if (c == 'n'){for (int i = 5; i > 0; i--){displayLine(n[i]);delay(delayTime);}displayLine(0);}
  if (c == 'o'){for (int i = 5; i > 0; i--){displayLine(o[i]);delay(delayTime);}displayLine(0);}
  if (c == 'p'){for (int i = 5; i > 0; i--){displayLine(p[i]);delay(delayTime);}displayLine(0);}
  if (c == 'q'){for (int i = 5; i > 0; i--){displayLine(q[i]);delay(delayTime);}displayLine(0);}
  if (c == 'r'){for (int i = 5; i > 0; i--){displayLine(r[i]);delay(delayTime);}displayLine(0);}
  if (c == 's'){for (int i = 5; i > 0; i--){displayLine(s[i]);delay(delayTime);}displayLine(0);}
  if (c == 't'){for (int i = 5; i > 0; i--){displayLine(t[i]);delay(delayTime);}displayLine(0);}
  if (c == 'u'){for (int i = 5; i > 0; i--){displayLine(u[i]);delay(delayTime);}displayLine(0);}
  if (c == 'v'){for (int i = 5; i > 0; i--){displayLine(v[i]);delay(delayTime);}displayLine(0);}
  if (c == 'w'){for (int i = 5; i > 0; i--){displayLine(w[i]);delay(delayTime);}displayLine(0);}
  if (c == 'x'){for (int i = 5; i > 0; i--){displayLine(x[i]);delay(delayTime);}displayLine(0);}
  if (c == 'y'){for (int i = 5; i > 0; i--){displayLine(y[i]);delay(delayTime);}displayLine(0);}
  if (c == 'z'){for (int i = 5; i > 0; i--){displayLine(z[i]);delay(delayTime);}displayLine(0);}
  */
  if (c == ' '){for (int i = 5; i > 0; i--){displayLine(space[i]);delay(delayTime);}displayLine(0);}
  
  // add in the preset character spacing
  delay(charBreak);
}

// takes the given string and calls displayChar for each character of the string
void displayString(char* s)
{
  if (swingLeft)
  {
    for (int i = 0; i<=strlen(s); i++)
    {
      displayCharL(s[i]);
    }
  }
  else
  {
    for (int i = strlen(s); i >= 0; i--)
    {
      displayCharR(' ');
    }
  }
}  

// reads in the accelerometer data and adjusts the display speed accordingly
void adjustSpeed()
{
  // testing for finding the "normal" acc values
  Serial.print(analogRead(accX));
  Serial.print("    ");
  Serial.print(analogRead(accY));
  Serial.print("\n");

  // CHECK ACCELEROMETER
  ydata = analogRead(accY);
  xdata = analogRead(accX); 
   
  deltay = ydata - oldy;
  deltay = xdata - oldx;
  
  deltay = sqrt(pow(deltay,2));
 
  oldy = ydata;
  oldx = xdata;

  //Serial.println(deltay);
  if (deltay> mag_movement) 
  {      
    if(millis() > (edgeTime + (currentSwing*.60)))
    {      
      // sit and wait for a L -> R swing
      if((ydata - 500) < -20)
      {
          tick = millis();
          swingLeft = true;
          edgeTime = millis();
          /*Serial.print("swing delay: ");
          Serial.println(currentSwing); 
          Serial.println("\nDetected L edge\n");*/
      }
      else if ((ydata - 500) > 20)
      {
          tock = millis();    
          swingLeft = false;
          edgeTime = millis();
          /*Serial.print("swing delay: ");
          Serial.println(currentSwing); 
          Serial.println("\nDetected R edge\n");*/
      }    
    }
  }

  if((tock - tick) > 300 && (tock - tick) < 1000 )
  {
    Serial.print("swing time: ");
    Serial.println(currentSwing);
    currentSwing = tock - tick;
    delayTime = (currentSwing/150);
    charBreak = (delayTime*2);
  }
}

//Parts of the code are donated from: https://diyhacking.com/arduino-pov-display/, which is an open source DIY website. Therefore, all tutorials and code are on the public domain.
// and from: https://github.com/unigamer/POV-Wand/blob/master/Arduino/POV_Wand/POV_Wand.ino
