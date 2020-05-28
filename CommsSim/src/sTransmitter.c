// sTransmitter.c
// Author: Thomas Ganley
// May 13, 2020
// "*" indicates code that should be removed once i2c & spi are implemented with the actual hardware

#include "sTransmitter.h"
#include "mock_i2c.h" //*
#include "mock_spi.h" //*
#include <stdint.h>
#include <unistd.h> //*
	
//* Simulated registers so that we can "store" values
static uint8_t reg0 = 0, reg1 = 0, reg3 = 0, reg4 = 0, reg5 = 1;
static uint8_t reg17 = 30, reg18 = 3, reg19 = 1, reg20 = 0;
static uint8_t reg21 = 0, reg22 = 0, reg23 = 0, reg24 = 0;
static uint8_t reg25 = 0, reg26 = 8, reg27 = 8, reg28 = 8;
static uint8_t reg29 = 8, reg30 = 50, reg31 = 0, reg32 = 255;
static uint8_t reg33 = 192, reg34 = 8, reg35 = 8, reg36 = 16;
static uint8_t reg37 = 16, reg38 = 192, reg39 = 64, reg40 = 0, reg41 = 9;

//* Simulated buffer function for adding 
ret_state add_vBuffer(int n_bytes)// Replace with spi_writeData eventually
{
	spi_writeData_Expect();
	spi_writeData();

	for(int j = 0; j < n_bytes; j++){ 
		
		// Time Delay
		sleep(S_DATA_TIME);

		// Overrun?
		if(reg25 == 0 && reg24 == 80){
			if(reg23 == 255){
				reg22++;
				reg23 = 0;
			}else{
				reg23++;
			}
			reg19 = 0;
			continue;
		}

		
		if(reg25 == 255){
			reg24++;
			reg25 = 0;
		}else{
			reg25++;
			uint16_t b_count = 0;
			get_S_buffer(0, &b_count);			
			if(b_count > 2560){
				reg19 = 0;
			}
		}
	}
	return FUNC_PASS;
}

ret_state transmit_vBuffer(int n_bytes) // No such function will actually need to be called
{	
	for(int k = 0; k < n_bytes; k++){
		
		// Time Delay
		sleep(S_DATA_TIME);
		// Underrun?
		if(reg25 == 0 && reg24 == 0){
			if(reg21 == 255){
				reg20++;
				reg21 = 0;
			}else{
				reg21++;
			}
			reg19 = 1;
			continue;
		}
		
		if(reg25 == 0){
			reg25 = 255;
			reg24--;	
		}else{
			reg25--;
			
			uint16_t b_count = 0;
			get_S_buffer(0, &b_count);
			if(b_count <= 2560){
				reg19 = 1;
			}
		}
	}
	return FUNC_PASS;
}
void empty_vBuffer(void)
{
	reg25 = 0;
	reg24 = 0;
}

//* Function to read a register, called in other functions (replace with i2c_readRegister eventually)
ret_state read_reg(uint8_t address, uint8_t * ptr)
{
	uint8_t exp = 0x0; //*
	switch (address){
        case 0: exp = reg0; break;//*
        case 1: exp = reg1; break;//*
        case 3: exp = reg3; break;//*
        case 4: exp = reg4; break;//*
        case 5: exp = reg5; break;//*
        case 17: exp = reg17; break;//*
        case 18: exp = reg18; break;//*
        case 19: exp = reg19; break;//*
        case 20: exp = reg20; break;//*
        case 21: exp = reg21; break;//*
        case 22: exp = reg22; break;//*
        case 23: exp = reg23; break;//*
        case 24: exp = reg24; break;//*
        case 25: exp = reg25; break;//*
        case 26: exp = reg26; break;//*
        case 27: exp = reg27; break;//*
        case 28: exp = reg28; break;//*
        case 29: exp = reg29; break;//*
        case 30: exp = reg30; break;//*
        case 31: exp = reg31; break;//*
        case 32: exp = reg32; break;//*
        case 33: exp = reg33; break;//*
        case 34: exp = reg34; break;//*
        case 35: exp = reg35; break;//*
        case 36: exp = reg36; break;//*
        case 37: exp = reg37; break;//*
        case 38: exp = reg38; break;//*
        case 39: exp = reg39; break;//*
        case 40: exp = reg40; break;//*
        case 41: exp = reg41; break;//*
	default: return BAD_PARAM;//*
	}

	i2c_readRegister_ExpectAndReturn(address, exp);//*
	*ptr = i2c_readRegister(address);
	resetTest(); //* Clears ExpectAndReturn memory
	return FUNC_PASS;
}
// Function to write to a register, called in other functions
ret_state write_reg(uint8_t address, uint8_t val)
{
	i2c_writeRegister_Expect(address, val); //*
	i2c_writeRegister(address, val);

	switch (address){
	case 0: reg0 = val; break;//*
	case 1: reg1 = val; break;//*
	case 3: reg3 = val; break;//*
	case 4: reg4 = val; break;//*
	case 5: reg5 = val; break;//*
	case 17: reg17 = val; break;//*
	case 18: reg18 = val; break;//*
	case 19: reg19 = val; break;//*
	case 20: reg20 = val; break;//*
	case 21: reg21 = val; break;//*
	case 22: reg22 = val; break;//*
	case 23: reg23 = val; break;//*
	case 24: reg24 = val; break;//*
	case 25: reg25 = val; break;//*
	case 26: reg26 = val; break;//*
	case 27: reg27 = val; break;//*
	case 28: reg28 = val; break;//*
	case 29: reg29 = val; break;//*
	case 30: reg30 = val; break;//*
	case 31: reg31 = val; break;//*
	case 32: reg32 = val; break;//*
	case 33: reg33 = val; break;//*
	case 34: reg34 = val; break;//*
	case 35: reg35 = val; break;//*
	case 36: reg36 = val; break;//*
	case 37: reg37 = val; break;//*
	case 38: reg38 = val; break;//*
	case 39: reg39 = val; break;//*
	case 40: reg40 = val; break;//*
	case 41: reg41 = val; break;//*
	default: return BAD_PARAM; //*
	}
	return FUNC_PASS;
}
// Function to combine readings from two registers 
uint16_t append_bytes(uint8_t b1, uint8_t b2)
{
	uint16_t b = (b1 << 8) | b2;
	return b;
}

