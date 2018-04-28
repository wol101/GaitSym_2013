/*
 *  StackedBoxCarDriver.h
 *  GaitSymODE
 *
 *  Created by Bill Sellers on Thu Feb 21 2013.
 *  Copyright (c) 2013 Bill Sellers. All rights reserved.
 *
 *  Uses a cyclic boxcar function to return a the value at a given time
 *
 */

#ifndef STACKEDBOXCARDRIVER_H
#define STACKEDBOXCARDRIVER_H

#include <vector>
#include "Driver.h"

class StackedBoxCarDriver : public Driver
{
public:
    StackedBoxCarDriver();
    ~StackedBoxCarDriver();

    void SetStackSize(int StackSize);
    void SetCycleTimes(dReal *CycleTimes);
    void SetDelays(dReal *Delays);
    void SetWidths(dReal *Widths);
    void SetHeights(dReal *Heights);

    std::vector<dReal> *GetCycleTimes() { return &m_CycleTimes; }
    std::vector<dReal> *GetDelays() { return &m_Delays; }
    std::vector<dReal> *GetWidths() { return &m_Widths; }
    std::vector<dReal> *GetHeights() { return &m_Heights; }

    dReal GetValue(dReal Time);

protected:
    std::vector<dReal> m_CycleTimes;
    std::vector<dReal> m_Delays;
    std::vector<dReal> m_Widths;
    std::vector<dReal> m_Heights;
    int m_StackSize;
};

#endif // STACKEDBOXCARDRIVER_H

