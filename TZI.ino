/*
 *
 * Более подробно о проекте на: http://randomnerdtutorials.com/
 * Модифицирован Руи Сантосом (Rui Santos)
 *
 * Написан FILIPEFLOP
 *
 */
 
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define YES 2
#define NO 3

MFRC522 mfrc522(SS_PIN, RST_PIN);   // создаем экземпляр MFRC522
char val='0';


 
void setup()
{
  Serial.begin(9600);   // запускаем последовательную коммуникацию
  SPI.begin();          // инициализируем шину SPI
  mfrc522.PCD_Init();   // инициализируем MFRC522
  pinMode(YES,OUTPUT);
  pinMode(NO, OUTPUT);
  Serial.println("Приложите карту:");
}

void loop()
{   
    if (Serial.available() > 0) 
    {
      val = Serial.read();
      Serial.print(val);
      if (val=='1')
      {
        digitalWrite(YES,HIGH);
        delay(1000);
        digitalWrite(YES,LOW);
      }
      else
      {
      }
      if (val=='0')
      {
        digitalWrite(NO, HIGH);
        delay(1000);
        digitalWrite(NO, LOW);
      }
      
    }
    // ищем новые карты:
    if ( ! mfrc522.PICC_IsNewCardPresent())
    {
      return;
    }
    // выбираем одну из карт:
    if ( ! mfrc522.PICC_ReadCardSerial())
    {
      return;
    }
    // показываем UID на мониторе порта:
    Serial.print("1IN");
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : "");
       Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println("");
    
    delay(1000);


}
