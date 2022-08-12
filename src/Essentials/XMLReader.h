#pragma once
#include <functional>
#include <string>
#include <vector>
#include <map>

struct XMLNode
{
    std::string name = "";
    std::string content = "";
    int type;

    XMLNode* parent;
    void* userptr;
    std::vector<XMLNode*> children;
    std::map<std::string, std::string> mAttributes;

    ~XMLNode()
    {
        for(size_t i = 0; i < children.size(); i++)
        {
            if(children[i] != nullptr)
                delete children[i];
        }
    }
};

class XMLReader
{
private:
    std::string sFileName;
    std::string sEncoding;
    XMLNode* pRootNode;

    std::vector<XMLNode*> vNodesList;

public:

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

    XMLReader(std::string filename);

    /**
        This Constructor won't save any data and just call the given function recursively
     */
    XMLReader(std::string filename, NODE_TYPES allowedtypes, std::function<void(XMLNode* node)> func);
    ~XMLReader();

    std::vector<XMLNode*> getNodeListByName(std::string name);
    XMLNode* getRootNode();
    void addNode(XMLNode* node);
};