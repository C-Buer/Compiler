#ifndef MULTILEVELLEXER_HPP
#define MULTILEVELLEXER_HPP
#include "LexerLevel.hpp"
#include "SourceChunk.hpp"
#include "Token.hpp"
#include <memory>
#include <vector>

class MultilevelLexer
{
  public:
    void addLayer(std::unique_ptr<LexerLevel> layer);
    std::vector<Token> processChunk(const SourceChunk &chunk);
    void processAll(std::vector<SourceChunk> &chunks);

  private:
    std::vector<std::unique_ptr<LexerLevel>> layers;
};

#endif
