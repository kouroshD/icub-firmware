/*
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author:  Valentina Gaggero
 * email:   valentina.gaggero@iit.it
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


/* @file       eOcfg_icubCanProto_sensorBoardMsgLookupTbl.c
    @brief      This file keeps ...
    @author     valentina.gaggero@iit.it
    @date       03/12/2012
**/


// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------
#include "EOcommon.h"
#include "EOicubCanProto.h"
#include "EOicubCanProto_specifications.h"
#include "EOicubCanProto_hid.h"

#include "EOconstLookupTbl.h"
#include "EOconstLookupTbl_hid.h"


#include "eOcfg_icubCanProto_sensorBoardMsgFunctions.h"
// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------
#include "eOcfg_icubCanProto_sensorBoardMsgLookupTbl.h"


// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern hidden interface 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------
/*currently only one message per class is managed (test porpouse)*/
#define eo_icubCanProto_pollingSensorBoardMsg_inTbl_max        1//ICUBCANPROTO_POL_SB_CMD_MAXNUM
#define eo_icubCanProto_pollingSensorBoardMsgClass_maxNum           ICUBCANPROTO_POL_SB_CMD_MAXNUM

/*currently only one message per class is managed (test porpouse)*/
#define eo_icubCanProto_periodicSensorBoardMsg_inTbl_max       1//ICUBCANPROTO_PER_SB_CMD_MAXNUM 
#define eo_icubCanProto_periodicSensorBoardMsg_maxNum          ICUBCANPROTO_PER_SB_CMD_MAXNUM



// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------
static eOresult_t s_eo_icubCanProto_exceptionMsgpollingSensorBoard_parser(EOicubCanProto *p, eo_icubCanProto_msgCommand_cmdId_t cmdId, eOcanframe_t *frame, eOcanport_t canPort);
static eOresult_t s_eo_icubCanProto_exceptionMsgpollingSensorBoard_former(EOicubCanProto *p, eo_icubCanProto_msgCommand_cmdId_t cmdID, void *nv_ptr, eo_icubCanProto_msgDestination_t dest, eOcanframe_t *canFrame);

static eOresult_t s_eo_icubCanProto_pollingSensorBoardMsg_parser_excFn(void *arg);
static eOresult_t s_eo_icubCanProto_pollingSensorBoardMsg_former_excFn(void *arg);
static eOresult_t s_eo_icubCanProto_periodicSensorBoardMsg_parser_excFn(void *arg);

// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------

/**************************************************************************************************************/
/*                 POLLING     SENSOR     BOARD     MESSAGES     LOOKUP     TABLE                             */
/**************************************************************************************************************/

/* DECLARATION OF POLLING MOTOR BOARD PARSER BODY TBL */
static const eo_icubCanProto_hid_LUTbl_item_parserFnHandling_t  s_pollingSensorBoardMsg_parserFn_list[eo_icubCanProto_pollingSensorBoardMsg_inTbl_max] = 
{
    {   // 0 ICUBCANPROTO_POL_SB_CMD__NONE			
        EO_INIT(.parser)    eo_icubCanProto_parser_pol_sb_unexpected_cmd
    }
};        

/* DECLARATION OF POLLING MOTOR BOARD PARSER LOOKUP TBL */
extern const EOconstLookupTbl icubCanProto_pollingSensorBoardMsg_parser_LUTbl = 
{                                        

    EO_INIT(.capacity)          eo_icubCanProto_pollingSensorBoardMsg_inTbl_max,
    EO_INIT(.offset)            0,
    EO_INIT(.exceptionMngFn)    s_eo_icubCanProto_pollingSensorBoardMsg_parser_excFn,
    EO_INIT(.itemsList)         &s_pollingSensorBoardMsg_parserFn_list[0]                          
};

extern const EOconstLookupTbl* const icubCanProto_pollingSensorBoardMsg_parser_LUTbl__ptr = &icubCanProto_pollingSensorBoardMsg_parser_LUTbl;



