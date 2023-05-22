
#ifndef __MEMUTIL__
#define __MEMUTIL__

#ifndef DELETE
#define DELETE(x) if ( x!= nullptr ) { delete x; x = nullptr; } 
#endif


#endif