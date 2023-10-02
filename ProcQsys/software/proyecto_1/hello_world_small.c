#include "sys/alt_irq.h"

#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

#include "system.h"
#include <unistd.h>

static unsigned short key_d[4] = {15, 5, 6, 0};
static unsigned short key_n[4] = {11, 4, 7, 1};
static unsigned short n_value = 0;
static unsigned short d_value = 0;
static unsigned short percentage[4] = {0, 5, 0, 0};
static unsigned int percentage_value = 50;
static unsigned int limit = 0;


void io_button_isr(void * context);
void io_button_setup();
void check_mode();
void update_key();
void update_seg7(unsigned short* value);
void process_pixel();
void rsa();
unsigned short fast_modular_exponentiation(unsigned short exponent, unsigned short modulus);
void update_percentage();

volatile int start;
volatile int mode;
volatile int key_select;
volatile int percent;

volatile int edge_val;
volatile int image_size;
volatile unsigned short pixel = 0;

static unsigned int count = 0;
static unsigned int started = 0;


/**
 * @brief Responsible for handling the timer counter and timer interrupts with its modes
 *
 * @param context
 */
void timer_irs(void *context)
{
	(void)context;


	//Sets the value to be decoded to show in the display.


}


void check_mode()
{
	start = IORD_ALTERA_AVALON_PIO_DATA(START_BASE);

	//Reads the mode from the switch: auto / manual
	mode = IORD_ALTERA_AVALON_PIO_DATA(MODE_0_BASE);

	//Reads the key mode from the switch: key n or key d
	key_select = IORD_ALTERA_AVALON_PIO_DATA(KEY_SELECT_0_BASE);

	//Reads the key mode from the switch: key n or key d
	percent = IORD_ALTERA_AVALON_PIO_DATA(PERCENT_BASE);

	if (start == 0)		//key
	{
		started = 0;
		count = 0;

		if (percent == 1)
		{
			if (edge_val != 0)
			{
				update_percentage();
				edge_val = 0;
			}
			update_seg7(percentage);
			return;
		}

		if (edge_val != 0)
		{
			update_key();
			edge_val = 0;
		}
		if (key_select == 0)
			update_seg7(key_n);
		else
			update_seg7(key_d);
	}
	else
	{
		if (started == 0)
		{
			started = 1;

			n_value = key_n[3] * 4096 + key_n[2] * 256 + key_n[1] * 16 + key_n[0];
			d_value = key_d[3] * 4096 + key_d[2] * 256 + key_d[1] * 16 + key_d[0];

			percentage_value = percentage[2] * 100 + percentage[1] * 10 + percentage[0];

			limit = (unsigned int)(image_size*2*(float)percentage_value/100.0f);

			// Gets the image size from SD
			unsigned short width = IORD_16DIRECT(SDRAM_BASE, 0);
			unsigned short height = IORD_16DIRECT(SDRAM_BASE, 2);
			image_size = (int)(width * height);

			// Stores the percentage
			IOWR_16DIRECT(SDRAM_BASE, image_size*4 + 4, (unsigned short)percentage_value);
			IOWR_16DIRECT(SDRAM_BASE, image_size*4 + 6, (unsigned short)image_size);
		}


		if (mode == 0 && edge_val == 1 && count < image_size) 	//manual
		{
			process_pixel();
			edge_val = 0;
		}
		else if (mode == 1) 									//auto
		{
			//IOWR_16DIRECT(SDRAM_BASE, image_size*4 + 6, (unsigned short)1);
			while(mode == 1 && start == 1 && count < image_size)
				process_pixel();
		}

		unsigned short value[4];
		value[0] = pixel % 10;
		value[1] = (pixel / 10) % 10;
		value[2] = (pixel / 100) % 10;
		value[3] = (pixel / 1000) % 10;
		update_seg7(value);

		if (count == image_size)
			IOWR_16DIRECT(SDRAM_BASE, image_size*4 + 6, (unsigned short)1);

	}

}

void update_percentage()
{
	unsigned int index = 2;
	percentage_value = percentage[2] * 100 + percentage[1] * 10 + percentage[0];

	if (edge_val == 1)		//0x1
		index = 0;
	else if (edge_val == 2)	//0x10
		index = 1;

	if (index == 0)
	{
		if (percentage_value == 100)
			percentage_value = 0;
		else
			percentage_value++;
	}
	else if (index == 1)
	{
		if (percentage_value + 10 > 100)
			percentage_value = 0;
		else
			percentage_value += 10;
	}


	percentage[0] = percentage_value % 10;
	percentage[1] = (percentage_value / 10) % 10;
	percentage[2] = (percentage_value / 100) % 10;
}

void update_key()
{
	unsigned int index = 0;

	if (edge_val == 1)		//0x1
		index = 0;
	else if (edge_val == 2)	//0x10
		index = 1;
	else if (edge_val == 4) //0x100
		index = 2;
	else if (edge_val == 8)	//0x1000
		index = 3;

	if (key_select == 0)
		key_n[index] = (key_n[index] + 1) & 0xf;
	else
		key_d[index] = (key_d[index] + 1) & 0xf;
}

void update_seg7(unsigned short* value)
{
	IOWR_ALTERA_AVALON_PIO_DATA(SEG7_0_BASE, value[0]);
	IOWR_ALTERA_AVALON_PIO_DATA(SEG7_1_BASE, value[1]);
	IOWR_ALTERA_AVALON_PIO_DATA(SEG7_2_BASE, value[2]);
	IOWR_ALTERA_AVALON_PIO_DATA(SEG7_3_BASE, value[3]);
}


void process_pixel()
{
	pixel = IORD_16DIRECT(SDRAM_BASE, count*2 + 4);
	rsa();

	count++;
}


void rsa()
{
	pixel = fast_modular_exponentiation(d_value, n_value);
	IOWR_16DIRECT(SDRAM_BASE, image_size*2 + count*2 + 4, pixel);
}


unsigned short fast_modular_exponentiation(unsigned short exponent, unsigned short modulus)
{
	unsigned short result = 1;
	pixel = pixel % modulus;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * pixel) % modulus;
        pixel = (pixel*pixel) % modulus;
        exponent = exponent / 2;
    }
    return result;
}


void laplace()
{
	return;
}


/**
 * @brief Configure the necessary for button interruptions
 *
 */
void io_button_setup(void){
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTONS_0_BASE, 0xF);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_0_BASE, 0x0);
	void * edge_val_ptr;
	edge_val_ptr = (void *) &edge_val;
	alt_ic_isr_register(BUTTONS_0_IRQ_INTERRUPT_CONTROLLER_ID,
						BUTTONS_0_IRQ,
						io_button_isr,
						edge_val_ptr,
						0x00);
}

/**
 * @brief Handles button interrupts and resets its state
 *
 * @param context
 */
void io_button_isr(void * context){
	volatile int * edge_ptr;
	edge_ptr = (volatile int *) context;
	*edge_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_0_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_0_BASE, 0);
}


/**
 * @brief Main function in charge of calling and executing the complete program
 *
 * @return int
 */
int main()
{
	edge_val = 0;

	io_button_setup();

	/* Event loop never exits. */
	while (1){
		check_mode();
	}

	return 0;
}
