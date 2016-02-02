/*
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author:  Valentina Gaggero, Davide Pollarolo
 * email:   valentina.gaggero@iit.it, davide.pollarolo@iit.it
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/


// - include guard ----------------------------------------------------------------------------------------------------

#ifndef _EOAPPENCODERSREADER_HID_H_
#define _EOAPPENCODERSREADER_HID_H_


// - doxy -------------------------------------------------------------------------------------------------------------
/* @file       EOappEncodersReader.h
    @brief     This file provides hidden interface to encodersReader obj.
    @author    valentina.gaggero@iit.it, davide.pollarolo@iit.it
    @date       02/17/2012
**/


// - external dependencies --------------------------------------------------------------------------------------------


#include "hal_spiencoder.h"


// - declaration of extern public interface ---------------------------------------------------------------------------

#include "EOappEncodersReader.h"


// - definition of the hidden struct implementing the object ----------------------------------------------------------

typedef struct
{                                       
    eOmn_serv_mc_sensor_t       primary;
    eOmn_serv_mc_sensor_t       secondary;
} eOappEncReader_jomoconfig_t;


typedef struct
{   
    uint8_t                     numofjomos;  
    eOappEncReader_jomoconfig_t jomoconfig[eOappEncReader_jomos_maxnumberof];                           
} eOappEncReader_cfg_t;


typedef struct 
{
    hal_spiencoder_type_t   type;                               /**< the type of SPI encoders. it must be only one */
    uint8_t                 numberof;                           /**< their number inside the stream */
    uint8_t                 maxsupported;
    volatile eObool_t       isacquiring;                        
    hal_spiencoder_t        id[hal_spiencoder_maxnumber_in_stream+1]; // reading order of encoders 
} eOappEncReader_stream_t;


struct EOappEncReader_hid
{
    eObool_t                                initted;
    eObool_t                                active;
    uint8_t                                 totalnumberofencoders; // it cannot be higher than eOappEncReader_encoders_maxnumberof
    const hal_spiencoder_stream_map_t*      stream_map;
    eOappEncReader_cfg_t                    config;       
    eOappEncReader_stream_t                 SPI_streams[hal_spiencoder_streams_number];  // SPI streams; must be coherent with what inside cfg
}; 


// - declaration of extern hidden functions ---------------------------------------------------------------------------
// empty-section


#endif  // include guard

// - end-of-file (leave a blank line after)----------------------------------------------------------------------------



