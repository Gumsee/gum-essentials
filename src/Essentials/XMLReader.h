#pragma once
#include <string>
#include <vector>
#include <map>

//Lib XML
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

struct XMLNode
{
    std::string name = "";
    std::string content = "";
    int type;
    xmlNode *libxmlNode;

    XMLNode *parent;
    std::vector<XMLNode*> children;
    std::map<std::string, std::string> mAttributes;
};

class XMLReader
{
private:
    std::string sFileName;
    std::string sEncoding;

    xmlDoc *pDocument;
    xmlNode *pRootElement;

    XMLNode *pRootNode;
    std::vector<XMLNode*> vNodesList;
    void buildTree(xmlNode *node, XMLNode *parent);

public:
    XMLReader(std::string filename);
    ~XMLReader();


    std::vector<XMLNode*> getNodeListByName(std::string name);
    XMLNode* getRootNode();
};