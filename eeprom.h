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

//TODO: Better memory management, sometimes seems to fail reading settings

// Config data model
struct ArduGarden {
    bool sistemaEncendido;
    int espacioConfig;
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
    0,
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { true, true, true, true, true, true, true },
    { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 2, 3, 0, 0, 0, 0, 0, 0 }
};

void writeParams(unsigned int pointer){ // Dinamic data alocation extends EEPROM life

    if (pointer == 0) pointer = EEPROM.read(DINAMIC_ED_POINTER);
    unsigned int nextPointerPos = pointer + arduGardenSettings.espacioConfig;
    unsigned int dataSize = sizeof(arduGardenSettings);
    arduGardenSettings.espacioConfig = dataSize;
    
    if ((nextPointerPos + dataSize) > EEPROM.length()) nextPointerPos = FIRST_EEPROM_POS;
    
    EEPROM.put(DINAMIC_ED_POINTER, nextPointerPos);
    EEPROM.put(nextPointerPos, arduGardenSettings);
    
    lcd.clear();
    lcd.home();
    lcd.print(STR_CONFIG_SAVED);
    lcd.setCursor(0,1);
    lcd.print(String(dataSize) + "Bytes, Pos " + String(nextPointerPos));
    delay(1500);
}

void readParams(){
    unsigned int dataPointer = EEPROM.read(DINAMIC_ED_POINTER); // Read data position in eeprom
    if (dataPointer > 0) EEPROM.get(dataPointer, arduGardenSettings); // Store in data model
    else writeParams(FIRST_EEPROM_POS); // Write default values
}
