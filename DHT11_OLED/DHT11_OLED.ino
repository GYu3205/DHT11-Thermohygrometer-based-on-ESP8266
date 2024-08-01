#include <DHT11.h>
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

DHT11 dht11(14);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
    Serial.begin(9600);
    u8g2.begin();
}

void loop() {
    int temperature = 0;
    int humidity = 0;
    int result = dht11.readTemperatureHumidity(temperature, humidity);

    if (result == 0) {
        u8g2.clearBuffer();				
        u8g2.setFont(u8g2_font_ncenB10_tr);	
        u8g2.drawStr(21,12,"Hello GonY!");	
        u8g2.setFont(u8g2_font_ncenB08_tr);
        u8g2.drawStr(12,32,"Temperature:");
        u8g2.drawStr(107,32,"*C");
        u8g2.setCursor(90, 32);
        u8g2.print(temperature);

        u8g2.drawStr(12,52,"Humidity:");
        u8g2.drawStr(109,52,"%");
        u8g2.setCursor(90, 52);
        u8g2.print(humidity);


        u8g2.sendBuffer();
        delay(1000);

        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    } else {
        Serial.println(DHT11::getErrorString(result));
    }

  
}
