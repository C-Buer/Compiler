#ifndef MULTILEVELLEXER_HPP
#define MULTILEVELLEXER_HPP

#include "../threadpool/ThreadPool.hpp"
#include "LexerLevel.hpp"
#include <memory>
#include <vector>


class MultilevelLexer
{
  private:
    std::vector<std::unique_ptr<LexerLevel>> layers;
    std::unique_ptr<ThreadPool> pool;

  public:
    MultilevelLexer();
    void addLayer(std::unique_ptr<LexerLevel> layer);
    std::vector<SourceChunk> chunkify(const std::string &source, size_t linesPerChunk);
    void processAll(std::vector<SourceChunk> &chunks);
    std::vector<Token> processChunk(const SourceChunk &chunk);
};

#endif
