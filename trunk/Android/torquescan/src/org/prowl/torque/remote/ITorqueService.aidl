package org.prowl.torque.remote;

interface ITorqueService {

   /**
    * Get the API version (currently 1)
    */
   int getVersion();

   /**
    * Get the most recent value stored for the given PID.  This will return immediately whether or not data exists.
    * @param triggersDataRefresh Cause the data to be re-requested from the ECU
    */
   float getValueForPid(long pid, boolean triggersDataRefresh);

   /**
    * Get a textual, long description regarding the PID, already translated (when translation is implemented)
    */
   String getDescriptionForPid(long pid);
   
   /**
    * Get the shortname of the PID
    */
   String getShortNameForPid(long pid);

   /**
    * Get the Si unit in string form for the PID, if no Si unit is available, a textual-description is returned instead.
    */
   String getUnitForPid(long pid);
   
   /**
    * Get the minimum value expected for this PID
    */
   float getMinValueForPid(long pid);
   
   /**
    * Get the maximum value expected for this PId
    */
   float getMaxValueForPid(long pid);
   
   /**
    * Returns a list of currently 'active' PIDs. This list will change often.
    *
    * PIDs are stored as hex values, so '0x01, 0x0D' (vehicle speed) is the equivalent:  Integer.parseInt("010D",16);
    */
   long[] getListOfActivePids();

}