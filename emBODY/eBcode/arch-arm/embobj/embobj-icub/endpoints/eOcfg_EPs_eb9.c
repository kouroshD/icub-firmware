/*
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
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

/* @file       eOcfg_EPs_eb9.c
    @brief      This file keeps ...
    @author     marco.accame@iit.it
    @date       09/06/2011
**/


// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "stdlib.h" 
#include "string.h"
#include "stdio.h"





#include "EOconstvector_hid.h"





#include "eOcfg_nvsEP_mngmnt_con.h"
#include "eOcfg_nvsEP_mngmnt_usr.h"

#include "eOcfg_nvsEP_mc_any_con_bodypart.h"

#include "eOcfg_nvsEP_mc_lowerleg_con.h"
#include "eOcfg_nvsEP_mc_lowerleg_usr.h"




// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------

#include "eOcfg_EPs_eb9.h"


// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern hidden interface 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------

static uint16_t s_hash(uint16_t ep);

static uint16_t s_eo_cfg_nvsEP_eb9_hashfunction_ep2index(uint16_t ep);

// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------


extern const EOconstvector  s_eo_cfg_nvsEP_mngmnt_constvector_of_treenodes_EOnv_con;
extern const EOconstvector  s_eo_cfg_nvsEP_mngmnt_usr_constvector_of_EOnv_usr;


extern const EOconstvector  s_eo_cfg_nvsEP_mc_lowerleg_constvector_of_treenodes_EOnv_con;
extern const EOconstvector  s_eo_cfg_nvsEP_mc_lowerleg_usr_constvector_of_EOnv_usr;



static const eOnvscfg_EP_t s_eo_cfg_EPs_vectorof_eb9_data[] =
{  
    {   // mngmnt
        EO_INIT(.endpoint)                          EOK_cfg_nvsEP_mngmnt_EP,
        EO_INIT(.sizeof_endpoint_data)              EOK_cfg_nvsEP_mngmnt_RAMSIZE,
        EO_INIT(.hashfunction_id2index)             eo_cfg_nvsEP_mngmnt_hashfunction_id2index,
        EO_INIT(.constvector_of_treenodes_EOnv_con) &s_eo_cfg_nvsEP_mngmnt_constvector_of_treenodes_EOnv_con, 
        EO_INIT(.constvector_of_EOnv_usr)           &s_eo_cfg_nvsEP_mngmnt_usr_constvector_of_EOnv_usr, 
        EO_INIT(.endpoint_data_init)                eo_cfg_nvsEP_mngmnt_usr_initialise
    }, 

    {   // mc-rightleg-lower
        EO_INIT(.endpoint)                          EOK_cfg_nvsEP_mc_rightlowerleg_EP,
        EO_INIT(.sizeof_endpoint_data)              sizeof(eo_cfg_nvsEP_mc_lowerleg_t),
        EO_INIT(.hashfunction_id2index)             eo_cfg_nvsEP_mc_lowerleg_hashfunction_id2index,
        EO_INIT(.constvector_of_treenodes_EOnv_con) &s_eo_cfg_nvsEP_mc_lowerleg_constvector_of_treenodes_EOnv_con, 
        EO_INIT(.constvector_of_EOnv_usr)           &s_eo_cfg_nvsEP_mc_lowerleg_usr_constvector_of_EOnv_usr, 
        EO_INIT(.endpoint_data_init)                eo_cfg_nvsEP_mc_lowerleg_usr_initialise
    }
    
};

static const EOconstvector s_eo_cfg_EPs_vectorof_eb9 = 
{
    EO_INIT(.size)                  sizeof(s_eo_cfg_EPs_vectorof_eb9_data)/sizeof(const eOnvscfg_EP_t),
    EO_INIT(.item_size)             sizeof(eOnvscfg_EP_t),
    EO_INIT(.item_array_data)       s_eo_cfg_EPs_vectorof_eb9_data
};



// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables
// --------------------------------------------------------------------------------------------------------------------


extern const EOconstvector* const eo_cfg_EPs_vectorof_eb9 = &s_eo_cfg_EPs_vectorof_eb9;

extern const eOuint16_fp_uint16_t eo_cfg_nvsEP_eb9_fptr_hashfunction_ep2index = s_eo_cfg_nvsEP_eb9_hashfunction_ep2index;



// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------
// - definition of extern hidden functions 
// --------------------------------------------------------------------------------------------------------------------
// empty-section

// --------------------------------------------------------------------------------------------------------------------
// - definition of static functions 
// --------------------------------------------------------------------------------------------------------------------

static uint16_t s_hash(uint16_t ep)
{
    uint16_t r = ep & 0xff;
    
    if(EOK_cfg_nvsEP_mngmnt_EP == r)
    {
        return(0);
    }
    else if(EOK_cfg_nvsEP_mc_rightlowerleg_EP == r)
    {
        return(1);
    }

    
    return(EOK_uint16dummy);
    #warning --> ma meglio usare una tabella con i numeri 0, 1  in posizione corrispondente al valore di r. magari una tabella comune definita in endpoints.c
}

static uint16_t s_eo_cfg_nvsEP_eb9_hashfunction_ep2index(uint16_t ep)
{
    // in order to always have a hit the table s_eptable[] it must be of size equal to max{ s_hash(ep) }, thus if we
    // use an ep of value 16 and s_hash() just keeps the lsb, then the size must be 17 
    // if there are holes, they shall have EOK_uint16dummy in other entries. for example, if we have eps = {0, 7, 16}
    // then the table shall be of size 17, shall contain 0xffff everywhere but in positions 0, 7, 16 where the values
    // are ... 0, 7, 16    


    #define EPTABLESIZE     2

    static const uint16_t s_eptable[EPTABLESIZE] = 
    { 
        EOK_cfg_nvsEP_mngmnt_EP,        EOK_cfg_nvsEP_mc_rightlowerleg_EP
    };
   
    uint16_t index = s_hash(ep);
    
    if((index < EPTABLESIZE) && (ep == s_eptable[index]) )
    {
        return(index);
    }
    else
    {
        return(EOK_uint16dummy);
    }
}



// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------



