#include <avr/pgmspace.h> // allows use of PROGMEM to store patterns in flash

/*
** Defining pins in array makes it easier to rearrange how cube is wired
** Adjust numbers here until LEDs flash in order - L to R, T to B
** Note that analog inputs 0-5 are also digital outputs 14-19!
** Pin DigitalOut0 (serial RX) and AnalogIn5 are left open for future apps
*/
int blinkdelay = 170;   //This basically controls brightness. Lower is dimmer
int runspeed = 30;      //smaller = faster
int pins[] = {1,2,3,4};

const int heartpins[12][2] ={
    {1, 4}, //D0
    {1, 3}, //D1
    {1, 2}, //D2
    {2, 4}, //D3
    {2, 3}, //D4
    {2, 1}, //D5
    {3, 1}, //D8
    {3, 4}, //D6
    {3, 2}, //D7
    {4, 3}, //D9
    {4, 2}, //D10
    {4, 1}  //D11   
};

const byte heart[][12] PROGMEM ={  // This stores the array in Flash ROM. You can easily have 500+ frames.
  //
  // You can actually arrange the lines in a way that it mimics the heart shape and it will
  // run just fine. I use this for programming the animations, then reduce it to lines later.
{1,0,0,0,0,0,0,0,0,0,0,0},
{1,1,0,0,0,0,0,0,0,0,0,0},
{1,1,1,0,0,0,0,0,0,0,0,0},
{1,1,1,1,0,0,0,0,0,0,0,0},
{1,1,1,1,1,0,0,0,0,0,0,0},
{1,1,1,1,1,1,0,0,0,0,0,0},
{1,1,1,1,1,1,1,0,0,0,0,0},
{1,1,1,1,1,1,1,1,0,0,0,0},
{1,1,1,1,1,1,1,1,1,0,0,0},
{1,1,1,1,1,1,1,1,1,1,0,0},
{1,1,1,1,1,1,1,1,1,1,1,0},
{1,1,1,1,1,1,1,1,1,1,1,1}};
//{0,1,1,1,1,1,1,1,1,1,1,1},
//{0,0,1,1,1,1,1,1,1,1,1,1},
//{0,0,0,1,1,1,1,1,1,1,1,1},
//{0,0,0,0,1,1,1,1,1,1,1,1},
//{0,0,0,0,0,1,1,1,1,1,1,1},
//{0,0,0,0,0,0,1,1,1,1,1,1},
//{0,0,0,0,0,0,0,1,1,1,1,1},
//{0,0,0,0,0,0,0,0,1,1,1,1},
//{0,0,0,0,0,0,0,0,0,1,1,1},
//{0,0,0,0,0,0,0,0,0,0,1,1},
//{0,0,0,0,0,0,0,0,0,0,0,1},
//{0,0,0,0,0,0,0,0,0,0,0,0}};
//{1,1,1,1,1,1,1,1,1,1,1,0},
//{1,1,1,1,1,1,1,1,1,1,0,0},
//{1,1,1,1,1,1,1,1,1,0,0,0},
//{1,1,1,1,1,1,1,1,0,0,0,0},
//{1,1,1,1,1,1,1,0,0,0,0,0},
//{1,1,1,1,1,1,0,0,0,0,0,0},
//{1,1,1,1,1,0,0,0,0,0,0,0},
//{1,1,1,1,0,0,0,0,0,0,0,0},
//{1,1,1,0,0,0,0,0,0,0,0,0},
//{1,1,1,0,0,0,0,0,0,0,0,0},
//{1,1,0,0,0,0,0,0,0,0,0,0},
//{1,0,0,0,0,0,0,0,0,0,0,0},
//{0,0,0,0,0,0,0,0,0,0,0,0},};
//{1,1,1,1,1,1,1,1,1,1,1,1},
//{0,0,0,0,0,0,0,0,0,0,0,0},
//{1,1,1,1,1,1,1,1,1,1,1,1},
//{0,0,0,0,0,0,0,0,0,0,0,0}};

void play()
{
  boolean run = true;
  byte k;
  int t = 0;
  while(run == true)
  {
    for(int i = 0; i < runspeed; i++)
    {
      for(int j = 0; j < 27; j++)
      {
        k = pgm_read_byte(&(heart[t][j]));
        if (k == 2)
        {
          run = false;
        }
        else if(k == 1)
        {
          turnon(j);
          delayMicroseconds(blinkdelay);
          alloff();
          //alloff();
        }
        else if(k == 0)
        {
          
          delayMicroseconds(blinkdelay);
        }
      }
    }
    t++;
  }
}

void turnon(int led)
{
  int pospin = heartpins[led][0];
  int negpin = heartpins[led][1];
  pinMode(pospin, OUTPUT);
  pinMode(negpin, OUTPUT);
  digitalWrite(pospin, HIGH);
  digitalWrite(negpin, LOW);
}


void alloff()
{
  for(int i = 0; i < 4; i++)
  {
    pinMode(pins[i], INPUT);
  }
}

void sequenceon()
{
  for(int i = 0; i < 12; i++)
  {
    turnon(i);
    delay(100);   
    alloff();
    delay(100);   
  }
}
void blinkall(int numblink)
{
  alloff();
  for(int n = 0; n < numblink; n++)
  {
    for(int i = 0; i < runspeed; i++)
    {
      for(int j = 0; j < 12; j++)
      {
        turnon(j);
        delay(blinkdelay);
        alloff();
      }
    }
    delay(500);
  }
}

void setup()
{
  //blinkall();
}

void loop()
{
  play();
  alloff();

}

