#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define HW_REGS_BASE (0xC0000000)
#define HW_REGS_SPAN (0x04000000)
#define HW_REGS_MASK (HW_REGS_SPAN - 1)
#define SDRAM_BASE 0x08000000

static int started = 0;

int assign_mem(void **virtual_base, int *dev_mem, volatile unsigned short **sdram_addr)
{
    // Open /dev/mem
    if ((*dev_mem = open("/dev/mem", (O_RDWR | O_SYNC))) == -1)
    {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return 1;
    }

    // get virtual addr that maps to physical
    *virtual_base = mmap(NULL, HW_REGS_SPAN, (PROT_READ | PROT_WRITE),
                         MAP_SHARED, *dev_mem, HW_REGS_BASE);
    if (*virtual_base == MAP_FAILED)
    {
        printf("ERROR: mmap() failed...\n");
        close(*dev_mem);
        return 1;
    }

    // Get the address that maps to the SD
    *sdram_addr = (unsigned short *)(*virtual_base + ((SDRAM_BASE) & (HW_REGS_MASK)));

    return 0;
}

int clear_mem(void **virtual_base, int *dev_mem)
{
    if (munmap(*virtual_base, HW_REGS_SPAN) != 0)
    {
        printf("ERROR: munmap() failed...\n");
        close(*dev_mem);
        return 1;
    }
    close(*dev_mem);
    return 0;
}

int load_file(volatile unsigned short **sdram_addr)
{
    FILE *file = fopen("images/5.txt", "r");

    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return 1;
    }

    int number;
    int count = 0;
    while (fscanf(file, "%d", &number) == 1)
    {
        (*sdram_addr)[count] = (unsigned short)number;
        count++;
    }

    fclose(file);
    return 0;
}

/*
void start(volatile unsigned short **sdram_addr, int offset)
{
    printf("Started...");
    printf("Percentage Nios: %us, Cortex: %us", (*sdram_addr)[offset], 100 - (*sdram_addr)[offset]);

    printf("Procesando...");

    printf("Finalizado.");
    (*sdram_addr)[offset] = (unsigned short)2;
}*/

int main()
{
    printf("asd2");
    void *virtual_base;
    int dev_mem = 0;
    volatile unsigned short *sdram_addr = NULL;

    printf("asd2");
    if (assign_mem(&virtual_base, &dev_mem, &sdram_addr) != 0)
    {
        printf("Error during memory assignment.\n");
        return 1;
    }

    printf("asd2");
    if (load_file(&sdram_addr))
    {
        printf("Error while loading the file.\n");
        return 1;
    }

    int size = sdram_addr[0] * sdram_addr[1];
    // int info_offset = size * 2 + 2;
    // unsigned short start_flag = 0;

    // sdram_addr[info_offset + 1] = 0;

    while (1)
    {
        printf("Cifrada: %u, %u, %u, %u\n", sdram_addr[0], sdram_addr[1], sdram_addr[2], sdram_addr[3]);
        printf("Cifrada: %u, %u, %u, %u\n", sdram_addr[size - 2], sdram_addr[size - 1], sdram_addr[size], sdram_addr[size + 1]);
        printf("Desc: %u, %u, %u, %u\n", sdram_addr[size + 2], sdram_addr[size + 3], sdram_addr[size + 4], sdram_addr[size + 5]);
        printf("Desc: %u, %u, %u, %u\n", sdram_addr[size * 2 - 2], sdram_addr[size * 2 - 1], sdram_addr[size * 2], sdram_addr[size * 2 + 1]);
        printf("Porcentaje: %u, \n", sdram_addr[size * 2 + 2]);
        printf("Flag: %u\n", sdram_addr[size * 2 + 3]);
        sleep(1);
    }

    clear_mem(&virtual_base, &dev_mem);

    return 0;
}
