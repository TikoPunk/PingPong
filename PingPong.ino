#include <avr/sleep.h>
#define BUTTON1       2
#define BUTTON2       12
#define LED_LIGHT_1   5
#define LED_LIGHT_2   6
#define LED_LIGHT_3   9

#define NUMLEDS       2     //Add 1 for the right number

#define PAUSE 500

class Player
{
  private:
    String name;
    int score = 0;

  public:
    Player(String);
    String getName() {return name;};
    void increaseScore() { score++;};
    int getScore() {return score;};
};

Player::Player(String newName)
{
  name = newName;
}

int ledLights[] = {LED_LIGHT_1, LED_LIGHT_2, LED_LIGHT_3};
int button[] = {BUTTON1, BUTTON2};
int turn = 0;

unsigned long t1;
unsigned long t2;

Player players[] = {Player("Player one"), Player("Player two")};

void setup() {
  Serial.begin(9600); 
  pinMode(BUTTON1, INPUT);
  pinMode(LED_LIGHT_1, OUTPUT);
  pinMode(LED_LIGHT_2, OUTPUT);
  pinMode(LED_LIGHT_3, OUTPUT);
  pinMode(BUTTON2, INPUT);

}

void reverse(int* ledLights, int num)
{
  int temp;
  
  for (auto i = 0; i < num; i++)
  {
    temp = ledLights[i];
    ledLights[i] = ledLights[num - i];
    ledLights[num - i] = temp;
  }
}

void loop() {
  
  turn++;

    reverse(ledLights, NUMLEDS);
  
    analogWrite(ledLights[0],200);

    delay(PAUSE);
    analogWrite(ledLights[0],0);
    analogWrite(ledLights[1],200);

    delay(PAUSE);

    analogWrite(ledLights[1],0);
    analogWrite(ledLights[2],200);

    delay(PAUSE);

    analogWrite(ledLights[2],0);

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
        analogWrite(ledLights[0],200);
        delay(250);
        analogWrite(ledLights[0],0);
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
