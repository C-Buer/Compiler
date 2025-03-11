add_rules("mode.release", "mode.debug")

add_languages("cxx20")

add_requires("re-flex")

target("Lexer")
    set_kind("static")
    set_encodings("utf-8")

    add_files("src/Lexer/*.cpp")
    add_packages("re-flex")

    add_vectorexts("all")

target_end()

target("cbuerc")
    set_kind("binary")
    set_encodings("utf-8")

    add_files("src/*.cpp")
    add_deps("Lexer")
    
    add_vectorexts("all")

target_end()