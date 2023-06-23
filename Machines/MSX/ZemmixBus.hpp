//
//  ZemmixBus.hpp
//  Clock Signal
//
//  Created by Miso Kim on 24/06/2023.
//  Copyright 2023 Miso Kim. All rights reserved.
//

#ifndef ZemmixBus_hpp
#define ZemmixBus_hpp

#include "MemorySlotHandler.hpp"
#include "zmx.h"
#include "zmxbus.h"

#define ZMX_DRIVER "./zmxdrive" ZEMMIX_EXT 
#define ZMX_PATH  "."

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace MSX {

class ZemmixBus: public MemorySlotHandler {
	public:
		ZemmixBus(MSX::MemorySlot &slot);
        void reset();
		void write(uint16_t address, uint8_t value, bool pc_is_outside_bios) final;
		uint8_t read(uint16_t address) final;
        void writeio(uint16_t port, uint8_t value) final;
        uint8_t readio(uint16_t port) final;
		void run_for(HalfCycles half_cycles) final;
    private:
        ReadfnPtr readmsx;
        WritefnPtr writemsx;
        InitfnPtr init;
        ResetfnPtr resetz;	
        void *hDLL = 0;
        char path[256];
        char zmxdriver[256];
};

}

#endif /* DiskROM_hpp */
