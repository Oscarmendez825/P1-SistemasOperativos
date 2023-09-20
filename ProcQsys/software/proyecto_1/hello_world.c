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
void process_pixel();
void rsa(int pixel);
int fast_modular_exponentiation(int base, int exponent, int modulus);

volatile int start;
volatile int mode;

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

	if (start == 0)		//key
	{
		if (edge_val != 0)
			update_key();
	}
	else
	{
		n_value = key_n[3] * 4096 + key_n[2] * 256 + key_n[1] * 16 + key_n[0];
		d_value = key_d[3] * 4096 + key_d[2] * 256 + key_d[1] * 16 + key_d[0];

		if (mode == 0 && edge_val == 1) 	//manual
			process_pixel();
		else								//auto
			process_pixel();
	}

}

void update_key()
{
	//Reads the key mode from the switch: key n or key d
	unsigned int key_select = IORD_ALTERA_AVALON_PIO_DATA(KEY_SELECT_0_BASE);

	if (key_select == 0)
	{
		key_n[edge_val-1] = (key_n[edge_val-1] + 1) & 0xf;
		IOWR_ALTERA_AVALON_PIO_DATA(SEG7_0_BASE, key_n[0]);
		IOWR_ALTERA_AVALON_PIO_DATA(SEG7_1_BASE, key_n[1]);
		IOWR_ALTERA_AVALON_PIO_DATA(SEG7_2_BASE, key_n[2]);
		IOWR_ALTERA_AVALON_PIO_DATA(SEG7_3_BASE, key_n[3]);
	}
	else
	{
		key_d[edge_val-1] = (key_d[edge_val-1] + 1) & 0xf;
		IOWR_ALTERA_AVALON_PIO_DATA(SEG7_0_BASE, key_d[0]);
		IOWR_ALTERA_AVALON_PIO_DATA(SEG7_1_BASE, key_d[1]);
		IOWR_ALTERA_AVALON_PIO_DATA(SEG7_2_BASE, key_d[2]);
		IOWR_ALTERA_AVALON_PIO_DATA(SEG7_3_BASE, key_d[3]);
	}

	edge_val = 0;
}


void process_pixel()
{
	if (count >= RAM_0_SIZE_VALUE)
		return;

	int pixel = IORD_ALTERA_AVALON_PIO_DATA(RAM_0_BASE + count);
	rsa(pixel);

	count++;
}


void rsa(int pixel)
{
	int new_pixel = fast_modular_exponentiation(pixel, d_value, n_value);

	// Actualizar el lugar donde se escribe
	IOWR_ALTERA_AVALON_PIO_DATA(RAM_0_BASE + count, new_pixel);
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
	io_button_setup();

	/* Event loop never exits. */
	while (1){
		check_mode();
	}

	return 0;
}
