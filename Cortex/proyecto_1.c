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

int main()
{
    void *virtual_base;
    int dev_mem = 0;
    volatile unsigned short *sdram_addr = NULL;

    if (assign_mem(&virtual_base, &dev_mem, &sdram_addr) != 0)
    {
        printf("Error during memory assignment.\n");
        return 1;
    }

    if (load_file(&sdram_addr))
    {
        printf("Error while loading the file.\n");
        return 1;
    }

    int size = sdram_addr[0] * sdram_addr[1];
    int info_offset = size * 2 + 2;
    int started = 0;

    sdram_addr[info_offset + 1] = 0;

    while (1)
    {
        if (sdram_addr[info_offset + 1] == 1) // Start
        {
            if (started == 0)
            {
                started = 1;
                printf("Started...");
                printf("Percentage Nios: %us, Cortex: %us", sdram_addr[info_offset], 100 - sdram_addr[info_offset]);
            }

            // PROCESAR SEGUN PORCENTAJE

            // continue;
        }
        else
        {
            started = 0;
        }

        usleep(1000);
    }

    clear_mem(&virtual_base, &dev_mem);

    return 0;
}
