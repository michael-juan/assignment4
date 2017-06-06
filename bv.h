// bv.h — Bit Vector interface
// Author: Prof. Darrell Long

# ifndef _BVector
# define _BVector
# include <stdint.h>

typedef struct bitV {
	uint8_t *v;
	uint32_t l;
} bitV;

bitV *newVec(uint32_t);

void delVec(bitV *);

void oneVec(bitV *);

void setBit(bitV *, uint32_t);

void clrBit(bitV *, uint32_t);

uint8_t valBit(bitV *, uint32_t);

uint32_t lenVec(bitV *);

uint8_t checkBit(uint8_t, uint8_t *);

uint8_t getNextBit(uint8_t *, uint8_t);

# endif