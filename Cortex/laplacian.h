#ifndef LAPLACE_H
#define LAPLACE_H

void laplacian_set_zeros(volatile unsigned short **sdram_addr);
void laplacian(volatile unsigned short **sdram_addr);

#endif