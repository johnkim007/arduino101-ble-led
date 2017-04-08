#include <CurieBLE.h>

BLEPeripheral blePeripheral;
BLEService UARTService ("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
BLEUnsignedCharCharacteristic RXCharacteristic ("6E400002-B5A3-F393-E0A9-E50E24DCCA9E", BLEWrite);
BLEUnsignedCharCharacteristic TXCharacteristic ("6E400003-B5A3-F393-E0A9-E50E24DCCA9E", BLERead);
 

int LED = 13;

void setup () {
    blePeripheral.setLocalName ("LED");
    blePeripheral.setDeviceName ("LED");
    blePeripheral.setAdvertisedServiceUuid (UARTService.uuid());
    blePeripheral.addAttribute (UARTService);
    blePeripheral.addAttribute (RXCharacteristic);
    blePeripheral.addAttribute (TXCharacteristic);
    RXCharacteristic.setValue (0);
    blePeripheral.begin ();
    pinMode(LED, OUTPUT);
}

void loop() {
    BLECentral central = blePeripheral.central (); 
    if (central) { 
        while (central.connected ()) { 
            if (RXCharacteristic.written()) { ParseRXValue (RXCharacteristic.value ()); }
            RXCharacteristic.setValue (0); }
            }
}

void ParseRXValue (int RXValue) { 
    if (RXValue == 116) {
      digitalWrite(LED, HIGH);
    }  // t
    if (RXValue == 117) {
      digitalWrite(LED, LOW);
    } //u
}
