/* Датчик влажности и температуры 
Для вывода информации использован графический дисплей MT-12864J:
http://amperka.ru/product/graphic-lcd-128x64
*/
	// библиотека для работы с графическими дисплеями
    #include <U8g2lib.h>
    // библиотека для работы с датчиками серии DHT
    #include <TroykaDHT.h>   
      
    /* пины дисплея:
      | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 |
      |+5В|Vdd|Vo |DB0|DB1|DB2|DB3|DB4|DB5| DB6| DB7| CS1| CS2| RST| R/W| D/I| E  | Vee| A  | K  |
     
      U8G2_KS0108_128X64_F u8g2(ROTATION, D0, D1, D2, D3, D2, D3, D4, D5, D6, D7,
                                EN, D/I, CS0, CS1, CS2, RESET);
      ROTATION:   угол поворота дисплея
        U8G2_R0:  0 градусов
        U8G2_R1:  90 градусов
        U8G2_R2:  180 градусов
        U8G2_R3:  270 градусов
      D0..D7: пины данных
      EN: стробирование данных
      D/I: команды / данные
      CS0-CS2: выбор кристала
      RESET: сброс
      R/W: чтение / запись (подключайте к земле)
    */
     
    // создаём объект для работы с графическим дисплеем
    U8G2_KS0108_128X64_F u8g2(U8G2_R0, 13, 12, 11, 10, 9, 8, 7, 6,
                              2, 3, 5, 4, U8X8_PIN_NONE, U8X8_PIN_NONE);

    // создаём объект класса DHT
    // передаём номер пина к которому подключён датчик и тип датчика
    // тип сенсора: DHT11, DHT21, DHT22
    DHT dht(0, DHT11);
     
    void setup(void) 
    {
      // открываем последовательный порт для мониторинга действий в программе
      Serial.begin(9600);
      dht.begin();
      // начало работы с дисплеем
      u8g2.begin();
      // очищаем память дисплея
      u8g2.clearBuffer();
      // включаем поддержку UTF8
      u8g2.enableUTF8Print();
      // выбираем шрифт
      u8g2.setFont(u8g2_font_ncenB08_tr);
      //u8g2.setFont(u8g2_font_5x8_t_cyrillic);
    }
     
    void loop(void)
    {
      // считывание данных с датчика
      dht.read();
      // проверяем состояние данных
      switch(dht.getState()) {
        case DHT_OK:
          // выводим показания влажности и температуры
          u8g2.setCursor(2, 10);
          u8g2.print("Temperature: ");
          u8g2.print(dht.getTemperatureC());
          u8g2.print("C");
          u8g2.sendBuffer();
          u8g2.setCursor(2, 20);
          u8g2.print("Humidity: ");
          u8g2.print(dht.getHumidity());
          u8g2.print("%");
          u8g2.sendBuffer();
          break;
        // DEBUG logging - ошибка контрольной суммы
        case DHT_ERROR_CHECKSUM:
          Serial.println("Checksum error");
          break;
        // DEBUG logging - превышение времени ожидания
        case DHT_ERROR_TIMEOUT:
          Serial.println("Time out error");
          break;
        // данных нет, датчик не реагирует или отсутствует
        case DHT_ERROR_NO_REPLY:
          u8g2.print("Sensor not connected!");
          break;
      }
     
      delay(3000);
      u8g2.clearBuffer();
    }

/*lejbron*/