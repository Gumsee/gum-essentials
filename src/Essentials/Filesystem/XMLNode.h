#pragma once
#include <string>
#include <map>
#include <vector>
#include <functional>

struct XMLNode
{
    enum NODE_TYPES
    {
        UNKNOWN   = 0b0000001,
        ELEMENT   = 0b0000010,
        TEXT      = 0b0000100,
        COMMENT   = 0b0001000,
        ATTRIBUTE = 0b0010000,
        DOCUMENT  = 0b0100000,
        ENTITY    = 0b1000000,
        ALL       = 0b1111111,
    };

    std::string name = "";
    std::string content = "";
    NODE_TYPES type;

    XMLNode* parent;
    void* userptr;
    std::vector<XMLNode*> children;
    std::map<std::string, std::string> mAttributes;

    XMLNode() {}
    XMLNode(std::string name, NODE_TYPES type) : name(name), type(type)
    {

    }

    ~XMLNode()
    {
        for(size_t i = 0; i < children.size(); i++)
        {
            if(children[i] != nullptr)
                delete children[i];
        }
    }

    void addAttribute(std::string attrname, std::string value)
    {
        this->mAttributes[attrname] = value;
    }

    void retrieveAttributes(std::function<void(std::string name, std::string value)> func)
    {
        for(auto attr : mAttributes)
            func(attr.first, attr.second);
    }
};