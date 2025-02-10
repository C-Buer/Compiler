#include "MultilevelLexer.hpp"

MultilevelLexer::MultilevelLexer()
{
    pool = std::make_unique<ThreadPool>(4);
}

void MultilevelLexer::addLayer(std::unique_ptr<LexerLevel> layer)
{
    layers.push_back(std::move(layer));
}

void MultilevelLexer::processAll(std::vector<SourceChunk> &chunks)
{
    std::vector<std::future<std::vector<Token>>> futures;
    futures.reserve(chunks.size());
    for (auto &chunk : chunks)
    {
        if (!chunk.isDirty)
        {
            futures.push_back(std::async(std::launch::deferred, [] { return std::vector<Token>{}; }));
            continue;
        }
        futures.push_back(pool->postTask([this, &chunk] { return this->processChunk(chunk); }));
    }
    for (size_t i = 0; i < chunks.size(); i++)
    {
        std::vector<Token> result = futures[i].get();
        if (chunks[i].isDirty)
        {
            chunks[i].isDirty = false;
        }
    }
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
