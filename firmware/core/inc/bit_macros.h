#ifndef BIT_MACROS_H
#define BIT_MACROS_H

#include <stdint.h>

#define BIT(n)                              (1UL << (n))

#define SET_BIT(register, n)                ((register) |= (BIT(n)))

#define CLEAR_BIT(register, n)              ((register) &= (~(BIT(n))))

#define TOOGLE_BIT(register, n)             ((register) ^= (BIT(n)))
#define TOGGLE_BIT(register, n)             ((register) ^= (BIT(n)))

#define READ_BIT(register, n)               (((register) >> (n)) & 1UL)

#define CHECK_BIT(register, n)              ((register) & BIT(n))

#define WRITE_BIT(register, n, val)         ((val) ? SET_BIT(register, n) : CLEAR_BIT(register, n))

#define MODIFY_REG(register, clearmask, setmask) \
    ((register) = (((register) & ~(clearmask)) | (setmask)))

#endif /* BIT_MACROS_H */