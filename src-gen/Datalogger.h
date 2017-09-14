
#ifndef DATALOGGER_H_
#define DATALOGGER_H_

#include "sc_types.h"
		
#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'datalogger'.
*/


/*! Enumeration of all states */ 
typedef enum
{
	Datalogger_last_state,
	Datalogger_main_region_Logger,
	Datalogger_main_region_Logger_r1_Active,
	Datalogger_main_region_Logger_r1_Active_r1_MQTT_Connecting,
	Datalogger_main_region_Logger_r1_Active_r1_Collecting_Data,
	Datalogger_main_region_Logger_r1_Active_r1_Publishing_Data,
	Datalogger_main_region_Logger_r1_Active_r1_Wait,
	Datalogger_main_region_Logger_r1_Error,
	Datalogger_main_region_Logger_r2_Display_Sleepmode,
	Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Active,
	Datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Sleeping
} DataloggerStates;

/*! Type definition of the data structure for the DataloggerIfaceDisplay interface scope. */
typedef struct
{
	sc_boolean isSleeping;
	sc_string displayText;
} DataloggerIfaceDisplay;

/*! Type definition of the data structure for the DataloggerIface interface scope. */
typedef struct
{
	sc_boolean ButtonPressed_raised;
	sc_boolean Failure_raised;
} DataloggerIface;

/*! Type definition of the data structure for the DataloggerTimeEvents interface scope. */
typedef struct
{
	sc_boolean datalogger_main_region_Logger_r1_Active_r1_Wait_tev0_raised;
	sc_boolean datalogger_main_region_Logger_r2_Display_Sleepmode_r1_Active_tev0_raised;
} DataloggerTimeEvents;


/*! Define dimension of the state configuration vector for orthogonal states. */
#define DATALOGGER_MAX_ORTHOGONAL_STATES 2
	/*! Define dimension of the state configuration vector for history states. */
#define DATALOGGER_MAX_HISTORY_STATES 1

/*! Define indices of states in the StateConfVector */
#define SCVI_DATALOGGER_MAIN_REGION_LOGGER 0
#define SCVI_DATALOGGER_MAIN_REGION_LOGGER_R1_ACTIVE 0
#define SCVI_DATALOGGER_MAIN_REGION_LOGGER_R1_ACTIVE_R1_MQTT_CONNECTING 0
#define SCVI_DATALOGGER_MAIN_REGION_LOGGER_R1_ACTIVE_R1_COLLECTING_DATA 0
#define SCVI_DATALOGGER_MAIN_REGION_LOGGER_R1_ACTIVE_R1_PUBLISHING_DATA 0
#define SCVI_DATALOGGER_MAIN_REGION_LOGGER_R1_ACTIVE_R1_WAIT 0
#define SCVI_DATALOGGER_MAIN_REGION_LOGGER_R1_ERROR 0
#define SCVI_DATALOGGER_MAIN_REGION_LOGGER_R2_DISPLAY_SLEEPMODE 1
#define SCVI_DATALOGGER_MAIN_REGION_LOGGER_R2_DISPLAY_SLEEPMODE_R1_ACTIVE 1
#define SCVI_DATALOGGER_MAIN_REGION_LOGGER_R2_DISPLAY_SLEEPMODE_R1_SLEEPING 1

/*! 
 * Type definition of the data structure for the Datalogger state machine.
 * This data structure has to be allocated by the client code. 
 */
typedef struct
{
	DataloggerStates stateConfVector[DATALOGGER_MAX_ORTHOGONAL_STATES];
	DataloggerStates historyVector[DATALOGGER_MAX_HISTORY_STATES];
	sc_ushort stateConfVectorPosition; 
	
	DataloggerIfaceDisplay ifaceDisplay;
	DataloggerIface iface;
	DataloggerTimeEvents timeEvents;
} Datalogger;


/*! Initializes the Datalogger state machine data structures. Must be called before first usage.*/
extern void datalogger_init(Datalogger* handle);

/*! Activates the state machine */
extern void datalogger_enter(Datalogger* handle);

/*! Deactivates the state machine */
extern void datalogger_exit(Datalogger* handle);

/*! Performs a 'run to completion' step. */
extern void datalogger_runCycle(Datalogger* handle);

/*! Raises a time event. */
extern void datalogger_raiseTimeEvent(const Datalogger* handle, sc_eventid evid);

/*! Gets the value of the variable 'isSleeping' that is defined in the interface scope 'Display'. */ 
extern sc_boolean dataloggerIfaceDisplay_get_isSleeping(const Datalogger* handle);
/*! Sets the value of the variable 'isSleeping' that is defined in the interface scope 'Display'. */ 
extern void dataloggerIfaceDisplay_set_isSleeping(Datalogger* handle, sc_boolean value);
/*! Gets the value of the variable 'displayText' that is defined in the interface scope 'Display'. */ 
extern sc_string dataloggerIfaceDisplay_get_displayText(const Datalogger* handle);
/*! Sets the value of the variable 'displayText' that is defined in the interface scope 'Display'. */ 
extern void dataloggerIfaceDisplay_set_displayText(Datalogger* handle, sc_string value);
/*! Raises the in event 'ButtonPressed' that is defined in the default interface scope. */ 
extern void dataloggerIface_raise_buttonPressed(Datalogger* handle);

/*! Raises the in event 'Failure' that is defined in the default interface scope. */ 
extern void dataloggerIface_raise_failure(Datalogger* handle);


/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean datalogger_isActive(const Datalogger* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean datalogger_isFinal(const Datalogger* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean datalogger_isStateActive(const Datalogger* handle, DataloggerStates state);



#ifdef __cplusplus
}
#endif 

#endif /* DATALOGGER_H_ */
