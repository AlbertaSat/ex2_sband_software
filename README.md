# S-band Equipment Handler
sTransmitter.c contains functions to access s-band transmitter functionality. These read and/or write each register outlined in the HSTXC-01-00090 User Manual.
These functions should be used elsewhere as needed to configure and get housekeeping 
data from the S-Band transmitter. Since we don't have the actual hardware, I2C and SPI communication has 
been mocked using CMock. Other simulated aspects include the register "memory" and the buffer, which stores data prior to transmission. There are functions to add and remove from this buffer. Though no data is actually stored, the buffer count, underrun, overrun, and status of the transmit ready line should be accurate.
Functions implemented here are also listed in the ["S-Band and 
UHF Functions List" spreadsheet](https://docs.google.com/spreadsheets/d/1zNhxhs0KJCp1187Vm3-zAzQHCY31f77l-0nlQmfXu1w/edit#gid=565953736) on the drive. Refer to that for details about input/output.

## Ceedling Build Instructions
First, [install Ceedling](https://github.com/ThrowTheSwitch/Ceedling). Then run:
```
git clone https://github.com/AlbertaSat/ex2_sband_software
cd ex2_sband_software/CommsSim
ceedling
```
The above instructions should run all unit tests of the S-band Transmitter Equipment Handler

