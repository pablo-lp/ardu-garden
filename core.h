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
 *  [ Core file ]
 */

// Core vars

int dia = 0;
int mes = 0;
int ano = 17;
int horas = 0;
int minutos = 0;
unsigned int segundos = 0;
unsigned int diaSemana = 1;
unsigned long backlightStartTime = 0;
int gradosCelsius = 0;
bool menuActive = false;
bool rainSensorActive = false;
char buffer[16];

byte simboloLogo[] = { 0x00, 0x04, 0x0E, 0x17, 0x0A, 0x04, 0x00, 0x00 };
byte simboloGrados[] = { 0x18, 0x18, 0x00, 0x0F, 0x08, 0x08, 0x0F, 0x00 };
byte flechaIzquierda[] = { 0x02, 0x06, 0x0E, 0x1E, 0x0E, 0x06, 0x02, 0x00 };
byte flechaDerecha[] = { 0x08, 0x0C, 0x0E, 0x0F, 0x0E, 0x0C, 0x08, 0x00 };
byte simboloLluvia[] = { 0x0A, 0x14, 0x00, 0x0E, 0x15, 0x04, 0x04, 0x0C };

// Core methods

char* getWeekDayName(int number){
    switch(number){
        case 1: return STR_MONDAY;
        case 2: return STR_TUESDAY;
        case 3: return STR_WEDNESDAY;
        case 4: return STR_THURSDAY;
        case 5: return STR_FRIDAY;
        case 6: return STR_SATURDAY;
        case 7: return STR_SUNDAY;
    }
}

char* getMonthName(int number){
    switch(number){
        case 1: return STR_JANUARY;
        case 2: return STR_FEBRUARY;
        case 3: return STR_MARCH;
        case 4: return STR_APRIL;
        case 5: return STR_MAY;
        case 6: return STR_JUNE;
        case 7: return STR_JULY;
        case 8: return STR_AUGUST;
        case 9: return STR_SEPTEMBER;
        case 10: return STR_OCTOBER;
        case 11: return STR_NOVEMBER;
        case 12: return STR_DECEMBER;
    }
}

void backlightOn(){
    backlightStartTime = millis();
    digitalWrite(10, HIGH); // Backlight on
}

void manageBacklight(){
    if (BACKLIGHT_TIMEOUT > 0 && backlightStartTime > 0){
        long millis_elapsed = millis() - backlightStartTime;
        if (millis_elapsed > BACKLIGHT_TIMEOUT){
            digitalWrite(10, LOW); // Backlight off
            backlightStartTime = 0;
        }
    }
}

int read_LCD_buttons(){ 
    unsigned int adc_key_in = analogRead(0);
    if (adc_key_in < 50)   return BTN_RIGHT; 
    if (adc_key_in < 250)  return BTN_UP;
    if (adc_key_in < 400)  return BTN_DOWN;
    if (adc_key_in < 650)  return BTN_LEFT;
    if (adc_key_in < 850)  return BTN_SELECT; 
    return BTN_NONE;
}

void defaultScreen(){
    lcd.setCursor(0,0);
    lcd.write(byte(0));
    lcd.print("ARDU-GARDEN");
    
    if (!arduGardenSettings.sistemaEncendido) lcd.print(" OFF");
    else{
        sprintf(buffer, " %02d", gradosCelsius);
        lcd.print(buffer);
        lcd.write(byte(1));
    }

    lcd.setCursor(0,1);
    sprintf(buffer, "%02d:%02d:%02d %02d/%02d ", horas, minutos, segundos, dia, mes);
    lcd.print(buffer);
    if (rainSensorActive) lcd.write(byte(4));
    else lcd.write(" ");
}

void updateRainSensorState(){
    if (arduGardenSettings.sensorLluvia > 0){ // If rain sensor is active don't do anything
        rainSensorActive = (RAIN_SENSOR_OFF != digitalRead(arduGardenSettings.sensorLluvia))? true:false;
    }
}

