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

/* @file       eOcfg_nvsEP_as_onestrain_con.c
    @brief      This file keeps ....
    @author     marco.accame@iit.it
    @date       09/06/2011
**/


// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "stdlib.h" 
#include "string.h"
#include "stdio.h"

#include "EoCommon.h"
#include "EOnv_hid.h"
#include "EOtreenode_hid.h"
#include "EOconstvector_hid.h"


#include "eOcfg_nvsEP_as_any_con_sxx.h"    
#include "eOcfg_nvsEP_as_any_con_sxxdefault.h" 

#include "eOcfg_nvsEP_as_any_con_mxx.h"    
#include "eOcfg_nvsEP_as_any_con_mxxdefault.h" 



// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------

#include "eOcfg_nvsEP_as_onestrain_con.h"


// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern hidden interface 
// --------------------------------------------------------------------------------------------------------------------

#include "eOcfg_nvsEP_as_onestrain_con_hid.h"

// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------

static uint16_t s_hash(uint16_t id);

// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------


// -- the 1 strain

#define SMACRO_EXTERNALPREFIX_GETID                EOK_cfg_nvsEP_as_onestrain_con_NVID_sxx


// strain 00
#define SMACRO_PSTR      _onestrain
#define SMACRO_STR       _s00
#define SMACRO_PNUM      5
#define SMACRO_NUM       0    
#define SMACRO_OFF      (SMACRO_NUM*sizeof(eOsnsr_strain_t))

#include "eOcfg_nvsEP_as_any_con_sxxmacro.c"


#define OFFSET_OF_END_OF_STRAINS    (strainUpperArm_TOTALnumber*sizeof(eOsnsr_strain_t))


// -- the 0 mais

#define MMACRO_EXTERNALPREFIX_GETID                EOK_cfg_nvsEP_as_onestrain_con_NVID_mxx
        

//// mais 00
//#define MMACRO_PSTR    _onestrain
//#define MMACRO_STR    _m00
//#define MMACRO_PNUM    5
//#define MMACRO_NUM    0    
//#define MMACRO_OFF    (OFFSET_OF_END_OF_STRAINS+MMACRO_NUM*sizeof(eOsnsr_mais_t))
//
//#include "eOcfg_nvsEP_as_any_con_mxxmacro.c"





// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables
// --------------------------------------------------------------------------------------------------------------------


#define Snvs    (EOK_cfg_nvsEP_as_any_con_sxx_snvindex_TOTALnumber)

// strainUpperArm_TOTALnumber is 1 and is the number of strain in the onestrain
#define SNUM    (strainUpperArm_TOTALnumber)


// it is the start of index for the strain
#define Sstart  (0)

#define Sindex(s, i)   (Sstart + (s)*Snvs + (i))




#define Mnvs    (EOK_cfg_nvsEP_as_any_con_mxx_mnvindex_TOTALnumber)

// mais_TOTALnumber is 0 and is the number of mais in the onestrain
#define MNUM     (maisUpperArm_TOTALnumber)


// it is the start of index for the motors
#define Mstart  (Snvs*SNUM+0)

#define Mindex(m, i)   (Mstart + (m)*Mnvs + (i))



