#include "Lexer/Lexer.hpp"
#include <chrono>
#include <iostream>
#include <string>

int main()
{
    Lexer::addKeyword("if");
    Lexer::addKeyword("else");
    Lexer::addKeyword("for");
    Lexer::addKeyword("while");
    Lexer::addKeyword("return");
    std::string testInput;
    for (int i = 0; i < 1000000; i++)
    {
        testInput += "int a = 123; if(a){ a = a + 1; } ";
    }
    auto start = std::chrono::steady_clock::now();
    Lexer traditionalLexer(testInput);
    auto tokensTraditional = traditionalLexer.tokenize();
    auto end = std::chrono::steady_clock::now();
    auto durationTraditional = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    start = std::chrono::steady_clock::now();
    auto tokensMulti = Lexer::tokenizeMultiThread(testInput, 1024);
    end = std::chrono::steady_clock::now();
    auto durationMulti = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Traditional Lexer tokens: " << tokensTraditional.size() << " time: " << durationTraditional
              << " ms\n";
    std::cout << "Multithread Lexer tokens: " << tokensMulti.size() << " time: " << durationMulti << " ms\n";
    std::string changedChunk = "int b = 456; else { b = b - 1; }";
    auto incrementalTokens = Lexer::incrementalTokenize(changedChunk, 50, 10);
    std::cout << "Incremental tokens: " << incrementalTokens.size() << "\n";
    std::cout << "First 5 tokens from traditional lexing:\n";
    for (int i = 0; i < 5 && i < tokensTraditional.size(); i++)
    {
        std::cout << "Token: " << tokensTraditional[i].lexeme
                  << " type: " << static_cast<int>(tokensTraditional[i].type) << " line: " << tokensTraditional[i].line
                  << " col: " << tokensTraditional[i].column << "\n";
    }
    return 0;
}
