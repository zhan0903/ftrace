/********************************************************************
 * File: trace.c
 *
 * main function for the pvtrace utility.
 *
 * Author: M. Tim Jones <mtj@mtjones.com>
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "symbols.h"


int main( int argc, char *argv[] )
{
  FILE *tracef;
  char fromfunc[MAX_FUNCTION_NAME+1], tofunc[MAX_FUNCTION_NAME+1];
  unsigned int fromaddr, toaddr;


  if (argc != 2) {

    printf("Usage: pvtrace <tracefile> \n\n");
    exit(-1);

  }

  initSymbol( );

  tracef = fopen(argv[1], "r");

  if (tracef == NULL) {
    printf("Can't open %s\n",argv[1]);
    exit(-1);
  }

  while (!feof(tracef)) {

	memset(fromfunc,0,MAX_FUNCTION_NAME+1);
  	memset(tofunc,0,MAX_FUNCTION_NAME+1);
    fscanf( tracef, "%s <%x> <-%s <%x>\n",tofunc,&toaddr,fromfunc,&fromaddr);

      addSymbol( fromaddr , fromfunc);
      addSymbol( toaddr , tofunc );

      addCallTrace( fromaddr, toaddr );

  }

  emitSymbols();

  fclose( tracef );
  
  return 0;
}

