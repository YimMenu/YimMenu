#pragma once
#include "command.hpp"

namespace big
{
	class bool_command : public command
	{
	protected:
		bool& m_toggle;
		virtual void execute(const std::vector<std::uint64_t>& args, const command_context&) override;
		virtual std::optional<std::vector<std::uint64_t>> parse_args(const std::vector<std::string>& args, const command_context&) override;
	public:
		bool_command(const std::string& name, bool& toggle);
	};
}