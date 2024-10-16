set_policy("package.install_always", true)
add_rules("mode.release", "mode.debug")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "./"})

option("tab_repo")
    set_default(true)
    set_showmenu(true)
option_end()

add_languages("cxx20")

if has_config("tab_repo") then
    add_repositories("tab-repo https://github.com/TabNahida/repo-xmake.git")
end
add_requires("tstring")

target("Lexer")
    set_kind("static")

    add_files("src/Lexer/*.cpp")
    add_includedirs("include")

    add_packages("tstring")
target_end()

target("CB-Compiler")
    set_kind("binary")

    add_files("src/*.cpp")
    add_includedirs("include")
    add_deps("Lexer")

    add_packages("tstring")
target_end()