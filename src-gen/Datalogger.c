
#include <stdlib.h>
#include <string.h>
#include "sc_types.h"
#include "Datalogger.h"
#include "DataloggerRequired.h"
/*! \file Implementation of the state machine 'datalogger'
*/

/* prototypes of all internal functions */
static sc_boolean datalogger_check_main_region_Logger_r1_Active_tr0_tr0(const Datalogger* handle);
static sc_boolean datalogger_check_main_region_Logger_r1_Active_r1_MQTT_Connecting_tr0_tr0(const Datalogger* handle);
static sc_boolean datalogger_check_main_region_Logger_r1_Active_r1_Collecting_Data_tr0_tr0(const Datalogger* handle);
static sc_boolean datalogger_check_main_region_Logger_r1_Active_r1_Publishing_Data_tr0_tr0(const Datalogger* handle);
static sc_boolean datalogger_check_main_region_Logger_r1_Active_r1_Wait_tr0_tr0(const Datalogger* handle);
static sc_boolean datalogger_check_main_region_Logger_r2_Display_Sleepmode_r1_Active_tr0_tr0(const Datalogger* handle);
static sc_boolean datalogger_check_main_region_Logger_r2_Display_Sleepmode_r1_Active_tr1_tr1(const Datalogger* handle);
static sc_boolean datalogger_check_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping_tr0_tr0(const Datalogger* handle);
static void datalogger_effect_main_region_Logger_r1_Active_tr0(Datalogger* handle);
static void datalogger_effect_main_region_Logger_r1_Active_r1_MQTT_Connecting_tr0(Datalogger* handle);
static void datalogger_effect_main_region_Logger_r1_Active_r1_Collecting_Data_tr0(Datalogger* handle);
static void datalogger_effect_main_region_Logger_r1_Active_r1_Publishing_Data_tr0(Datalogger* handle);
static void datalogger_effect_main_region_Logger_r1_Active_r1_Wait_tr0(Datalogger* handle);
static void datalogger_effect_main_region_Logger_r2_Display_Sleepmode_r1_Active_tr0(Datalogger* handle);
static void datalogger_effect_main_region_Logger_r2_Display_Sleepmode_r1_Active_tr1(Datalogger* handle);
static void datalogger_effect_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping_tr0(Datalogger* handle);
static void datalogger_enact_main_region_Logger_r1_Active_r1_Wait(Datalogger* handle);
static void datalogger_enact_main_region_Logger_r2_Display_Sleepmode_r1_Active(Datalogger* handle);
static void datalogger_exact_main_region_Logger_r1_Active_r1_Wait(Datalogger* handle);
static void datalogger_exact_main_region_Logger_r2_Display_Sleepmode_r1_Active(Datalogger* handle);
static void datalogger_enseq_main_region_Logger_default(Datalogger* handle);
static void datalogger_enseq_main_region_Logger_r1_Active_r1_MQTT_Connecting_default(Datalogger* handle);
static void datalogger_enseq_main_region_Logger_r1_Active_r1_Collecting_Data_default(Datalogger* handle);
static void datalogger_enseq_main_region_Logger_r1_Active_r1_Publishing_Data_default(Datalogger* handle);
static void datalogger_enseq_main_region_Logger_r1_Active_r1_Wait_default(Datalogger* handle);
static void datalogger_enseq_main_region_Logger_r1_Error_default(Datalogger* handle);
static void datalogger_enseq_main_region_Logger_r2_Display_Sleepmode_r1_Active_default(Datalogger* handle);
static void datalogger_enseq_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping_default(Datalogger* handle);
static void datalogger_enseq_main_region_default(Datalogger* handle);
static void datalogger_enseq_main_region_Logger_r1_default(Datalogger* handle);
static void datalogger_enseq_main_region_Logger_r2_default(Datalogger* handle);
static void datalogger_shenseq_main_region_Logger_r2_Display_Sleepmode_r1(Datalogger* handle);
static void datalogger_exseq_main_region_Logger_r1_Active(Datalogger* handle);
static void datalogger_exseq_main_region_Logger_r1_Active_r1_MQTT_Connecting(Datalogger* handle);
static void datalogger_exseq_main_region_Logger_r1_Active_r1_Collecting_Data(Datalogger* handle);
static void datalogger_exseq_main_region_Logger_r1_Active_r1_Publishing_Data(Datalogger* handle);
static void datalogger_exseq_main_region_Logger_r1_Active_r1_Wait(Datalogger* handle);
static void datalogger_exseq_main_region_Logger_r1_Error(Datalogger* handle);
static void datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1_Active(Datalogger* handle);
static void datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping(Datalogger* handle);
static void datalogger_exseq_main_region(Datalogger* handle);
static void datalogger_exseq_main_region_Logger_r1(Datalogger* handle);
static void datalogger_exseq_main_region_Logger_r1_Active_r1(Datalogger* handle);
static void datalogger_exseq_main_region_Logger_r2(Datalogger* handle);
static void datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1(Datalogger* handle);
static void datalogger_react_main_region_Logger_r1_Active_r1_MQTT_Connecting(Datalogger* handle);
static void datalogger_react_main_region_Logger_r1_Active_r1_Collecting_Data(Datalogger* handle);
static void datalogger_react_main_region_Logger_r1_Active_r1_Publishing_Data(Datalogger* handle);
static void datalogger_react_main_region_Logger_r1_Active_r1_Wait(Datalogger* handle);
static void datalogger_react_main_region_Logger_r1_Error(Datalogger* handle);
static void datalogger_react_main_region_Logger_r2_Display_Sleepmode_r1_Active(Datalogger* handle);
static void datalogger_react_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping(Datalogger* handle);
static void datalogger_react_main_region_Logger_r1__entry_Default(Datalogger* handle);
static void datalogger_react_main_region_Logger_r2_Display_Sleepmode_r1__entry_Default(Datalogger* handle);
static void datalogger_react_main_region_Logger_r2__entry_Default(Datalogger* handle);
static void datalogger_react_main_region__entry_Default(Datalogger* handle);
static void datalogger_clearInEvents(Datalogger* handle);
static void datalogger_clearOutEvents(Datalogger* handle);


