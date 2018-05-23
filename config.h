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
 *  [ Config file ]
 */

#define SYSTEM_LANG_ES // Selects language in lang.h, default english
#define LCD_COLUMNS 16 // Number of LCD columns
#define LCD_ROWS 2 // Number of LCD rows
#define BACKLIGHT_TIMEOUT 10000 // 0 No timeout
#define DELAY_ON_BTN_PRESS 150 // Delay to prevent double trigger
#define YEARS_OFFSET 2000 // Millenium to work with short year (2000 + 17)

#define NUM_VALVES 8  // Default configurable valves/zones
#define VALVES_OFF HIGH // 1 Not-active, 0 Active
#define RAIN_SENSOR_OFF LOW // 1 Not-active, 0 Active
#define MIN_ON_MINUTES 1 // Minimun minutes for valve
#define MAX_ON_MINUTES 30 // Maximum minutes for valve
#define MAX_DAY_TIMES 5 // Maximum configurable irrigation times
#define WEEK_DAYS 7 // Number of days in a week
#define YEAR_MONTHS 12 // Number of months in a year

#define MAX_PIN_NUMBER 35 // Maximum config pin number to set
#define FIRST_EEPROM_POS 1 // First EEPROM pos to write data (0 Reserved to flag)
#define EXTERNAL_TRIGGER 0 // Analogic PIN input (1-5, 0 Not used)

// Keypad buttons identification
#define BTN_NONE   0
#define BTN_UP     1
#define BTN_DOWN   2
#define BTN_RIGHT  3
#define BTN_LEFT   4
#define BTN_SELECT 5
