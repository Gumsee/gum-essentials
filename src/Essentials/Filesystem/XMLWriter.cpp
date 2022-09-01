#include "XMLWriter.h"
#include "../Output.h"
#include "XMLNode.h"

//Lib XML
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>


xmlTextWriterPtr pWriter;

xmlChar* ConvertInput(std::string in, std::string encoding);

XMLWriter::XMLWriter(std::string filename, XMLNode* rootnode, bool oneline, int compression, std::string encoding)
{
    pWriter = xmlNewTextWriterFilename(filename.c_str(), compression);
    if (!pWriter) 
    { 
        Gum::Output::error("XMLWriter: Error creating the xml writer"); 
        return;
    }
    xmlTextWriterSetIndent(pWriter, !oneline);

    int rc = xmlTextWriterStartDocument(pWriter, "1.0", encoding.c_str(), 0);
    if (rc < 0) 
    { 
        Gum::Output::error("XMLWriter: Error at xmlTextWriterStartDocument"); 
        return;
    }

    writeElement(rootnode, encoding);

    rc = xmlTextWriterEndDocument(pWriter);
    if (rc < 0) 
        Gum::Output::error("XMLWriter: Error whilst finishing Document");

    xmlFreeTextWriter(pWriter);
}

XMLWriter::~XMLWriter() 
{

}


void XMLWriter::writeElement(XMLNode* node, std::string encoding)
{
    xmlChar *pNameStr = ConvertInput(node->name, encoding);
    int rc = xmlTextWriterStartElement(pWriter, pNameStr);
    if (pNameStr != nullptr) xmlFree(pNameStr);

    if (rc < 0) 
    { 
        Gum::Output::error("XMLWriter: Error at xmlTextWriterStartElement"); 
        return;
    }

    //Add Attributes
    node->retrieveAttributes([encoding](std::string attr, std::string value) {
        xmlChar *pValStr = ConvertInput(value, encoding);
        xmlChar *pNameStr = ConvertInput(attr, encoding);
        int rc = xmlTextWriterWriteAttribute(pWriter, pNameStr, pValStr);
        if (pValStr != nullptr) xmlFree(pValStr);
        if (pNameStr != nullptr) xmlFree(pNameStr);

        if (rc < 0) 
            Gum::Output::error("XMLWriter: Error at xmlTextWriterWriteAttribute");
    });

    //Recursively write nodes
    for(size_t i = 0; i < node->children.size(); i++)
        writeElement(node->children[i], encoding);


    rc = xmlTextWriterEndElement(pWriter);
    if (rc < 0) 
        Gum::Output::error("XMLWriter: Error when trying to close Element " + node->name + "!");
}



xmlChar* ConvertInput(std::string in, std::string encoding)
{
    xmlChar *out;
    int ret;
    int size;
    int out_size;
    int temp;
    xmlCharEncodingHandlerPtr handler;

    if (in == "") { return 0; }

    handler = xmlFindCharEncodingHandler(encoding.c_str());
    if (!handler)  { Gum::Output::error("ConvertInput: no encoding handler found for " + encoding); return 0; }

    size = (int) in.length() + 1;
    out_size = size * 2 - 1;
    out = (unsigned char *) xmlMalloc((size_t) out_size);

    if (out != 0) 
    {
        temp = size - 1;
        ret = handler->input(out, &out_size, (const xmlChar *)in.c_str(), &temp);
        if ((ret < 0) || (temp - size + 1)) 
        {
            if (ret < 0)    { Gum::Output::error("ConvertInput: conversion wasn't successful."); } 
            else            { Gum::Output::error("ConvertInput: conversion wasn't successful. converted: " + std::to_string(temp) + " octets."); }
            xmlFree(out);
            out = 0;
        } 
        else 
        {
            out = (unsigned char *) xmlRealloc(out, out_size + 1);
            out[out_size] = 0;  /*null terminating out */
        }
    } 
    else 
    {
        Gum::Output::error("ConvertInput: no mem");
    }

    return out;
}



/*XMLNode* XMLWriter::addInlineElement(std::string elementName, std::string value, XMLWriterElement *parentElement)
{
    if(parentElement == nullptr)
    {
        if(pCurrentElement != nullptr) { parentElement = pCurrentElement; }
        else { Gum::Output::error("XMLWriter: Couldn't add attribute, CurrentElement does not exist!"); return nullptr; }
    }
    if(pWriter == nullptr) { Gum::Output::error("XMLWriter: Couldn't add FormatElement, Writer was nullptr."); return nullptr; }

    xmlChar *pValStr = ConvertInput(value);
    xmlChar *pNameStr = ConvertInput(elementName);
    int rc = xmlTextWriterWriteElement(pWriter, pNameStr, pValStr);
    if (rc < 0) { Gum::Output::error("XMLWriter: Error whilest adding InlineElement."); }
    if (pValStr != 0) xmlFree(pValStr);
    if (pNameStr != 0) xmlFree(pNameStr);

    XMLNode *retElement = new XMLNode();
    retElement->sName = elementName;
    retElement->sType = "inline";
    retElement->pParent = pCurrentElement;

    return retElement;
}

void XMLWriter::addComment(std::string comment, XMLWriterElement *parentElement)
{
    if(parentElement == nullptr)
    {
        if(pCurrentElement != nullptr) { parentElement = pCurrentElement; }
        else { Gum::Output::error("XMLWriter: Couldn't add Comment, CurrentElement does not exist!"); return; }
    }
    if(pWriter == nullptr) { Gum::Output::error("XMLWriter: Couldn't add Comment, Writer was nullptr."); return; }
    
    parentElement->vComments.push_back(comment);
    xmlChar *pStr = ConvertInput(comment);
    int rc = xmlTextWriterWriteComment(pWriter, pStr);
    if (rc < 0) { Gum::Output::error("XMLWriter: Error when trying to add Comment to" + pCurrentElement->sName); }
    if (pStr != 0) xmlFree(pStr);
}*/