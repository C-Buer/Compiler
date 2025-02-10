add_rules("mode.release", "mode.debug")

add_languages("cxx20")

target("ThreadPool")
    set_kind("static")
    set_encodings("utf-8")

    add_files("src/threadpool/*.cpp")
    add_includedirs("include/threadpool")

target_end()

target("Lexer")
    set_kind("static")
    set_encodings("utf-8")

    add_files("src/Lexer/*.cpp")
    add_includedirs("include")
    add_deps("ThreadPool")

target_end()

--[[
target("Parser")
    set_kind("static")
    set_encodings("utf-8")

    add_files("src/Parser/*.cpp")
    add_includedirs("include")

    add_vectorexts("all")

target_end()

target("AST")
    set_kind("static")
    set_encodings("utf-8")

    add_files("src/AST/*.cpp")
    add_includedirs("include")

    add_vectorexts("all")

target_end()
--]]

target("cbuerc")
    set_kind("binary")
    set_encodings("utf-8")

    add_files("src/*.cpp")
    add_includedirs("include")
    add_deps("Lexer")

target_end()