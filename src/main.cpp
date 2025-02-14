#include "Lexer/FirstLayer.hpp"
#include "Lexer/MultilevelLexer.hpp"
#include "Lexer/SecondLayer.hpp"
#include "Lexer/SourceChunk.hpp"
#include <iostream>
#include <vector>

int main()
{
    std::vector<SourceChunk> chunks = {{"int main() { if(x>0){x=1;} }", true},
                                       {"for(i=0;i<10;i++){ doSomething(); }", true}};
    MultilevelLexer lexer;
    lexer.addLayer(std::make_unique<FirstLayer>());
    lexer.addLayer(std::make_unique<SecondLayer>());
    lexer.processAll(chunks);
    for (const auto &chunk : chunks)
    {
        std::cout << chunk.content << "\n";
    }
    return 0;
}
