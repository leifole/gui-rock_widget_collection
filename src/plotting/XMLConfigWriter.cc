/* 
 * File:   XMLConfigWriter.cc
 * Author: blueck
 * 
 * Created on 24. November 2010, 13:37
 */

#include "XMLConfigWriter.h"

XMLConfigWriter::XMLConfigWriter()
{
    encoding = "ISO-8859-1";
}

bool XMLConfigWriter::writeConfigFile(char* filename)
{
    // compression deactivated
    // TODO make compression configurable
    char* currentLocale = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, "C");
    writer = xmlNewTextWriterFilename(filename, 0);
    xmlTextWriterSetIndent(writer, 1);
    if (writer == NULL)
    {
        std::cerr << "Could not create an XML Writer to:[" << filename << "]" << std::endl;
        return false;
    }
    // TODO: make encoding configurable
    int retValue = xmlTextWriterStartDocument(writer, NULL, encoding, NULL);
    if(retValue < 0)
    {
        std::cerr << "Could not start writing XML document" << std::endl;
        return false;
    }
    retValue = xmlTextWriterStartElement(writer, BAD_CAST "configuration");
    if (retValue < 0)
    {
        std::cerr << "Could not write xml element <configuration>" << std::endl;
        return false;
    }
    // content goes here, call the abstract method
    writeContent();
    // close everything
    retValue = xmlTextWriterEndDocument(writer);
    if (retValue < 0)
    {
        std::cerr << "Could not end the xml document" << std::endl;
        return false;
    }
    xmlFreeTextWriter(writer);
    setlocale(LC_ALL, currentLocale);
    return true;
}

bool XMLConfigWriter::startTag(const char* name)
{
    int retValue = xmlTextWriterStartElement(writer, BAD_CAST name);
    if (retValue < 0)
    {
        std::cerr << "Could not write xml element <configuration>" << std::endl;
        return false;
    }
    return true;
}

bool XMLConfigWriter::writeTag(const char* name, const char* content)
{
    int retValue = xmlTextWriterWriteElement(writer, BAD_CAST name, ((content == 0) ? (const xmlChar*)"" : (const xmlChar*)(content)));
    if (retValue < 0)
    {
        std::cerr << "Could not write xml element " << name << std::endl;
        return false;
    }
    return true;
}

bool XMLConfigWriter::writeAttribute(const char* name, const char* value)
{
    return xmlTextWriterWriteAttribute(writer, BAD_CAST name, BAD_CAST value);
}

bool XMLConfigWriter::endTag()
{
    return xmlTextWriterEndElement(writer);
}

bool XMLConfigWriter::writeTagContent(const char* content)
{
    return xmlTextWriterWriteString(writer, BAD_CAST content);
}


XMLConfigWriter::~XMLConfigWriter()
{
}
