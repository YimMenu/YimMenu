#pragma once

#include "natives.hpp"

namespace big
{
	struct model_attachment
	{
		Hash model_hash;
		Vector3 position;
		Vector3 rotation;
	};

	static void to_json(nlohmann::json& j, const model_attachment& attachment)
	{
		j = nlohmann::json{ {"model_hash", attachment.model_hash},
							{"position_x", attachment.position.x}, {"position_y", attachment.position.y}, {"position_z", attachment.position.z},
							{"rotation_x", attachment.rotation.x}, {"rotation_y", attachment.rotation.y}, {"rotation_z", attachment.rotation.z} };
	}

	static void from_json(const nlohmann::json& j, model_attachment& attachment)
	{
		j.at("model_hash").get_to(attachment.model_hash);
		j.at("position_x").get_to(attachment.position.x); j.at("position_y").get_to(attachment.position.y); j.at("position_z").get_to(attachment.position.z);
		j.at("rotation_x").get_to(attachment.rotation.x); j.at("rotation_y").get_to(attachment.rotation.y); j.at("rotation_z").get_to(attachment.rotation.z);
	}
};
