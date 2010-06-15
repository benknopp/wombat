/*
 * QNativeBodyXmlBackend.h
 *
 *  Created on: 15.03.2010
 *      Author: bknopp
 */

#ifndef QNATIVEBODYXMLBACKEND_H_
#define QNATIVEBODYXMLBACKEND_H_

#include <wombat/body.h>

#include <QtXml>
#include <vector>

/*
 *
 */
namespace wombat
{

class NativeBodyConfigurator;

class QNativeBodyXmlBackend
{
	public:
		QNativeBodyXmlBackend();
		virtual ~QNativeBodyXmlBackend();

        bool read(QIODevice *device);
        bool write(QIODevice *device);

		void setData(const std::vector<PartInfo> &_parts,
					 const std::vector<JointInfo> &_joints,
					 const std::vector<DofInfo> &_dofs);


		void getData(std::vector<PartInfo> &_parts,
					 std::vector<JointInfo> &_joints,
					 std::vector<DofInfo> &_dofs) const;

	protected:
		QDomElement elementFromPart(const PartInfo &_part);
		PartInfo partFromElement(const QDomElement &_element) const ;

		QDomElement elementFromJoint(const JointInfo &_joint);
		JointInfo jointFromElement(const QDomElement &_element) const;

		QDomElement elementFromDof(const DofInfo &_dof);
		DofInfo dofFromElement(const QDomElement &_element) const;

        QDomDocument mDomDocument;
        QDomElement mRootElement;
        QString mFormatName, mVersionString;


};


bool fillConfiguratorFromBackend(NativeBodyConfigurator &_configurator, const QNativeBodyXmlBackend &_backend);

}

#endif /* QNATIVEBODYXMLBACKEND_H_ */
