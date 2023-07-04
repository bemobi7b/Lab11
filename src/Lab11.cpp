/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "c:/Users/Rich/CTD2023/Lab11/src/Lab11.ino"
#include "Particle.h"
#include "oled-wing-adafruit.h"

#include "LIS3DH.h"

// Electron sample to print accelerometer samples to serial
// (also works on the Photon, P1, Core)

void setup();
void loop();
void resetDisplay();
#line 9 "c:/Users/Rich/CTD2023/Lab11/src/Lab11.ino"
SYSTEM_THREAD(ENABLED);

// This sample only uses serial, not data, so cellular is turned off to save data
SYSTEM_MODE(MANUAL);

// Print 10 samples per second to serial
const unsigned long PRINT_SAMPLE_PERIOD = 100;

// LIS3DH is connected as in the AssetTracker, to the primary SPI with A2 as the CS (SS) pin, and INT connected to WKP
LIS3DHSPI accel(SPI, D3, WKP);
OledWingAdafruit display;

unsigned long lastPrintSample = 0;

void setup() {  
  display.setup();
  resetDisplay();
  display.display();
  
	Serial.begin(9600);

	// delay(5000);

	// Initialize sensors
	LIS3DHConfig config;
	config.setAccelMode(LIS3DH::RATE_100_HZ);

	bool setupSuccess = accel.setup(config);
	Serial.printlnf("setupSuccess=%d", setupSuccess);
}

void loop() {
  display.loop();
  resetDisplay();
	if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD) {
		lastPrintSample = millis();

		LIS3DHSample sample;
		if (accel.getSample(sample)) {
			Serial.printlnf("%d,%d,%d", sample.x, sample.y, sample.z);
      display.println("X, Y, Z:");
      display.printf("%d,%d,%d", sample.x, sample.y, sample.z);
      display.display();
		}
		else {
			Serial.println("no sample");
		}
	}
}

void resetDisplay(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  // display.display();
}


