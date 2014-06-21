/*!  \brief  ProtoPlane.h: Simple plane
 ProtoPlane.h
 Protobyte Library v02
 
 Created by Ira on 7/23/13.
 Copyright (c) 2013 Ira Greenberg. All rights reserved.
 
 Library Usage:
 This work is licensed under the Creative Commons
 Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 To view a copy of this license, visit
 http://creativecommons.org/licenses/by-nc-sa/3.0/
 or send a letter to Creative Commons,
 444 Castro Street, Suite 900,
 Mountain View, California, 94041, USA.
 
 This notice must be retained any source distribution.
 
 \ingroup common
 This class is part of the group common (update)
 \sa NO LINK
 */

#ifndef PROTO_PLANE_H
#define	PROTO_PLANE_H

#include "ProtoGeom3.h"

namespace ijg {

	// forward declare & create namespace safe shortname
	class ProtoPlane;
	typedef ProtoPlane Plane;
	
	class ProtoPlane : public ProtoGeom3 {
    public:
        friend std::ostream& operator<<(std::ostream& out, const ProtoPlane& plane);

        ProtoPlane();
        
		ProtoPlane(const Vec3f& pos, const Vec3f& rot, const Dim2f& size,
                const Col4f& col4, int rows, int columns);

		ProtoPlane(const Vec3f& pos, const Vec3f& rot, const Dim2f& size,
			const Col4f& col4, int rows, int columns, const std::string& textureImageURL, float textureScale = 1);

		ProtoPlane(const Vec3f& pos, const Vec3f& rot, const Dim2f& size,
			const Col4f& col4, int rows, int columns, const std::vector<std::string>& textureImageURLs, float textureScale = 1);

		

        void calcVerts();
        void calcInds();

        void setRows(int rows);
        int getRows() const;
        void setColumns(int columns);
        int getColumns() const;

    private:
        int columns, rows;


    };

    inline void ProtoPlane::setRows(int rows) {
        this->rows = rows;
    }

    inline int ProtoPlane::getRows() const {
        return rows;
    }

    inline void ProtoPlane::setColumns(int columns) {
        this->columns = columns;
    }

    inline int ProtoPlane::getColumns() const {
        return columns;
    }
}

#endif	/* PROTO_PLANE_H */