// Calculates the board temperature (called in get_S_hk)
float b_Temp(uint16_t b)
{
	float temperature = 0;
	b = b >> 4;
	if (b & 2048){
		temperature = -0.0625f*(float)((~b & 4095) + 1);
	}else{
		temperature = 0.0625f*(float)(b);
	}
	return temperature;
}

// REGISTER 0x00:
// Get the value of the control register
ret_state get_S_control(uint8_t * pa, uint8_t * mode)
{
	uint8_t rawValue = 0;
	if(read_reg(0x0, &rawValue) != FUNC_PASS){
		return BAD_READ;	
	}else{
		*pa = rawValue >> 7;
		*mode = rawValue & 3;
		return FUNC_PASS;
	}
}

// Set a new control on the transmitter
ret_state set_S_control(uint8_t new_pa, uint8_t new_mode)
{
	
	if(new_mode > 3 || new_pa > 1){
		return BAD_PARAM;
	}
	
	new_mode |= (new_pa << 7);

	if(write_reg(0x0, new_mode) != FUNC_PASS){
		return BAD_WRITE;
	}else{
		return FUNC_PASS;
	}
}

// REGISTER 0x01:
// Get the value of the encoder register
ret_state get_S_encoder(uint8_t * scrambler, uint8_t * filter, uint8_t * mod, uint8_t * rate)
{
	uint8_t rawValue = 0;
       	if(read_reg(0x01, &rawValue) != FUNC_PASS){
		return BAD_READ;
	}else{
		*rate = rawValue & 3;
		*mod = 1 & (rawValue >> 2);
		*filter = 1 & (rawValue >> 3);
		*scrambler = 1 & (rawValue >> 4);
		return FUNC_PASS;
	}

}

// Set a new encoder value
ret_state set_S_encoder(uint8_t new_scrambler, uint8_t new_filter, uint8_t new_mod, uint8_t new_rate)
{
	if(new_rate > 1 || new_mod > 1 || new_filter > 1 || new_scrambler > 1){
		return BAD_PARAM;
	}
	
	new_rate = (new_rate) | (new_mod << 2) | (new_filter << 3) | (new_scrambler << 4);

	uint8_t mode = 0, pa = 0;
	if(get_S_control(&pa, &mode) == FUNC_PASS){
		if(mode == 0){
			if(write_reg(0x01, new_rate)){
				return BAD_WRITE;
			}else{
				return FUNC_PASS;
			}
		}else{
			return BAD_PARAM;
		}
	
	}else{
		return BAD_READ;
	}
}

// REGISTER 0x03:
// Get the Power Amplifier power
ret_state get_S_paPower(uint8_t * power)
{
	uint8_t rawValue = 0;
       	
	if(read_reg(0x03, &rawValue) != FUNC_PASS){
		return BAD_READ;
	}else{
		switch (rawValue){
		case 0: *power = 24; break;
		case 1: *power = 26; break;
		case 2: *power = 28; break;
		case 3: *power = 30; break;
		default: return BAD_PARAM;
		}
		return FUNC_PASS;
	}
}
// Set the Power Amplifier power
ret_state set_S_paPower(uint8_t new_paPower)
{
	uint8_t rawValue = 0;

	switch (new_paPower){
	case 24: rawValue = 0; break;
	case 26: rawValue = 1; break;
	case 28: rawValue = 2; break;
	case 30: rawValue = 3; break;
	default: return BAD_PARAM;
	}

	if(write_reg(0x03, rawValue) != FUNC_PASS){
		return BAD_WRITE;
	}else{
		return FUNC_PASS;
	}
}


