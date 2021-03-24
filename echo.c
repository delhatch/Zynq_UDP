#include <stdio.h>
#include <string.h>

#include "lwip/err.h"
#include "lwip/udp.h"
#if defined (__arm__) || defined (__aarch64__)
#include "xil_printf.h"
#endif

// Include our own definitions
#include "includes.h"

// Global variables for data flow
extern volatile u8      IndArrDone;
extern volatile u32	EthBytesReceived;
int*			IndArrPtr;
extern volatile u8	SendResults;
extern volatile u8   	DMA_TX_Busy;
extern volatile u8	Error;

// Global Variables for Ethernet handling
extern u16_t    	RemotePort;
extern struct ip4_addr  	RemoteAddr;
extern struct udp_pcb 	send_pcb;

int transfer_data() {
	return 0;
}

/*
void print_app_header()
{
	xil_printf("\n\r\n\r-----lwIP TCP echo server ------\n\r");
	xil_printf("TCP packets sent to port 6001 will be echoed back\n\r");
}
*/

/* recv_callback: function that handles responding to UDP packets */
void recv_callback(void *arg, struct udp_pcb *upcb,
                              struct pbuf *p, struct ip4_addr *addr, u16_t port)
{

	// Set up a timeout counter and a status variable
	//int TimeOutCntr = 0;
	//int status = 0;

	/* Do not read the packet if we are not in ESTABLISHED state */
	if (!p) {
		udp_disconnect(upcb);
		return;
	}

	/* Assign the Remote IP:port from the callback on each first pulse */
	RemotePort = port;
	RemoteAddr = *addr;

	/* Keep track of the control block so we can send data back in the main while loop */
	send_pcb = *upcb;

	/********************** WAVE ARRAY ********************************/
	// Determine the number of bytes received and copy this segment to the temp array
	EthBytesReceived = p->len;
	xil_printf("Data len = %d \r\n", p->len );
	//memcpy(&WaveformArr[0], (u32*)p->payload, EthBytesReceived);

	/* free the received pbuf */
	pbuf_free(p);
	return;

}

/* start_application: function to set up UDP listener */
int start_application()
{
	struct udp_pcb *pcb;
	err_t err;
	unsigned port = FF_UDP_PORT;

	/* create new UDP PCB structure */
	pcb = udp_new();
	if (!pcb) {
		xil_printf("Error creating PCB. Out of Memory\n\r");
		return -1;
	}

	/* bind to specified @port */
	err = udp_bind(pcb, IP_ADDR_ANY, port);
	if (err != ERR_OK) {
		xil_printf("Unable to bind to port %d: err = %d\n\r", port, err);
		return -2;
	}

	/* specify callback to use for incoming connections */
	udp_recv(pcb, recv_callback, NULL);

	xil_printf("UDP echo server started @ port %d\n\r", port);

	return 0;
}
