#include "pch.h"
#include "Helpers.h"

#include "Logger.h"
#include "Keys.h"

namespace toad 
{
	bool window_is_focused(const HWND& window)
	{
		return GetForegroundWindow() == window;
	}

bool map_hotkeys(const std::vector<std::string>& hotkeys, std::vector<int>& mapped)
{
	// Minecraft encode les boutons souris en codes négatifs : -100 + index_bouton
	// index_bouton : 0=gauche, 1=droit, 2=molette, 3=mouse4 (arrière), 4=mouse5 (avant)
	static const int mouse_button_to_vk[] = { VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2 };

	for (int i = 0; i < hotkeys.size(); i++)
	{
		const std::string& hotkey = hotkeys[i];
		int keycode = -1;

		try
		{
			keycode = std::stoi(hotkey);
		}
		catch (std::exception& e)
		{
			LOG_ERRORF("[map_hotkeys] %s", e.what());
			mapped.push_back(-1); // garde l'alignement même si la touche n'a pas pu être lue
			continue;
		}

		if (keycode <= -96 && keycode >= -100)
		{
			// c'est un bouton souris, pas une touche clavier
			int button_index = keycode + 100;
			mapped.push_back(mouse_button_to_vk[button_index]);
			continue;
		}

		auto it = mc_as_vkc.find(keycode);
		mapped.push_back(it != mc_as_vkc.end() ? it->second : -1); // toujours push, même si pas trouvé, pour garder l'alignement
	}

	return true;
}


	std::vector<std::string> get_all_files_ext(const std::filesystem::path& path, const char* ext, const bool includeExt)
	{
		std::vector <std::string> vec = {};
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			if (entry.path().extension() == ext)
				includeExt ? vec.push_back(entry.path().stem().string() + ext) : vec.push_back(entry.path().stem().string());
		}
		return vec;
	}

	std::filesystem::path get_exe_path()
	{
		char path[MAX_PATH];
		GetModuleFileNameA(NULL, path, MAX_PATH);
		return path;
	}

	std::string get_date_str(std::string_view format)
	{
		std::ostringstream ss;
		std::string time;

		auto t = std::time(nullptr);
		tm newtime{};

		localtime_s(&newtime, &t);

		ss << std::put_time(&newtime, format.data());
		return ss.str();
	}

	float random_float(float min, float max)
	{
		std::uniform_real_distribution<float> dis(min, max);
		return dis(gen);
	}

	int random_int(int min, int max)
	{
		std::uniform_int_distribution<int> dis(min, max);
		return dis(gen);
	}

	void precise_sleep(double seconds)
	{
		static double estimate = 0.005;
		static double mean = 0.005;
		static double m2 = 0;
		static int64_t count = 1;

		while (seconds > estimate) {
			auto start = std::chrono::high_resolution_clock::now();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			auto end = std::chrono::high_resolution_clock::now();

			double observed = (end - start).count() / 1e9;
			seconds -= observed;

			++count;
			double delta = observed - mean;
			mean += delta / count;
			m2 += delta * (observed - mean);
			double stddev = sqrt(m2 / (count - 1));
			estimate = mean + stddev;
		}

		// spin lock
		auto start = std::chrono::high_resolution_clock::now();
		while ((std::chrono::high_resolution_clock::now() - start).count() / 1e9 < seconds);
	}

}
