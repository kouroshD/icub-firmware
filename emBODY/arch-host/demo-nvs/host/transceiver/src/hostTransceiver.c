
/* @file       hostTransceiver.c
    @brief      This file implements internal implementation of a nv object.
    @author     marco.accame@iit.it
    @date       09/03/2010
**/


// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "stdlib.h"
#include "EoCommon.h"
#include "string.h"

#include "EOnv_hid.h"


// the endpoints on that particular ems
#include "eOcfg_EPs_rem_board.h"





// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------

#include "hostTransceiver.h"


// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern hidden interface 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables, but better using _get(), _set() 
// --------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------

typedef struct
{
        EOhostTransceiver*  hosttxrx; 
        EOtransceiver*      pc104txrx;
        EOnvsCfg*           pc104nvscfg;  
        uint32_t            localipaddr;
        uint32_t            remoteipaddr;
        uint16_t            ipport;
        EOpacket*           pkt;        
} hostTransceiver;


// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------

static void s_hostTransceiver_AddSetROP_with_data_already_set(uint16_t ep, uint16_t id);


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------

static hostTransceiver thehosttransceiver;

//static EOhostTransceiver *hosttxrx = NULL;
//static EOtransceiver *pc104txrx = NULL;
//static EOnvsCfg *pc104nvscfg = NULL:


// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------




extern void hostTransceiver_Init(uint32_t localipaddr, uint32_t remoteipaddr, uint16_t ipport, uint16_t pktsize)
{
    // the configuration of the transceiver: it is specific of a given remote board
    eOhosttransceiver_cfg_t hosttxrxcfg = 
    {
        EO_INIT(.vectorof_endpoint_cfg) eo_cfg_EPs_vectorof_rem_board,
        EO_INIT(.hashfunction_ep2index) eo_cfg_nvsEP_rem_board_fptr_hashfunction_ep2index,
        EO_INIT(remoteboardipv4addr)    remoteipaddr,
        EO_INIT(.remoteboardipv4port)   ipport,
        EO_INIT(.tobedefined)           0
    };


    
    thehosttransceiver.localipaddr  = localipaddr;
    thehosttransceiver.remoteipaddr = remoteipaddr;
    thehosttransceiver.ipport       = ipport;
    
    // initialise the transceiver: it creates a EOtransceiver and its nvsCfg by loading all the endpoints
    thehosttransceiver.hosttxrx     = eo_hosttransceiver_New(&hosttxrxcfg);
    
    // retrieve teh transceiver
    thehosttransceiver.pc104txrx    = eo_hosttransceiver_Transceiver(thehosttransceiver.hosttxrx);
    
    // retrieve the nvscfg
    thehosttransceiver.pc104nvscfg  = eo_hosttransceiver_NVsCfg(thehosttransceiver.hosttxrx);

}


extern void hostTransceiver_ConfigureRegularsOnRemote(void)
{
    // 1. at first write the nv that we want to set: the EOK_cfg_nvsEP_mngmnt_NVID__upto10rop2signal
    //    there are two alternative ways to do that:
    //    A. QUICK MODE - to write directly onto the local struct of the endpoint. WE USE THIS SECOND WAY because we know
    //       the name of the specific variable to use in the rop
    //    B. FORMAL MODE (and more generic): to use teh nvscfg to retrieve the handle of a EOnv which is relative to the 
    //       pair (endpoint, id) which we wnat to manipulate, and then to use the methods of EOnv to set the value of that variable.
    //       we shall use this mode in function hostTransceiver_AddSetROP()
    
    EOarray *upto = (EOarray*) & eo_cfg_nvsEP_mngmnt_usr_rem_board_mem_local->upto10rop2signal;
    eOropSIGcfg_t sigcfg;

    // clear the variable.
    eo_array_Reset(upto);

    // push back in teh array the first nv that the remote board shall signal
    sigcfg.ep = EOK_cfg_nvsEP_base_endpoint;
    sigcfg.id = EOK_cfg_nvsEP_base_NVID_ipnetwork__ipaddress;
    sigcfg.plustime = 0;
    eo_array_PushBack(upto, &sigcfg);

    // push back in teh array the second nv that the remote board shall signal
    sigcfg.ep = EOK_cfg_nvsEP_base_endpoint;
    sigcfg.id = EOK_cfg_nvsEP_base_NVID__bootprocess;
    sigcfg.plustime = 0;
    eo_array_PushBack(upto, &sigcfg);
    
    // 2. then put the rop set<upto10rop2signal, data> inside the transceiver
    s_hostTransceiver_AddSetROP_with_data_already_set(EOK_cfg_nvsEP_mngmnt_endpoint, EOK_cfg_nvsEP_mngmnt_NVID__upto10rop2signal);   
}


