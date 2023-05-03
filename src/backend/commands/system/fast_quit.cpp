#include "fast_quit.hpp"

namespace big
{
	void fast_quit::execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
	{
		exit(0);
	}
}
