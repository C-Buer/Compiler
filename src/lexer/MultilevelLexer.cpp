#include "MultilevelLexer.hpp"
#include <sstream>

MultilevelLexer::MultilevelLexer()
{
    pool = std::make_unique<ThreadPool>(2);
}

void MultilevelLexer::addLayer(std::unique_ptr<LexerLevel> layer)
{
    layers.push_back(std::move(layer));
}

std::vector<SourceChunk> MultilevelLexer::chunkify(const std::string &source, size_t linesPerChunk)
{
    std::vector<SourceChunk> result;
    std::istringstream iss(source);
    std::string line;
    std::string buffer;
    size_t lineCount = 0;
    while (std::getline(iss, line))
    {
        buffer += line + "\n";
        lineCount++;
        if (lineCount >= linesPerChunk)
        {
            result.push_back({buffer, true, {}});
            buffer.clear();
            lineCount = 0;
        }
    }
    if (!buffer.empty())
    {
        result.push_back({buffer, true, {}});
    }
    return result;
}

void MultilevelLexer::processAll(std::vector<SourceChunk> &chunks)
{
    for (auto &chunk : chunks)
    {
        if (!chunk.isDirty)
        {
            continue;
        }
        pool->postTask([this, &chunk] {
            std::vector<Token> output = processChunk(chunk);
            chunk.tokens = std::move(output);
            chunk.isDirty = false;
        });
    }
    pool->waitAll();
}

std::vector<Token> MultilevelLexer::processChunk(const SourceChunk &chunk)
{
    std::vector<Token> output;
    if (!layers.empty())
    {
        output = layers[0]->processChunk(chunk);
        for (size_t i = 1; i < layers.size(); i++)
        {
            output = layers[i]->processTokens(output);
        }
    }
    return output;
}
