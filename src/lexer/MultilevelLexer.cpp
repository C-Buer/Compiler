#include "MultilevelLexer.hpp"
#include <iostream>
#include <thread>


static const size_t SMALL_SOURCE_THRESHOLD = 50000;

MultilevelLexer::MultilevelLexer()
{
    unsigned int hw = std::thread::hardware_concurrency();
    std::cout << hw << std::endl;
    if (hw < 2)
    {
        hw = 1;
    }
    if (hw > 1)
    {
        pool = std::make_unique<ThreadPool>(hw);
        useMultithreading = true;
    }
    else
    {
        useMultithreading = false;
    }
}

void MultilevelLexer::addLayer(std::unique_ptr<LexerLevel> layer)
{
    layers.push_back(std::move(layer));
}

std::vector<SourceChunk> MultilevelLexer::adaptiveChunkify(const std::string &source)
{
    std::vector<SourceChunk> result;
    size_t totalSize = source.size();
    if (totalSize < SMALL_SOURCE_THRESHOLD || !useMultithreading)
    {
        result.push_back({source, true, {}});
        return result;
    }
    unsigned int hw = std::thread::hardware_concurrency();
    if (hw < 1)
    {
        hw = 1;
    }
    size_t chunkCount = hw * 2;
    size_t chunkSize = totalSize / chunkCount;
    size_t offset = 0;
    for (size_t i = 0; i < chunkCount; i++)
    {
        size_t sz = (i == chunkCount - 1) ? (totalSize - offset) : chunkSize;
        std::string sub = source.substr(offset, sz);
        offset += sz;
        result.push_back({std::move(sub), true, {}});
    }
    return result;
}

void MultilevelLexer::processAll(std::vector<SourceChunk> &chunks)
{
    size_t totalSize = 0;
    for (auto &c : chunks)
    {
        if (c.isDirty)
        {
            totalSize += c.content.size();
        }
    }
    if (!useMultithreading || totalSize < SMALL_SOURCE_THRESHOLD)
    {
        for (auto &c : chunks)
        {
            if (c.isDirty)
            {
                c.tokens = processChunk(c);
                c.isDirty = false;
            }
        }
        return;
    }
    batchProcessChunks(chunks);
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

void MultilevelLexer::batchProcessChunks(std::vector<SourceChunk> &chunks)
{
    unsigned int hw = std::thread::hardware_concurrency();
    if (hw < 1)
    {
        hw = 1;
    }
    size_t chunkCount = chunks.size();
    if (chunkCount <= hw)
    {
        for (auto &c : chunks)
        {
            if (c.isDirty)
            {
                pool->postTask([this, &c] {
                    c.tokens = processChunk(c);
                    c.isDirty = false;
                });
            }
        }
        pool->waitAll();
        return;
    }
    size_t step = (chunkCount + hw - 1) / hw;
    size_t startIndex = 0;
    for (unsigned int i = 0; i < hw; i++)
    {
        size_t endIndex = (startIndex + step < chunkCount) ? (startIndex + step) : chunkCount;
        if (startIndex >= endIndex)
        {
            break;
        }
        pool->postTask([this, &chunks, startIndex, endIndex] {
            for (size_t idx = startIndex; idx < endIndex; idx++)
            {
                if (chunks[idx].isDirty)
                {
                    chunks[idx].tokens = processChunk(chunks[idx]);
                    chunks[idx].isDirty = false;
                }
            }
        });
        startIndex = endIndex;
    }
    pool->waitAll();
}
