/********************************************************************
 * File: symbols.h
 *
 * Symbols types and prototypes file.
 *
 * Author: M. Tim Jones <mtj@mtjones.com>
 *
 */

#ifndef __SYMBOLS_H
#define __SYMBOLS_H

#define MAX_FUNCTIONS		5000
#define MAX_FUNCTION_NAME	50

typedef struct {
  unsigned int address;
  char funcName[MAX_FUNCTION_NAME+1];
} func_t;


void initSymbol( void);

int lookupSymbol( unsigned int address );

void addSymbol( unsigned int address , char *funcname);

void addCallTrace( unsigned int fromaddr, unsigned int toaddr );

void emitSymbols( void );

#endif /* __SYMBOLS_H */
