-- include subprojects
includes("lib/commonlibf4")

-- name and version
local plugin_name = "Fallout4Utils"
local plugin_version = "0.1.0"
local plugin_version_major, plugin_version_minor, plugin_version_patch = plugin_version:match("^(%d+)%.(%d+)%.(%d+)$")

-- set project constants
set_project(plugin_name)
set_version(plugin_version)
set_license("GPL-3.0")
set_languages("c++26")
set_toolchains("msvc")
set_warnings("allextra")
set_encodings("utf-8")

-- set policies
set_policy("build.optimization.lto", true)

-- add common rules
add_rules("mode.debug", "mode.release", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")
add_rules("plugin.compile_commands.autoupdate", { lsp = "clangd" })

-- add options
set_config("commonlib_toml", true)

-- commonlib pins itself to c++23; raise it so headers and sources share one _HAS_CXX26 state
for _, dep in ipairs({ "commonlib-shared", "commonlibf4" }) do
    target(dep, function()
        set_languages("c++26")
    end)
end

-- pinned Dear ImGUI: the DMUI host rejects when build doesn't match
target("imgui", function()
    set_kind("static")
    set_default("false")
    add_files(
        "lib/imgui/imgui.cpp",
        "lib/imgui/imgui_draw.cpp",
        "lib/imgui/imgui_tables.cpp",
        "lib/imgui/imgui_widgets.cpp"
    )
    add_includedirs("lib/imgui", { public = true })
end)

-- define targets
target(plugin_name, function()
    add_cxxflags("/permissive-", "/Zc:preprocessor", { public = true })

    -- add commonlibf4 plugin
    add_rules("commonlibf4.plugin", {
        name = plugin_name,
        author = "Kuz",
        description = "In-game development and testing utilities for Fallout 4",
        plugin_template = "res/commonlibf4-plugin.cpp.in"
    })

    -- add src files
    add_deps("imgui")
    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    add_includedirs("include")
    set_pcxxheader("src/pch.h")

    -- pass name and version
    add_defines(
        'PLUGIN_NAME="' .. plugin_name .. '"',
        'PLUGIN_VERSION="' .. plugin_version .. '"',
        "PLUGIN_VERSION_MAJOR=" .. plugin_version_major,
        "PLUGIN_VERSION_MINOR=" .. plugin_version_minor,
        "PLUGIN_VERSION_PATCH=" .. plugin_version_patch
    )

    -- the commonlib rule derives installdir from the target name inside its own on_config,
    -- which cannot express a mod folder named differently; claim it afterwards
    on_config(function(target)
        local deploy_path = os.getenv("FO4_DEV_DEPLOY")

        if deploy_path then
            target:set("installdir", deploy_path)
        end
    end)
end)
