/********************************************************************
 * File: symbols.c
 *
 * Symbols functions.  This file has functions for symbols mgmt
 *  (such as translating addresses to function names with 
 *  addr2line) and also connectivity matrix functions to keep
 *  the function call trace counts.
 *
 * Author: M. Tim Jones <mtj@mtjones.com>
 *
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "symbols.h"

func_t       functions[MAX_FUNCTIONS];
unsigned int totals[MAX_FUNCTIONS];
unsigned int calls[MAX_FUNCTIONS][MAX_FUNCTIONS];

/*char imageName[50];*/

void initSymbol(void )
{
  int from, to;

  for ( from = 0 ; from < MAX_FUNCTIONS ; from++ ) {

    functions[from].address = 0;
    functions[from].funcName[0] = 0;
    totals[from] = 0;

    for ( to = 0 ; to < MAX_FUNCTIONS ; to++ ) {

      calls[from][to] = 0;

    }

  }

  return;
}


int lookupSymbol( unsigned int address )
{
  int index;

  for (index = 0 ; index < MAX_FUNCTIONS ; index++) {

    if (functions[index].address == 0) break;

    if (functions[index].address == address) return index;

  }

  assert(0);

  return 0;
}


void addSymbol( unsigned int address , char *funcname)
{
  int index;

  for (index = 0 ; index < MAX_FUNCTIONS ; index++) {

    if (functions[index].address == address) return;

    if (functions[index].address == 0) break;

  }

  if (index < MAX_FUNCTIONS) {

    functions[index].address = address;

    strncpy(functions[index].funcName , funcname , MAX_FUNCTION_NAME+1);

  } else {

    assert( 0 );

  }

  return;
}


void addCallTrace( unsigned int fromaddr, unsigned int toaddr )
{

    calls[lookupSymbol(fromaddr)][lookupSymbol(toaddr)]++;

  return;
}


void emitSymbols( void )
{
  int from, to;
  FILE *fp;

  fp = fopen("full.graph", "w");
  if (fp == NULL) {
    printf("Couldn't open full.graph\n");
    exit(0);
  }

  fprintf(fp, "digraph fullgraph {\n");
  fprintf(fp, "node [ fontname=Helvetica, fontsize=12 ];\n");

  /* Identify node shapes */
  for (from = 0 ; from < MAX_FUNCTIONS ; from++) {

    if (functions[from].address == 0) break;

    for (to = 0 ; to < MAX_FUNCTIONS ; to++) {

      if (functions[to].address == 0) break;

      if (calls[from][to]) totals[from]++;

    }

    if (totals[from]) {

      fprintf( fp, "%s [shape=rectangle];\n", functions[from].funcName );

    } else {

      fprintf( fp, "%s [shape=ellipse];\n", functions[from].funcName );

    }

  }

  /* Emit call graph */
  for (from = 0 ; from < MAX_FUNCTIONS ; from++) {

    if (functions[from].address == 0) break;

    for (to = 0 ; to < MAX_FUNCTIONS ; to++) {

      if (calls[from][to]) {
        fprintf( fp, "%s -> %s [label=\"%d calls\"];\n", 
                  functions[from].funcName, functions[to].funcName,
                  calls[from][to] );
      }

      if (functions[to].address == 0) break;

    }

  }

  fprintf( fp, "\n}\n" );

  fclose(fp);

  return;
}

