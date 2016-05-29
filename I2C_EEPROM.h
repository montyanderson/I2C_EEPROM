#ifndef I2C_EEPROM_h
#define I2C_EEPROM_h

#include <Arduino.h>
#include <Wire.h>

#define I2C_EEPROM_WRITE_DELAY 5

class I2C_EEPROM {
public:
	I2C_EEPROM(int device);
	byte read(unsigned address);
	void write(unsigned address, byte data);
	void update(unsigned address, byte data);

	template<typename T> T &get(unsigned address, T &t) {
		byte *ptr = (byte *) &t;

		for(int i = 0; i < sizeof(T); i++) {
			ptr[i] = this->read(address + i);
		}

		return t;
	};

	template<typename T> T &put(unsigned address, T &t) {
		byte *ptr = (byte *) &t;

		for(int i = 0; i < sizeof(T); i++) {
			this->update(address + i, ptr[i]);
		}

		return t;
	};

private:
	int device;
};

#endif
