/*** USCI master library ************************************************************

 In this file the usage of the USCI I2C master library without DMA support is
 shown. This library uses pointers to specify what data is to be sent.

 When calling the TI_USCI_I2C_receive or TI_USCI_I2C_transmit routines
 the number of bytes, which are to be transmitted or received have to be passed as
 well as a pointer to a data field, that contains(or stores) the data.

 This code checks if there is a slave with address 0x50 is connected to the I2C
 bus and if the slave device is present, bytes are received and transmitted.

 Uli Kretzschmar
 MSP430 Systems
 Freising
 *******************************************************************************/
#include "msp430g2553.h"
#include "TI_USCI_I2C_master.h"
#include "uart.h"

#define I2C_prescale 0xb0
#define eepromArrdr 0x50

unsigned char timercounter;
unsigned char array[40] = { 0x00, 0x0,  0x1,  0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa,
		0xb };
unsigned char store[40] = { 0x0,  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

/* задержка */
void delay(unsigned int ms)
{
	int i;
	while(ms>0)
	{
		i = 500;
		while(i>0){i++;}
		ms--;
	}
}

void writeReg(char addr,char reg, char value)
{
  unsigned char regdata[2]={reg,value};
  TI_USCI_I2C_transmitinit(addr,I2C_prescale);
  TI_USCI_I2C_transmit(2,regdata);              // start transmitting
  while ( TI_USCI_I2C_notready() );
  return;
}


void main(void) {
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

	BCSCTL1 = CALBC1_8MHZ;      // Set DCO
	DCOCTL = CALDCO_8MHZ;

	P1DIR |=BIT0;
	P1OUT |=BIT0;

	uart_init();

	uart_putc(0x90);

	delay(1);

	_EINT();

	TI_USCI_I2C_transmitinit(eepromArrdr, I2C_prescale);  // init transmitting with USCI
	while (TI_USCI_I2C_notready());         // wait for bus to be free

	if (1 /*TI_USCI_I2C_slave_present(eepromArrdr) */)    // slave address may differ from
			{                                         // initialization
		uart_putc(0x91);

		delay(1);
//		 	 	 writeReg(eepromArrdr, 0x00, 0x00);//enable gyro
//		 	 	 writeReg(eepromArrdr, 0x01, 0x01);//enable gyro
//		 	 	 writeReg(eepromArrdr, 0x02, 0x02);//enable gyro
//		 	 	 writeReg(eepromArrdr, 0x03, 0x03);//enable gyro
//		 	 	 writeReg(eepromArrdr, 0x04, 0x04);//enable gyro
//
					while (TI_USCI_I2C_notready());         // wait for bus to be free
		//

				TI_USCI_I2C_transmitinit(eepromArrdr, I2C_prescale);  // init transmitting with
				while (TI_USCI_I2C_notready());         // wait for bus to be free
				TI_USCI_I2C_transmit(9, array);       // start transmitting
//
				while (TI_USCI_I2C_notready());         // wait for bus to be free
					delay(1);

				TI_USCI_I2C_transmitinit(eepromArrdr, I2C_prescale);  // init transmitting with
				while (TI_USCI_I2C_notready());         // wait for bus to be free
				TI_USCI_I2C_transmit(1, array);       // start transmitting
//
				delay(1);

				while (TI_USCI_I2C_notready());         // wait for bus to be free
	//
				TI_USCI_I2C_receiveinit(eepromArrdr, I2C_prescale);   // init receiving with USCI
//				while (TI_USCI_I2C_notready());         // wait for bus to be free
				TI_USCI_I2C_receive(7, store);
				while (TI_USCI_I2C_notready());         // wait for bus to be free

				P1OUT &=~BIT0;
	}






	uart_putc(store[0]);
	uart_putc(store[1]);
	uart_putc(store[2]);
	uart_putc(store[3]);
	uart_putc(store[4]);
	uart_putc(store[5]);

	uart_putc(0x92);

	while(1){
		;
	}



	LPM3;

}

