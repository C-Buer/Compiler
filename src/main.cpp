#include "AST\AST.hpp"
#include "AST\ASTPrinter.hpp"
#include "Lexer\Lexer.hpp"
#include "Parser\Parser.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: cbuer <source_file>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    Lexer lexer(source);
    auto tokens = lexer.tokenize();

    // Uncomment the following lines to print tokens for debugging
    /*
    for (const auto& token : tokens) {
        std::cout << "Token(Type: " << static_cast<int>(token.type)
                  << ", Lexeme: \"" << token.lexeme
                  << "\", Line: " << token.line
                  << ", Column: " << token.column << ")\n";
    }
    */

    auto start = std::chrono::high_resolution_clock::now();

    Parser parser(tokens);
    std::unique_ptr<Program> program = parser.parse();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // AST Printing
    ASTPrinter printer;
    program->accept(&printer);

    std::cout << "Parsing completed successfully.\n";
    std::cout << "Parse time: " << duration.count() << " us\n";

    return 0;
}