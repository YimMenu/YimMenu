#pragma once
#include "json_util.hpp"
#include "natives.hpp"

namespace big
{
	struct model_attachment
	{
		Hash model_hash;
		Vector3 position;
		Vector3 rotation;
		bool has_collision;
		bool is_visible;
	};

	static void to_json(nlohmann::json& j, const model_attachment& attachment)
	{
		j = nlohmann::json{{"model_hash", attachment.model_hash},
		    {"position_x", attachment.position.x},
		    {"position_y", attachment.position.y},
		    {"position_z", attachment.position.z},
		    {"rotation_x", attachment.rotation.x},
		    {"rotation_y", attachment.rotation.y},
		    {"rotation_z", attachment.rotation.z},
		    {"has_collision", attachment.has_collision},
		    {"is_visible", attachment.is_visible},
		};
	};

	static void from_json(const nlohmann::json& j, model_attachment& attachment)
	{
		set_from_key_or_default(j, "model_hash", attachment.model_hash);

		set_from_key_or_default(j, "position_x", attachment.position.x);
		set_from_key_or_default(j, "position_y", attachment.position.y);
		set_from_key_or_default(j, "position_z", attachment.position.z);

		set_from_key_or_default(j, "rotation_x", attachment.rotation.x);
		set_from_key_or_default(j, "rotation_y", attachment.rotation.y);
		set_from_key_or_default(j, "rotation_z", attachment.rotation.z);

		set_from_key_or_default(j, "has_collision", attachment.has_collision);
		set_from_key_or_default(j, "is_visible", attachment.is_visible, true);
	}
};
