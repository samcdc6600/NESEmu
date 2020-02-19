#ifndef CPU_HPP_
#define CPU_HPP_


#include "mem.hpp"


void cpu();
#ifdef DEBUG
memory::address getCurrentPC();
#endif


#endif
