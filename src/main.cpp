#include "pch.h"
#include <spdlog/spdlog.h>

namespace
{
	void InitPlugin(const F4SE::LoadInterface* a_f4se)
	{
		F4SE::Init(a_f4se);
        // Modern CommonLibF4 automatically configures spdlog during Init
		spdlog::info("Fallout4Utils loaded");
	}
}

F4SE_PLUGIN_QUERY(const F4SE::QueryInterface* a_f4se, F4SE::PluginInfo* a_info)
{
	if (const auto data = F4SE::PluginVersionData::GetSingleton())
	{
		a_info->infoVersion = F4SE::PluginInfo::kVersion;
		a_info->name = data->GetPluginName().data();
		a_info->version = data->GetPluginVersion().pack();
	}
    
    if (a_f4se->IsEditor()) {
		return false;
	}

	return true;
}

F4SE_PLUGIN_LOAD(const F4SE::LoadInterface* a_f4se)
{
	InitPlugin(a_f4se);
	return true;
}
