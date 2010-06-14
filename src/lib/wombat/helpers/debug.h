/*
 * debug.h
 *
 *  Created on: 17.10.2009
 *      Author: bknopp
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdio.h>

#ifndef DEBUG
#define TRACE( x... )
#endif
#ifdef DEBUG
#define TRACE( x... ) {printf( "%s %s (%d) :", __FILE__, __FUNCTION__, __LINE__ ); printf( x ); printf("\n");}
#endif


#endif /* DEBUG_H_ */
