#include "BodyPartXmlBackend.h"
#include <wombat/helpers.h>

namespace wombat
{


    BodyPartXmlBackend::BodyPartXmlBackend() : mDomDocument("MyBPL")
    {
        mRootElement = mDomDocument.createElement("BodyParts");
        mRootElement.setAttribute("version", "0.1");
        mDomDocument.appendChild(mRootElement);
    }

    bool BodyPartXmlBackend::read(QIODevice *_device)
    {
        QString errorStr;
        int errorLine;
        int errorColumn;

        if (!mDomDocument.setContent(_device, true, &errorStr, &errorLine, &errorColumn))
        {
            TRACE("Parse error at line %i, column %i: %s",
                  errorLine, errorColumn, errorStr.toStdString().c_str());
            return false;
        }

        QDomElement root = mDomDocument.documentElement();
        if (root.tagName() != "BodyParts") {
            TRACE("no bodyparts list.");
            return false;
        } else if (root.hasAttribute("version") && root.attribute("version") != "0.1")
        {
            TRACE("not version 0.1")
            return false;
        }

        QDomElement child = root.firstChildElement("BodyPart");
        while (!child.isNull()) {
//            TRACE("parsing child");
            parseBodyPart(child);
            child = child.nextSiblingElement("BodyPart");
        }

        return true;
    }

    bool BodyPartXmlBackend::write(QIODevice *device)
    {
//        TRACE("writing %i DOM-elements.", mNodeMap.size());
        const int IndentSize = 4;

        QTextStream out(device);
        mDomDocument.save(out, IndentSize);
        return true;
    }

    void BodyPartXmlBackend::insertBodyPartNode(BodyPartNode &_node)
    {
        QString key = QString::fromStdString(_node.name);

        QDomElement element = mDomDocument.createElement("BodyPart");
        mRootElement.appendChild(element);

        if(!element.isNull())
        { // element NOT exists
            element.setTagName("BodyPart");
            element.setAttribute("name", key);
            element.setAttribute("xsize", (double) _node.size.x());
            element.setAttribute("ysize", (double) _node.size.y());
            element.setAttribute("zsize", (double) _node.size.z());
        }
    }

    BodyPartNode BodyPartXmlBackend::bodyPartNode(unsigned _index) const
    {
        BodyPartNode node;
        if(_index < (unsigned) mNodeMap.size()) node = mNodeMap.value(mNodeMap.keys().at(_index));
        return node;
    }

    bool BodyPartXmlBackend::findBodyPartNode(const QString &_name, BodyPartNode &_node) const
    {
        bool success = mNodeMap.contains(_name);
        if(success)
        {
            _node = mNodeMap.value(_name);
        }

        return success;
    }

    void BodyPartXmlBackend::parseBodyPart(const QDomElement &_element)
    {
        QString name = _element.attribute("name");//_element.firstChildElement("name").text();
        double xsize = _element.attribute("xsize").toDouble();//_element.firstChildElement("xsize").text().toDouble();
        double ysize = _element.attribute("ysize").toDouble();//_element.firstChildElement("ysize").text().toDouble();
        double zsize = _element.attribute("zsize").toDouble();//_element.firstChildElement("zsize").text().toDouble();

//        TRACE("found element %s -> [%f;%f;%f]", name.toStdString().c_str(), xsize, ysize, zsize);

        BodyPartNode node;
        node.name = name.toStdString();
        node.size << xsize, ysize, zsize;
        mNodeMap.insert(name, node);
    }

}
