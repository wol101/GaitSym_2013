/*
 *  TwoCylinderWrapStrap.h
 *  GaitSymODE
 *
 *  Created by Bill Sellers on 19/12/2012.
 *  Copyright 2012 Bill Sellers. All rights reserved.
 *
 */

#ifndef TwoCylinderWrapStrap_h
#define TwoCylinderWrapStrap_h

#include "Strap.h"
#include "PGDMath.h"

class TwoCylinderWrapStrap: public Strap
{
public:

    TwoCylinderWrapStrap();
    virtual ~TwoCylinderWrapStrap();

    void SetOrigin(Body *body, dVector3 point);
    void SetInsertion(Body *body, dVector3 point);
    void SetOrigin(Body *body, const char *buf);
    void SetInsertion(Body *body, const char *buf);

    void SetCylinderBody(Body *body);
    void SetCylinder1Radius(dReal radius) { m_Cylinder1Radius = radius; };
    void SetCylinder1Position(dReal x, dReal y, dReal z);
    void SetCylinderQuaternion(dReal q0, dReal q1, dReal q2, dReal q3);
    void SetCylinderAxis(dReal x, dReal y, dReal z);
    void SetCylinder1Position(const char *buf);
    void SetCylinderQuaternion(const char *buf);
    void SetCylinderAxis(const char *buf);
    void SetCylinder2Radius(dReal radius) { m_Cylinder2Radius = radius; };
    void SetCylinder2Position(dReal x, dReal y, dReal z);
    void SetCylinder2Position(const char *buf);
    void SetNumWrapSegments(int num) { m_NumWrapSegments = num; };

    virtual void Calculate(dReal deltaT);

    void GetOrigin(Body **body, dVector3 pos) { *body = m_OriginBody; pos[0] = m_OriginPosition.x; pos[1] = m_OriginPosition.y; pos[2] = m_OriginPosition.z; };
    void GetInsertion(Body **body, dVector3 pos) { *body = m_InsertionBody; pos[0] = m_InsertionPosition.x; pos[1] = m_InsertionPosition.y; pos[2] = m_InsertionPosition.z; };
    void GetCylinder1(Body **body, dVector3 pos, dReal *radius, dQuaternion q);
    void GetCylinder2(Body **body, dVector3 pos, dReal *radius, dQuaternion q);

    virtual int SanityCheck(Strap *otherStrap, AxisType axis, const std::string &sanityCheckLeft, const std::string &sanityCheckRight);

#ifdef USE_OPENGL
    virtual void Draw();
    void SetCylinderColour(Colour &colour)  { m_CylinderColour = colour; };
    void SetCylinderLength(GLfloat length)  { m_CylinderLength = length; };
#endif

protected:

    void TwoCylinderWrap(pgd::Vector &origin, pgd::Vector &insertion, pgd::Vector &cylinderPosition1, dReal radius1,
                         pgd::Vector &cylinderPosition2, dReal radius2, dReal tension, int nPointsPerCylinderArc, dReal maxAngle,
                         pgd::Vector &originForce, pgd::Vector &insertionForce, pgd::Vector &cylinderForce1, pgd::Vector &cylinderForcePosition1,
                         pgd::Vector &cylinderForce2, pgd::Vector &cylinderForcePosition2, dReal *pathLength,
                         pgd::Vector *pathCoordinates, int *numPathCoordinates, int *wrapOK);
    void FindCircleCircleTangents(pgd::Vector &c1, dReal radius1, pgd::Vector &c2, dReal radius2,
                                  pgd::Vector &outer1_p1, pgd::Vector &outer1_p2, pgd::Vector &outer2_p1, pgd::Vector &outer2_p2,
                                  pgd::Vector &inner1_p1, pgd::Vector &inner1_p2, pgd::Vector &inner2_p1, pgd::Vector &inner2_p2, int *number_of_tangents);
    void FindTangents(pgd::Vector &center, dReal radius, pgd::Vector &external_point, pgd::Vector &pt1, pgd::Vector &pt2, int *number_of_tangents);
    void FindCircleCircleIntersections(dReal cx0, dReal cy0, dReal radius0, dReal cx1, dReal cy1, dReal radius1,
                                       pgd::Vector &intersection1, pgd::Vector &intersection2, int *number_of_intersections);

    dReal vector_distance2d(pgd::Vector &v1, pgd::Vector v2);
    dReal vector_distance3d(pgd::Vector &v1, pgd::Vector &v2);
    void vector_with_magnitude(pgd::Vector &v1, pgd::Vector &v2, dReal magnitude, pgd::Vector &v);

    Body *m_OriginBody;
    pgd::Vector m_OriginPosition;
    Body *m_InsertionBody;
    pgd::Vector m_InsertionPosition;

    Body *m_CylinderBody;
    pgd::Vector m_Cylinder1Position;
    pgd::Quaternion m_CylinderQuaternion;
    dReal m_Cylinder1Radius;
    pgd::Vector m_Cylinder2Position;
    dReal m_Cylinder2Radius;
    int m_NumWrapSegments;

    int m_WrapStatus;

    pgd::Vector *m_PathCoordinates;
    int m_NumPathCoordinates;

#ifdef USE_OPENGL
    Colour m_CylinderColour;
    GLfloat m_CylinderLength;
#endif
};

#endif

