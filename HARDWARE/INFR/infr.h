#ifndef __INFR_H
#define __INFR_H	 
#include "sys.h"
#include "stdbool.h"

#define INFR0 PCin(0)   	//PC0
#define INFR1 PCin(1)   	//PC1

#define LEFT   0
#define RIGHT  1

void infr_init(void);//IO≥ı ºªØ
bool infr_check(u8 id);				    
#endif