// Register 0x04:
// Get the frequency
ret_state get_S_frequency(float * freq)
{
	uint8_t offset = 0;
	if(read_reg(0x04, &offset) != FUNC_PASS){
		return BAD_READ;
	}else{
		*freq = (float)offset/2 + 2200.0f;
		return FUNC_PASS;
	}
}

// Set a new frequency
ret_state set_S_frequency(float new_frequency)
{
	if(new_frequency >= 2200.0f && new_frequency <= 2300.0f){
		uint8_t offset = (uint8_t)((new_frequency - 2200.0f)*2);
		
		if(write_reg(0x04, offset) != FUNC_PASS){
			return BAD_WRITE;
		}else{
			return FUNC_PASS; // Successful Write
		}
	}else{
		return BAD_PARAM;
	}
}

// REGISTER 0x05:
// Reset the FPGA logic
ret_state softResetFPGA(void)
{
	if(write_reg(0x05, 0x0) != FUNC_PASS){
		return BAD_WRITE;
	}else{
		return FUNC_PASS;
	}
}

// REGISTER 0x11:
// Get the firmware version
ret_state get_S_firmwareVersion(float * version)
{
	uint8_t rawValue = 0;
	if(read_reg(0x11, &rawValue) != FUNC_PASS){
		return BAD_READ;
	}else{
		float major = (float)(rawValue >> 4);
        	float minor = (float)(rawValue & 15);
		minor /= 100.0f;
		*version = (major+minor);
		return FUNC_PASS;
	}
}

// REGISTER 0x12:
// Get the status of the lock and the PA
ret_state get_S_status(uint8_t * pwrgd, uint8_t * txl)
{
	uint8_t rawValue = 0;
	if(read_reg(0x12, &rawValue) != FUNC_PASS){
		return BAD_READ;
	}else{
		*pwrgd = (rawValue & 2) >> 1;
		*txl = rawValue & 1;
		return FUNC_PASS;
	}
}

// REGISTER 0x13:
// Check if Transmit Ready
ret_state get_S_TR(int * transmit)
{
	uint8_t rawValue = 0;
       	if(read_reg(0x13, &rawValue) != FUNC_PASS){
		return BAD_READ;
	}else{
		*transmit = rawValue & 1;
		return FUNC_PASS;
	}
}

// REGISTERS 0x14 through 0x19: (Buffer Registers)
// The following function will read the desired buffer quantity
ret_state get_S_buffer(int quantity, uint16_t * ptr)
{
	uint8_t rawValue1 = 0;
	uint8_t rawValue2 = 0;
	uint8_t address = 0;

	switch(quantity){
		case 0: // Buffer Count
			address = 0x18;
			break;
		case 1: // Buffer Underrun
			address = 0x14;
			break;
		case 2: // Buffer Overrun
			address = 0x16;
			break;
		default: return BAD_PARAM;
		}

	if(read_reg(address, &rawValue1) != FUNC_PASS){
		return BAD_READ;
	}else if(read_reg(address + 1, &rawValue2) != FUNC_PASS){
		return BAD_READ;
	}else{
		*ptr = append_bytes(rawValue1, rawValue2);
		return FUNC_PASS;
	}
}

// REGISTERS 0x1A through 0x29
// The following function collects housekeeping data for the s-band transmitter in an array
ret_state get_S_hk(float * array) // Array should contain 8 floats
{
	uint16_t val = 0;
	int16_t temp = 0;

	for(uint8_t address = 0x1A; address < 0x29; address = address + 2){
		uint8_t val1 = 0, val2 = 0;

		if(read_reg(address, &val1) != FUNC_PASS){
			printf("bad read %d\n", address);
			return BAD_READ;
		}else if(read_reg(1 + address, &val2) != FUNC_PASS){
			printf("bad second read %d\n", address);
			return BAD_READ;
		}else{
			val = append_bytes(val1, val2);		
			switch(address){
				case 0x1A:
					val &= 4095;
					array[0] = ((float)val*(7.0f/6144.0f));
					break;
				case 0x1C:
					val &= 4095;
					array[1] = (((float)val*3.0f/4096.0f)-0.5f)*100.0f;
					break;
				case 0x1E:
					array[2] = b_Temp(val);
					break;
				case 0x20:
					array[3] = b_Temp(val);
					break;
				case 0x22:
					temp = (int16_t)val;
			                array[4] = (float)temp*0.00004f; 
					break;
				case 0x24:
					val &= 8191;
               				array[5] = (float)val*0.004f;
					break;
				case 0x26:
					temp = (int16_t)val;
			                array[6] = (float)temp*0.00004f;
					break;
				case 0x28:
					val &= 8191;
			                array[7] = (float)val*0.004f;
					break;
			}
		}

	}
	return FUNC_PASS;
}