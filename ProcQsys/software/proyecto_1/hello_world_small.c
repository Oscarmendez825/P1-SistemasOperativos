#include "sys/alt_irq.h"

#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

#include "system.h"

static unsigned int key_d[4] = {0};
static unsigned int key_n[4] = {0};
static unsigned int n_value = 0;
static unsigned int d_value = 0;


void io_button_isr(void * context);
void io_button_setup();
void check_mode();
void update_key();
void update_seg7(unsigned int* value);
void process_pixel();
void rsa(int pixel);
int fast_modular_exponentiation(int base, int exponent, int modulus);

volatile int start;
volatile int mode;
volatile int key_select;
volatile int key_select_prev = 0;

volatile int edge_val;

static unsigned int count = 0;


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

	if (start == 0)		//key
	{
		if (edge_val != 0)
			update_key();
		else if (key_select != key_select_prev)
		{
			if (key_select == 0)
				update_seg7(key_n);
			else
				update_seg7(key_d);
		}

		key_select_prev = key_select;
	}
	else
	{
		n_value = key_n[3] * 4096 + key_n[2] * 256 + key_n[1] * 16 + key_n[0];
		d_value = key_d[3] * 4096 + key_d[2] * 256 + key_d[1] * 16 + key_d[0];

		if (mode == 0 && edge_val == 1) 	//manual
			process_pixel();
		else if (mode == 1)					//auto
			process_pixel();
	}

	edge_val = 0;
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
	{
		key_n[index] = (key_n[index] + 1) & 0xf;
		update_seg7(key_n);
	}
	else
	{
		key_d[index] = (key_d[index] + 1) & 0xf;
		update_seg7(key_d);
	}
}

void update_seg7(unsigned int* value)
{
	IOWR_ALTERA_AVALON_PIO_DATA(SEG7_0_BASE, value[0]);
	IOWR_ALTERA_AVALON_PIO_DATA(SEG7_1_BASE, value[1]);
	IOWR_ALTERA_AVALON_PIO_DATA(SEG7_2_BASE, value[2]);
	IOWR_ALTERA_AVALON_PIO_DATA(SEG7_3_BASE, value[3]);
}


void process_pixel()
{
	if (count >= RAM_0_SIZE_VALUE)
		return;

	int pixel = IORD_ALTERA_AVALON_PIO_DATA(SDRAM_BASE + count*4);
	rsa(pixel);

	count++;
}


void rsa(int pixel)
{
	int new_pixel = fast_modular_exponentiation(pixel, d_value, n_value);
	unsigned int value[4];
	value[0] = new_pixel % 10;
	value[1] = (new_pixel / 10) % 10;
	value[2] = (new_pixel / 100) % 10;
	value[3] = (new_pixel / 1000) % 10;
	update_seg7(value);
	// Actualizar el lugar donde se escribe
	//IOWR_ALTERA_AVALON_PIO_DATA(RAM_0_BASE + count, new_pixel);
}


int fast_modular_exponentiation(int base, int exponent, int modulus)
{
    int result = 1;
    base = base % modulus;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        base = (base*base) % modulus;
        exponent = exponent / 2;
    }
    return result;
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
	IOWR_ALTERA_AVALON_PIO_DATA(SDRAM_BASE, 143909726);
	IOWR_ALTERA_AVALON_PIO_DATA(SDRAM_BASE + 4, 12605018);
	IOWR_ALTERA_AVALON_PIO_DATA(SDRAM_BASE + 8, 229800739);
	IOWR_ALTERA_AVALON_PIO_DATA(SDRAM_BASE + 12, 41677818);

	io_button_setup();

	/* Event loop never exits. */
	while (1){
		check_mode();
	}

	return 0;
}
