/*
 *      _______         __          ______               __         
 *     / ___  /________/ /_  __    / ____/___ __________/ /__  ____ 
 *    / /__/ / ___/ __  / / / /___/ / __/ __ `/ ___/ __  / _ _/ __ \
 *   / ___  / /  / /_/ / /_/ /___/ /_/ / /_/ / /  / /_/ /  __/ / / /
 *  /_/  /_/_/   \__,_/\__,_/    \____/\__,_/_/   \__,_/\___/_/ /_/ C++
 *  
 *  By Pablo Luaces <pablo.luaces@gmail.com>                                       
 *  Licensed under Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
 *  Complete license text here: https://creativecommons.org/licenses/by-nc/4.0/
 *  Version: 1.0
 *  [ Main file ]
 */

#include <MenuSystem.h>
#include <Thread.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <DS3231.h>

Thread defaultTimer; // Update time and display at x interval
Thread tempTimer; // Update temperature at x interval
Thread keysTimer; // Handle inputs
LiquidCrystal lcd = LiquidCrystal(8, 9, 4, 5, 6, 7); // Init LCD
DS3231 clock;

#include "config.h" // Settings constants definitions
#include "lang.h" // Language constants definitions
#include "eeprom.h" // Permanent save settings methods
#include "core.h" // Main methods

void setup() {
    //Serial.begin(115200);   // Inicializar puerto serie
    lcd.begin(LCD_COLUMNS, LCD_ROWS);   // Inicializar el LCD
    lcd.createChar(0, simboloLogo);
    lcd.createChar(1, simboloGrados);
    lcd.createChar(2, flechaIzquierda);
    lcd.createChar(3, flechaDerecha);
    lcd.createChar(4, simboloLluvia);
    lcd.home();
    
    lcd.write(byte(0));
    lcd.print("ARDU-GARDEN PRO");
    lcd.setCursor(0,1);
    lcd.print("By Pablo Luaces");
    
    delay(1000);

    clock.begin(); // Enable real time clock
    
    lcd.setCursor(0,1);
    lcd.print("RTC Clock Found!");
    delay(1000);

    readParams(); // Read EEPROM settings
    createMenu(); // Create menu in memory
    initGpio(); // Configure Arduino Pinout

    defaultTimer.onRun(updateTime); // LCD Update clock
    defaultTimer.setInterval(100);
    
    tempTimer.onRun(updateTemperature); // Update temperature
    tempTimer.setInterval(5000);

    keysTimer.onRun(readKeypad); // Handle inputs
    keysTimer.setInterval(100);
}

void loop() {
    manageBacklight(); // Auto power off backlight
    if(defaultTimer.shouldRun()) defaultTimer.run();
    if(tempTimer.shouldRun()) tempTimer.run();
    if(keysTimer.shouldRun()) keysTimer.run();
}
