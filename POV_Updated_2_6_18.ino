/*
 * For ECE 341
 * Team 1
 * Caleb Hubbell, Mohamed Eldebri, Tony Penoyer
 * POV wand project
 */

// letter declarations. These are constant
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
int ex[] = {29,0,0,0,0};

// Variables to dictate pin headers
const int accX = A0;
const int accY = A1;
const int accZ = A2;
const int noPixels  = 10;   // the number of LEDs in our display
const int LEDpinmap[noPixels] = {2,3,4,5,6,7,8,9,10,11};  // maps the LEDs to the corresponding i/o pins
// pin 2 is the top led

// POV variables
double delayTime = 2.75;    // initalized to a value incase the setting below breaks
double charBreak = 5.5;    // initalized to a value incase the setting below breaks
double currentSwing = 600;  // initalized to a value incase the setting below breaks
long tick = 0;            // used for timing the length of one swing
long tock = 0;            // used for timing the length of one swing
boolean swingLeft;        // flag to dictate if it is a L->R swing
long edgeTime;            // used for remembering the millis that it last detected an edge

// Accelerometer variables
int xdata;                // stores the value read in from the X pin
int ydata;                // stores the value read in from the Y pin
int deltaxy;              // stores the delta calculation of the combination of X and Y
int oldx;                 // stores the value from the last X reading
int oldy;                 // stores the value from the last Y reading
int mag_movement = 10;    // the threshold that deltaxy must pass in order for an edge to be detected

/**************************************************************/
// change the desired string here
char *toDisplay0 = "   xylphone   "; // only lowercase, space and '!' allowed!!
char *toDisplay1 = " beavers ";  
char *toDisplay2 = " yahoo ";
char *toDisplay3 = " yipee! ";
char *toDisplay4 = "";
/**************************************************************/

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
  // call the function which displays the preset string
  displayString(toDisplay0);
  /*long starttime = millis();  //this section used for diplaying multiple words
  while ((millis() - starttime) <=4000) {
    displayString(toDisplay0);
  }
  while ((millis() - starttime) >=4000 && (millis()-starttime) <= 8000) {
    displayString(toDisplay1);
  }
  while ((millis() - starttime) >=8000 && (millis()-starttime) <= 12000) {
    displayString(toDisplay2);
  }
   while ((millis() - starttime) >=12000 && (millis()-starttime) <= 16000) {
    displayString(toDisplay3);
  }*/
  
}

// function that acceps an integer containing the height of a specific row of a character and maps it into LED's
void displayLine(int line)
{
  int myline;
  myline = line;

  // walk down the column and determine which LED's must be set to on
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

// function that accepts one character from the provided word and calls display line for each of the 5 preset lines of a char, from left to right
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
  if (c == ' '){for (int i = 0; i <5; i++){displayLine(0);delay(delayTime);}displayLine(0);}
  if (c == '!'){for (int i = 0; i <5; i++) {displayLine(ex[i]);delay(delayTime);}displayLine(0);}

  //Serial.print(c);
 

  // add in the preset character spacing
  delay(charBreak);
}

// function that accepts one character from the provided word and calls display line for each of the 5 preset lines of a char, from right to left
void displayCharR(char c)
{
  if (c == 'a'){for (int i = 4; i >= 0; i--){displayLine(a[i]);delay(delayTime);}displayLine(0);}
  if (c == 'b'){for (int i = 4; i >= 0; i--){displayLine(b[i]);delay(delayTime);}displayLine(0);}
  if (c == 'c'){for (int i = 4; i >= 0; i--){displayLine(c2[i]);delay(delayTime);}displayLine(0);}
  if (c == 'd'){for (int i = 4; i >= 0; i--){displayLine(d[i]);delay(delayTime);}displayLine(0);}
  if (c == 'e'){for (int i = 4; i >= 0; i--){displayLine(e[i]);delay(delayTime);}displayLine(0);}
  if (c == 'f'){for (int i = 4; i >= 0; i--){displayLine(f[i]);delay(delayTime);}displayLine(0);}
  if (c == 'g'){for (int i = 4; i >= 0; i--){displayLine(g[i]);delay(delayTime);}displayLine(0);}
  if (c == 'h'){for (int i = 4; i >= 0; i--){displayLine(h[i]);delay(delayTime);}displayLine(0);}
  if (c == 'i'){for (int it = 4; it >= 0; it--){displayLine(i[it]);delay(delayTime);}displayLine(0);}
  if (c == 'j'){for (int i = 4; i >= 0; i--){displayLine(j[i]);delay(delayTime);}displayLine(0);}
  if (c == 'k'){for (int i = 4; i >= 0; i--){displayLine(k[i]);delay(delayTime);}displayLine(0);}
  if (c == 'l'){for (int i = 4; i >= 0; i--){displayLine(l[i]);delay(delayTime);}displayLine(0);}
  if (c == 'm'){for (int i = 4; i >= 0; i--){displayLine(m[i]);delay(delayTime);}displayLine(0);}
  if (c == 'n'){for (int i = 4; i >= 0; i--){displayLine(n[i]);delay(delayTime);}displayLine(0);}
  if (c == 'o'){for (int i = 4; i >= 0; i--){displayLine(o[i]);delay(delayTime);}displayLine(0);}
  if (c == 'p'){for (int i = 4; i >= 0; i--){displayLine(p[i]);delay(delayTime);}displayLine(0);}
  if (c == 'q'){for (int i = 4; i >= 0; i--){displayLine(q[i]);delay(delayTime);}displayLine(0);}
  if (c == 'r'){for (int i = 4; i >= 0; i--){displayLine(r[i]);delay(delayTime);}displayLine(0);}
  if (c == 's'){for (int i = 4; i >= 0; i--){displayLine(s[i]);delay(delayTime);}displayLine(0);}
  if (c == 't'){for (int i = 4; i >= 0; i--){displayLine(t[i]);delay(delayTime);}displayLine(0);}
  if (c == 'u'){for (int i = 4; i >= 0; i--){displayLine(u[i]);delay(delayTime);}displayLine(0);}
  if (c == 'v'){for (int i = 4; i >= 0; i--){displayLine(v[i]);delay(delayTime);}displayLine(0);}
  if (c == 'w'){for (int i = 4; i >= 0; i--){displayLine(w[i]);delay(delayTime);}displayLine(0);}
  if (c == 'x'){for (int i = 4; i >= 0; i--){displayLine(x[i]);delay(delayTime);}displayLine(0);}
  if (c == 'y'){for (int i = 4; i >= 0; i--){displayLine(y[i]);delay(delayTime);}displayLine(0);}
  if (c == 'z'){for (int i = 4; i >= 0; i--){displayLine(z[i]);delay(delayTime);}displayLine(0);}
  if (c == ' '){for (int i = 4; i >= 0; i--){displayLine(0);delay(delayTime);}displayLine(0);}
  if (c == '!'){for (int i = 4; i >= 0; i--) {displayLine(ex[i]);delay(delayTime);}displayLine(0);}

  //Serial.print(c);
  //Serial.print(",");
  
  // add in the preset character spacing
  delay(charBreak);
}

