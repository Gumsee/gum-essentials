#include "XMLReader.h"
#include "../Output.h"
#include <functional>
#include <iostream>

//Lib XML
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

#include "../MemoryManagement.h"


std::string indent(int i)
{
    std::string ret = "";
    for(int j = 0; j < i; j++)
    {
        ret += " ";
    }
    return ret;
}

void buildTree(xmlNode *node, XMLNode* parent, XMLReader* reader);
XMLNode* recurseThroughTree(xmlNode *node, XMLNode* parent, XMLReader::NODE_TYPES allowedtypes, std::function<void(XMLNode*)> func);

XMLReader::XMLReader(std::string filename)
{
    this->sFileName = filename;

    /*parse the file and get the DOM */
    xmlDoc* pDocument = xmlReadFile(filename.c_str(), nullptr, 0);
    if (pDocument == nullptr)
    {
       Gum::Output::error("XMLReader: could not parse XML file " + filename);
       return;
    }

    pRootNode = recurseThroughTree(xmlDocGetRootElement(pDocument), nullptr, NODE_TYPES::ALL, [this](XMLNode* node) {
        addNode(node);
    });



    xmlFreeDoc(pDocument); // free document
    xmlCleanupParser();    // Free globals
}

XMLReader::XMLReader(std::string filename, NODE_TYPES allowedtypes, std::function<void(XMLNode* node)> func)
{
    /*parse the file and get the DOM */
    xmlDoc* pDocument = xmlReadFile(filename.c_str(), nullptr, 0);
    if (pDocument == nullptr)
    {
       Gum::Output::error("XMLReader: could not parse XML file " + filename);
       return;
    }

    pRootNode = recurseThroughTree(xmlDocGetRootElement(pDocument), nullptr, allowedtypes, func);
    xmlFreeDoc(pDocument); // free document
    xmlCleanupParser();    // Free globals
}

XMLReader::~XMLReader()
{
    Gum::_delete(pRootNode);
}

XMLNode* recurseThroughTree(xmlNode *node, XMLNode* parent, XMLReader::NODE_TYPES allowedtypes, std::function<void(XMLNode*)> func)
{
    if(node == nullptr)
        return nullptr;

    XMLNode *retNode = new XMLNode();
    xmlChar *content = xmlNodeGetContent(node);
    retNode->name = reinterpret_cast<const char*>(node->name); //Get name of node
    retNode->content = reinterpret_cast<const char*>(content); //Get content of node
    retNode->parent = parent;
    xmlFree(content);

    switch (node->type) 
    { 
        case XML_ELEMENT_NODE:       retNode->type = XMLReader::NODE_TYPES::ELEMENT;   break;
        case XML_TEXT_NODE:          retNode->type = XMLReader::NODE_TYPES::TEXT;      break;
        case XML_COMMENT_NODE:       retNode->type = XMLReader::NODE_TYPES::COMMENT;   break;
        case XML_ATTRIBUTE_NODE:     retNode->type = XMLReader::NODE_TYPES::ATTRIBUTE; break;
        case XML_DOCUMENT_TYPE_NODE: retNode->type = XMLReader::NODE_TYPES::DOCUMENT;  break;
        case XML_ENTITY_NODE:        retNode->type = XMLReader::NODE_TYPES::ENTITY;    break;
        default:                     retNode->type = XMLReader::NODE_TYPES::UNKNOWN;   break;
    }

    
    //Getting attributes:
    for(xmlAttr* attribute = node->properties; attribute; attribute = attribute->next)
    {
        std::string name = reinterpret_cast<const char*>(attribute->name); //Get name of attribute
        xmlChar *valuechar = xmlNodeListGetString(node->doc, attribute->children, 1); //Get value of attribute
        std::string value = reinterpret_cast<const char*>(valuechar); 
        xmlFree(valuechar);
        retNode->mAttributes[name] = value;
    }

    if(allowedtypes & retNode->type)
        func(retNode);

    xmlNode *childNode = node->children;
    while(childNode != nullptr)
    {
        retNode->children.push_back(recurseThroughTree(childNode, retNode, allowedtypes, func));
        childNode = childNode->next;
    }
    return retNode;
}

std::vector<XMLNode*> XMLReader::getNodeListByName(std::string name)
{
    std::vector<XMLNode*> ret;
    for(size_t i = 0; i < vNodesList.size(); i++)
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

void XMLReader::addNode(XMLNode* node)
{
    this->vNodesList.push_back(node);
}