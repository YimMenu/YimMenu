#include "backend/command.hpp"
#include "util/vehicle.hpp"


namespace big
{
        class repairpv : command
        {
                using command::command;
                virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx)
                {
                        vehicle::repair(self::veh);
                }
        };
        repairpv g_repairpv("repairpv", "Repair PV", "Repairs your currently active personal vehicle", 0);
}