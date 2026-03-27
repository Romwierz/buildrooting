// SCZR 2022 W 6, demo code by WZab
// Sources of the timer appplication
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "wzab_tim1.h"

#define CLR_BIT(wrd, bit) ((wrd) &= ~(1 << (bit)))
#define SET_BIT(wrd, bit) ((wrd) |= 1 << (bit))

int main(int argc, char *argv[])
{
    int i;
    int fd;
    WzTim1Regs * volatile regs;
    uint64_t res;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s sampling_period_[ns]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    uint64_t period=atoi(argv[1]);
    fd=open("/dev/my_tim0",O_RDWR);
    assert(fd>=0);
    regs=(WzTim1Regs *) mmap(0,0x1000,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    assert(regs != MAP_FAILED);
    //Check if the timer is available
    assert(regs->id == 0x7130900d);
    //There should start our code

    int stat_init_val = regs->stat;
    printf("Timer STAT init value: %x\n", stat_init_val);

    SET_BIT(regs->stat, 0);
    printf("Timer STAT after setting bit_0: 0x%016X\n\n", regs->stat);

    CLR_BIT(regs->stat, 0);
    printf("Timer STAT after clearing bit_0: 0x%016X\n\n", regs->stat);

    //End of our code
    munmap(regs,0x1000);
    close(fd);
}

