#include "lexer/FirstLayer.hpp"
#include "lexer/MultilevelLexer.hpp"
#include "lexer/SecondLayer.hpp"

int main()
{
    std::vector<SourceChunk> chunks = {{"int x = 10; if(x > 5) x = 0;", true},
                                       {"for(i=0;i<5;i++){ doSomething(); }", true}};

    MultilevelLexer lexer;
    lexer.addLayer(std::make_unique<FirstLayer>());
    lexer.addLayer(std::make_unique<SecondLayer>());

    lexer.processAll(chunks);

    chunks[0].content = "int x = 20; if(x == 0) { x=1; }";
    chunks[0].isDirty = true;

    lexer.processAll(chunks);
    return 0;
}
