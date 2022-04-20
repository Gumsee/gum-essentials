#pragma once
#include <string>
#include <vector>
#include <map>

//Lib XML
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

struct XMLWriterElement
{
    std::string sName = "";
    std::string sType = "";
    XMLWriterElement *pParent = nullptr;

    //1st: Name; 2nd: Value
    std::map<std::string, std::string> mAttributes;
    std::vector<std::string> vComments;
};

class XMLWriter
{
private:
    std::string sFileName;
    std::string sEncoding;

    XMLWriterElement *pCurrentElement = nullptr;
    xmlTextWriterPtr pWriter;

    xmlChar* ConvertInput(std::string in);

public:
    XMLWriter(std::string filename, int compression = 0, std::string encoding = "ISO-8859-1");
    ~XMLWriter();

    XMLWriterElement* openElement(std::string name);
    void addAttribute(std::string attrname, std::string value, XMLWriterElement *parentElement = nullptr);
    XMLWriterElement* addInlineElement(std::string elementName, std::string value, XMLWriterElement *parentElement = nullptr);
    void addComment(std::string comment, XMLWriterElement *parentElement = nullptr);
    void closeElement();
    void finishDocument();
};