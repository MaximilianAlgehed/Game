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
        Resource& get(Identifier);
        void load(Identifier, const std::string & path);
};

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& path)
{
    Resource * resource = new Resource();
    resource->loadFromFile(path);
    this->map[id] = resource;
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    Resource* found = this->map.find(id)->second;
    return *found;
}

#endif
