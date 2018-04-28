/*
 *  FacettedObject.h
 *  GaitSymODE
 *
 *  Created by Bill Sellers on 13/09/2005.
 *  Copyright 2005 Bill Sellers. All rights reserved.
 *
 */

#ifndef FacetedObject_h
#define FacetedObject_h

#include "NamedObject.h"

class DataFile;
class TrimeshGeom;
class ostringstream;

class FacetedObject: public NamedObject
{
public:
    FacetedObject();
    ~FacetedObject();

    bool ParseOBJFile(const char *filename);
    bool ParseOBJFile(DataFile &theFile);

    virtual void WritePOVRay(std::ostringstream &theString);
    virtual void WriteOBJFile(std::ostringstream &out);

    int GetNumVertices() { return mNumVertices; }
    dReal *GetVertex(int i) { return mVertexList + (3 * i); }
    dReal *GetNormal(int i) { return mNormalList + (3 * i); }
    dReal *GetVertexList() { return mVertexList; }
    dReal *GetNormalList() { return mNormalList; }
    int *GetIndexList() { return mIndexList; }

    void AddPolygon(const dReal *vertices, int nSides);
    void AddTriangle(const dReal *vertices);

    int GetNumTriangles() { return mNumVertices / 3; }
    dReal *GetTriangle(int i) { return mVertexList + (9 * i); }

    virtual void Draw();
    void SetDisplayPosition(dReal x, dReal y, dReal z);
    void SetDisplayRotation(const dMatrix3 R, bool fast = true);
    void SetDisplayRotationFromQuaternion(const dQuaternion q, bool fast = true);
    void SetDisplayRotationFromAxis(dReal x, dReal y, dReal z, bool fast = true);

    const dReal *GetDisplayPosition()  { return m_DisplayPosition; }
    const dReal *GetDisplayRotation()  { return m_DisplayRotation; }

    // static utilities
    static void ComputeFaceNormal(const dReal *v1, const dReal *v2, const dReal *v3, dReal normal[3]);

    // manipulation functions
    void Move(dReal x, dReal y, dReal z);
    void Scale(dReal x, dReal y, dReal z);
    void Mirror(bool x, bool y, bool z);
    void SwapAxes(int axis1, int axis2);
    void RotateAxes(int axis0, int axis1, int axis2);

    // utility
    void ReverseWinding();
    void AllocateMemory(int allocation);
    void SetVerticesAsSpheresRadius(dReal verticesAsSpheresRadius) { m_VerticesAsSpheresRadius = verticesAsSpheresRadius; }

    // ODE link
    void CalculateTrimesh(double **vertices, int *numVertices, int *vertexStride, dTriIndex **triIndexes, int *numTriIndexes, int *triStride);
    void CalculateTrimesh(float **vertices, int *numVertices, int *vertexStride, dTriIndex **triIndexes, int *numTriIndexes, int *triStride);
    void CalculateMassProperties(dMass *m, dReal density, bool clockwise);

#ifdef USE_OPENGL
    void SetBadMesh(bool v) { m_BadMesh = v; }
#endif

protected:

    int mNumVertices;
    int mNumVerticesAllocated;
    dReal *mVertexList;
    dReal *mNormalList;
    int *mIndexList;

    dVector3 m_DisplayPosition;
    dMatrix3 m_DisplayRotation;

    bool m_UseRelativeOBJ;

    dReal m_VerticesAsSpheresRadius;

#ifdef USE_OPENGL
    GLuint m_BufferObjects[3];
    bool m_BufferObjectsAllocated;
    bool m_BadMesh;
#endif

    static const int kAllocationIncrement = 10000;
};

#endif