extern EOtreenode eo_cfg_nvsEP_as_onestrain_tree_con[] =
{
    // strain s00
    {   // 0
        EO_INIT(.data)      (void*)&eo_cfg_nvsEP_as_onestrain_s00_sconfig__mode,
        EO_INIT(.index)     Sindex(0, 0),
        EO_INIT(.nchildren) 0,
        EO_INIT(.ichildren) {0},
        EO_INIT(.pchildren) {NULL}
    },
    {   // 1
        EO_INIT(.data)      (void*)&eo_cfg_nvsEP_as_onestrain_s00_sconfig__datarate,
        EO_INIT(.index)     Sindex(0, 1),
        EO_INIT(.nchildren) 0,
        EO_INIT(.ichildren) {0},
        EO_INIT(.pchildren) {NULL}
    },  
    {   // 2
        EO_INIT(.data)      (void*)&eo_cfg_nvsEP_as_onestrain_s00_sconfig__signaloncefullscale,
        EO_INIT(.index)     Sindex(0, 2),
        EO_INIT(.nchildren) 0,
        EO_INIT(.ichildren) {0},
        EO_INIT(.pchildren) {NULL}
    },
    {   // 3
        EO_INIT(.data)      (void*)&eo_cfg_nvsEP_as_onestrain_s00_sstatus__fullscale,
        EO_INIT(.index)     Sindex(0, 3),
        EO_INIT(.nchildren) 0,
        EO_INIT(.ichildren) {0},
        EO_INIT(.pchildren) {NULL}
    },  
    {   // 4
        EO_INIT(.data)      (void*)&eo_cfg_nvsEP_as_onestrain_s00_sstatus__calibratedvalues,
        EO_INIT(.index)     Sindex(0, 4),
        EO_INIT(.nchildren) 0,
        EO_INIT(.ichildren) {0},
        EO_INIT(.pchildren) {NULL}
    },  
    {   // 5
        EO_INIT(.data)      (void*)&eo_cfg_nvsEP_as_onestrain_s00_sstatus__uncalibratedvalues,
        EO_INIT(.index)     Sindex(0, 5),
        EO_INIT(.nchildren) 0,
        EO_INIT(.ichildren) {0},
        EO_INIT(.pchildren) {NULL}
    }   
    
     
    
    // the 0 mais
#if 0  
    ,  
    // mais_00
    {   // 0
        EO_INIT(.data)      (void*)&eo_cfg_nvsEP_as_onestrain_m00_mconfig__mode,
        EO_INIT(.index)     Mindex(0, 0),
        EO_INIT(.nchildren) 0,
        EO_INIT(.ichildren) {0},
        EO_INIT(.pchildren) {NULL}
    },
    {   // 1
        EO_INIT(.data)      (void*)&eo_cfg_nvsEP_as_onestrain_m00_mconfig__datarate,
        EO_INIT(.index)     Mindex(0, 1),
        EO_INIT(.nchildren) 0,
        EO_INIT(.ichildren) {0},
        EO_INIT(.pchildren) {NULL}
    },  
    {   // 2
        EO_INIT(.data)      (void*)&eo_cfg_nvsEP_as_onestrain_m00_mconfig__resolution,
        EO_INIT(.index)     Mindex(0, 2),
        EO_INIT(.nchildren) 0,
        EO_INIT(.ichildren) {0},
        EO_INIT(.pchildren) {NULL}
    },
    {   // 3
        EO_INIT(.data)      (void*)&eo_cfg_nvsEP_as_onestrain_m00_mstatus__the15values,
        EO_INIT(.index)     Mindex(0, 3),
        EO_INIT(.nchildren) 0,
        EO_INIT(.ichildren) {0},
        EO_INIT(.pchildren) {NULL}
    }
    
#endif
       
    
};  EO_VERIFYsizeof(eo_cfg_nvsEP_as_onestrain_tree_con, sizeof(EOtreenode)*(varsASonestrain_TOTALnumber));





const EOconstvector  s_eo_cfg_nvsEP_as_onestrain_constvector_of_treenodes_EOnv_con = 
{
    EO_INIT(.size)              sizeof(eo_cfg_nvsEP_as_onestrain_tree_con)/sizeof(EOtreenode), //EOK_cfg_nvsEP_onestrain_numberof,
    EO_INIT(.item_size)         sizeof(EOtreenode),
    EO_INIT(.item_array_data)   eo_cfg_nvsEP_as_onestrain_tree_con
};


extern const EOconstvector* const eo_cfg_nvsEP_as_onestrain_constvector_of_treenodes_EOnv_con = &s_eo_cfg_nvsEP_as_onestrain_constvector_of_treenodes_EOnv_con;


extern const eOuint16_fp_uint16_t eo_cfg_nvsEP_as_onestrain_fptr_hashfunction_id2index = eo_cfg_nvsEP_as_onestrain_hashfunction_id2index;


// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------