// function that takes the given string and calls the appropriate displayChar for each character of the string based on the direction of the swing
void displayString(char* s)
{
  
  // for a L->R swing
  if (swingLeft)
  {
    for (int i = 0; i<strlen(s); i++)
    {
      // check to see if the swing is no longer L->R, if so we need to break the printing short
      adjustSpeed();
      if (!swingLeft) { 
        break;
      }
       //otherwise, display the char
      else {
        displayCharL(s[i]);
      }
    }
  }
  
  // for a R->L swing
  else
  {
    for (int i = strlen(s)-1; i >= 0; i--)
    {
      // check to see if the swing is no longer R->L, if so we need to break the printing short
      adjustSpeed();
      if (swingLeft) {
        break;
      }
       //otherwise, display the char
      else {
        displayCharR(s[i]);
      }
    }
  }
}  

// function that reads in the accelerometer data and adjusts the display speed and direction accordingly
void adjustSpeed()
{
  // testing for finding the "normal" acc values
  /*Serial.print(analogRead(accX));
  Serial.print("    ");
  Serial.println(analogRead(accY));
  Serial.println(deltaxy);*/

  // read in the acc data
  ydata = analogRead(accY);
  xdata = analogRead(accX); 

  // math to determine the difference from the old to the new
  deltaxy = xdata + ydata - oldx - oldy;

  // math to determine the magnitute of acceleration rate of change
  deltaxy = sqrt(pow(deltaxy,2));

  // remember the old values
  oldy = ydata;
  oldx = xdata;

  // if the delta is above the preset magnitude, we have detected an edge
  if (deltaxy> mag_movement) 
  {     

    // check to make sure an edge didnt get detected twice at one side
    if(millis() > (edgeTime + (currentSwing*.4)))
    {
      //Serial.print("reading: ");
      //Serial.println((xdata + ydata - 1000)); 
      // check if the swing is L -> R
      if((xdata + ydata - 1000) < -200)
      {
          // store the time which the edge was detected, and set the left hand flag
          tick = millis();
          edgeTime = millis();
          swingLeft = true;
          //Serial.print("swing delay: ");
          //Serial.println(currentSwing); 
          Serial.println("\nDetected L edge\n");
      }

      // check if the swing is R -> L
      else if ((xdata + ydata - 1000) > 200)
      {
          // store the time which the edge was detected, and set the left hand flag to false
          tock = millis();   
          edgeTime = millis(); 
          swingLeft = false;
          //Serial.print("swing delay: ");
          //Serial.println(currentSwing); 
          Serial.println("\nDetected R edge\n");
      }    
    }
  }

  // check if the timed swing is within "realistic" parameters
  if((tock - tick) > 300 && (tock - tick) < 1000 )
  {
    // if it is, calculate the appropriate delays and set them
    currentSwing = tock - tick;
    Serial.print("currentSwing\t");
    Serial.print(currentSwing);
    delayTime = (currentSwing / (strlen(toDisplay0) * 22));
    Serial.println("delayTime\t");
    Serial.print(delayTime);
    charBreak = (delayTime * 2);
  }
}

//Parts of the code are donated from: https://diyhacking.com/arduino-pov-display/, which is an open source DIY website. Therefore, all tutorials and code are on the public domain.

