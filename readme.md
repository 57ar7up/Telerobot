Проект создания робота телеприсутствия на Arduino с корпусом, напечатанным на 3D-принтере, управляющимся через Web-интерфейс посредством Wi-Fi

Веб-интерфейс: http://auroraproject.ru/telerobot

Hardware:

- Arduino Uno, ATmega 328P
- Dragino Yun Shield	(CPU 400MHz; RAM: 64MB; ROM 16MB; Open source Linux (OpenWrt). Internet via WiFi or 3G dongle. Web server)
- Arduino Motor & Servo Shield
- Веб-камера
- Датчики расстояния до объектов

serial_connector.php		Файл, связывающийся с UART через библиотеку PHP Serial

data/UART_mapping.json		Соответствие команд, отправляемых на последовательный порт кодам клавиш клавиатуры.

data/keycodes.json		Соответствие числовых кодов символам клавиатуры