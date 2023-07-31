#include "backend/command.hpp"
#include "util/vehicle.hpp"


namespace big
{
        class repairpv : command
        {
                using command::command;
                virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx) override
                {
                        vehicle::repair(self::veh);
                }
        };
        repairpv g_repairpv("repairpv", "REPAIR_PV", "REPAIR_PV_DESC", 0);
}