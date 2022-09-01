#pragma once
#include "XMLNode.h"

class XMLReader
{
private:
    std::string sFileName;
    std::string sEncoding;
    XMLNode* pRootNode;

    std::vector<XMLNode*> vNodesList;

public:
    XMLReader(std::string filename);

    /**
        This Constructor won't save any data and just call the given function recursively
     */
    XMLReader(std::string filename, XMLNode::NODE_TYPES allowedtypes, std::function<void(XMLNode* node)> func);
    ~XMLReader();

    std::vector<XMLNode*> getNodeListByName(std::string name);
    XMLNode* getRootNode();
    void addNode(XMLNode* node);
};