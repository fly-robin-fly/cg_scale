#include "HX711.h"
#include <LiquidCrystal_I2C.h>

#define HX711_SCK_PIN 4
#define HX711_F_DOUT 3
#define HX711_R_DOUT 2

#define D_LEADING_EDGE 35
#define D_BETWEEN 137


HX711 frontScale;
HX711 rearScale;
LiquidCrystal_I2C lcd(0x27, 20, 4);



void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  frontScale.begin(HX711_F_DOUT, HX711_SCK_PIN);
  rearScale.begin(HX711_R_DOUT, HX711_SCK_PIN);
  frontScale.tare(20);
  rearScale.tare(20);
  frontScale.set_scale(420.52);
  rearScale.set_scale(420.52);

  while (!frontScale.is_ready() || !rearScale.is_ready()) {
    lcd.setCursor(0, 0);
    lcd.print("Waiting for scales to be ready ...");
  }
}

void loop() {
  float frontWeight = frontScale.get_units(5);  // Average of 5 readings
  float rearWeight = rearScale.get_units(5);
  float totalWeight = frontWeight + rearWeight;
  float cg = D_LEADING_EDGE + (D_BETWEEN * (rearWeight / totalWeight));
  lcd.setCursor(0, 0);
  lcd.print("Weight: ");
  lcd.print(totalWeight);
  lcd.print("g");
  lcd.setCursor(0, 1);
  lcd.print("CG: ");
  lcd.print(cg);
  lcd.print("mm");
  delay(100);
}
