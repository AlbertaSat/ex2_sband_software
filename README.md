# This Repo is for Configuring and Simulating Ex-Alta 2's S-Band Transmitter
sTransmitter.c contains functions to access s-band transmitter functionality. These read and/or write each register outlined in the HSTXC-01-00090 User Manual.
These functions should be used elsewhere as needed to configure and get housekeeping 
data from the S-Band transmitter. Since we don't have the actual hardware, i2c and spi communication has 
to be mocked using CMock. Other simulated aspects include the register "memory" and the buffer, which stores data prior to transmission. There are functions to add and remove from this buffer. Though no data is actually stored, the buffer count, underrun, overrun, and status of the transmit ready line should be accurate.
Refer to the [User Manual](https://drive.google.com/drive/u/1/search?q=s-band%20user%20manual) for more details or the "Simulate an S-Band transmitter" [task in clickup.](https://app.clickup.com/t/6pbzd9) Functions are listed in the ["S-Band and 
UHF Functions List" spreadsheet](https://docs.google.com/spreadsheets/d/1zNhxhs0KJCp1187Vm3-zAzQHCY31f77l-0nlQmfXu1w/edit#gid=565953736) on the drive. Refer to that for details about input/output.

Test contains the ceedling test file.
