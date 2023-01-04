# WiFi-Thermometer

Italiano/English

WiFi Thermometer è un dispositivo IoT pronto all'uso ma con la possibilità di cambiare firmware in modo semplice tramite connettore dedicato.
La scheda viene spedita gia con l'esempio "HTTP" caricato, quindi pronta all'uso.

A bordo è presente un AC/DC (RAC02-3.3SGB) di ottima qualità, un ESP8266 (mod. ESP12) e un sensore di temperatura/umidità (HTU21D).
Ti basterà alimentare la scheda tramite il connettore a morsetti direttamente alla tensione di rete oppure tramite pin 1 (GND) e pin 6 (3.3v) del
connettore per la programmazione.
ATTENZIONE! NON ALIMENTARE LA SCHEDA CON I DUE METODI CONTEMPORANEAMENTE.
Per aggiornare o cambiare il firmware avrai bisogno del programmatore o un convertitore USB/UART come il CH340G ATTENZIONE! IL CONVERTITORE DEVE LAVORARE A 3.3V


PINOUT


1: GND

2: GPIO2

3: GPIO0

4: RX

5: TX

6: VCC 3.3v


COME FUNZIONA

Al momento dell accensione se non è stato gia configurato il dispositivo metterà a disposizione un access point (SSID: WiFi Thermometer, Password:12345678)
tramite il quale sara possibile inserire SSID e Password della propria rete lan.




You can find WiFi Thermometer on Tindie

(This page is work in progress!)
