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
 *  [ Eeprom management file ]
 */

#include <EEPROM.h>

// Config data model
struct ArduGarden {
    bool sistemaEncendido;
    int sensorLluvia;
    int temperaturaMinima;
    int tiempoRiego[NUM_VALVES];
    int horasRiego[MAX_DAY_TIMES];
    int minutosRiego[MAX_DAY_TIMES];
    bool diasRiego[WEEK_DAYS];
    int estacion[YEAR_MONTHS];
    int valvulas[NUM_VALVES];
};

// Data to store
ArduGarden arduGardenSettings = {
    false,
    0,
    0,
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { true, true, true, true, true, true, true },
    { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 2, 3, 0, 0, 0, 0, 0, 0 }
};

void writeParams(unsigned int pointer){ // Dinamic data alocation extends EEPROM life

    unsigned int dataSize = sizeof(arduGardenSettings);

    EEPROM.write(0, 1); // Data saved flag
    EEPROM.put(FIRST_EEPROM_POS, arduGardenSettings);
    
    lcd.clear();
    lcd.home();
    lcd.print(STR_CONFIG_SAVED);
    lcd.setCursor(0,1);
    lcd.print(String(dataSize) + "Bytes, Pos " + String(FIRST_EEPROM_POS));
    delay(1500);
}

void readParams(){
    if (EEPROM.read(0) == 1) EEPROM.get(FIRST_EEPROM_POS, arduGardenSettings); // Store in data model
}
