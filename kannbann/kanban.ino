const int litsnsrPin = 3; //3:ConnectorA 4:ConnectorB
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> //by Adafruit

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  pinMode(litsnsrPin, INPUT);
  Wire.begin(5, 4); //(SDA, SCL) 1,3:ConnectorA 5,4:ConnectorB

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for(;;); 
  }

  display.clearDisplay();
  display.display();
}


void loop() {
  float litsnsr_ad = analogRead(litsnsrPin); // Read analog data
  float litsnsr_v = litsnsr_ad * 3.3 / 4096; // Calculation of voltage value
  float lux = 10000 * litsnsr_v / (3.3 - litsnsr_v) / 1000; // Calculation of lux value

  Serial.print(lux);
  Serial.print(" Lux : ");
  
  if (lux < 110) { 
    Serial.println("Dark → show display");

    display.clearDisplay();
    display.setTextSize(5);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 15);
    display.print(F("OPEN"));
    display.display();
    delay(4000);

    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 22);
    display.print(F("Welcome"));
    display.display();
    delay(4000);

    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 5);
    display.print(F("close"));
    display.setCursor(0, 40);
    display.print(F("25:00"));
    display.display();
    delay(4000);

  } else {
    Serial.println("Bright → no display");
    display.clearDisplay(); // 念のため消す
    display.display();
    delay(500); // 明るい時のループ待機
  }
}