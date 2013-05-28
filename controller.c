/* 
 *	SOLAR-CONTROLLER
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <dirent.h>
#include <complex.h>
#include <stdbool.h>

int main(int argc, char ** argv) {
	//init DAC
	//install DAC module
	system("insmod i2cdev.ko");

	//init ADC
	//install ADC module
	system("insmod /lib/modules/3.2.33-psp26.1/kernel/drivers/input/touchscreen/ti_tscadc.ko");
	//Usage: cat /sys/devices/platform/omap/tsc/ain1

	//init GPIO
	//
	//export pin to userspace
	system("echo 23 > /sys/class/gpio/export");
	//Now, there is a /sys/class/gpio/gpio23 directory:
	//set direction of pin
	system("echo out > /sys/class/gpio/gpio23/direction");

	//To set the value of the GPIO output:
	//system("echo 1 > /sys/class/gpio/gpio23/value");

asd
asd
	// MAIN LOOP
	while (1) {
		/*
		 * Start
		 * Generate webpage and wait for user input
		 * If(test started from web interface)
		 * -Turn on halogen spots
		 * -wait x sec. for lights to stabilize
		 * -Setup DAC
		 *
		 * -while(test not over)
		 * ---Read ADC (volt & current on panels)
		 * ---Increase DAC
		 *
		 * -Turn of lights
		 * -Calculate MPP
		 * -Generate Test report/graphs
		 * -update webpage
		 * -wait for next test to start
		 */
	}
	return 0;
}

