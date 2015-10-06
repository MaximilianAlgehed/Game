#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <map>
#include <string>

//Template class for resource loaders
template <typename Resource, typename Identifier>
class ResourceHolder
{
    private:
        //Map the identifier to a resource pointer
        std::map<Identifier, Resource*> map;
    public:
        //Destructor
        ~ResourceHolder();

        //Get a resource from the holder
        Resource& get(Identifier);

        //Load a resource
        void load(Identifier, const std::string & path);
};

//Destroy the resource holder
template<typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::~ResourceHolder()
{
    //Destroy all the resources so they dont leak
    for(auto pair : map)
        delete pair.second;
}

//Load a resource from file
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
    //Return the found resource
    Resource* found = this->map.find(id)->second;
    return *found;
}

#endif
