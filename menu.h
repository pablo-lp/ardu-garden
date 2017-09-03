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
 *  [ System menu file ]
 */

// Menu variables

MenuSystem ms;
Menu mm(STR_MENU_NAME);
MenuItem sistema_encendido(STR_MENU_SYSTEM_STATE);
MenuItem encendido_manual(STR_MENU_MANUAL_ON);
MenuItem sensor_lluvia(STR_MENU_RAIN_SENSOR);
MenuItem sensor_temperatura(STR_MENU_SET_MIN_TEMP);
MenuItem tiempo_riego(STR_MENU_ZONE_TIMEOUT);
MenuItem horas_riego(STR_MENU_ON_HOURS);
MenuItem dias_riego(STR_MENU_ON_DAYS);
MenuItem ajuste_estacion(STR_MENU_CALENDAR);
MenuItem fecha_hora(STR_MENU_SET_DATETIME);
MenuItem ajuste_valvulas(STR_MENU_SET_VALVES);
MenuItem guardar_salir(STR_MENU_SAVE_EXIT);
MenuItem pantalla_inicial(STR_MENU_EXIT);

unsigned int manualTimeout = 0;

// Menu helpers

void displayMenu() {
    menuActive = true;
    
    lcd.clear();
    lcd.setCursor(0,0);
    
    // Display the menu
    Menu const* cp_menu = ms.get_current_menu();
    lcd.print(cp_menu->get_name());
    lcd.setCursor(0,1);
    lcd.print(cp_menu->get_selected()->get_name());

    backlightOn();
}

// Menu callback function

void on_sistema_encendido(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_MENU_SYSTEM_STATE);
    delay(500); // simulate transition

    int cursorPosition = 14;
    unsigned int pressedBtn;
    keysTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        char* activ = (arduGardenSettings.sistemaEncendido)? STR_ON:STR_OFF;
        sprintf(buffer, "%-12s %3s", STR_SYSTEM_STATE, activ);
        lcd.setCursor(0,1);
        lcd.print(buffer);
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_LCD_buttons();
      
        switch (pressedBtn){
            case BTN_UP: // Add

                arduGardenSettings.sistemaEncendido = true;
                break;
                
            case BTN_DOWN: // Substract

                arduGardenSettings.sistemaEncendido = false;
        }

    }while(pressedBtn != BTN_SELECT);

    delay(DELAY_ON_BTN_PRESS);
    
    keysTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_encendido_manual(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_MANUAL_ON);
    delay(500); // simulate transition

    int cursorPosition = 14;
    unsigned int pressedBtn;
    keysTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        sprintf(buffer, "%-13s %02d", STR_MINUTOS, manualTimeout);
        lcd.setCursor(0,1);
        lcd.print(buffer);
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_LCD_buttons();
      
        switch (pressedBtn){
            case BTN_UP: // Add
            
                manualTimeout++;
                break;
                
            case BTN_DOWN: // Substract
            
                manualTimeout--;
        }

        if (manualTimeout < 0) manualTimeout = MAX_ON_MINUTES;
        else if (manualTimeout > MAX_ON_MINUTES) manualTimeout = 0;

    }while(pressedBtn != BTN_SELECT);

    delay(DELAY_ON_BTN_PRESS);
    
    lcd.noBlink();
    keysTimer.enabled = true;
    if (manualTimeout > 0) sequentialIrrigation(manualTimeout * 60);
    defaultScreen();
}

