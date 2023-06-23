//
//  Target.hpp
//  Clock Signal
//
//  Created by Thomas Harte on 02/04/2018.
//  Copyright 2018 Thomas Harte. All rights reserved.
//

#ifndef Analyser_Static_MSX_Target_h
#define Analyser_Static_MSX_Target_h

#include "../../../Reflection/Enum.hpp"
#include "../../../Reflection/Struct.hpp"
#include "../StaticAnalyser.hpp"
#include <string>

namespace Analyser::Static::MSX {

struct Target: public ::Analyser::Static::Target, public Reflection::StructImpl<Target> {
	bool has_disk_drive = false;
	bool has_msx_music = true;
	std::string loading_command;

	ReflectableEnum(Model,
		MSX1,
		MSX2
	);
	Model model = Model::MSX2;

	ReflectableEnum(Region,
		Japan,
		USA,
		Europe,
		Korea
	);
	Region region = Region::USA;

	ReflectableEnum(Slot,
		None,
		Slot1,
		Slot2
	);

	Slot slot = Slot::None;

	Target(): Analyser::Static::Target(Machine::MSX) {
		if(needs_declare()) {
			DeclareField(has_disk_drive);
			DeclareField(has_msx_music);
			DeclareField(region);
			AnnounceEnum(Region);
			DeclareField(model);
			AnnounceEnum(Model);
			DeclareField(slot);
			AnnounceEnum(Slot);
		}
	}
};

}

#endif /* Analyser_Static_MSX_Target_h */
