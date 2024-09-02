#pragma once

#include <yaml-cpp/yaml.h>

#include "Log.h"
#include "Core.h"

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

				WIN_WIDTH = mainNode["Config"]["Application"]["WindowWidth"].as<unsigned int>();
				WIN_HEIGHT = mainNode["Config"]["Application"]["WindowHeight"].as<unsigned int>();
				UPDATE_FRAMERATE = mainNode["Config"]["Application"]["UpdateTimerFramerate"].as<int>();

				SIM_RES = mainNode["Config"]["Simulation"]["Resolution"].as<int>();
				// SIM_RES_Y = mainNode["Config"]["Simulation"]["ResolutionY"].as<int>();
			}
			catch (...) {
				LOG_CORE_ERROR("Unable to parse config file");
				FLUIDIFY_CORE_ASSERT(true, "");

				exit(1);
			}
		}

		// Window
		unsigned int WIN_WIDTH = 800;
		unsigned int WIN_HEIGHT = 600;

		int UPDATE_FRAMERATE = 16;

		int SIM_RES = 64;
		//int SIM_RES_Y = 64;
	};

	extern Config conf;
}
