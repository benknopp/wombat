/*
 * BodyPartXmlBackend.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp@uni-koblenz.de
 */
#ifndef BODYPARTXMLBACKEND_H
#define BODYPARTXMLBACKEND_H

#include "../BodyNodes.h"
#include <QtXml>


namespace wombat
{
    class BodyPartXmlBackend
     {
     public:
         BodyPartXmlBackend();
         bool read(QIODevice *device);
         bool write(QIODevice *device);

         // insert or override node in dom-tree
         void insertBodyPartNode(BodyPartNode &_node);
         unsigned size() const{return mNodeMap.size();}
         BodyPartNode bodyPartNode(unsigned _index) const;
         bool findBodyPartNode(const QString &_name, BodyPartNode &_node) const;
     private:
         void parseBodyPart(const QDomElement &_element);

         QDomDocument mDomDocument;
         QDomElement mRootElement;
         //QHash<QString, QDomElement> mHashMap;
         QMap<QString, BodyPartNode> mNodeMap;
     };

}
#endif // BODYPARTXMLBACKEND_H
