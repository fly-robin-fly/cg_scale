#include "HX711.h"
#include <LiquidCrystal_I2C.h>

#define HX711_SCK_PIN 4
#define HX711_F_DOUT 3
#define HX711_R_DOUT 2

#define D_LEADING_EDGE 35.0f
#define D_BETWEEN 137.0f

HX711 frontScale;
HX711 rearScale;
LiquidCrystal_I2C lcd(0x27, 16, 2);

float lastTotalWeight = -999.0f;
float lastCG = -999.0f;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello pilots! :)");
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Initializing");
  lcd.setCursor(0, 1);
  lcd.print("scales ...");
  Serial.println("Initializing scales ...");

  frontScale.begin(HX711_F_DOUT, HX711_SCK_PIN);
  rearScale.begin(HX711_R_DOUT, HX711_SCK_PIN);

  delay(1000);
  while (!frontScale.is_ready() || !rearScale.is_ready()) {
    delay(100);
  }

  frontScale.tare(20);
  rearScale.tare(20);
  frontScale.set_scale(420.52f);
  rearScale.set_scale(420.52f);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scales Ready!");

  delay(1000);
  lcd.clear();
}

void loop() {
  float frontWeight = frontScale.get_units(5);
  float rearWeight = rearScale.get_units(5);
  float totalWeight = frontWeight + rearWeight;

  bool isValidWeight = (totalWeight > 2.0f);
  bool wasValidWeight = (lastTotalWeight > 2.0f);

  float cg = 0.0f;
  if (isValidWeight) {
    cg = D_LEADING_EDGE + (D_BETWEEN * (rearWeight / totalWeight));
  } else {
    lastCG = 0.0f;
  }

  if (fabs(totalWeight - lastTotalWeight) > 1.0f || fabs(cg - lastCG) > 0.5f || isValidWeight != wasValidWeight) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Weight: ");
    lcd.print(totalWeight, 0);
    lcd.print(" g");

    lcd.setCursor(0, 1);
    lcd.print("CG:     ");
    if (isValidWeight) {
      lcd.print(cg, 1);
      lcd.print(" mm");
    } else {
      lcd.print("N/A");
    }

    lastTotalWeight = totalWeight;
    lastCG = cg;
  }

  delay(100);
}