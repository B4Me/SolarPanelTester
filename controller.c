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

#define 	MAX_GATE_SUPPLY		3.29
#define 	MIN_GATE_SUPPLY		2.00

#define array_size  (int)((MAX_GATE_SUPPLY - MIN_GATE_SUPPLY) / 0.01)

#define 	SWEEP_DELAY_MS		5

FILE* file;
int adc0_value, adc1_value, adc2_value, adc4_value, adc6_value;

int I_V_array[2][array_size];
int array_index = 0;

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
		 * -read initials
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

		printf("Read initial values. \n");
		file = fopen("/sys/devices/platform/omap/tsc/ain1", "r");
		fscanf(file, "%d", &adc0_value);
		fclose(file);
		fprintf(stdout, "Iref adc reading: %d\n", adc0_value);

		file = fopen("/sys/devices/platform/omap/tsc/ain2", "r");
		fscanf(file, "%d", &adc1_value);
		fclose(file);
		fprintf(stdout, "Vref adc reading: %d\n", adc1_value);

		file = fopen("/sys/devices/platform/omap/tsc/ain3", "r");
		fscanf(file, "%d", &adc2_value);
		fclose(file);
		fprintf(stdout, "IOUT offset adc reading: %d\n", adc2_value);

		file = fopen("/sys/devices/platform/omap/tsc/ain5", "r");
		fscanf(file, "%d", &adc4_value);
		fclose(file);
		fprintf(stdout, "VOUT adc reading: %d\n", adc4_value);

		file = fopen("/sys/devices/platform/omap/tsc/ain7", "r");
		fscanf(file, "%d", &adc6_value);
		fclose(file);
		fprintf(stdout, "IOUT adc reading: %d\n", adc6_value);

		printf("Test loop... \n");
		array_index = 0;	//reset index
		for (DAC_value = MIN_GATE_SUPPLY; DAC_value < MAX_GATE_SUPPLY;
				DAC_value += 0.01) {
			//write to DAC

			file = fopen("/dev/dac", "w");
			fprintf(file, "%4.2fv", DAC_value);
			fclose(file);
			printf("DAC value:%4.2fv\n", DAC_value);
			//wait xx ms
			sleep_ms(SWEEP_DELAY_MS);
			//read ADC's
			file = fopen("/sys/devices/platform/omap/tsc/ain5", "r");
			fscanf(file, "%d", &adc4_value);
			fclose(file);
			fprintf(stdout, "VOUT adc reading: %d\n", adc4_value);
			file = fopen("/sys/devices/platform/omap/tsc/ain7", "r");
			fscanf(file, "%d", &adc6_value);
			fclose(file);
			fprintf(stdout, "IOUT adc reading: %d\n", adc6_value);
			I_V_array[1][array_index] = adc4_value;
			I_V_array[2][array_index] = adc6_value;
			array_index++;
		}

		//turn off DAC
		DAC_value = 0;
		file = fopen("/dev/dac", "w");
		fprintf(file, "%4.2fv", DAC_value);
		fclose(file);
		printf("DAC value:%4.2fv\n", DAC_value);

		printf("Turn lights off. \n");
		//system("echo 0 > /sys/class/gpio/gpio23/value");
		printf("Calculate MPP. \n");
		printf("Generate Test report/graphs. \n");
		printf("update webpage. \n");
		printf("wait for next test to start. \n");
		sleep(4);
		for (array_index = 0; array_index < array_size; array_index++) {
			printf("V:%d - I%d \n", I_V_array[1][array_index],
					I_V_array[2][array_index]);
		}
		sleep(4);
	}
	return 0;
}

void sleep_ms(int ms) {
	usleep(ms * 1000); //convert to microseconds
	return;
}
