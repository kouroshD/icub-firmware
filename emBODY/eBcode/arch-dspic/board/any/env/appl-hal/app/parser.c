
/* @file       privateData.c
    @brief      This header file implements ....
    @author     valentina.gaggero@iit.it
    @date       27/01/2012
**/

// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "stdint.h"
#include "string.h"
#include "hal.h"

// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------

#include "parser.h"



// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern hidden interface 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables, but better using _get(), _set() 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section



// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------

/*  PROTOCOL MESSAGE */
#define CMD_SENDING_ENA             0
#define CMD_PRIVDATA_SET            1
#define CMD_PRIVDATA_GET            2
#define CMD_ERESEAPPFLASH           3
#define CMD_GETADDITIONALINFO       0XC


// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------
// empty-section

// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------

static ap_parser_cmd_t s_cmd;

                                                                             
// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------

extern hal_result_t ap_parse_init(void)
{
    s_cmd.opc = cmd_none;
    memset(&s_cmd.data[0], 0, 8);

    return(hal_res_OK);
}

extern hal_result_t ap_parse_canFrame(hal_can_frame_t *recframe, ap_parser_cmd_t **cmd)
{
    hal_result_t res = hal_res_OK;

    if((NULL == recframe) || (NULL == cmd) )
    {
        return(hal_res_NOK_generic);
    }

    *cmd = &s_cmd;

    switch(recframe->data[0])
    {
        case CMD_SENDING_ENA:
        {
            if(recframe->data[1])
            {
                s_cmd.opc = cmd_sending_enable;
            }
            else
            {
                s_cmd.opc = cmd_sending_disable;
            }
            
        } break;
        
        case CMD_PRIVDATA_SET:
        {

            s_cmd.opc = cmd_privdata_set;
            memcpy(&s_cmd.data[0],&recframe->data[0], 8);
        } break;

        case CMD_PRIVDATA_GET:
        {
            s_cmd.opc = cmd_privdata_get;
        } break;

        case CMD_ERESEAPPFLASH:
        {
            s_cmd.opc = cmd_erase_applflash;
        } break;

        default:
        {
            ;
        } break;
    }
    return(res);

}



// --------------------------------------------------------------------------------------------------------------------
// - definition of extern hidden functions 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition of static functions 
// --------------------------------------------------------------------------------------------------------------------
// empty-section




// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------
// empty-section


