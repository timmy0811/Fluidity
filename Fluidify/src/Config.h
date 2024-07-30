#pragma once

#include <yaml-cpp/yaml.h>

#include "Log.h"

namespace FLD {
	class Config {
	private:
		const std::string m_Path;

	public:
		Config(const std::string& path)
			:m_Path(path)
		{
			Parse();
		}

		void Parse() {
			YAML::Node mainNode;

			try {
				mainNode = YAML::LoadFile(m_Path);
			}
			catch (...) {
				LOG_CORE_ERROR("Unable to open config file");
			}

			WIN_WIDTH = mainNode["Config"]["Application"]["WindowWidth"].as<unsigned int>();
			WIN_HEIGHT = mainNode["Config"]["Application"]["WindowHeight"].as<unsigned int>();
		}

		// Window
		unsigned int WIN_WIDTH = 0;
		unsigned int WIN_HEIGHT = 0;
	};

	extern Config conf;
}
