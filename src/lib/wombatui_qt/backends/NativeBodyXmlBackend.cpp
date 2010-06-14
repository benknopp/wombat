/*
 * NativeBodyXmlBackend.cpp
 *
 *  Created on: 15.03.2010
 *      Author: bknopp
 */

#include "NativeBodyXmlBackend.h"
#include "../Configurators/Native/NativeBodyConfigurator.h"


namespace wombat
{

NativeBodyXmlBackend::NativeBodyXmlBackend()
{
	mFormatName = "NativeBodyElements";
	mVersionString = "0.1";

	mDomDocument.clear();
    mRootElement = mDomDocument.createElement(mFormatName);
    mRootElement.setAttribute("version", mVersionString);
    mDomDocument.createComment("this file is used to store a ridgid body and its dofs, as used by WOMBAT");
    mDomDocument.appendChild(mRootElement);
}


NativeBodyXmlBackend::~NativeBodyXmlBackend()
{

}


bool NativeBodyXmlBackend::read(QIODevice *_device)
{
    QString errorStr;
    int errorLine = 0, errorColumn = 0;

    if (!mDomDocument.setContent(_device, true, &errorStr, &errorLine, &errorColumn))
    {
    	Logger::criticalErrorMessage(errorStr);
        return false;
    }

    mRootElement = mDomDocument.documentElement();
    if (mRootElement.tagName() != mFormatName) {
        Logger::statusMessage("no body description file.");
        return false;
    }

    if (mRootElement.hasAttribute("version") &&
    		mRootElement.attribute("version") != mVersionString)
    {
        TRACE("not version 0.1")
        return false;
    }

    return true;
}


bool NativeBodyXmlBackend::write(QIODevice *_device)
{
    const int IndentSize = 4;
    QTextStream out(_device);
    mDomDocument.save(out, IndentSize);
    return true;
}


void NativeBodyXmlBackend::setData(const std::vector<PartInfo> &_parts,
			 const std::vector<JointInfo> &_joints,
			 const std::vector<DofInfo> &_dofs)
{
	for(std::vector<PartInfo>::const_iterator it = _parts.begin(); it != _parts.end(); it++)
	{
		elementFromPart(*it);
	}

	for(std::vector<JointInfo>::const_iterator it = _joints.begin(); it != _joints.end(); it++)
	{
		elementFromJoint(*it);
	}

	for(std::vector<DofInfo>::const_iterator it = _dofs.begin(); it != _dofs.end(); it++)
	{
		elementFromDof(*it);
	}

}


void NativeBodyXmlBackend::getData(std::vector<PartInfo> &_parts,
			 std::vector<JointInfo> &_joints,
			 std::vector<DofInfo> &_dofs) const
{
	_parts.clear();
	_joints.clear();
	_dofs.clear();

	QDomElement child = mRootElement.firstChildElement("Part");
	while (!child.isNull())
	{
		_parts.push_back(partFromElement(child));
		child = child.nextSiblingElement("Part");
	}

	child = mRootElement.firstChildElement("Joint");
	while (!child.isNull())
	{
		_joints.push_back(jointFromElement(child));
		child = child.nextSiblingElement("Joint");
	}

	child = mRootElement.firstChildElement("Dof");
	while (!child.isNull())
	{
		_dofs.push_back(dofFromElement(child));
		child = child.nextSiblingElement("Dof");
	}

}




QDomElement NativeBodyXmlBackend::elementFromPart(const PartInfo &_part)
{
	QDomElement element = mDomDocument.createElement("Part");
	mRootElement.appendChild(element);

	if(!element.isNull())
	{
		element.setAttribute("childs", QString::fromStdString(_part.childs));
		element.setAttribute("name", QString::fromStdString(_part.name));
		element.setAttribute("originTransform", QString::fromStdString(_part.originTransform));
		element.setAttribute("parent", QString::fromStdString(_part.parent));
		element.setAttribute("sizes", QString::fromStdString(_part.sizes));
	}
	return element;
}


PartInfo NativeBodyXmlBackend::partFromElement(const QDomElement &_element) const
{
	PartInfo info;
	info.childs = _element.attribute("childs", "").toStdString();
	info.name = _element.attribute("name", "").toStdString();
	info.originTransform = _element.attribute("originTransform", "").toStdString();
	info.parent = _element.attribute("parent", "").toStdString();
	info.sizes = _element.attribute("sizes", "").toStdString();
	return info;
}


QDomElement NativeBodyXmlBackend::elementFromJoint(const JointInfo &_joint)
{
	QDomElement element = mDomDocument.createElement("Joint");
	mRootElement.appendChild(element);

	if(!element.isNull())
	{
		element.setAttribute("childs", QString::fromStdString(_joint.childs));
		element.setAttribute("name", QString::fromStdString(_joint.name));
		element.setAttribute("indexFunc", QString::fromStdString(_joint.indexFunc));
		element.setAttribute("indices", QString::fromStdString(_joint.indices));
		element.setAttribute("parent", QString::fromStdString(_joint.parent));
		element.setAttribute("parentAnchor", QString::fromStdString(_joint.parentAnchor));
	}
	return element;
}


JointInfo NativeBodyXmlBackend::jointFromElement(const QDomElement &_element) const
{
	JointInfo info;
	info.childs = _element.attribute("childs", "").toStdString();
	info.indexFunc = _element.attribute("indexFunc", "").toStdString();
	info.indices = _element.attribute("indices", "").toStdString();
	info.name = _element.attribute("name", "").toStdString();
	info.parent = _element.attribute("parent", "").toStdString();
	info.parentAnchor = _element.attribute("parentAnchor", "").toStdString();
	return info;
}


QDomElement NativeBodyXmlBackend::elementFromDof(const DofInfo &_dof)
{
	QDomElement element = mDomDocument.createElement("Dof");
	mRootElement.appendChild(element);

	if(!element.isNull())
	{
		element.setAttribute("index", QString::fromStdString(_dof.index));
		element.setAttribute("type", QString::fromStdString(_dof.type));
		element.setAttribute("values", QString::fromStdString(_dof.values));
	}
	return element;
}


DofInfo NativeBodyXmlBackend::dofFromElement(const QDomElement &_element) const
{
	DofInfo info;
	info.index = _element.attribute("index", "-1").toStdString();
	info.type = _element.attribute("type", "unlimited").toStdString();
	info.values = _element.attribute("values", "0").toStdString();
	return info;
}

bool fillConfiguratorFromBackend(NativeBodyConfigurator &_configurator, const NativeBodyXmlBackend &_backend)
{
	std::vector<PartInfo> parts;
	std::vector<JointInfo> joints;
	std::vector<DofInfo> dofs;
	_backend.getData(parts, joints, dofs);

	for(std::vector<PartInfo>::iterator it = parts.begin(); it != parts.end(); it++)
	{
		_configurator.addPart(*it);
	}

	for(std::vector<JointInfo>::iterator it = joints.begin(); it != joints.end(); it++)
	{
		_configurator.addJoint(*it);
	}

	for(std::vector<DofInfo>::iterator it = dofs.begin(); it != dofs.end(); it++)
	{
		_configurator.addDof(*it);
	}

	return true;
}



}
