#include "ResourceHolder.h"

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& path)
{
    Resource * resource = new Resource();
    resource->loadFromFile(path);
    this->map.insert(id, resource);
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    Resource* found = this->map.find(id);
    return found;
}