void sequentialIrrigation(unsigned long seconds){

    unsigned int minOnSeconds = MIN_ON_MINUTES * 60;

    if (seconds == 0){ // Only in automatic mode, not manual
        if (rainSensorActive){ // If rain sensor is active don't do anything
            backlightOn();
            lcd.setCursor(0,1);
            lcd.print(STR_RAIN_SENSOR_ACTIVE);
            delay(3000);
            return;
        }
    
        if (arduGardenSettings.temperaturaMinima > 0 && gradosCelsius < arduGardenSettings.temperaturaMinima){ // If temperature not reach the minimun don't do anything
            backlightOn();
            lcd.setCursor(0,1);
            lcd.print(STR_TEMP_UNDER_MIN);
            delay(3000);
            return;
        }
    }

    for(unsigned int v = 0; v < NUM_VALVES; v++){

        if (arduGardenSettings.valvulas[v] == 0 || arduGardenSettings.tiempoRiego[v] == 0) continue; // Zone not active/configured

        int numMes = (int (mes-1) < 0)? 11:(mes-1);
        int numDia = (int (diaSemana-1) < 0)? 6:(diaSemana-1);
        
        unsigned long valveSeconds = (seconds > 0)? seconds:((arduGardenSettings.tiempoRiego[v] * 60) * arduGardenSettings.estacion[numMes]) / 100;

        if (valveSeconds > 0){
            unsigned long seconds_elapsed;
            unsigned long start_time = millis();

            if (valveSeconds < minOnSeconds) valveSeconds = minOnSeconds; // Min ON time
            
            lcd.setCursor(0,1);
            lcd.print("Zona " + String(v+1) + ":       ");
            backlightOn();
            
            do{
                seconds_elapsed = (millis() - start_time) / 1000;
                unsigned int remaining_minutes = (valveSeconds-seconds_elapsed) / 60;
                unsigned int remaining_seconds = (valveSeconds-seconds_elapsed) % 60;
                lcd.setCursor(8,1);
                sprintf(buffer, "%02d:%02d %02d", remaining_minutes, remaining_seconds, valveSeconds/60);
                lcd.print(buffer);  
                digitalWrite(arduGardenSettings.valvulas[v], LOW); //Encender valvula
            }while(seconds_elapsed < valveSeconds);
    
            digitalWrite(arduGardenSettings.valvulas[v], HIGH); //Apagar valvula
        }
    }

    menuActive = false; // Go to default screen
}

void activateOnSheduled(){
    if (arduGardenSettings.sistemaEncendido){ // Only if system is active
        if (arduGardenSettings.diasRiego[diaSemana-1]){ // If is active in this week day
            for(unsigned int t = 0; t < MAX_DAY_TIMES; t++){ // Activate by time saved
                if (arduGardenSettings.horasRiego[t] == 0 && arduGardenSettings.minutosRiego[t] == 0) continue;
                if (arduGardenSettings.horasRiego[t] == horas && arduGardenSettings.minutosRiego[t] == minutos){
                    lcd.clear();
                    lcd.setCursor(0,0);
                    lcd.print(STR_SHEDULED_ON);
                    delay(500);
                    
                    sequentialIrrigation(0);
                }
            } 
        }
    }
}

void activateOnExtTrigger(){
    if (arduGardenSettings.sistemaEncendido){ // Only if system is active
        if (EXTERNAL_TRIGGER > 0){ // Allow external input to activate system
            if (analogRead(EXTERNAL_TRIGGER) > 512){
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print(STR_REMOTE_ON);
                delay(500);
                sequentialIrrigation(0);
            }
        }
    }
}

void initGpio(){
    pinMode(10, OUTPUT); // Backlight pin
    backlightOn(); // Backlight on
  
    if (arduGardenSettings.sensorLluvia > 0) pinMode(arduGardenSettings.sensorLluvia, INPUT); // Water sensor input
    
    for(unsigned int v = 0; v < NUM_VALVES; v++){
        if (arduGardenSettings.valvulas[v] == 0) continue;
        pinMode(arduGardenSettings.valvulas[v], OUTPUT); // Valve 1 pin
        digitalWrite(arduGardenSettings.valvulas[v], VALVES_OFF); // Valve 1 off
    }
}

#include "menu.h" // Menu methods

void readKeypad(){
    switch (read_LCD_buttons()) {
        case BTN_UP: // Previus item
            ms.prev();
            displayMenu();
            break;
        case BTN_DOWN: // Next item
            ms.next();
            displayMenu();
            break;
        case BTN_RIGHT: // Right presed
            backlightOn();
            break;
        case BTN_SELECT: // Select presed
            backlightOn();
            if (menuActive)
            ms.select();
    }
}

void updateTime() { // Runs every 100ms

    updateRainSensorState();

    RTCDateTime dt = clock.getDateTime();
    dia = atoi(clock.dateFormat("d", dt));
    mes = atoi(clock.dateFormat("m", dt));
    ano = atoi(clock.dateFormat("y", dt));
    horas = atoi(clock.dateFormat("H", dt));
    minutos = atoi(clock.dateFormat("i", dt));
    segundos = atoi(clock.dateFormat("s", dt));
    diaSemana = atoi(clock.dateFormat("N", dt)); // Returns Week Day in ISO-8601 format (1-7)
    
    if (!menuActive) defaultScreen();

    activateOnSheduled();
    activateOnExtTrigger();
}

void updateTemperature(){ // Runs every 5 seconds
    clock.forceConversion(); // Update temperature conversion
    gradosCelsius = clock.readTemperature();
}

