/*
 예제 6.3
 LM35를 이용한 온도 측정
 */
 
// I2C 통신 라이브러리 설정 
#include <Wire.h>
// I2C LCD 라리브러리 설정
#include <LiquidCrystal_I2C.h>

// LCD I2C address 설정 
// PCF8574:0x27, PCF8574A:0x3F
LiquidCrystal_I2C lcd(0x27,16,2);  

// 0번 아날로그핀을 LM35 입력으로 설정한다.
const int LM35Pin = 0;
const int CdSPin = 1;

void setup() {
  
  // 16X2 LCD 모듈 설정하고 백라이트를 켠다.
  lcd.init(); // LCD 설정
  lcd.backlight();

  // 메세지를 표시한다.
  lcd.print("ex 6.3");
  lcd.setCursor(0,1);
  lcd.print("Checking Temp.");
      
  // 3초동안 메세지를 표시한다.
  delay(3000);

  // 모든 메세지를 삭체한 뒤
  // 숫자를 제외한 부분들을 미리 출력시킨다.
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Illuminance:");
  lcd.setCursor(15,0);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temp. is ");

  //LCD 문자표에서 '°' 기호를 직접 써준다
  lcd.setCursor(13,1);
  lcd.write(B11011111);
   // '°' 기호 문자코드
  lcd.setCursor(14,1);
  lcd.print("C");
   // 'C'를 표시한다.
}

void loop(){
  int adcValue1;
  int adcValue2;
  int illuminance;
  long temp; // 현재의 온도
    
  // LM35의 Vout을 읽는다.
  adcValue1 = analogRead(LM35Pin);
  adcValue2 = analogRead(CdSPin);
  // 온도값으로 환산한다. 오버플로우 방지를 위하여 500L로 표시한다.
  // 500L의 경우 500을 32비트 long 형태의 숫자로 나타내 준다.
  illuminance = map(adcValue2, 0, 1023, 100, 0);
  temp = (adcValue1 * 500L) / 1023;



  lcd.setCursor(12,0);
  lcd.print(illuminance);


  // 온도를 표시한다  
  lcd.setCursor(10,1);
  lcd.print(temp);
  
  delay(2000); 
}
