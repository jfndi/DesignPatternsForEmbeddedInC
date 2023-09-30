#include <stdlib.h>
#include <stdio.h>

#include "MotorProxy.h"

int main(void)
{
	MotorProxy* me;
	unsigned int* DummyAddr;

	printf("---->> Creating the Motor Proxy.\n");
	me = MotorProxy_Create();

	printf("\t---->> Configuring the Device.\n");
	DummyAddr = (unsigned int*)malloc(sizeof(unsigned));
	MotorProxy_configure(me, 5, DummyAddr);

	printf("\t---->> Initializing the Device to a known state.\n");
	MotorProxy_initialize(me);

	printf("\t---->> Enabling the Device.\n");
	MotorProxy_enable(me);

	printf("\t\t---->> Set the Motor speed and direction.\n");
	MotorProxy_writeMotorSpeed(me, FORWARD, 15);

	printf("\t\t---->> Motor direction set to %d.\n",
		MotorProxy_accessMotorDirection(me));

	printf("----> Destroying the Motor Proxy.\n");
	MotorProxy_Destroy(me);

	return 0;
}