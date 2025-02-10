#include "lexer/ClassicLexer.hpp"
#include "lexer/FirstLayer.hpp"
#include "lexer/MultilevelLexer.hpp"
#include "lexer/SecondLayer.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <vector>


static void printTokens(const std::vector<Token> &tokens)
{
    for (auto &tk : tokens)
    {
        std::cout << tk.text << "(" << (int)tk.type << ") ";
    }
    std::cout << std::endl;
}

static std::vector<SourceChunk> generateTestChunks(size_t numChunks, size_t chunkSize)
{
    std::vector<SourceChunk> chunks;
    std::string sampleCode = "int x = 10; if(x > 5) x = 0;";
    for (size_t i = 0; i < numChunks; ++i)
    {
        std::string content;
        for (size_t j = 0; j < chunkSize; ++j)
        {
            content += sampleCode + " ";
        }
        chunks.push_back({content, true});
    }
    return chunks;
}

int main()
{
    size_t numChunks = 100; // 总块数
    size_t chunkSize = 10;  // 每块的代码行数

    std::cout << "Generating test data..." << std::endl;
    std::vector<SourceChunk> chunks = generateTestChunks(numChunks, chunkSize);

    MultilevelLexer lexer;
    lexer.addLayer(std::make_unique<FirstLayer>());
    lexer.addLayer(std::make_unique<SecondLayer>());

    std::cout << "Testing MultilevelLexer..." << std::endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    lexer.processAll(chunks);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto durationMultilevel = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "MultilevelLexer initial pass time (us): " << durationMultilevel << std::endl;

    std::cout << "Simulating modifications to a subset of chunks..." << std::endl;
    for (size_t i = 0; i < numChunks; i += 10)
    {
        chunks[i].content = "int x = 20; if(x == 0) { x=1; }";
        chunks[i].isDirty = true;
    }

    auto t3 = std::chrono::high_resolution_clock::now();
    lexer.processAll(chunks);
    auto t4 = std::chrono::high_resolution_clock::now();

    auto durationMultilevelIncremental = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
    std::cout << "MultilevelLexer incremental pass time (us): " << durationMultilevelIncremental << std::endl;

    std::cout << "Testing ClassicLexer..." << std::endl;
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
