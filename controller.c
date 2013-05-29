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
#include <sys/wait.h>

#define 	MAX_GATE_SUPPLY		3.30
#define 	MIN_GATE_SUPPLY		0.00

FILE* file;
int adc_value;
float DAC_value = 0.0;

void sleep_ms();

int main(int argc, char ** argv) {
	//init DAC
	//install DAC module
	system("insmod i2cdev.ko");

	//init ADC
	//install ADC module
	system(
			"insmod /lib/modules/3.2.33-psp26.1/kernel/drivers/input/touchscreen/ti_tscadc.ko");
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

	//init WT ?
	//

	printf("init done. \n");

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
		 * -Turn lights off
		 * -Calculate MPP
		 * -Generate Test report/graphs
		 * -update webpage
		 * -wait for next test to start
		 */

		printf("Start. \n");
		printf("Generate webpage and wait for user input. \n");
		printf("Turn on halogen spots. \n");
		//system("echo 1 > /sys/class/gpio/gpio23/value");
		
		printf("wait x sec. for lights to stabilize. \n");
		printf("Setup DAC. \n");
		printf("Test loop... \n");
		for (DAC_value = MIN_GATE_SUPPLY; DAC_value <= MAX_GATE_SUPPLY; DAC_value +=
				0.01) {
			//write to DAC

			file = fopen("/dev/dac", "w");
			fprintf(file, "%4.2fv", DAC_value);
			fclose(file);
			printf("DAC value:%4.2fv\n", DAC_value);
			//wait xx ms
			sleep_ms(50);
			//read ADC's
			file = fopen("/sys/devices/platform/omap/tsc/ain1", "r");
			fscanf(file, "%d", &adc_value);
			fclose(file);
			fprintf(stdout, "adc reading: %d\n",adc_value);

		}
		printf("Turn lights off. \n");
		//system("echo 0 > /sys/class/gpio/gpio23/value");
		printf("Calculate MPP. \n");
		printf("Generate Test report/graphs. \n");
		printf("update webpage. \n");
		printf("wait for next test to start. \n");
		sleep(1);
	}
	return 0;
}

void sleep_ms(int ms) {
	usleep(ms * 1000); //convert to microseconds
	return;
}
