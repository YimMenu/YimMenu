#include "ASILoader.h"
#include "logger.hpp"
#include "Utility/PEImage.h"

using namespace Utility;

void ASILoader::Initialize() {

	LOG(INFO) << "Loading *.asi plugins.";

	std::string currentFolder = std::getenv("appdata");
	currentFolder += "\\BigBaseV2";
	const std::string asiFolder = currentFolder + "\\OpenHookV";

	const std::string asiSearchQuery = asiFolder + "\\*.asi";

	WIN32_FIND_DATAA fileData;
	HANDLE fileHandle = FindFirstFileA(asiSearchQuery.c_str(), &fileData);
	if (fileHandle != INVALID_HANDLE_VALUE) {

		do {

			const std::string pluginPath = asiFolder + "\\" + fileData.cFileName;

			LOG(INFO) << "Loading " << pluginPath.c_str();

			PEImage pluginImage;
			if (!pluginImage.Load(pluginPath)) {

				LOG(FATAL) << "Failed to load image.";
				continue;
			}

			// Image not compatible, needs patching
			if (!pluginImage.IsOpenVHookCompatible()) {

				LOG(INFO) << "Detected non compatible image. Patching compatibility.";

				if (pluginImage.PatchCompatibility()) {
					LOG(INFO) << "Successfully patched.";
				}
				else {
					LOG(FATAL) << "Failed to patch compatibility.";
					continue;
				}
			}

			// Image compatible (now), load it
			HMODULE module = LoadLibraryA(pluginPath.c_str());
			if (!module)
			{
				DWORD error = ::GetLastError();
				LOG(INFO) << error;
				LPSTR messageBuffer = nullptr;
				FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
			}
				LOG(INFO) << "Loaded " << fileData.cFileName << " -> " HEX_TO_UPPER(module);
			
			

		} while (FindNextFileA(fileHandle, &fileData));

		FindClose(fileHandle);
	}

	LOG(INFO) << "Finished loading *.asi plugins.";
}