// somebody adds a set-rop  plus data.
extern void hostTransceiver_AddSetROP(uint16_t ep, uint16_t id, uint8_t* data, uint16_t size)
{
    uint16_t ss;
    EOnv nv;
    EOtreenode *treenode = NULL;
    uint8_t ipindex, epindex, idindex;

    // 1. search for teh EOnv with pair (ep, id)

//    eo_nvscfg_GetIndices(thehosttransceiver.pc104nvscfg, thehosttransceiver.remoteipaddr, ep, id,
//                         &ipindex, &epindex, &idindex);
            
    if(eores_OK != eo_nvscfg_GetIndices(thehosttransceiver.pc104nvscfg, thehosttransceiver.remoteipaddr, ep, id, &ipindex, &epindex, &idindex))
    {
        // there is no such variable with (remoteipaddr-ep-id) 
        return;
    }

    eo_nvscfg_GetNV(thehosttransceiver.pc104nvscfg, ipindex, epindex, idindex, treenode, &nv);

    // eo_nvscfg_GetNV(thehosttransceiver.pc104nvscfg, thehosttransceiver.remoteipaddr, ep, id, &nv)
    
    // 1bis. verify that the datasize is correct.
    ss = eo_nv_Size(&nv, data);
    if(ss < size)
    {
        // non faccio nulla intanto quando scrivo uso la capacita' della nv.
        // sarebbe bene pero' emettere un warning        
    }
    
    
    // 2. set the data. dont force the set so that we dont write if the nv is readonly.
    
    if(eores_OK != eo_nv_Set(&nv, data, eobool_false, eo_nv_upd_dontdo))
    {   
        // teh nv is not writeable
        return;
    }
    
    
    // 3. add the rop 
    s_hostTransceiver_AddSetROP_with_data_already_set(ep, id);

}

// somebody passes the received packe
extern void hostTransceiver_SetReceived(uint8_t *data, uint16_t size)
{
    uint16_t numofrops;
    uint64_t txtime;
    
    eo_packet_Payload_Set(thehosttransceiver.pkt, data, size);
    eo_packet_Addressing_Set(thehosttransceiver.pkt, thehosttransceiver.remoteipaddr, thehosttransceiver.ipport);
         
    eo_transceiver_Receive(thehosttransceiver.pc104txrx, thehosttransceiver.pkt, &numofrops, &txtime);
}


// somebody retrieves what must be transmitted
extern void hostTransceiver_GetTransmit(uint8_t **data, uint16_t *size)
{
    uint16_t numofrops;
    
    eo_transceiver_Transmit(thehosttransceiver.pc104txrx, &thehosttransceiver.pkt, &numofrops);
    
    eo_packet_Payload_Get(thehosttransceiver.pkt, data, size);
    
}



// --------------------------------------------------------------------------------------------------------------------
// - definition of extern hidden functions 
// --------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------
// - definition of static functions 
// --------------------------------------------------------------------------------------------------------------------

static void s_hostTransceiver_AddSetROP_with_data_already_set(uint16_t ep, uint16_t id)
{
    eo_transceiver_ropinfo_t ropinfo;

    ropinfo.ropcfg      = eok_ropconfig_basic;
    ropinfo.ropcode     = eo_ropcode_set;
    ropinfo.nvep        = ep;
    ropinfo.nvid        = id;
    
    eo_transceiver_rop_occasional_Load(thehosttransceiver.pc104txrx, &ropinfo);
}



// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------




