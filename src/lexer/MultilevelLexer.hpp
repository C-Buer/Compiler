#ifndef MULTILEVELLEXER_HPP
#define MULTILEVELLEXER_HPP

#include "../threadpool/ThreadPool.hpp"
#include "LexerLevel.hpp"
#include <memory>
#include <vector>

class MultilevelLexer
{
  private:
    std::unique_ptr<ThreadPool> pool;
    std::vector<std::unique_ptr<LexerLevel>> layers;
    bool useMultithreading;

  public:
    MultilevelLexer();
    void addLayer(std::unique_ptr<LexerLevel> layer);
    std::vector<SourceChunk> adaptiveChunkify(const std::string &source);
    void processAll(std::vector<SourceChunk> &chunks);
    std::vector<Token> processChunk(const SourceChunk &chunk);

  private:
    void batchProcessChunks(std::vector<SourceChunk> &chunks);
};

#endif
