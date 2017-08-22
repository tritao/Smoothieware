typedef enum {
    RxIrq,
    TxIrq
} SerialIrq;

typedef int serial_t;

#define serial_irq_set(a, b, c)