#ifndef DEV_COMMANDS_H
#define DEV_COMMANDS_H

#define COMMAND_PING				0x0001
    //L: 0
    //D: []
    //Return the same

#define COMMAND_DEBUG_LED_OFF		0x0010
    //L: 0
    //D: [];
    //Turn off green LED

#define COMMAND_DEBUG_LED_ON		0x0011
    //L: 0
    //D: [];
    //Turn on green LED

// ***DEVICE CONTROL***

#define COMMAND_LEDS_DISABLE		0x0110
    //L: 0
    //D: [];
    //Disable and turn off all LEDs

#define COMMAND_LEDS_ENABLE			0x0111
    //L: 0
    //D: [];
    //Enable all LEDs

// ***TRIGGER SETTING***

#define COMMAND_TRIGGER_DISABLE		0x0210
    //L: 0
    //D: [];
    //Disable trigger generation in master mode

#define COMMAND_TRIGGER_ENABLE		0x0211
    //L: 0
    //D: [];
    //Enable trigger generation in master mode

#define COMMAND_TRIGGER_SET_SLAVE	0x0220
    //L: 0
    //D: [];
    //Set trigger to slave mode

#define COMMAND_TRIGGER_SET_MASTER	0x0221
    //L: 0
    //D: [];
    //Set trigger to master mode

#define COMMAND_TRIGGER_SET_PERIOD	0x0230
    //L: 1											L: 0
    //D: [Period_ticks]								D: []
    //Set trigger period for master mode in timer ticks

#define COMMAND_TRIGGER_SET_TINT	0x0240
    //L: 1											L: 0
    //D: [Tint_ticks]								D: []
    //Set integration time in timer ticks

#define COMMAND_SET_GAIN            0x0250
    //L: 1                                          L:0
    //D: [gain]                                     D: []

#define COMMAND_TRIGGER_SET_MASTER_DELAY	0x0260
    //L: 1											L: 0
    //D: [Tdelay_ticks]								D: []
    //Set trigger delay time in timer ticks for master mode.

#define COMMAND_TRIGGER_SET_SLAVE_DELAY		0x0270
    //L: 1											L: 0
    //D: [Tdelay_ticks]								D: []
    //Set trigger delay time in timer ticks for slave mode.


// ***DAQ CONTROL***

#define COMMAND_DAQ_DISABLE			0x0310
    //L: 0
    //D: [];
    //Disable sending data

#define COMMAND_DAQ_ENABLE			0x0311
    //L: 0
    //D: [];
    //Enable sending data

#define COMMAND_DAQ_RESET_COUNTERS	0x0321
    //L: 0
    //D: []
    //Reset synchronization counters

#define COMMAND_DAQ_FLUSH_DATA		0x0322
    //L: 0
    //D: []
    //Send all remaining data over data socket

#define COMMAND_DAQ_CONFIG_PEER		0x0331
    //L: 5											L: 0
    //D: [ip ip ip ip port]							D: []
    //Set connection settings (peer IP and port) for data transfer
    //Warning: IP is sent as 4 shorts with MSB=0!

// ***SLOW CONTROL***

#define COMMAND_SLOWCTRL_SNAPSHOT	0x0410
	//L: 0											L: 10
	//D:[]											D: [(Readout of 5 ADC channels as 32-bit integers)]
	//Slow control snapshot - read all channels of ADC

#define COMMAND_SET_CLUSTER_THRESHOLD 0x4001
    //L: ?
    //D: []
    //Send 8 bit beam cluster selection threshold

// ***DATA TRANSFER - SOCKET 1!!!!***

#define COMMAND_DATA_TRANSFER		0x8000
	//(no incoming packet)							L: 64*daq_dma_frame_bunch*daq_eth_frame_bunch
	//(no incoming packet)							D: [(Readout of 5 ADC channels as 32-bit integers)]
	//Slow control snapshot - read all channels of ADC



#endif // DEV_COMMANDS_H
