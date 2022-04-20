#include "XMLReader.h"
#include "Output.h"
#include <iostream>


XMLReader::XMLReader(std::string filename)
{
    this->sFileName = filename;

    /*parse the file and get the DOM */
    pDocument = xmlReadFile(filename.c_str(), nullptr, 0);
    if (pDocument == nullptr)
    {
       Gum::Output::error("XMLReader: could not parse XML file " + filename);
       return;
    }

    pRootElement = xmlDocGetRootElement(pDocument);
    pRootNode = new XMLNode();
    pRootNode->name = "Root";
    buildTree(pRootElement, pRootNode);



    xmlFreeDoc(pDocument); // free document
    xmlCleanupParser();    // Free globals
}

XMLReader::~XMLReader() {}

void XMLReader::buildTree(xmlNode *node, XMLNode *parent)
{
    if(node == nullptr) return;

    for(xmlNode *currentNode = node; currentNode; currentNode = currentNode->next)
    {
        if (currentNode->type == XML_ELEMENT_NODE) 
        {
            XMLNode *nodeTreeEntry = new XMLNode();
            std::string name = (const char*)currentNode->name; //Get name of node
            std::string content = reinterpret_cast<const char*>(xmlNodeGetContent(currentNode)); //Get content of node
            nodeTreeEntry->name = name;
            nodeTreeEntry->content = content;
            nodeTreeEntry->parent = parent;
            nodeTreeEntry->type = currentNode->type;

            //Getting attributes:
            for(xmlAttr* attribute = currentNode->properties; attribute; attribute = attribute->next)
            {
                std::string name = reinterpret_cast<const char*>(attribute->name); //Get name of attribute
                std::string value = reinterpret_cast<const char*>(xmlNodeListGetString(node->doc, attribute->children, 1)); //Get value of attribute
                nodeTreeEntry->mAttributes[name] = value;
            }
            
            vNodesList.push_back(nodeTreeEntry);
            buildTree(currentNode->children, nodeTreeEntry);
            parent->children.push_back(nodeTreeEntry);
        }
    }
}

std::vector<XMLNode*> XMLReader::getNodeListByName(std::string name)
{
    std::vector<XMLNode*> ret;
    for(int i = 0; i < vNodesList.size(); i++)
    {
        if(vNodesList[i]->name == name)
        {
            ret.push_back(vNodesList[i]);
        }
    }
    return ret;
}

XMLNode* XMLReader::getRootNode()
{
    return pRootNode;
}