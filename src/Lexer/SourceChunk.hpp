#ifndef SOURCECHUNK_HPP
#define SOURCECHUNK_HPP
#include <string>

struct SourceChunk
{
    std::string content;
    bool isDirty = true;
};

#endif
