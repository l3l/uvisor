#include <iot-os.h>

static void svc_irq(uint32_t *args)
{
    uint8_t svcn = ((uint8_t*)args[6])[-2];

    dprintf("svcn=%i\r\n", svcn);
}

static void __attribute__((naked)) __svc_irq(void)
{
    asm volatile(
        "TST lr, #4\n"
        "ITE eq\n"
        "MRSEQ r0, MSP\n"
        "MRSNE r0, PSP\n"
        "B %0\n"
        ::"i"(svc_irq):"r0"
    );
}

void svc_init(void)
{
    /* register SVC call interface */
    ISR_SET(SVCall_IRQn, &__svc_irq);
    ISR_SET(PendSV_IRQn, &__svc_irq);
}
