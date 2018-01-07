/*
  This example configures LinkIt 7697 to act as a simple GATT server with 1 characteristic.

  To use it, open AppInventor project:

    * 

  Build & install it on Android id

  created Mar 2017
*/
#include <LBLE.h>
#include <LBLEPeriphral.h>
#define LEDR 13
#define LEDG 14
#define LEDB 15

// Define a simple GATT service with only 1 characteristic
LBLEService ledService("19B10010-E8F2-537E-4F6C-D104768A1214");
LBLECharacteristicInt switchCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", LBLE_READ | LBLE_WRITE);

void setup() {

  // Initialize LED pin
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // to check if USR button is pressed
  pinMode(6, INPUT);

  // Initialize BLE subsystem
  LBLE.begin();
  while (!LBLE.ready()) {
    delay(100);
  }
  Serial.println("BLE ready");

  Serial.print("Device Address = [");
  Serial.print(LBLE.getDeviceAddress());
  Serial.println("]");

  // configure our advertisement data.
  // In this case, we simply create an advertisement that represents an
  // connectable device with a device name
  LBLEAdvertisementData advertisement;
  advertisement.configAsConnectableDevice("BLE LED");

  // Configure our device's Generic Access Profile's device name
  // Ususally this is the same as the name in the advertisement data.
  LBLEPeripheral.setName("BLE LED");

  // Add characteristics into ledService
  ledService.addAttribute(switchCharacteristic);

  // Add service to GATT server (peripheral)
  LBLEPeripheral.addService(ledService);

  // start the GATT server - it is now 
  // available to connect
  LBLEPeripheral.begin();

  // start advertisment
  LBLEPeripheral.advertise(advertisement);
  pinMode(LEDR,OUTPUT);
  pinMode(LEDG,OUTPUT);
  pinMode(LEDB,OUTPUT);
  
}

void loop() {
  delay(1000);

  Serial.print("conected=");
  Serial.println(LBLEPeripheral.connected());

  if (digitalRead(6))
  {
    Serial.println("disconnect all!");
    LBLEPeripheral.disconnectAll();
  }

  /*if (switchCharacteristic.isWritten()) {
    const char value = switchCharacteristic.getValue();
    switch (value) {
      case 1:
        digitalWrite(LED_BUILTIN, HIGH);
        break;
      case 0:
        digitalWrite(LED_BUILTIN, LOW);
        break;
      default:
        Serial.println("Unknown value written");
        break;
    }
  }*/
  
  /*the unknow part*/
  if(switchCharacteristic.isWritten()){
    int value=switchCharacteristic.getValue();
    Serial.println(value);

    switch(value){
      case 1:
      setColor(255,0,0); //red
      break;
      case 2:
      setColor(255,69,0); //orange 255.165.0
      break;
      case 3:
      setColor(255,255,0);  //yellow
      break;
      case 4:
      setColor(0,255,0);  //green
      break;
      case 5:
      setColor(0,0,255); //blue
      break;
      case 6:
      setColor(0,255,255); //cyan
      break;
      case 7:
      setColor(255,0,255); //purple
      break;
      case 8:
      setColor(255,255,255); //white
      break;
      case 9:
      setColor(255,0,0); //cool
      delay(1000);
      setColor(255,69,0);
      delay(1000);
      setColor(255,255,0);
      delay(1000);
      setColor(0,255,0);
      delay(1000);
      setColor(0,0,255);
      delay(1000);
      setColor(0,255,255);
      delay(1000);
      setColor(255,0,255);
      delay(1000);
      setColor(255,255,255);
      delay(1000);
      break;
    }
  }
}

void setColor(int red, int green, int blue)
{
  analogWrite(LEDR, red);
  analogWrite(LEDG, green);
  analogWrite(LEDB, blue);  
}