void on_sensor_lluvia(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_MENU_RAIN_SENSOR);
    delay(500); // simulate transition

    int cursorPosition = 14;
    unsigned int pressedBtn;
    keysTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        sprintf(buffer, "%-13s %02d", STR_PIN_NUMBER, arduGardenSettings.sensorLluvia);
        lcd.setCursor(0,1);
        lcd.print(buffer);
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_LCD_buttons();
      
        switch (pressedBtn){
            case BTN_UP: // Add

                arduGardenSettings.sensorLluvia++;
                break;
                
            case BTN_DOWN: // Substract

                arduGardenSettings.sensorLluvia--;
        }

        if (arduGardenSettings.sensorLluvia < 0) arduGardenSettings.sensorLluvia = MAX_PIN_NUMBER;
        else if (arduGardenSettings.sensorLluvia > MAX_PIN_NUMBER) arduGardenSettings.sensorLluvia = 0;

    }while(pressedBtn != BTN_SELECT);

    delay(DELAY_ON_BTN_PRESS);
    
    keysTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_sensor_temperatura(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_TEMP_MIN);
    delay(500); // simulate transition

    int cursorPosition = 13;
    unsigned int pressedBtn;
    keysTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        sprintf(buffer, "%-12s %02d", STR_TEMP_SENSOR, arduGardenSettings.temperaturaMinima);
        lcd.setCursor(0,1);
        lcd.print(buffer);
        lcd.setCursor(15,1);
        lcd.write(byte(1));
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_LCD_buttons();
      
        switch (pressedBtn){
            case BTN_UP: // Add

                arduGardenSettings.temperaturaMinima++;
                break;
                
            case BTN_DOWN: // Substract

                arduGardenSettings.temperaturaMinima--;
        }

        if (arduGardenSettings.temperaturaMinima < 0) arduGardenSettings.temperaturaMinima = 50;
        else if (arduGardenSettings.temperaturaMinima > 50) arduGardenSettings.temperaturaMinima = 0;

    }while(pressedBtn != BTN_SELECT);

    keysTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_tiempo_riego(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_MENU_ZONE_TIMEOUT);
    delay(500); // simulate transition

    int valveNum = 0;
    int cursorPosition = 14;
    unsigned int pressedBtn;
    keysTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        lcd.setCursor(0,1);
        lcd.write(byte(2));
        sprintf(buffer, "%-2s%d %-7s", STR_ZONE_SHORTENED, valveNum+1, STR_ZONE_MINUTES);
        lcd.print(buffer);
        lcd.write(byte(3));
        sprintf(buffer, " %02d", arduGardenSettings.tiempoRiego[valveNum]);
        lcd.print(buffer);
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_LCD_buttons();
      
        switch (pressedBtn){
            case BTN_UP: // Add

                arduGardenSettings.tiempoRiego[valveNum]++;
                break;
                
            case BTN_DOWN: // Substract

                arduGardenSettings.tiempoRiego[valveNum]--;
                break;
                
            case BTN_LEFT: // Back

                valveNum--;
                break;
                
            case BTN_RIGHT: // Next

                valveNum++;
        }

        if (valveNum < 0) valveNum = NUM_VALVES-1;
        else if (valveNum > NUM_VALVES-1) valveNum = 0;
        
        if (arduGardenSettings.tiempoRiego[valveNum] < 0) arduGardenSettings.tiempoRiego[valveNum] = MAX_ON_MINUTES;
        else if (arduGardenSettings.tiempoRiego[valveNum] > MAX_ON_MINUTES) arduGardenSettings.tiempoRiego[valveNum] = 0;

    }while(pressedBtn != BTN_SELECT);

    delay(DELAY_ON_BTN_PRESS);
    
    keysTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_horas_riego(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_MENU_ON_HOURS);
    delay(500); // simulate transition

    int BTN_PosCounter = 0;
    int cursorPosition = 5;
    int hourNum = 0;
    unsigned int pressedBtn;
    keysTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        sprintf(buffer, "[Prog %d]   %02d:%02d", hourNum+1, arduGardenSettings.horasRiego[hourNum], arduGardenSettings.minutosRiego[hourNum]);
        lcd.setCursor(0,1);
        lcd.print(buffer);
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_LCD_buttons();
      
        switch (pressedBtn){
            case BTN_UP: // Add

                if (BTN_PosCounter == 0) hourNum++;
                else if (BTN_PosCounter == 1) arduGardenSettings.horasRiego[hourNum]++;
                else if (BTN_PosCounter == 2) arduGardenSettings.minutosRiego[hourNum]++;
                break;
                
            case BTN_DOWN: // Substract

                if (BTN_PosCounter == 0) hourNum--;
                else if (BTN_PosCounter == 1) arduGardenSettings.horasRiego[hourNum]--;
                else if (BTN_PosCounter == 2) arduGardenSettings.minutosRiego[hourNum]--;
                break;
                
            case BTN_LEFT: // Back

                BTN_PosCounter--;
                if (BTN_PosCounter < 0) BTN_PosCounter = 0;
                break;
                
            case BTN_RIGHT: // Next

                BTN_PosCounter++;
                if (BTN_PosCounter > 2) BTN_PosCounter = 2;
        }

        // Change cursor
        if (BTN_PosCounter == 0) cursorPosition = 5;
        else if (BTN_PosCounter == 1) cursorPosition = 11;
        else cursorPosition = 14;

        // Change hours-minutes
        if (hourNum < 0) hourNum = MAX_DAY_TIMES-1;
        else if (hourNum > MAX_DAY_TIMES-1) hourNum = 0;
        
        if (arduGardenSettings.horasRiego[hourNum] < 0) arduGardenSettings.horasRiego[hourNum] = 24;
        else if (arduGardenSettings.horasRiego[hourNum] > 24) arduGardenSettings.horasRiego[hourNum] = 0;

        if (arduGardenSettings.minutosRiego[hourNum] < 0) arduGardenSettings.minutosRiego[hourNum] = 60;
        else if (arduGardenSettings.minutosRiego[hourNum] > 60) arduGardenSettings.minutosRiego[hourNum] = 0;

    }while(pressedBtn != BTN_SELECT);

    delay(DELAY_ON_BTN_PRESS);
    
    keysTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_dias_riego(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_MENU_ON_DAYS);
    delay(500); // simulate transition
    lcd.blink();

    int cursorPosition = 14;
    unsigned int pressedBtn;
    unsigned int dayNum = 1;
    keysTimer.enabled = false;
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        char* activ = (arduGardenSettings.diasRiego[dayNum-1])? STR_ON:STR_OFF;
        lcd.setCursor(0,1);
        lcd.write(byte(2));
        sprintf(buffer, "%-10s", getWeekDayName(dayNum));
        lcd.print(buffer);
        lcd.write(byte(3));
        sprintf(buffer, " %3s", activ);
        lcd.print(buffer);
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_LCD_buttons();
      
        switch (pressedBtn){
            case BTN_UP: // Add

                arduGardenSettings.diasRiego[dayNum-1] = true;
                break;
                
            case BTN_DOWN: // Substract

                arduGardenSettings.diasRiego[dayNum-1] = false;
                break;
                
            case BTN_LEFT: // Back

                dayNum--;
                break;
                
            case BTN_RIGHT: // Next

                dayNum++;
        }

        if (dayNum < 1) dayNum = WEEK_DAYS;
        else if (dayNum > WEEK_DAYS) dayNum = 1;
        
    }while(pressedBtn != BTN_SELECT);

    delay(DELAY_ON_BTN_PRESS);

    keysTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_ajuste_estacion(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("%" + String(STR_MENU_CALENDAR));
    delay(500); // simulate transition

    int cursorPosition = 14;
    unsigned int pressedBtn;
    unsigned int monthNum = 1;
    keysTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        lcd.setCursor(0,1);
        lcd.write(byte(2));
        sprintf(buffer, "%-10s", getMonthName(monthNum));
        lcd.print(buffer);
        lcd.write(byte(3));
        sprintf(buffer, " %03d", arduGardenSettings.estacion[monthNum-1]);
        lcd.print(buffer);
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_LCD_buttons();
      
        switch (pressedBtn){
            case BTN_UP: // Add

                arduGardenSettings.estacion[monthNum-1]++;
                break;
                
            case BTN_DOWN: // Substract

                arduGardenSettings.estacion[monthNum-1]--;
                break;
                
            case BTN_LEFT: // Back

                monthNum--;
                break;
                
            case BTN_RIGHT: // Next

                monthNum++;
        }

        if (monthNum < 1) monthNum = YEAR_MONTHS;
        else if (monthNum > YEAR_MONTHS) monthNum = 1;

        if (arduGardenSettings.estacion[monthNum-1] < 0) arduGardenSettings.estacion[monthNum-1] = 100;
        else if (arduGardenSettings.estacion[monthNum-1] > 100) arduGardenSettings.estacion[monthNum-1] = 0;
        
    }while(pressedBtn != BTN_SELECT);

    delay(DELAY_ON_BTN_PRESS);

    keysTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_fecha_hora(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_MENU_SET_DATETIME);
    delay(500); // simulate transition

    int BTN_PosCounter = 0;
    int cursorPosition = 0;
    unsigned int pressedBtn;
    keysTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        sprintf(buffer, "%02d/%02d/%02d   %02d:%02d", dia, mes, ano,  horas, minutos);
        lcd.setCursor(0,1);
        lcd.print(buffer);
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_LCD_buttons();
      
        switch (pressedBtn){
            case BTN_UP: // Add

                if (BTN_PosCounter == 0) dia++;
                else if(BTN_PosCounter == 1) mes++;
                else if(BTN_PosCounter == 2) ano++;
                else if(BTN_PosCounter == 3) horas++;
                else if(BTN_PosCounter == 4) minutos++;
                break;
                
            case BTN_DOWN: // Substract

                if (BTN_PosCounter == 0) dia--;
                else if(BTN_PosCounter == 1) mes--;
                else if(BTN_PosCounter == 2) ano--;
                else if(BTN_PosCounter == 3) horas--;
                else if(BTN_PosCounter == 4) minutos--;
                break;
                
            case BTN_LEFT: // Back

                BTN_PosCounter--;
                if (BTN_PosCounter < 0) BTN_PosCounter = 0;
                break;
                
            case BTN_RIGHT: // Next

                BTN_PosCounter++;
                if (BTN_PosCounter > 4) BTN_PosCounter = 4;
        }

        // Change cursor
        if (BTN_PosCounter == 0) cursorPosition = 0;
        else if (BTN_PosCounter == 1) cursorPosition = 3;
        else if (BTN_PosCounter == 2) cursorPosition = 6;
        else if (BTN_PosCounter == 3) cursorPosition = 11;
        else cursorPosition = 14;

        // Change date-time
        if (dia < 0) dia = 31;
        else if (dia > 31) dia = 0;
        if (mes < 0) mes = 12;
        else if (mes > 12) mes = 0;
        if (ano < 0) ano = 50;
        else if (ano > 50) ano = 0;
        if (horas < 0) horas = 24;
        else if (horas > 24) horas = 0;
        if (minutos < 0) minutos = 59;
        else if (minutos > 59) minutos = 0;

    }while(pressedBtn != BTN_SELECT);

    delay(DELAY_ON_BTN_PRESS);

    clock.setDateTime(ano + YEARS_OFFSET, mes, dia, horas, minutos, 0); // Set date-time to RTC
    
    keysTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_ajuste_valvulas(MenuItem* p_menu_item){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(STR_MENU_SET_VALVES);
    delay(500); // simulate transition

    int valveNum = 0;
    int cursorPosition = 14;
    unsigned int pressedBtn;
    keysTimer.enabled = false;
    lcd.blink();
    
    do{

        delay(DELAY_ON_BTN_PRESS);
        lcd.setCursor(0,1);
        lcd.write(byte(2));
        sprintf(buffer, "%-2s%d %-7s", STR_ZONE_SHORTENED, valveNum+1, STR_VALVE_PIN);
        lcd.print(buffer);
        lcd.write(byte(3));
        sprintf(buffer, " %02d", arduGardenSettings.valvulas[valveNum]);
        lcd.print(buffer);
        lcd.setCursor(cursorPosition+1,1);
        
        pressedBtn = read_LCD_buttons();
      
        switch (pressedBtn){
            case BTN_UP: // Add

                arduGardenSettings.valvulas[valveNum]++;
                break;
                
            case BTN_DOWN: // Substract

                arduGardenSettings.valvulas[valveNum]--;
                break;
                
            case BTN_LEFT: // Back

                valveNum--;
                break;
                
            case BTN_RIGHT: // Next

                valveNum++;
        }

        if (valveNum < 0) valveNum = NUM_VALVES-1;
        else if (valveNum > NUM_VALVES-1) valveNum = 0;
        
        if (arduGardenSettings.valvulas[valveNum] < 0) arduGardenSettings.valvulas[valveNum] = MAX_PIN_NUMBER;
        else if (arduGardenSettings.valvulas[valveNum] > MAX_PIN_NUMBER) arduGardenSettings.valvulas[valveNum] = 0;

    }while(pressedBtn != BTN_SELECT);

    delay(DELAY_ON_BTN_PRESS);

    initGpio();
    keysTimer.enabled = true;
    lcd.noBlink();
    displayMenu();
}

void on_guardar_salir(MenuItem* p_menu_item){
    writeParams(0);
    ms.reset();
    menuActive = false;
}

void on_pantalla_inicial(MenuItem* p_menu_item){
    ms.reset();
    menuActive = false;
}

// Create menu in memory

void createMenu(){
    mm.add_item(&sistema_encendido, &on_sistema_encendido);
    mm.add_item(&encendido_manual, &on_encendido_manual);
    mm.add_item(&sensor_lluvia, &on_sensor_lluvia);
    mm.add_item(&sensor_temperatura, &on_sensor_temperatura);
    mm.add_item(&tiempo_riego, &on_tiempo_riego);
    mm.add_item(&horas_riego, &on_horas_riego);
    mm.add_item(&dias_riego, &on_dias_riego);
    mm.add_item(&ajuste_estacion, &on_ajuste_estacion);
    mm.add_item(&fecha_hora, &on_fecha_hora);
    mm.add_item(&ajuste_valvulas, &on_ajuste_valvulas);
    mm.add_item(&guardar_salir, &on_guardar_salir);
    mm.add_item(&pantalla_inicial, &on_pantalla_inicial);
    ms.set_root_menu(&mm);
}

