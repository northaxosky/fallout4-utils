#pragma once

#include <string_view>

#include <imgui.h>
#include <imgui_internal.h>

#include <DearModdingUI/ImGuiFingerprint.h>

#ifndef IMGUI_HAS_DOCK
#	error "The DearModdingUI contract requires the pinned Dear ImGui docking build"
#endif

static_assert(IMGUI_VERSION_NUM == DMUI_IMGUI_VERSION_NUM,
	"lib/imgui is out of sync with the vendored DearModdingUI API");
static_assert(std::string_view{ IMGUI_VERSION } == std::string_view{ "1.92.9b" },
	"lib/imgui must stay pinned to Dear ImGui 1.92.9b-docking");
static_assert(sizeof(DMUI_IMGUI_UPSTREAM_COMMIT) == 41);

namespace Host
{
	inline const DMUI_ImGuiFingerprint& ClientFingerprint() noexcept
	{
		static const DMUI_ImGuiFingerprint fingerprint = DMUI_MakeImGuiFingerprint();
		return fingerprint;
	}
}
