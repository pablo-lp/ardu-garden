![alt text](http://dezatec.es/wp-content/uploads/2018/12/logo-300x60.png)

Programador de riego profesional basado en Arduino

# Componentes necesarios

Ver en: http://dezatec.es/ardu-garden-pro

# Instalación

1 - Añadimos las librerías que están dentro de "Dependencies" a nuestro software Arduino, para evitar errores se aconseja usar las versiones incluídas que ya están testeadas. Después podemos eliminar esta carpeta.

2 - Abrimos el sketch con nuestro software Arduino

3 - Compilamos y lo subimos a nuestra placa (Probado solo con Arduino Uno)

# ¿Como usarlo?

Para poder poner en marcha el controlador de riego todos los componentes indicados deben estar correctamente conectados. Si no se encuentra el reloj RTC el skecth no se iniciará.

Conectar la corriente al módulo y configurarlo mediante los menús. Si las teclas no responden deberemos ajustar los valores de cada una en el fichero core.h dentro del método read_LCD_buttons() en la línea 81. Podemos imprimir la variable adc_key_in en el display para saber el valor de la tecla pulsada:

    lcd.setCursor(0,1);
    lcd.print(adc_key_in);
    delay(5000);

Para hacer una prueba puedes activar el "Encendido manual", se iniciará una sequencia de riego con las válvulas configuradas y durante el tiempo máximo indicado para cada una de ellas.

# Licencia

Este trabajo está bajo la licencia Attribution-NonCommercial 4.0 International de Creative Commons. Para ver una copia de esta licencia visite http://creativecommons.org/licenses/by-nc/4.0/ o envíe una carta a Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

# Problemas conocidos

Las variables globales de este sketch ocupan un 77% de la memoria dinámica disponible en Arduino Uno, lo que puede causar problemas de estabilidad. Si tiene problemas de este tipo puede solucionarlo fácilmente eliminando el idioma que no use del fichero lang.h

# Exención de responsabilidad

El software se proporciona "tal cual", sin garantías explícitas ni implícitas de ningún tipo, incluyendo, entre otras, garantías de comerciabilidad, idoneidad para un determinado fin, título y ausencia de infracción. Ni los propietarios de copyright ni los que distribuyan el software serán responsables en ningún caso de ningún daño ni de cualquier otra responsabilidad, ya sea por contrato, por litigio, como de cualquier otro tipo, que pudieran surgir de, o en conexión con el software o el uso u otros tratos del software.
