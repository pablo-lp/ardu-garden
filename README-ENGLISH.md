Ardu-Garden Pro - Professional Arduino based irrigation programmer

# Required components

See in: http://dezatec.es/ardu-garden-pro

# Installation

1 - Add the libraries that are inside "Dependencies" to your Arduino software, to avoid errors it is advised to use the included versions that are already tested. Then you can delete this folder.

2 - Open the sketch with our Arduino software

3 - Compile and upload it to your board (Tested only with Arduino Uno)

# How to use it?

To be able to start the irrigation controller, all the indicated components must be correctly connected. If the RTC clock is not found, the skecth will not start.

Connect power to the module and configure it through the menus. If the keys do not respond we must adjust the values of each one in the core.h file inside the read_LCD_buttons() method on line 81. We can print the variable adc_key_in on the display to know the value of the key pressed:

     lcd.setCursor (0,1);
     lcd.print (adc_key_in);
     delay (5000);

To make a test you can activate the "Manual ignition", it will start a sequence of irrigation with the valves configured and during the maximum time indicated for each of them.

# License

This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

# Know problems

Global variables of this sketch takes 77% of the available dynamic memory in Arduino Uno, which can cause stability problems. If you have problems of this type you can easily solve it by removing the language that does not use the file lang.h

# Disclaimer

The software is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose and non infringement. In no event shall the authors or copyright holders be liable for any claim, damages or other liability, whether in an action of contract, tort or otherwise, arising from, out of or in connection with the software or the use or other dealings in the software.