/* DECLARATION OF POLLING MOTOR BOARD FORMER BODY TBL */
static const eo_icubCanProto_hid_LUTbl_item_formerFnHandling_t  s_pollingSensorBoardMsg_formerFn_list[eo_icubCanProto_pollingSensorBoardMsg_inTbl_max] = 
{
    {   // 0 ICUBCANPROTO_POL_SB_CMD__NONE			
        EO_INIT(.former)    eo_icubCanProto_former_pol_sb_unexpected_cmd
    }
};        




/* DECLARATION OF POLLING MOTOR BOARD FORMER LOOKUP TBL */
extern const EOconstLookupTbl icubCanProto_pollingSensorBoardMsg_former_LUTbl = 
{

    EO_INIT(.capacity)          eo_icubCanProto_pollingSensorBoardMsg_inTbl_max,
    EO_INIT(.offset)            0,
    EO_INIT(.exceptionMngFn)    s_eo_icubCanProto_pollingSensorBoardMsg_former_excFn,
    EO_INIT(.itemsList)         &s_pollingSensorBoardMsg_formerFn_list[0]  
};

extern const EOconstLookupTbl* const icubCanProto_pollingSensorBoardMsg_former_LUTbl__ptr = &icubCanProto_pollingSensorBoardMsg_former_LUTbl;










/**************************************************************************************************************/
/*                 PERIODIC     SENSOR     BOARD     MESSAGES     LOOKUP     TABLE                             */
/**************************************************************************************************************/

/* DECLARATION OF PERIODIC MOTOR BOARD PARSER BODY TBL */
static const eo_icubCanProto_hid_LUTbl_item_parserFnHandling_t  s_periodicSensorBoardMsg_parserFn_list[eo_icubCanProto_periodicSensorBoardMsg_inTbl_max] = 
{
    {   // 10 ICUBCANPROTO_PER_SB_CMD__FORCE_VECTOR 			
        EO_INIT(.parser)    eo_icubCanProto_parser_per_sb_cmd__forceVector
    }
};        

extern const EOconstLookupTbl icubCanProto_periodicSensorBoardMsg_parser_LUTbl = 
{                                        

    EO_INIT(.capacity)          eo_icubCanProto_periodicSensorBoardMsg_inTbl_max,
    EO_INIT(.offset)            0,
    EO_INIT(.exceptionMngFn)    s_eo_icubCanProto_periodicSensorBoardMsg_parser_excFn,
    EO_INIT(.itemsList)         &s_periodicSensorBoardMsg_parserFn_list[0]                          
};

extern const EOconstLookupTbl* const icubCanProto_periodicSensorBoardMsg_parser_LUTbl__ptr = &icubCanProto_periodicSensorBoardMsg_parser_LUTbl;


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition of extern hidden functions 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition of static functions 
// --------------------------------------------------------------------------------------------------------------------
static eOresult_t s_eo_icubCanProto_exceptionMsgpollingSensorBoard_parser(EOicubCanProto *p, eo_icubCanProto_msgCommand_cmdId_t cmdId, 
                                                                          eOcanframe_t *frame, eOcanport_t canPort)
{                                                                      
    eOresult_t res;

    switch(cmdId)
    {

        default:
        {
            res = eo_icubCanProto_parser_pol_sb_unexpected_cmd(p, frame, canPort);
        }
    };


    return(res);        
}





static eOresult_t s_eo_icubCanProto_exceptionMsgpollingSensorBoard_former(EOicubCanProto *p, eo_icubCanProto_msgCommand_cmdId_t cmdId, 
                                                                            void *nv_ptr,
                                                                            eo_icubCanProto_msgDestination_t dest,
                                                                            eOcanframe_t *canFrame)
{
    eOresult_t res;

    switch(cmdId)
    {
        default:
        {
            res = eo_icubCanProto_former_pol_sb_unexpected_cmd(p, nv_ptr, dest, canFrame);
        }
    };


    return(res);        
}

static eOresult_t s_eo_icubCanProto_pollingSensorBoardMsg_parser_excFn(void *arg)
{
    return(eores_OK);
}
static eOresult_t s_eo_icubCanProto_pollingSensorBoardMsg_former_excFn(void *arg)
{
    return(eores_OK);
}

static eOresult_t s_eo_icubCanProto_periodicSensorBoardMsg_parser_excFn(void *arg)
{
    return(eores_OK);
}

// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------



