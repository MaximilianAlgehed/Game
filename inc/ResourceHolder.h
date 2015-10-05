#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <map>
#include <string>

template <typename Resource, typename Identifier>
class ResourceHolder
{
    private:
        std::map<Identifier, Resource*> map;
    public:
        const Resource& get(Identifier);
        void load(Identifier, const std::string & path);
};

#endif