void datalogger_init(Datalogger* handle)
{
		sc_integer i;
	
		for (i = 0; i < DATALOGGER_MAX_ORTHOGONAL_STATES; ++i)
		{
			handle->stateConfVector[i] = Datalogger_last_state;
		}
		
		for (i = 0; i < DATALOGGER_MAX_HISTORY_STATES; ++i)
		{
			handle->historyVector[i] = Datalogger_last_state;
		}
		
		handle->stateConfVectorPosition = 0;
	
		datalogger_clearInEvents(handle);
		datalogger_clearOutEvents(handle);
	
		/* Default init sequence for statechart datalogger */
		handle->ifaceDisplay.isSleeping = bool_false;
		handle->ifaceDisplay.displayText = "";
}

void datalogger_enter(Datalogger* handle)
{
	/* Default enter sequence for statechart datalogger */
	datalogger_enseq_main_region_default(handle);
}

void datalogger_exit(Datalogger* handle)
{
	/* Default exit sequence for statechart datalogger */
	datalogger_exseq_main_region(handle);
}

sc_boolean datalogger_isActive(const Datalogger* handle)
{
	sc_boolean result = bool_false;
	int i;
	
	for(i = 0; i < DATALOGGER_MAX_ORTHOGONAL_STATES; i++)
	{
		result = result || handle->stateConfVector[i] != Datalogger_last_state;
	}
	
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean datalogger_isFinal(const Datalogger* handle)
{
   return bool_false;
}

static void datalogger_clearInEvents(Datalogger* handle)
{
	handle->iface.ButtonPressed_raised = bool_false;
	handle->iface.Failure_raised = bool_false;
	handle->timeEvents.datalogger_main_region_Logger_r1_Active_r1_Wait_tev0_raised = bool_false;
	handle->timeEvents.datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Active_tev0_raised = bool_false;
}

static void datalogger_clearOutEvents(Datalogger* handle)
{
}

void datalogger_runCycle(Datalogger* handle)
{
	
	datalogger_clearOutEvents(handle);
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < DATALOGGER_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++)
		{
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition])
		{
		case Datalogger_main_region_Logger_r1_Active_r1_MQTT_Connecting:
		{
			datalogger_react_main_region_Logger_r1_Active_r1_MQTT_Connecting(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Active_r1_Collecting_Data:
		{
			datalogger_react_main_region_Logger_r1_Active_r1_Collecting_Data(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Active_r1_Publishing_Data:
		{
			datalogger_react_main_region_Logger_r1_Active_r1_Publishing_Data(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Active_r1_Wait:
		{
			datalogger_react_main_region_Logger_r1_Active_r1_Wait(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Error:
		{
			datalogger_react_main_region_Logger_r1_Error(handle);
			break;
		}
		case Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Active:
		{
			datalogger_react_main_region_Logger_r2_Display_Sleepmode_r1_Active(handle);
			break;
		}
		case Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping:
		{
			datalogger_react_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping(handle);
			break;
		}
		default:
			break;
		}
	}
	
	datalogger_clearInEvents(handle);
}

void datalogger_raiseTimeEvent(const Datalogger* handle, sc_eventid evid)
{
	if ( ((sc_intptr_t)evid) >= ((sc_intptr_t)&(handle->timeEvents))
		&&  ((sc_intptr_t)evid) < ((sc_intptr_t)&(handle->timeEvents)) + sizeof(DataloggerTimeEvents))
		{
		*(sc_boolean*)evid = bool_true;
	}		
}

sc_boolean datalogger_isStateActive(const Datalogger* handle, DataloggerStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case Datalogger_main_region_Logger :
			result = (sc_boolean) (handle->stateConfVector[SCVI_DATALOGGER_MAIN_REGION_LOGGER] >= Datalogger_main_region_Logger
				&& handle->stateConfVector[SCVI_DATALOGGER_MAIN_REGION_LOGGER] <= Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping);
			break;
		case Datalogger_main_region_Logger_r1_Active :
			result = (sc_boolean) (handle->stateConfVector[SCVI_DATALOGGER_MAIN_REGION_LOGGER_R1_ACTIVE] >= Datalogger_main_region_Logger_r1_Active
				&& handle->stateConfVector[SCVI_DATALOGGER_MAIN_REGION_LOGGER_R1_ACTIVE] <= Datalogger_main_region_Logger_r1_Active_r1_Wait);
			break;
		case Datalogger_main_region_Logger_r1_Active_r1_MQTT_Connecting :
			result = (sc_boolean) (handle->stateConfVector[SCVI_DATALOGGER_MAIN_REGION_LOGGER_R1_ACTIVE_R1_MQTT_CONNECTING] == Datalogger_main_region_Logger_r1_Active_r1_MQTT_Connecting
			);
			break;
		case Datalogger_main_region_Logger_r1_Active_r1_Collecting_Data :
			result = (sc_boolean) (handle->stateConfVector[SCVI_DATALOGGER_MAIN_REGION_LOGGER_R1_ACTIVE_R1_COLLECTING_DATA] == Datalogger_main_region_Logger_r1_Active_r1_Collecting_Data
			);
			break;
		case Datalogger_main_region_Logger_r1_Active_r1_Publishing_Data :
			result = (sc_boolean) (handle->stateConfVector[SCVI_DATALOGGER_MAIN_REGION_LOGGER_R1_ACTIVE_R1_PUBLISHING_DATA] == Datalogger_main_region_Logger_r1_Active_r1_Publishing_Data
			);
			break;
		case Datalogger_main_region_Logger_r1_Active_r1_Wait :
			result = (sc_boolean) (handle->stateConfVector[SCVI_DATALOGGER_MAIN_REGION_LOGGER_R1_ACTIVE_R1_WAIT] == Datalogger_main_region_Logger_r1_Active_r1_Wait
			);
			break;
		case Datalogger_main_region_Logger_r1_Error :
			result = (sc_boolean) (handle->stateConfVector[SCVI_DATALOGGER_MAIN_REGION_LOGGER_R1_ERROR] == Datalogger_main_region_Logger_r1_Error
			);
			break;
		case Datalogger_main_region_Logger_r2_Display_Sleepmode :
			result = (sc_boolean) (handle->stateConfVector[SCVI_DATALOGGER_MAIN_REGION_LOGGER_R2_DISPLAY_SLEEPMODE] >= Datalogger_main_region_Logger_r2_Display_Sleepmode
				&& handle->stateConfVector[SCVI_DATALOGGER_MAIN_REGION_LOGGER_R2_DISPLAY_SLEEPMODE] <= Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping);
			break;
		case Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Active :
			result = (sc_boolean) (handle->stateConfVector[SCVI_DATALOGGER_MAIN_REGION_LOGGER_R2_DISPLAY_SLEEPMODE_R1_ACTIVE] == Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Active
			);
			break;
		case Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping :
			result = (sc_boolean) (handle->stateConfVector[SCVI_DATALOGGER_MAIN_REGION_LOGGER_R2_DISPLAY_SLEEPMODE_R1_SLEEPING] == Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}



sc_boolean dataloggerIfaceDisplay_get_isSleeping(const Datalogger* handle)
{
	return handle->ifaceDisplay.isSleeping;
}
void dataloggerIfaceDisplay_set_isSleeping(Datalogger* handle, sc_boolean value)
{
	handle->ifaceDisplay.isSleeping = value;
}
sc_string dataloggerIfaceDisplay_get_displayText(const Datalogger* handle)
{
	return handle->ifaceDisplay.displayText;
}
void dataloggerIfaceDisplay_set_displayText(Datalogger* handle, sc_string value)
{
	handle->ifaceDisplay.displayText = value;
}
void dataloggerIface_raise_buttonPressed(Datalogger* handle)
{
	handle->iface.ButtonPressed_raised = bool_true;
}
void dataloggerIface_raise_failure(Datalogger* handle)
{
	handle->iface.Failure_raised = bool_true;
}



/* implementations of all internal functions */

static sc_boolean datalogger_check_main_region_Logger_r1_Active_tr0_tr0(const Datalogger* handle)
{
	return handle->iface.Failure_raised;
}

static sc_boolean datalogger_check_main_region_Logger_r1_Active_r1_MQTT_Connecting_tr0_tr0(const Datalogger* handle)
{
	return bool_true;
}

static sc_boolean datalogger_check_main_region_Logger_r1_Active_r1_Collecting_Data_tr0_tr0(const Datalogger* handle)
{
	return bool_true;
}

static sc_boolean datalogger_check_main_region_Logger_r1_Active_r1_Publishing_Data_tr0_tr0(const Datalogger* handle)
{
	return bool_true;
}

static sc_boolean datalogger_check_main_region_Logger_r1_Active_r1_Wait_tr0_tr0(const Datalogger* handle)
{
	return handle->timeEvents.datalogger_main_region_Logger_r1_Active_r1_Wait_tev0_raised;
}

static sc_boolean datalogger_check_main_region_Logger_r2_Display_Sleepmode_r1_Active_tr0_tr0(const Datalogger* handle)
{
	return handle->timeEvents.datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Active_tev0_raised;
}

static sc_boolean datalogger_check_main_region_Logger_r2_Display_Sleepmode_r1_Active_tr1_tr1(const Datalogger* handle)
{
	return handle->iface.ButtonPressed_raised;
}

static sc_boolean datalogger_check_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping_tr0_tr0(const Datalogger* handle)
{
	return handle->iface.ButtonPressed_raised;
}

static void datalogger_effect_main_region_Logger_r1_Active_tr0(Datalogger* handle)
{
	datalogger_exseq_main_region_Logger_r1_Active(handle);
	datalogger_enseq_main_region_Logger_r1_Error_default(handle);
}

static void datalogger_effect_main_region_Logger_r1_Active_r1_MQTT_Connecting_tr0(Datalogger* handle)
{
	datalogger_exseq_main_region_Logger_r1_Active_r1_MQTT_Connecting(handle);
	datalogger_enseq_main_region_Logger_r1_Active_r1_Collecting_Data_default(handle);
}

static void datalogger_effect_main_region_Logger_r1_Active_r1_Collecting_Data_tr0(Datalogger* handle)
{
	datalogger_exseq_main_region_Logger_r1_Active_r1_Collecting_Data(handle);
	datalogger_enseq_main_region_Logger_r1_Active_r1_Publishing_Data_default(handle);
}

static void datalogger_effect_main_region_Logger_r1_Active_r1_Publishing_Data_tr0(Datalogger* handle)
{
	datalogger_exseq_main_region_Logger_r1_Active_r1_Publishing_Data(handle);
	datalogger_enseq_main_region_Logger_r1_Active_r1_Wait_default(handle);
}

static void datalogger_effect_main_region_Logger_r1_Active_r1_Wait_tr0(Datalogger* handle)
{
	datalogger_exseq_main_region_Logger_r1_Active_r1_Wait(handle);
	datalogger_enseq_main_region_Logger_r1_Active_r1_MQTT_Connecting_default(handle);
}

static void datalogger_effect_main_region_Logger_r2_Display_Sleepmode_r1_Active_tr0(Datalogger* handle)
{
	datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1_Active(handle);
	datalogger_enseq_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping_default(handle);
}

static void datalogger_effect_main_region_Logger_r2_Display_Sleepmode_r1_Active_tr1(Datalogger* handle)
{
	datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1_Active(handle);
	datalogger_enseq_main_region_Logger_r2_Display_Sleepmode_r1_Active_default(handle);
}

static void datalogger_effect_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping_tr0(Datalogger* handle)
{
	datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping(handle);
	datalogger_enseq_main_region_Logger_r2_Display_Sleepmode_r1_Active_default(handle);
}

/* Entry action for state 'Wait'. */
static void datalogger_enact_main_region_Logger_r1_Active_r1_Wait(Datalogger* handle)
{
	/* Entry action for state 'Wait'. */
	datalogger_setTimer(handle, (sc_eventid) &(handle->timeEvents.datalogger_main_region_Logger_r1_Active_r1_Wait_tev0_raised) , 30 * 1000, bool_false);
}

/* Entry action for state 'Active'. */
static void datalogger_enact_main_region_Logger_r2_Display_Sleepmode_r1_Active(Datalogger* handle)
{
	/* Entry action for state 'Active'. */
	datalogger_setTimer(handle, (sc_eventid) &(handle->timeEvents.datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Active_tev0_raised) , 120 * 1000, bool_false);
}

/* Exit action for state 'Wait'. */
static void datalogger_exact_main_region_Logger_r1_Active_r1_Wait(Datalogger* handle)
{
	/* Exit action for state 'Wait'. */
	datalogger_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.datalogger_main_region_Logger_r1_Active_r1_Wait_tev0_raised) );		
}

/* Exit action for state 'Active'. */
static void datalogger_exact_main_region_Logger_r2_Display_Sleepmode_r1_Active(Datalogger* handle)
{
	/* Exit action for state 'Active'. */
	datalogger_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Active_tev0_raised) );		
}

/* 'default' enter sequence for state Logger */
static void datalogger_enseq_main_region_Logger_default(Datalogger* handle)
{
	/* 'default' enter sequence for state Logger */
	datalogger_enseq_main_region_Logger_r1_default(handle);
	datalogger_enseq_main_region_Logger_r2_default(handle);
}

/* 'default' enter sequence for state MQTT Connecting */
static void datalogger_enseq_main_region_Logger_r1_Active_r1_MQTT_Connecting_default(Datalogger* handle)
{
	/* 'default' enter sequence for state MQTT Connecting */
	handle->stateConfVector[0] = Datalogger_main_region_Logger_r1_Active_r1_MQTT_Connecting;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Collecting Data */
static void datalogger_enseq_main_region_Logger_r1_Active_r1_Collecting_Data_default(Datalogger* handle)
{
	/* 'default' enter sequence for state Collecting Data */
	handle->stateConfVector[0] = Datalogger_main_region_Logger_r1_Active_r1_Collecting_Data;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Publishing Data */
static void datalogger_enseq_main_region_Logger_r1_Active_r1_Publishing_Data_default(Datalogger* handle)
{
	/* 'default' enter sequence for state Publishing Data */
	handle->stateConfVector[0] = Datalogger_main_region_Logger_r1_Active_r1_Publishing_Data;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Wait */
static void datalogger_enseq_main_region_Logger_r1_Active_r1_Wait_default(Datalogger* handle)
{
	/* 'default' enter sequence for state Wait */
	datalogger_enact_main_region_Logger_r1_Active_r1_Wait(handle);
	handle->stateConfVector[0] = Datalogger_main_region_Logger_r1_Active_r1_Wait;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Error */
static void datalogger_enseq_main_region_Logger_r1_Error_default(Datalogger* handle)
{
	/* 'default' enter sequence for state Error */
	handle->stateConfVector[0] = Datalogger_main_region_Logger_r1_Error;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Active */
static void datalogger_enseq_main_region_Logger_r2_Display_Sleepmode_r1_Active_default(Datalogger* handle)
{
	/* 'default' enter sequence for state Active */
	datalogger_enact_main_region_Logger_r2_Display_Sleepmode_r1_Active(handle);
	handle->stateConfVector[1] = Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Active;
	handle->stateConfVectorPosition = 1;
	handle->historyVector[0] = handle->stateConfVector[1];
}

/* 'default' enter sequence for state Sleeping */
static void datalogger_enseq_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping_default(Datalogger* handle)
{
	/* 'default' enter sequence for state Sleeping */
	handle->stateConfVector[1] = Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping;
	handle->stateConfVectorPosition = 1;
	handle->historyVector[0] = handle->stateConfVector[1];
}

/* 'default' enter sequence for region main region */
static void datalogger_enseq_main_region_default(Datalogger* handle)
{
	/* 'default' enter sequence for region main region */
	datalogger_react_main_region__entry_Default(handle);
}

/* 'default' enter sequence for region r1 */
static void datalogger_enseq_main_region_Logger_r1_default(Datalogger* handle)
{
	/* 'default' enter sequence for region r1 */
	datalogger_react_main_region_Logger_r1__entry_Default(handle);
}

/* 'default' enter sequence for region r2 */
static void datalogger_enseq_main_region_Logger_r2_default(Datalogger* handle)
{
	/* 'default' enter sequence for region r2 */
	datalogger_react_main_region_Logger_r2__entry_Default(handle);
}

/* shallow enterSequence with history in child r1 */
static void datalogger_shenseq_main_region_Logger_r2_Display_Sleepmode_r1(Datalogger* handle)
{
	/* shallow enterSequence with history in child r1 */
	/* Handle shallow history entry of r1 */
	switch(handle->historyVector[ 0 ])
	{
		case Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Active :
		{
			datalogger_enseq_main_region_Logger_r2_Display_Sleepmode_r1_Active_default(handle);
			break;
		}
		case Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping :
		{
			datalogger_enseq_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping_default(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for state Active */
static void datalogger_exseq_main_region_Logger_r1_Active(Datalogger* handle)
{
	/* Default exit sequence for state Active */
	datalogger_exseq_main_region_Logger_r1_Active_r1(handle);
}

/* Default exit sequence for state MQTT Connecting */
static void datalogger_exseq_main_region_Logger_r1_Active_r1_MQTT_Connecting(Datalogger* handle)
{
	/* Default exit sequence for state MQTT Connecting */
	handle->stateConfVector[0] = Datalogger_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Collecting Data */
static void datalogger_exseq_main_region_Logger_r1_Active_r1_Collecting_Data(Datalogger* handle)
{
	/* Default exit sequence for state Collecting Data */
	handle->stateConfVector[0] = Datalogger_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Publishing Data */
static void datalogger_exseq_main_region_Logger_r1_Active_r1_Publishing_Data(Datalogger* handle)
{
	/* Default exit sequence for state Publishing Data */
	handle->stateConfVector[0] = Datalogger_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Wait */
static void datalogger_exseq_main_region_Logger_r1_Active_r1_Wait(Datalogger* handle)
{
	/* Default exit sequence for state Wait */
	handle->stateConfVector[0] = Datalogger_last_state;
	handle->stateConfVectorPosition = 0;
	datalogger_exact_main_region_Logger_r1_Active_r1_Wait(handle);
}

/* Default exit sequence for state Error */
static void datalogger_exseq_main_region_Logger_r1_Error(Datalogger* handle)
{
	/* Default exit sequence for state Error */
	handle->stateConfVector[0] = Datalogger_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Active */
static void datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1_Active(Datalogger* handle)
{
	/* Default exit sequence for state Active */
	handle->stateConfVector[1] = Datalogger_last_state;
	handle->stateConfVectorPosition = 1;
	datalogger_exact_main_region_Logger_r2_Display_Sleepmode_r1_Active(handle);
}

/* Default exit sequence for state Sleeping */
static void datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping(Datalogger* handle)
{
	/* Default exit sequence for state Sleeping */
	handle->stateConfVector[1] = Datalogger_last_state;
	handle->stateConfVectorPosition = 1;
}

/* Default exit sequence for region main region */
static void datalogger_exseq_main_region(Datalogger* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of datalogger.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Datalogger_main_region_Logger_r1_Active_r1_MQTT_Connecting :
		{
			datalogger_exseq_main_region_Logger_r1_Active_r1_MQTT_Connecting(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Active_r1_Collecting_Data :
		{
			datalogger_exseq_main_region_Logger_r1_Active_r1_Collecting_Data(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Active_r1_Publishing_Data :
		{
			datalogger_exseq_main_region_Logger_r1_Active_r1_Publishing_Data(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Active_r1_Wait :
		{
			datalogger_exseq_main_region_Logger_r1_Active_r1_Wait(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Error :
		{
			datalogger_exseq_main_region_Logger_r1_Error(handle);
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of datalogger.main_region) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Active :
		{
			datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1_Active(handle);
			break;
		}
		case Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping :
		{
			datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r1 */
static void datalogger_exseq_main_region_Logger_r1(Datalogger* handle)
{
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of datalogger.main_region.Logger.r1) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Datalogger_main_region_Logger_r1_Active_r1_MQTT_Connecting :
		{
			datalogger_exseq_main_region_Logger_r1_Active_r1_MQTT_Connecting(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Active_r1_Collecting_Data :
		{
			datalogger_exseq_main_region_Logger_r1_Active_r1_Collecting_Data(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Active_r1_Publishing_Data :
		{
			datalogger_exseq_main_region_Logger_r1_Active_r1_Publishing_Data(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Active_r1_Wait :
		{
			datalogger_exseq_main_region_Logger_r1_Active_r1_Wait(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Error :
		{
			datalogger_exseq_main_region_Logger_r1_Error(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r1 */
static void datalogger_exseq_main_region_Logger_r1_Active_r1(Datalogger* handle)
{
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of datalogger.main_region.Logger.r1.Active.r1) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Datalogger_main_region_Logger_r1_Active_r1_MQTT_Connecting :
		{
			datalogger_exseq_main_region_Logger_r1_Active_r1_MQTT_Connecting(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Active_r1_Collecting_Data :
		{
			datalogger_exseq_main_region_Logger_r1_Active_r1_Collecting_Data(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Active_r1_Publishing_Data :
		{
			datalogger_exseq_main_region_Logger_r1_Active_r1_Publishing_Data(handle);
			break;
		}
		case Datalogger_main_region_Logger_r1_Active_r1_Wait :
		{
			datalogger_exseq_main_region_Logger_r1_Active_r1_Wait(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r2 */
static void datalogger_exseq_main_region_Logger_r2(Datalogger* handle)
{
	/* Default exit sequence for region r2 */
	/* Handle exit of all possible states (of datalogger.main_region.Logger.r2) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Active :
		{
			datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1_Active(handle);
			break;
		}
		case Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping :
		{
			datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r1 */
static void datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1(Datalogger* handle)
{
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of datalogger.main_region.Logger.r2.Display_Sleepmode.r1) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Active :
		{
			datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1_Active(handle);
			break;
		}
		case Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping :
		{
			datalogger_exseq_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state MQTT Connecting. */
static void datalogger_react_main_region_Logger_r1_Active_r1_MQTT_Connecting(Datalogger* handle)
{
	/* The reactions of state MQTT Connecting. */
	if (datalogger_check_main_region_Logger_r1_Active_tr0_tr0(handle) == bool_true)
	{ 
		datalogger_effect_main_region_Logger_r1_Active_tr0(handle);
	}  else
	{
		datalogger_effect_main_region_Logger_r1_Active_r1_MQTT_Connecting_tr0(handle);
	}
}

/* The reactions of state Collecting Data. */
static void datalogger_react_main_region_Logger_r1_Active_r1_Collecting_Data(Datalogger* handle)
{
	/* The reactions of state Collecting Data. */
	if (datalogger_check_main_region_Logger_r1_Active_tr0_tr0(handle) == bool_true)
	{ 
		datalogger_effect_main_region_Logger_r1_Active_tr0(handle);
	}  else
	{
		datalogger_effect_main_region_Logger_r1_Active_r1_Collecting_Data_tr0(handle);
	}
}

/* The reactions of state Publishing Data. */
static void datalogger_react_main_region_Logger_r1_Active_r1_Publishing_Data(Datalogger* handle)
{
	/* The reactions of state Publishing Data. */
	if (datalogger_check_main_region_Logger_r1_Active_tr0_tr0(handle) == bool_true)
	{ 
		datalogger_effect_main_region_Logger_r1_Active_tr0(handle);
	}  else
	{
		datalogger_effect_main_region_Logger_r1_Active_r1_Publishing_Data_tr0(handle);
	}
}

/* The reactions of state Wait. */
static void datalogger_react_main_region_Logger_r1_Active_r1_Wait(Datalogger* handle)
{
	/* The reactions of state Wait. */
	if (datalogger_check_main_region_Logger_r1_Active_tr0_tr0(handle) == bool_true)
	{ 
		datalogger_effect_main_region_Logger_r1_Active_tr0(handle);
	}  else
	{
		if (datalogger_check_main_region_Logger_r1_Active_r1_Wait_tr0_tr0(handle) == bool_true)
		{ 
			datalogger_effect_main_region_Logger_r1_Active_r1_Wait_tr0(handle);
		} 
	}
}

/* The reactions of state Error. */
static void datalogger_react_main_region_Logger_r1_Error(Datalogger* handle)
{
}

/* The reactions of state Active. */
static void datalogger_react_main_region_Logger_r2_Display_Sleepmode_r1_Active(Datalogger* handle)
{
	/* The reactions of state Active. */
	if (datalogger_check_main_region_Logger_r2_Display_Sleepmode_r1_Active_tr0_tr0(handle) == bool_true)
	{ 
		datalogger_effect_main_region_Logger_r2_Display_Sleepmode_r1_Active_tr0(handle);
	}  else
	{
		if (datalogger_check_main_region_Logger_r2_Display_Sleepmode_r1_Active_tr1_tr1(handle) == bool_true)
		{ 
			datalogger_effect_main_region_Logger_r2_Display_Sleepmode_r1_Active_tr1(handle);
		} 
	}
}

/* The reactions of state Sleeping. */
static void datalogger_react_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping(Datalogger* handle)
{
	/* The reactions of state Sleeping. */
	if (datalogger_check_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping_tr0_tr0(handle) == bool_true)
	{ 
		datalogger_effect_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping_tr0(handle);
	} 
}

/* Default react sequence for initial entry  */
static void datalogger_react_main_region_Logger_r1__entry_Default(Datalogger* handle)
{
	/* Default react sequence for initial entry  */
	datalogger_enseq_main_region_Logger_r1_Active_r1_MQTT_Connecting_default(handle);
}

/* Default react sequence for shallow history entry  */
static void datalogger_react_main_region_Logger_r2_Display_Sleepmode_r1__entry_Default(Datalogger* handle)
{
	/* Default react sequence for shallow history entry  */
	/* Enter the region with shallow history */
	if (handle->historyVector[0] != Datalogger_last_state)
	{
		datalogger_shenseq_main_region_Logger_r2_Display_Sleepmode_r1(handle);
	} else
	{
		datalogger_enseq_main_region_Logger_r2_Display_Sleepmode_r1_Active_default(handle);
	} 
}

/* Default react sequence for initial entry  */
static void datalogger_react_main_region_Logger_r2__entry_Default(Datalogger* handle)
{
	/* Default react sequence for initial entry  */
	datalogger_react_main_region_Logger_r2_Display_Sleepmode_r1__entry_Default(handle);
}

/* Default react sequence for initial entry  */
static void datalogger_react_main_region__entry_Default(Datalogger* handle)
{
	/* Default react sequence for initial entry  */
	datalogger_enseq_main_region_Logger_default(handle);
}


