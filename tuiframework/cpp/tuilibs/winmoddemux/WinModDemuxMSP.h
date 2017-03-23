/*
    Copyright (C) 2010, 2011, 2012 The Fraunhofer Institute for Production Systems and
    Design Technology IPK. All rights reserved.

    This file is part of the TUIFramework library.
    It includes a software framework which contains common code
    providing generic functionality for developing applications
    with a tangible user interface (TUI).
    designed for creating applications with a tangible user interface (TUI).
    
    The TUIFramework library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    The TUIFramework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with the TUIFramework.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef _tuiframework_XControllerDemuxMSP_h_
#define _tuiframework_XControllerDemuxMSP_h_

#include <tuiframework/server/MSPConfig.h>
#include <tuiframework/server/MSPType.h>
#include <TUIPlugins/tuitypes/common/CommonTypeReg.h>
#include <tuiframework/core/IMSP.h>
#include <tuiframework/core/EventDelegate.h>

#include <string>
#include <map>

namespace tuiframework {

/**
 * \brief A MSP-Type to Demuxing WinMod-Data into 4 Data-Type Streams.
 *	
 *	This MSP-Type is used to split the Data coming from WinModData-Object to 4 Data-Type-streams. One for Float,Bytes,Word and DWords each.
 *	This Data-streams can be manipulated and given after to an EventSink. 
 *
 * \author Sebastian Keppler
 * \date 2015
 *
 * \sa IMSP Interface of MSP
 */

class WinModDemuxMSP : public IMSP {
public:

    /**
     * \brief Creates a function.
     *
     * \author Sebastian Keppler
     * \date 04.02.2016
     *
     * \param [in,out] arg If non-null, the argument.
     *
     * \return null if it fails, else the new function.
     */

    static IMSP * createFunction(void * arg);

    /**
     * \brief Gets MSP-Type name.
     *
     * \author Sebastian Keppler
     * \date 04.02.2016
     *
     * \return The MSP-type name.
     */

    static const std::string & getMSPTypeName();

    /**
     * \brief Constructor.
     *
     * \author Sebastian Keppler
     * \date 04.02.2016
     *
     * \param config The MSP-configuration.
     */

    WinModDemuxMSP(const MSPConfig & config);

    /**
     * \brief Destructor.
     *
     * \author Sebastian Keppler
     * \date 04.02.2016
     */

    virtual ~WinModDemuxMSP();

    /**
     * \brief Gets type name.
     *
     * \author Sebastian Keppler
     * \date 04.02.2016
     *
     * \return The type name.
     */

    virtual const std::string & getTypeName() const;

    /**
     * \brief Gets event sink.
     *
     * \author Sebastian Keppler
     * \date 04.02.2016
     *
     * \param name The name.
     *
     * \return null if it fails, else the event sink.
     */

    virtual IEventSink * getEventSink(const std::string & name);

    /**
     * \brief Registers the event sink.
     *
     * \author Sebastian Keppler
     * \date 04.02.2016
     *
     * \param name				 The name.
     * \param [in,out] eventSink If non-null, the event sink.
     */

    virtual void registerEventSink(const std::string & name, IEventSink * eventSink);

    /**
     * \brief Gets MSP-type.
     *
     * \author Sebastian Keppler
     * \date 04.02.2016
     *
     * \return The MSP-type.
     */

    virtual const MSPType & getMSPType() const;

    /**
     * \brief Handles the WinMod-Event described by e.
     *
     * \author Sebastian Keppler
     * \date 04.02.2016
     *
     * \param [in,out] e If non-null, the WinModEvent to process.
     */

    void handleWinModEvent(WinModEvent * e);

protected:
    /** \brief The configuration. */
    MSPConfig config;
    /** \brief The type. */
    MSPType type;

    /** \brief The WinMod event delegate. */
    EventDelegateNC<WinModEvent, WinModDemuxMSP> winModEventDelegate;
    /** \brief The name to identifier map. */
    std::map<std::string, int> nameToIdMap;

    /** \brief Array of EventSinks with the Size of 4, one for Float,Byte,Word and DWord each */
    IEventSink * out[4];
private:
	WinModData wd_temp;
};

}

#endif