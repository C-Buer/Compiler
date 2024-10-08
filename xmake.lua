add_languages("cxx20")
add_repositories("tab-repo https://github.com/TabNahida/repo-xmake.git")
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