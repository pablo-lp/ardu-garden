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
 *  [ Language file ]
 */

#ifdef SYSTEM_LANG_ES // LANG SPANISH

    // Menu items
    #define STR_MENU_NAME           "-Menu principal-"
    #define STR_MENU_SYSTEM_STATE   "Encender/apagar "
    #define STR_MENU_MANUAL_ON      "Encendido manual"
    #define STR_MENU_RAIN_SENSOR    "Sensor de lluvia"
    #define STR_MENU_SET_MIN_TEMP   "Temperat. Minima"
    #define STR_MENU_ZONE_TIMEOUT   "Tiempo de riego "
    #define STR_MENU_ON_HOURS       "Horas de riego  "
    #define STR_MENU_ON_DAYS        "Dias de riego   "
    #define STR_MENU_CALENDAR       "Ajuste estacion "
    #define STR_MENU_SET_DATETIME   "Ajst. fecha/hora"
    #define STR_MENU_SET_VALVES     "Ajst. Valvulas  "
    #define STR_MENU_SAVE_EXIT      "Guardar y salir "
    #define STR_MENU_EXIT           "Salir sin guardar"
    
    // Days names
    #define STR_MONDAY      "Lunes"
    #define STR_TUESDAY     "Martes"
    #define STR_WEDNESDAY   "Miercoles"
    #define STR_THURSDAY    "Jueves"
    #define STR_FRIDAY      "Viernes"
    #define STR_SATURDAY    "Sabado"
    #define STR_SUNDAY      "Domingo"
    
    // Months names
    #define STR_JANUARY     "Enero"
    #define STR_FEBRUARY    "Febrero"
    #define STR_MARCH       "Marzo"
    #define STR_APRIL       "Abril"
    #define STR_MAY         "Mayo"
    #define STR_JUNE        "Junio"
    #define STR_JULY        "Julio"
    #define STR_AUGUST      "Agosto"
    #define STR_SEPTEMBER   "Septiembre"
    #define STR_OCTOBER     "Octubre"
    #define STR_NOVEMBER    "Noviembre"
    #define STR_DECEMBER    "Diciembre"
    
    // Messages
    #define STR_ON                  "Si" // 3 CHAR MAX
    #define STR_OFF                 "No" // 3 CHAR MAX
    #define STR_MINUTOS             "Minutos:" // 13 CHAR MAX
    #define STR_PIN_NUMBER          "Pin (0 N/D):" // 13 CHAR MAX
    #define STR_TEMP_SENSOR         "(0 Desact.):" // 12 CHAR MAX
    #define STR_ZONE_SHORTENED      "ZO" // 2 CHAR MAX
    #define STR_ZONE_MINUTES        "Minutos" // 7 CHAR MAX
    #define STR_VALVE_PIN           "Out-Pin" // 7 CHAR MAX
    #define STR_SYSTEM_STATE        "Armado" // 12 CHAR MAX
    #define STR_TEMP_MIN            "Temperatura min."
    #define STR_CONFIG_SAVED        "Config. guardada"
    #define STR_MANUAL_ON           "Encendido manual"
    #define STR_REMOTE_ON           "Encendido remoto"
    #define STR_SHEDULED_ON         "Riego programado"
    #define STR_RAIN_SENSOR_ACTIVE  "Sensor lluvia ON"
    #define STR_TEMP_UNDER_MIN      "Temp. bajo MIN  "

#else // DEFAULT LANG ENGLISH

    // Menu items
    #define STR_MENU_NAME           "-- Main menu -- "
    #define STR_MENU_SYSTEM_STATE   "System on/off   "
    #define STR_MENU_MANUAL_ON      "Manual start    "
    #define STR_MENU_RAIN_SENSOR    "Rain sensor     "
    #define STR_MENU_SET_MIN_TEMP   "Min temperature "
    #define STR_MENU_ZONE_TIMEOUT   "Irrigate time   "
    #define STR_MENU_ON_HOURS       "Irrigate hours  "
    #define STR_MENU_ON_DAYS        "Irrigate days   "
    #define STR_MENU_CALENDAR       "Calendar (set %)"
    #define STR_MENU_SET_DATETIME   "Set date-time   "
    #define STR_MENU_SET_VALVES     "Set valves      "
    #define STR_MENU_SAVE_EXIT      "Save and exit   "
    #define STR_MENU_EXIT           "Exit menu       "
    
    // Days names
    #define STR_MONDAY      "Monday"
    #define STR_TUESDAY     "Tuesday"
    #define STR_WEDNESDAY   "Wednesday"
    #define STR_THURSDAY    "Thursday"
    #define STR_FRIDAY      "Friday"
    #define STR_SATURDAY    "Saturday"
    #define STR_SUNDAY      "Sunday"
    
    // Months names
    #define STR_JANUARY     "January"
    #define STR_FEBRUARY    "February"
    #define STR_MARCH       "March"
    #define STR_APRIL       "April"
    #define STR_MAY         "May"
    #define STR_JUNE        "June"
    #define STR_JULY        "July"
    #define STR_AUGUST      "August"
    #define STR_SEPTEMBER   "September"
    #define STR_OCTOBER     "October"
    #define STR_NOVEMBER    "November"
    #define STR_DECEMBER    "December"
    
    // Messages
    #define STR_ON                  "Yes" // 3 CHAR MAX
    #define STR_OFF                 "No" // 3 CHAR MAX
    #define STR_MINUTOS             "Minutes:" // 13 CHAR MAX
    #define STR_PIN_NUMBER          "Pin (0 N/D):" // 13 CHAR MAX
    #define STR_TEMP_SENSOR         "(0 Deacti.):" // 12 CHAR MAX
    #define STR_ZONE_SHORTENED      "ZO" // 2 CHAR MAX
    #define STR_ZONE_MINUTES        "Minutes" // 7 CHAR MAX
    #define STR_VALVE_PIN           "Out-Pin" // 7 CHAR MAX
    #define STR_SYSTEM_STATE        "System armed" // 12 CHAR MAX
    #define STR_TEMP_MIN            "Min. temperature"
    #define STR_CONFIG_SAVED        "Config saved    "
    #define STR_MANUAL_ON           "Manual start    "
    #define STR_REMOTE_ON           "Remote start    "
    #define STR_SHEDULED_ON         "Scheduled start "
    #define STR_RAIN_SENSOR_ACTIVE  "Rain sensor ON  "
    #define STR_TEMP_UNDER_MIN      "Temp. under MIN "

#endif
