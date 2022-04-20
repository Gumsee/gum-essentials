#include "XMLWriter.h"
#include "Output.h"


XMLWriter::XMLWriter(std::string filename, int compression, std::string encoding)
{
    this->sFileName = filename;
    this->sEncoding = encoding;

    pWriter = xmlNewTextWriterFilename(filename.c_str(), compression);
    xmlTextWriterSetIndent(pWriter, true);
    if (pWriter == 0) { Gum::Output::error("FileParser: Error creating the xml writer"); }


    int rc = xmlTextWriterStartDocument(pWriter, "1.0", encoding.c_str(), 0);
    if (rc < 0) { Gum::Output::error("XMLWriter: Error at xmlTextWriterStartDocument"); }
}

XMLWriter::~XMLWriter() {}


XMLWriterElement* XMLWriter::openElement(std::string name)
{
    xmlChar *pNameStr = ConvertInput(name);
    int rc = xmlTextWriterStartElement(pWriter, pNameStr);
    if (rc < 0) { Gum::Output::error("XMLWriter: Error at xmlTextWriterStartElement"); return nullptr; }
    if (pNameStr != 0) xmlFree(pNameStr);

    XMLWriterElement *retElement = new XMLWriterElement();
    retElement->sName = name;
    retElement->sType = "starter";
    retElement->pParent = pCurrentElement;
    this->pCurrentElement = retElement;

    return retElement;
}


/** Adds an attribute to the active Element
 *  @param[in] attrname Defines the name of the new Attribute
 *  @param[in] value Defines what value the attribute will have
 *  @param[in] *parentElement Points to the parent Element (this just affects the tree of the Engine and not the libxml tree)
 */
void XMLWriter::addAttribute(std::string attrname, std::string value, XMLWriterElement *parentElement)
{
    if(parentElement == nullptr)
    {
        if(pCurrentElement != nullptr) { parentElement = pCurrentElement; }
        else { Gum::Output::error("XMLWriter: Couldn't add attribute, CurrentElement does not exist!"); return; }
    }
    if(pWriter == nullptr) { Gum::Output::error("XMLWriter: Couldn't add attribute, Writer was nullptr."); return; }

    parentElement->mAttributes[attrname] = value;

    xmlChar *pValStr = ConvertInput(value);
    xmlChar *pNameStr = ConvertInput(attrname);
    int rc = xmlTextWriterWriteAttribute(pWriter, pNameStr, pValStr);
    if (rc < 0) { Gum::Output::error("XMLWriter: Error at xmlTextWriterWriteAttribute"); }
    if (pValStr != 0) xmlFree(pValStr);
    if (pNameStr != 0) xmlFree(pNameStr);
}

XMLWriterElement* XMLWriter::addInlineElement(std::string elementName, std::string value, XMLWriterElement *parentElement)
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

    XMLWriterElement *retElement = new XMLWriterElement();
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
}

void XMLWriter::closeElement()
{
    if(pCurrentElement == nullptr)  { Gum::Output::error("XMLWriter: Couldn't close, Element is nullptr!"); return; }
    if(pWriter == nullptr)          { Gum::Output::error("XMLWriter: Couldn't close Element, Writer was nullptr."); return; }

    //Going back a step
    pCurrentElement = pCurrentElement->pParent;
    int rc = xmlTextWriterEndElement(pWriter);
    if (rc < 0) { Gum::Output::error("XMLWriter: Error when trying to close Element " + pCurrentElement->sName + "!"); }
}

void XMLWriter::finishDocument()
{
    if(pWriter == nullptr) { Gum::Output::error("XMLWriter: Couldn't add attribute, Writer was nullptr."); return; }

    int rc = xmlTextWriterEndDocument(pWriter);
    if (rc < 0) { Gum::Output::error("XMLWriter: Error whilest finishing Document"); }

    xmlFreeTextWriter(pWriter);
}


xmlChar* XMLWriter::ConvertInput(std::string in)
{
    xmlChar *out;
    int ret;
    int size;
    int out_size;
    int temp;
    xmlCharEncodingHandlerPtr handler;

    if (in == "") { return 0; }

    handler = xmlFindCharEncodingHandler(sEncoding.c_str());
    if (!handler)  { Gum::Output::error("ConvertInput: no encoding handler found for " + sEncoding); return 0; }

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