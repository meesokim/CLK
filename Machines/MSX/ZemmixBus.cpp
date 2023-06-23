//
//  ZemmixBus.cpp
//  Clock Signal
//
//  Created by Miso Kim on 07/01/2018.
//  Copyright 2018 Miso Kim. All rights reserved.
//

#include "ZemmixBus.hpp"
#include <string.h>
using namespace MSX;

ZemmixBus::ZemmixBus(MSX::MemorySlot &slot) {
	reset();
}

void ZemmixBus::reset(void) {
	char *str = getenv("ZMX_DRIVER");
	strcpy(zmxdriver, str ? str : ZMX_DRIVER);
	str = getenv("ZMX_PATH");
	strcpy(path, str ? str : ZMX_PATH);	
    if (hDLL)
        CloseZemmix(hDLL);
    hDLL = OpenZemmix((char*)zmxdriver, RTLD_LAZY);
    if (!hDLL)
    {
        printf("DLL open error!! %s\n", zmxdriver);
        exit(1);
    }	
    readmsx = (ReadfnPtr)GetZemmixFunc(hDLL, (char*)MSXREAD);
    writemsx = (WritefnPtr)GetZemmixFunc(hDLL, (char*)MSXWRITE);
    init = (InitfnPtr)GetZemmixFunc(hDLL, (char*)MSXINIT);
    resetz = (ResetfnPtr)GetZemmixFunc(hDLL, (char*)MSXRESET);            
	init(path);
    resetz();	
}

void ZemmixBus::write(uint16_t address, uint8_t value, bool) {
	writemsx(WR_SLOT1, address, value);
}

uint8_t ZemmixBus::read(uint16_t address) {
	uint8_t b = 0xff;
	b = readmsx(RD_SLOT1, address);
	return b;
}

void ZemmixBus::writeio(uint16_t port, uint8_t value) {
	writemsx(WR_IO, port, value);
}

uint8_t ZemmixBus::readio(uint16_t port) {
    uint8_t b = 0xff;
	b = readmsx(RD_IO, port);
    return b;
}

void ZemmixBus::run_for(HalfCycles half_cycles) {
	// Input clock is going to be 7159090/2 Mhz, but the drive controller
	// needs an 8Mhz clock, so scale up. 8000000/7159090 simplifies to
	// 800000/715909.
}

