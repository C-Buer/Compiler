#include "lexer/ClassicLexer.hpp"
#include "lexer/FirstLayer.hpp"
#include "lexer/MultilevelLexer.hpp"
#include "lexer/SecondLayer.hpp"
#include <chrono>
#include <iostream>
#include <random>


static void printTokens(const std::vector<Token> &tokens)
{
    for (auto &tk : tokens)
    {
        std::cout << tk.text << "(" << (int)tk.type << ") ";
    }
    std::cout << std::endl;
}

int main()
{
    std::string sourceSample;
    for (int i = 0; i < 1000; i++)
    {
        sourceSample += "int x = 10; if(x > 5) x = 0;\n";
    }

    MultilevelLexer lexer;
    lexer.addLayer(std::make_unique<FirstLayer>());
    lexer.addLayer(std::make_unique<SecondLayer>());

    std::cout << "Splitting source into chunks..." << std::endl;
    std::vector<SourceChunk> chunks = lexer.chunkify(sourceSample, 50);

    auto t1 = std::chrono::high_resolution_clock::now();
    lexer.processAll(chunks);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto durationMultilevel = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "MultilevelLexer initial pass time (us): " << durationMultilevel << std::endl;

    std::cout << "Simulating random modifications..." << std::endl;
    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> dist(0, (int)chunks.size() - 1);
    for (int i = 0; i < 10; i++)
    {
        int idx = dist(rng);
        chunks[idx].content = "int y = 20; if(y == 0) { y=1; }";
        chunks[idx].isDirty = true;
    }

    auto t3 = std::chrono::high_resolution_clock::now();
    lexer.processAll(chunks);
    auto t4 = std::chrono::high_resolution_clock::now();
    auto durationMultilevelIncremental = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
    std::cout << "MultilevelLexer incremental pass time (us): " << durationMultilevelIncremental << std::endl;

    std::cout << "Printing modified chunks only:" << std::endl;
    for (size_t i = 0; i < chunks.size(); i++)
    {
        if (!chunks[i].tokens.empty() && chunks[i].content.find("y") != std::string::npos)
        {
            std::cout << "Chunk " << i << " tokens: ";
            printTokens(chunks[i].tokens);
        }
    }

    ClassicLexer classic;
    std::string combinedSource;
    for (auto &c : chunks)
    {
        combinedSource += c.content + "\n";
    }

    auto t5 = std::chrono::high_resolution_clock::now();
    auto classicTokens = classic.processFullSource(combinedSource);
    auto t6 = std::chrono::high_resolution_clock::now();
    auto durationClassic = std::chrono::duration_cast<std::chrono::microseconds>(t6 - t5).count();
    std::cout << "ClassicLexer time (us): " << durationClassic << std::endl;

    std::cout << "Performance Summary:" << std::endl;
    std::cout << "MultilevelLexer (Initial): " << durationMultilevel << " us" << std::endl;
    std::cout << "MultilevelLexer (Incremental): " << durationMultilevelIncremental << " us" << std::endl;
    std::cout << "ClassicLexer: " << durationClassic << " us" << std::endl;

    return 0;
}
