#include "sys/alt_irq.h"

#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include "alt_types.h"

#include "system.h"
#include <unistd.h>

static unsigned short key_d[4] = {5, 5, 11, 5};
static unsigned short key_n[4] = {5, 5, 10, 14};
static unsigned short n_value = 0;
static unsigned short d_value = 0;
static unsigned short percentage[4] = {0, 5, 0, 0};
static unsigned int percentage_value = 50;
static unsigned int limit = 0;
static unsigned short seconds = 0;
static unsigned int pressed = 0;
static unsigned short width;
static unsigned short height;

void io_button_isr(void * context);
void io_button_setup();
void timer_setup();
void timer_irs(void *context);
void loop();
void update_key();
void update_seg7(unsigned short* value);
void process_pixel();
void rsa();
unsigned short fast_modular_exponentiation(unsigned short exponent, unsigned short modulus);
void update_percentage();
void laplacian();

volatile int start;
volatile int mode;
volatile int key_select;
volatile int percent;

volatile int edge_val;
volatile int image_size;
volatile unsigned short pixel = 0;
volatile unsigned short flag = 0;

static unsigned int count = 0;
static unsigned int started = 0;



void loop()
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
		seconds = 0;
		pixel = 0;

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
		if (started == 2)  // Finished
			return;

		if (started == 0)
		{
			started = 1;

			n_value = key_n[3] * 4096 + key_n[2] * 256 + key_n[1] * 16 + key_n[0];
			d_value = key_d[3] * 4096 + key_d[2] * 256 + key_d[1] * 16 + key_d[0];

			percentage_value = percentage[2] * 100 + percentage[1] * 10 + percentage[0];

			// Gets the image size from SD
			width = IORD_16DIRECT(SDRAM_BASE, 0);
			height = IORD_16DIRECT(SDRAM_BASE, 2);
			image_size = (int)(width * height);

			// Stores the percentage
			IOWR_16DIRECT(SDRAM_BASE, image_size*4 + 4, (unsigned short)percentage_value);
		}


		if ((IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_0_BASE) & 0x1) == 0)
		{
			if (pressed <= 20000)
				pressed++;
		}
		else
			pressed = 0;

		if (mode == 0 && (edge_val == 1 || pressed >= 20000 )
				&& count < image_size) 	//manual
		{
			process_pixel();
			edge_val = 0;
		}
		else if (mode == 1) 									//auto
		{
			unsigned short message[4] = {0, 12, 14, 13};
			update_seg7(message);
			while(mode == 1 && start == 1 && count < image_size)
			{
				start = IORD_ALTERA_AVALON_PIO_DATA(START_BASE);
				mode = IORD_ALTERA_AVALON_PIO_DATA(MODE_0_BASE);
				process_pixel();
			}
		}

		unsigned short value[4] = {0};
		value[0] = pixel % 10;
		value[1] = (pixel / 10) % 10;
		value[2] = (pixel / 100) % 10;
		value[3] = (pixel / 1000) % 10;
		update_seg7(value);

		if (count == image_size)
		{
			// Signal decoding finished
			IOWR_16DIRECT(SDRAM_BASE, image_size*4 + 6, (unsigned short)1);
			count++;
		}

		flag = IORD_16DIRECT(SDRAM_BASE, image_size*4 + 6);

		if (flag == (unsigned short)2 && started == 1)
		{
			// When the space in memory is ready, signals the beginning of laplacian filter
			IOWR_16DIRECT(SDRAM_BASE, image_size*4 + 6, (unsigned short)3);
			unsigned short message[4] = {1, 15, 0, 0};
			update_seg7(message);
			laplacian();
		}

		if (flag == (unsigned short)4 && started == 1)
		{
			// When both sides finished the laplacian filter, signals to store the result files
			IOWR_16DIRECT(SDRAM_BASE, image_size*4 + 6, (unsigned short)5);
			started = 2;
			value[0] = seconds % 10;
			value[1] = (seconds / 10) % 10;
			value[2] = (seconds / 100) % 10;
			value[3] = (seconds / 1000) % 10;
			update_seg7(value);
		}

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

	// Modular exponentiation
	unsigned int base = (int)pixel;
	unsigned int modulus = (int)n_value;
	unsigned int exponent = (int)d_value;
	unsigned int result = 1;

	base = base % modulus;
	while (exponent > 0)
	{
		if (exponent % 2 == 1)
			result = (result * base) % modulus;
		base = (base*base) % modulus;
		exponent = exponent / 2;
	}

	pixel = (unsigned short)result;
	IOWR_16DIRECT(SDRAM_BASE, image_size*2 + count*2 + 4, pixel);

	count++;
}


void laplacian()
{
	if (percentage_value == 0)
		return;

	int base_offset = (width * height) + 2;
	int result_offset = 2;

	// Definimos la máscara del filtro laplaciano
	int mask[3][3] = {
		{-1, -1, -1},
		{-1, 8, -1},
		{-1, -1, -1}};

	// Iteramos a través de la imagen
	for (int y = 1; y < height*percentage_value/100 - 1; y++)
	{
		// Excluimos los bordes de la imagen
		for (int x = 1; x < width - 1; x++)
		{
			// Excluimos los bordes de la imagen
			int total = 0;

			// Aplicamos la máscara del filtro laplaciano
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					//int pixel_laplace = (*sdram_addr)[(y + i) * width + (x + j) + base_offset];
					int pixel_laplace = IORD_16DIRECT(SDRAM_BASE, ((y + i) * width + (x + j) + base_offset)*2);
					int mask_value = mask[i + 1][j + 1];
					total += pixel_laplace * mask_value;
				}
			}

			// Almacenamos el valor resultante en el arreglo de resultado
			if (total < 0)
				total = 0;
			else if (total > 255)
				total = 255;
			//(*sdram_addr)[y * width + x + result_offset] = (unsigned short)total;
			IOWR_16DIRECT(SDRAM_BASE, (y * width + x + result_offset)*2, (unsigned short)total);
		}
	}
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


void timer_setup()
{
	alt_ic_isr_register(
			TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID,
			TIMER_0_IRQ,
			timer_irs,
			NULL,
			NULL);

	IOWR_ALTERA_AVALON_TIMER_CONTROL(
			TIMER_0_BASE,
			ALTERA_AVALON_TIMER_CONTROL_ITO_MSK | ALTERA_AVALON_TIMER_CONTROL_CONT_MSK);
}


/**
 * @brief Responsible for handling the timer counter and timer interrupts with its modes
 *
 * @param context
 */
void timer_irs(void *context)
{
	(void)context;

	if (started == 1)
		seconds++;

	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
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
	timer_setup();

	/* Event loop never exits. */
	while (1){
		loop();
	}

	return 0;
}
