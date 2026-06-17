#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ================= OLED =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ================= PINS =================
#define JOY_Y 35
#define MENU_BUTTON 33

#define SOUND_SENSOR 36
#define LIGHT_CUP 13

#define BUZZER 14

#define LED_R 25
#define LED_G 26
#define LED_B 27

#define LED_2A 16
#define LED_2B 17

#define FLASH_LED 4

// ================= SYSTEM =================
int menuIndex = 0;
bool lastButton = HIGH;

// ================= SETUP =================
void setup()
{
  Serial.begin(115200);

  // INPUTS
  pinMode(JOY_Y, INPUT);
  pinMode(MENU_BUTTON, INPUT_PULLUP);
  pinMode(SOUND_SENSOR, INPUT);
  pinMode(LIGHT_CUP, INPUT_PULLUP);

  // OUTPUTS
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_2A, OUTPUT);
  pinMode(LED_2B, OUTPUT);
  pinMode(FLASH_LED, OUTPUT);

  // I2C
  Wire.begin(21, 22);

  // ================= OLED SAFE INIT =================
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED FAIL - check 0x3C / wiring");
    while(true);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 20);
  display.println("OLED OK");
  display.display();

  delay(1500);
}

// ================= LOOP =================
void loop()
{
  int y = analogRead(JOY_Y);
  bool btn = digitalRead(MENU_BUTTON) == LOW;

  // MENU CONTROL
  if(y < 1000)
  {
    menuIndex--;
    if(menuIndex < 0) menuIndex = 2;
    delay(150);
  }

  if(y > 3000)
  {
    menuIndex++;
    if(menuIndex > 2) menuIndex = 0;
    delay(150);
  }

  // BUTTON ACTION
  if(btn && lastButton == HIGH)
  {
    beep();
  }

  lastButton = btn;

  drawMenu();
  runMode();
}

// ================= OLED MENU =================
void drawMenu()
{
  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0,0);
  display.println("ESP32 CONTROL PANEL");

  const char* items[3] = {"SOUND", "RGB", "LIGHT"};

  for(int i=0;i<3;i++)
  {
    display.setCursor(0, 15 + i*12);

    if(i == menuIndex) display.print("> ");
    else display.print("  ");

    display.println(items[i]);
  }

  display.display();
}

// ================= BEEP =================
void beep()
{
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
}

// ================= MODE LOGIC =================
void runMode()
{
  int sound = analogRead(SOUND_SENSOR);
  int cup = digitalRead(LIGHT_CUP);

  // RESET OUTPUTS
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_2A, LOW);
  digitalWrite(LED_2B, LOW);
  digitalWrite(FLASH_LED, HIGH);
  digitalWrite(BUZZER, LOW);

  // ================= SOUND MODE =================
  if(menuIndex == 0)
  {
    displayStatus("SOUND MODE");

    if(sound > 2500)
    {
      digitalWrite(LED_R, HIGH);
      digitalWrite(BUZZER, HIGH);
    }
  }

  // ================= RGB MODE =================
  if(menuIndex == 1)
  {
    displayStatus("RGB MODE");

    int x = analogRead(34);

    if(x < 1300)
    {
      digitalWrite(LED_R, HIGH);
    }
    else if(x < 2600)
    {
      digitalWrite(LED_G, HIGH);
    }
    else
    {
      digitalWrite(LED_B, HIGH);
    }
  }

  // ================= LIGHT MODE =================
  if(menuIndex == 2)
  {
    displayStatus("LIGHT MODE");

    if(cup == LOW)
    {
      digitalWrite(LED_2A, HIGH);
      digitalWrite(FLASH_LED, LOW);
    }
    else
    {
      digitalWrite(LED_2B, HIGH);
      digitalWrite(FLASH_LED, HIGH);
    }
  }
}

// ================= OLED STATUS =================
void displayStatus(const char* text)
{
  display.setTextSize(1);
  display.setCursor(0, 50);
  display.println(text);
  display.display();
}