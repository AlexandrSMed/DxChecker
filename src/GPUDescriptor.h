#pragma once

#include <string>

namespace TDW {

	struct GPUDescriptor {
		std::string model;
		std::string vendor;
		std::string serial_num;
	};
}