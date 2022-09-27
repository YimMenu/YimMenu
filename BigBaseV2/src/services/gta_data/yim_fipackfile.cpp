#include "yim_fipackfile.hpp"
#include "pointers.hpp"
#include "gta/fidevice.hpp"
#include "script.hpp"

namespace big
{
	yim_fipackfile::yim_fipackfile(rage::fiPackfile* rpf, const std::string& mount_name)
	{
		this->rpf = rpf;
		this->mount_name = mount_name;
	}

	static std::vector<std::string> get_non_dlc_mounted_devices_names()
	{
		std::vector<std::string> non_dlc_mounted_devices_names;

		uint16_t mounted_devices_len = *g_pointers->m_fidevices_len;
		if (mounted_devices_len)
		{
			auto devices_arr = *(uint64_t*)g_pointers->m_fidevices;
			uint8_t** current_device_mount_name_ptr = *(unsigned __int8***)g_pointers->m_fidevices;
			auto device_i = 0;

			while (true)
			{
				non_dlc_mounted_devices_names.push_back(*(const char**)current_device_mount_name_ptr);

				++device_i;
				current_device_mount_name_ptr += 4;
				if (device_i >= mounted_devices_len)
					break;
			}
		}

		return non_dlc_mounted_devices_names;
	}

	static int ends_with(const char* str, const char* suffix)
	{
		if (!str || !suffix)
			return 0;
		size_t lenstr = strlen(str);
		size_t lensuffix = strlen(suffix);
		if (lensuffix > lenstr)
			return 0;
		return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
	}

	void yim_fipackfile::for_each_fipackfile(std::function<size_t(yim_fipackfile& rpf_wrapper)> cb)
	{
		// the idea is to reuse existing mount points as much as possible because
		// even when mounting / unmounting properly you'll get file errors
		// and crashes if the rpf file was already mounted

		// iterate the fidevice array which contains devices that are currently mounted
		// the dlc devices are in another array
		const auto non_dlc_mounted_devices_names = get_non_dlc_mounted_devices_names();

		// for not hanging the game too much
		auto yield_increment = 80;

		auto i = 1;
		while (g_pointers->m_fipackfile_instances[i])
		{
			auto* rpf = g_pointers->m_fipackfile_instances[i];

			// its hard coded in the binary?
			if (++i >= 3672)
			{
				break;
			}

			yim_fipackfile rpf_wrapper = yim_fipackfile(rpf, default_mount_name);

			auto already_mounted = false;
			for (const auto& non_dlc_mounted_device_name : non_dlc_mounted_devices_names)
			{
				rage::fiDevice* non_dlc_mounted_device = rage::fiDevice::GetDevice(non_dlc_mounted_device_name.c_str(), true);

				if (rpf == non_dlc_mounted_device)
				{
					rpf_wrapper.mount_name = non_dlc_mounted_device_name;
					already_mounted = true;
				}
			}

			if (!already_mounted)
			{
				size_t acc = 0;

				rpf_wrapper.mount_name = "memory:/";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "memory:";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "dlc";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "dlc:";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "dlc:/";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "common:/";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "commoncrc:/";
				acc += cb(rpf_wrapper);

				// if we got nothing with those mount points for this rpf, mount it
				// we mount localization rpfs regardless because they may return file paths but not all of them.
				// From my testing, the minimal mounting can still cause error or crashes when transitioning from SP to MP
				// atleast this will happen "only" once per game update
				if (!acc || (ends_with(rpf->GetName(), "dlc.rpf") && strlen(rpf->GetName()) > 7))
				{
					rpf_wrapper.mount_name = default_mount_name;
					rpf->Mount(default_mount_name);

					cb(rpf_wrapper);

					g_pointers->m_fipackfile_unmount(default_mount_name);
				}
			}
			else
			{
				cb(rpf_wrapper);
			}

			if (i % yield_increment == 0)
				script::get_current()->yield();
		}
	}

	std::vector<std::string> yim_fipackfile::get_file_paths()
	{
		std::vector<std::string> file_paths;

		std::function<void(std::string)> recurse;
		recurse = [&](std::string parent)
		{
			std::vector<std::string> directories;

			rage::fiFindData findData = { 0 };
			auto handlef = rpf->FindFirst(parent.c_str(), &findData);
			if (handlef != -1)
			{
				do
				{
					std::string fn = std::string(parent.c_str()) + std::string("/") + std::string(findData.fileName);

					if (findData.fileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						directories.push_back(fn);
					}
					else
					{
						file_paths.push_back(fn);
					}
				} while (rpf->FindNext(handlef, &findData));

				rpf->FindClose(handlef);
			}

			for (auto& directory : directories)
			{
				recurse(directory);
			}
		};

		recurse(mount_name);

		return file_paths;
	}

	void yim_fipackfile::read_xml_file(const std::string& path, std::function<void(pugi::xml_document& doc)> cb)
	{
		read_file<std::string>(path, [&](const std::string& file_content)
		{
			pugi::xml_document doc;
			if (doc.load_string(file_content.c_str()))
			{
				cb(doc);
			}
		});
	}
}
