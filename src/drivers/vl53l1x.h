#ifndef vl53l1x_h
#define vl53l1x_h
 
#include "mbed.h"
 
// Device I2C bus address (shift 1 bit left because mbed utilizes 8-bit addresses and not 7-bit)
#define VL53L1X_ADD                                           0x29 << 1 

// Device identity register address 
#define VL53L1X_ID                                            0x010F 
// Timming budget register addresses
#define VL53L1_RANGE_CONFIG__TIMEOUT_MACROP_A_HI              0x005E
#define VL53L1_RANGE_CONFIG__TIMEOUT_MACROP_B_HI              0x0061
// Intermeasurement period register addresses
#define VL53L1_RESULT__OSC_CALIBRATE_VAL                      0x00DE
#define VL53L1_SYSTEM__INTERMEASUREMENT_PERIOD                0x006C 
// Range data address
#define VL53L1_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0 0x0096

// Default configuration register addresses and data
const uint16_t default_reg[] = {0x002D, 0x002E, 0x002F, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F, 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F, 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F, 0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F, 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F, 0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087};
const uint8_t default_data[] = {0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x02, 0x08, 0x00, 0x08, 0x10, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x0B, 0x00, 0x00, 0x02, 0x0A, 0x21, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x38, 0xFF, 0x01, 0x00, 0x08, 0x00, 0x00, 0x01, 0xCC, 0x0F, 0x01, 0xF1, 0x0D, 0x01, 0x68, 0x00, 0x80, 0x08, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x89, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x0D, 0x0E, 0x0E, 0x00, 0x00, 0x02, 0xC7, 0xFF, 0x9B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40};
 
// VL53L1X (range sensor) class
class VL53L1X
{
    public:
        // Class constructor
        VL53L1X(PinName sda, PinName scl);
        // Initialize sensor
        bool init();
        // Read range data
        void read();
        // Range data [m]
        float d;
    private:
        // I2C bus
        I2C i2c;      
        // Read data from register on given I2C bus address
        uint8_t read_reg(uint8_t dev, uint16_t reg);     
        uint16_t read_reg16(uint8_t dev, uint16_t reg);     
        uint32_t read_reg32(uint8_t dev, uint16_t reg);    
        // Write data from register on given I2C bus address
        void write_reg(uint8_t dev, uint16_t reg, uint8_t data); 
        void write_reg16(uint8_t dev, uint16_t reg, uint16_t data); 
        void write_reg32(uint8_t dev, uint16_t reg, uint32_t data); 
};
 
#endif