extern uint16_t eo_cfg_nvsEP_as_onestrain_hashfunction_id2index(uint16_t id)
{

    #define IDTABLESSIZE        (EOK_cfg_nvsEP_as_any_con_sxx_snvindex_TOTALnumber*strainUpperArm_TOTALnumber)
    
    #define IDTABLEMSIZE        (EOK_cfg_nvsEP_as_any_con_mxx_mnvindex_TOTALnumber*maisUpperArm_TOTALnumber)    
    
    #define IDTABLESIZE         (IDTABLESSIZE+IDTABLEMSIZE)
    

    static const uint16_t s_idtable[] = 
    { 
        // s00
        EOK_cfg_nvsEP_as_onestrain_con_NVID_sxx_sconfig__mode(0),                   EOK_cfg_nvsEP_as_onestrain_con_NVID_sxx_sconfig__datarate(0),
        EOK_cfg_nvsEP_as_onestrain_con_NVID_sxx_sconfig__signaloncefullscale(0),    EOK_cfg_nvsEP_as_onestrain_con_NVID_sxx_sstatus__fullscale(0), 
        EOK_cfg_nvsEP_as_onestrain_con_NVID_sxx_sstatus__calibratedvalues(0),       EOK_cfg_nvsEP_as_onestrain_con_NVID_sxx_sstatus__uncalibratedvalues(0)  
        
        // m00
//        EOK_cfg_nvsEP_as_onestrain_con_NVID_mxx_mconfig__mode(0),                   EOK_cfg_nvsEP_as_onestrain_con_NVID_mxx_mconfig__datarate(0),
//        EOK_cfg_nvsEP_as_onestrain_con_NVID_mxx_mconfig__resolution(0),             EOK_cfg_nvsEP_as_onestrain_con_NVID_mxx_mstatus__the15values(0), 
    
    };  EO_VERIFYsizeof(s_idtable, sizeof(uint16_t)*(IDTABLESIZE));
    
    uint16_t index = s_hash(id);
    
   
    if((index < (IDTABLESIZE)) && (id == s_idtable[index]) )
    {
        return(index);
    }
    else
    {
        return(EOK_uint16dummy);
    }

      
}



// --------------------------------------------------------------------------------------------------------------------
// - definition of extern hidden functions 
// --------------------------------------------------------------------------------------------------------------------
// empty-section

// --------------------------------------------------------------------------------------------------------------------
// - definition of static functions 
// --------------------------------------------------------------------------------------------------------------------



typedef uint8_t sdfg[ ( EOK_cfg_nvsEP_as_onestrain_con_maxnumof_nvs_in_strain == 16 ) ? (1) : (0)];
typedef uint8_t redf[ ( EOK_cfg_nvsEP_as_onestrain_con_maxnumof_nsv_in_mais == 16 ) ? (1) : (0)];

static uint16_t s_hash(uint16_t id)
{
    uint16_t off = EO_nv_OFF(id);
    uint16_t a;
    uint16_t b;
    uint16_t r;
    
    if(off < EOK_cfg_nvsEP_as_onestrain_con_firstNVIDoff_of_mais(0))
    {
        a = off >> 4;
        b = off - (a << 4);
        r = a*EOK_cfg_nvsEP_as_any_con_sxx_snvindex_TOTALnumber+b;
    }
    else
    {
        off -= EOK_cfg_nvsEP_as_onestrain_con_firstNVIDoff_of_mais(0);
        a = off >> 4;
        b = off - (a << 4);
        r = a*EOK_cfg_nvsEP_as_any_con_mxx_mnvindex_TOTALnumber+b;
        r += (EOK_cfg_nvsEP_as_any_con_sxx_snvindex_TOTALnumber*strainUpperArm_TOTALnumber);
    }
    
    return(r);
}



extern eOnvID_t eo_cfg_nvsEP_as_onestrain_strain_NVID_Get(eo_cfg_nvsEP_as_onestrain_con_strainNumber_t s, eo_cfg_nvsEP_as_onestrain_con_strainNVindex_t snvindex)
{
    if((s >= strainUpperArm_TOTALnumber) || (snvindex >= EOK_cfg_nvsEP_as_any_con_sxx_snvindex_TOTALnumber))
    {
        return(EOK_uint16dummy);
    }
    return(EO_nv_ID(eo_cfg_nvsEP_as_any_con_sxx_funtyp[snvindex], EOK_cfg_nvsEP_as_onestrain_con_NVIDoff_of_strain(s, snvindex)));    
}

extern eOnvID_t eo_cfg_nvsEP_as_onestrain_mais_NVID_Get(eo_cfg_nvsEP_as_onestrain_con_maisNumber_t m, eo_cfg_nvsEP_as_onestrain_con_maisNVindex_t mnvindex)
{
//    if((m >= maisUpperArm_TOTALnumber) || (mnvindex >= EOK_cfg_nvsEP_as_any_con_mxx_mnvindex_TOTALnumber))
//    {
        return(EOK_uint16dummy);
//    }
//    return(EO_nv_ID(eo_cfg_nvsEP_as_any_con_mxx_funtyp[mnvindex], EOK_cfg_nvsEP_as_onestrain_con_NVIDoff_of_mais(m, mnvindex)));    
}

// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------



