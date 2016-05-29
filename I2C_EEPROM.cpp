#include "I2C_EEPROM.h"

I2C_EEPROM::I2C_EEPROM(int device) {
	this->device = device;
};

byte I2C_EEPROM::read(unsigned address) {
	byte data = 0xFF;

	Wire.beginTransmission(this->device);
	Wire.write((int) (address >> 8));
	Wire.write((int) (address & 0xFF));
	Wire.endTransmission();

	Wire.requestFrom(this->device, 1);
	if(Wire.available()) data = Wire.read();
	return data;
};

void I2C_EEPROM::write(unsigned address, byte data) {
	Wire.beginTransmission(this->device);
	Wire.write((int) (address >> 8));
	Wire.write((int) (address & 0xFF));
	Wire.write(int(data));
	Wire.endTransmission();

	delay(I2C_EEPROM_WRITE_DELAY);
};

void I2C_EEPROM::update(unsigned address, byte data) {
	if(this->read(address) != data) {
		Serial.println("writing!");
		this->write(address, data);
	}
}
