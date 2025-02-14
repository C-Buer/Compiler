#include "MultilevelLexer.hpp"
#include <future>
#include <vector>

void MultilevelLexer::addLayer(std::unique_ptr<LexerLevel> layer)
{
    layers.push_back(std::move(layer));
}
std::vector<Token> MultilevelLexer::processChunk(const SourceChunk &chunk)
{
    std::vector<Token> result;
    if (!layers.empty())
    {
        result = layers[0]->processChunk(chunk);
        for (size_t i = 1; i < layers.size(); ++i)
        {
            result = layers[i]->processTokens(result);
        }
    }
    return result;
}
void MultilevelLexer::processAll(std::vector<SourceChunk> &chunks)
{
    std::vector<std::future<std::vector<Token>>> futures;
    futures.reserve(chunks.size());
    for (auto &chunk : chunks)
    {
        if (!chunk.isDirty)
        {
            futures.push_back(std::async(std::launch::async, [] { return std::vector<Token>{}; }));
            continue;
        }
        futures.push_back(std::async(std::launch::async, [this, &chunk] { return this->processChunk(chunk); }));
    }
    for (size_t i = 0; i < chunks.size(); ++i)
    {
        futures[i].get();
        chunks[i].isDirty = false;
    }
}
