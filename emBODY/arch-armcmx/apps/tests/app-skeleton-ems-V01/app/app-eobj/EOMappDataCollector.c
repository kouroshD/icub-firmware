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


// --------------------------------------------------------------------------------------------------------------------
// - doxy
// --------------------------------------------------------------------------------------------------------------------

/* @file       EOMappDataCollector.c
    @brief      This file contains internal implementation for application data Collector
    @author     valentina.gaggero@iit.it
    @date       02/20/2012
**/


// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------
#include "stdlib.h"     // to see NULL, calloc etc.
#include "string.h"     //memcpy

// abstraction layers
#include "hal.h"
#include "hal_debugPin.h"

//embobj
#include "EOtheMemoryPool.h"
#include "EOtheErrorManager.h"
#include "EOtheBOARDTransceiver.h"
#include "EOtheBOARDTransceiver_hid.h"

//embobj-cfg-icub
#include "EoMotionControl.h"
#include "eOcfg_EPs_loc_board.h"

// application
#include "EOappEncodersReader.h"
#include "EOappCanServicesProvider.h"


// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------
#include "EOMappDataCollector.h"


// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern hidden interface 
// --------------------------------------------------------------------------------------------------------------------
#include "EOMappDataCollector_hid.h" 




// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------
#define EVT_CHECK(var, EVTMASK)             (EVTMASK == (var&EVTMASK))



#define TASK_DATACOLLECTOR_PRIO          60   // task piority

//************************ system controller task events **************************************************
#define EVT_GETDATA_START          (1 << 0)
#define EVT_GETDATA_STOP           (1 << 1)


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables. deprecated: better using _get(), _set() on static variables 
// --------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------
//function used to configure eOMtask obj
void s_eom_appDataCollector_taskInit(void *p);
static void s_eom_appDataCollector_taskStartup(EOMtask *p, uint32_t t);
static void s_eom_appDataCollector_taskRun(EOMtask *tsk, uint32_t evtmsgper); 


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------
static const char s_eobj_ownname[] = "EOMappDataCollector";

uint32_t encoders_values[6];
uint8_t motorControllerMod_motorValues[4][8]; 
// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------
extern EOMappDataCollector* eom_appDataCollector_New(EOMappDataCollector_cfg_t *cfg)
{
    EOMappDataCollector *retptr = NULL;

    if(NULL == cfg)
    {
        return(retptr);
    }

    retptr = eo_mempool_GetMemory(eo_mempool_GetHandle(), eo_mempool_align_32bit, sizeof(EOMappDataCollector), 1);

    retptr->st = eOm_appDataCollector_st__idle;

    //copy configuration data
    memcpy(&(retptr->cfg), cfg, sizeof(EOMappDataCollector_cfg_t));

    retptr->mytask = eom_task_New(eom_mtask_EventDriven,
                              TASK_DATACOLLECTOR_PRIO ,
                              2*1024,           //stacksize: da rivedere
                              s_eom_appDataCollector_taskStartup, 
                              s_eom_appDataCollector_taskRun,  
                              0,                //message queue size. the task is evt based 
                              eok_reltimeINFINITE,
                              retptr, 
                              s_eom_appDataCollector_taskInit, 
                              "dataCollector" );
    
    return(retptr);
}


extern eOresult_t eom_appDataCollector_Activate(EOMappDataCollector *p)
{
    if(NULL == p)
    {
        return(eores_NOK_nullpointer);
    }

    p->st = eOm_appDataCollector_st__active;

     return(eores_OK);
}


extern eOresult_t eom_appDataCollector_Deactivate(EOMappDataCollector *p)
{
    if(NULL == p)
    {
        return(eores_NOK_nullpointer);
    }

    p->st = eOm_appDataCollector_st__idle;

     return(eores_OK);
}


extern eOresult_t eom_appDataCollector_CollectDataStart(EOMappDataCollector *p)
{
    if(NULL == p)
    {
        return(eores_NOK_nullpointer);
    }

     if(eOm_appDataCollector_st__idle == p->st)
     {
        return(eores_NOK_generic);   
     }
     p->st = eOm_appDataCollector_st__collectingData;
     eom_task_isrSetEvent(p->mytask, EVT_GETDATA_START);//eom_task_SetEvent(p->mytask, EVT_GETDATA_START);
     return(eores_OK);
}

extern eOresult_t eom_appDataCollector_CollectDataStop(EOMappDataCollector *p)
{
    if(NULL == p)
    {
        return(eores_NOK_nullpointer);
    }

    if(eOm_appDataCollector_st__collectingData != p->st)
    {
        return(eores_NOK_generic);   
    }

     p->st = eOm_appDataCollector_st__active;
     eom_task_isrSetEvent(p->mytask, EVT_GETDATA_STOP);
     return(eores_OK);
}

    

// --------------------------------------------------------------------------------------------------------------------
// - definition of extern hidden functions 
// --------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------
// - definition of static functions 
// --------------------------------------------------------------------------------------------------------------------
void s_eom_appDataCollector_taskInit(void *p)
{
    eom_task_Start(p);
}


static void s_eom_appDataCollector_taskStartup(EOMtask *tsk, uint32_t t)
{
    EOMappDataCollector *p = (EOMappDataCollector*)eom_task_GetExternalData(tsk);

    eo_errman_Assert(eo_errman_GetHandle(), NULL != p, s_eobj_ownname, "extdata() is NULL");

}

static void s_eom_appDataCollector_taskRun(EOMtask *tsk, uint32_t evtmsgper)
{

    EOMappDataCollector *p = (EOMappDataCollector*)eom_task_GetExternalData(tsk);

    eOevent_t evt = (eOevent_t)evtmsgper;   

    if(EVT_CHECK(evt, EVT_GETDATA_START))
    {
        hal_led_on(hal_led1);
        hal_led_off(hal_led0);

        /* 1) start encoder reading */
         eo_appEncReader_startRead(p->cfg.encReader_ptr);

#ifdef _USE_TRANSCEIVER_ 
        /* 2) process received eth packet*/
        eo_transceiver_Receive(eo_boardtransceiver_GetHandle(), rxpkt, &numofrops_ems00_rx, &txtime);
#endif

        /* 3) process received can frame */
        eo_appCanSP_read(p->cfg.canSP_ptr);

        /* 4) get encoders values*/
        if(eobool_true == eo_appEncReader_isReady(p->cfg.encReader_ptr))
        {
            eo_appEncReader_getValues(p->cfg.encReader_ptr, encoders_values);
        }
        else
        {
           //Soluzione 1: mi invio un evento dedicato alla lettura dell'encoder 
           //nella gestione di questo evento verifico se i valorio sono pronti:
           //  se si ==>  ok
           //  altrimenti mi rinvio l'evento

           //Soluzione 2: faccio una lettura degli encoder su ricezione dell'evt_stop.
           //ho deciso di adottare questa soluzione.
        }

    }

    if(EVT_CHECK(evt, EVT_GETDATA_STOP))
    {

        hal_led_on(hal_led3);
        if(eobool_true == eo_appEncReader_isReady(p->cfg.encReader_ptr))
        {
            eo_appEncReader_getValues(p->cfg.encReader_ptr, encoders_values);
        }

        if(NULL != p->cfg.sig2appMotorController.fn)
        {
            p->cfg.sig2appMotorController.fn(p->cfg.sig2appMotorController.argoffn);            
        }
    }
}


// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------



