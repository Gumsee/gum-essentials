#pragma once
#include "XMLNode.h"
#include <string>
#include <vector>
#include <map>

class XMLWriter
{
private:
    std::string sFileName;
    std::string sEncoding;

    XMLNode *pCurrentElement = nullptr;
    void writeElement(XMLNode* node, std::string encoding);

public:
    XMLWriter(std::string filename, XMLNode* rootnode, int compression = 0, std::string encoding = "ISO-8859-1");
    ~XMLWriter();

    //XMLNode* addInlineElement(std::string elementName, std::string value, XMLWriterElement *parentElement = nullptr);
    //void addComment(std::string comment, XMLWriterElement *parentElement = nullptr);
};