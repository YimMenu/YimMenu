#include "skip_cutscene.hpp"

#include "natives.hpp"

namespace big
{
	void skip_cutscene::execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
	{
		CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
	}
}
