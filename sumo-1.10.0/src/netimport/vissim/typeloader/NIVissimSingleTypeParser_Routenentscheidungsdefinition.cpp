/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2021 German Aerospace Center (DLR) and others.
// This program and the accompanying materials are made available under the
// terms of the Eclipse Public License 2.0 which is available at
// https://www.eclipse.org/legal/epl-2.0/
// This Source Code may also be made available under the following Secondary
// Licenses when the conditions for such availability set forth in the Eclipse
// Public License 2.0 are satisfied: GNU General Public License, version 2
// or later which is available at
// https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
/****************************************************************************/
/// @file    NIVissimSingleTypeParser_Routenentscheidungsdefinition.cpp
/// @author  Daniel Krajzewicz
/// @author  Michael Behrisch
/// @date    Wed, 18 Dec 2002
///
//
/****************************************************************************/
#include <config.h>

#include <iostream>
#include <utils/common/StringUtils.h>
#include "../NIImporter_Vissim.h"
#include "NIVissimSingleTypeParser_Routenentscheidungsdefinition.h"


// ===========================================================================
// method definitions
// ===========================================================================
NIVissimSingleTypeParser_Routenentscheidungsdefinition::NIVissimSingleTypeParser_Routenentscheidungsdefinition(NIImporter_Vissim& parent)
    : NIImporter_Vissim::VissimSingleTypeParser(parent) {}


NIVissimSingleTypeParser_Routenentscheidungsdefinition::~NIVissimSingleTypeParser_Routenentscheidungsdefinition() {}


bool
NIVissimSingleTypeParser_Routenentscheidungsdefinition::parse(std::istream& from) {
    std::string tag;
    while (tag != "fahrzeugklassen") {
        tag = myRead(from);
    }
    do {
        while (tag != "DATAEND" || tag == "route") {
            if (tag == "route") {
                while (tag != "strecke") {
                    tag = myRead(from);
                }
                tag = readEndSecure(from);
            } else {
                tag = readEndSecure(from);
            }
        }
        if (tag != "DATAEND") {
            tag = readEndSecure(from);
        }
    } while (tag != "DATAEND");
    return true;
}


/****************************************************************************/
