#include <avr/sleep.h>  
#define BUTTON1   2
#define LED1      5
#define LED2      6
#define LED3      9
#define BUTTON2  12

#define NUMLEDS   2     //Add 1 for the right number

#define PAUSE 500

class Player
{
  private:
    String nme;
    int score = 0;

  public:
    Player(int);
    String getName() {return nme;};
    void increaseScore() { score++;};
    int getScore() {return score;};
};

Player::Player(int newNme)
{
  nme = newNme;
}

int led[] = {LED1, LED2, LED3};
int button[] = {BUTTON1, BUTTON2};
int turn = 0;

unsigned long t1;
unsigned long t2;

Player players[] = {new Player("Player two"), new Player("Player one")};

void setup() {
  Serial.begin(9600); 
  pinMode(BUTTON1, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BUTTON2, INPUT);

}

void reverse(int* led, int num)
{
  int* temp;
  
  for (auto i = 0; i < num; i++)
  {
    temp = led[i];
    led[i] = led[num - i];
    led[num - i] = temp;
  }
}

void loop() {
  
  turn++;

    reverse(led, NUMLEDS);
  
    analogWrite(led[0],200);

    delay(PAUSE);
    analogWrite(led[0],0);
    analogWrite(led[1],200);

    delay(PAUSE);

    analogWrite(led[1],0);
    analogWrite(led[2],200);

    delay(PAUSE);

    analogWrite(led[2],0);

    t1 = millis();

    int d = digitalRead(button[1 - (turn % 2)]);
    
    while (d == false)
    {
      t2 = millis();
      if (t2 - t1 > 1500)
      {
        Serial.println("Score");
        players[turn % 2].increaseScore();
        delay(2000);
        
        break;
      } 

      d = digitalRead(button[1 - (turn % 2)]);
      
    }

    Serial.print("It is turn");
    Serial.println(turn);
    Serial.print(players[turn % 2].getName());
    Serial.print("  Has:");
    Serial.println(players[turn % 2].getScore());

    if (players[0].getScore() > 2 || players[1].getScore() > 2)
    {

      for (auto i = 0; i < 3; i++)
      {
        analogWrite(led[0],200);
        delay(250);
        analogWrite(led[0],0);
        delay(250);
      }
        off();
    }
    
 }
 
void off() 
{  
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here  
    sleep_enable();          // enables the sleep bit in the mcucr register  
    sleep_mode();            // here the device is actually put to sleep!!  
}  

