package org.prowl.torque.remote;

interface ITorqueService {

   /**
    * Get the API version. The version will increment each time the API is revised.
    */
   int getVersion();

   /**
    * Get the most recent value stored for the given PID.  This will return immediately whether or not data exists.
    * @param triggersDataRefresh Cause the data to be re-requested from the ECU
    * @note If the PID returns multiple values(has multiple displays setup for the same PID), then this call will return the data for the first matching PID
    * @deprecated  See getPIDInformation(...), listAllPIDs(), getPIDValues(...) and listActivePIDs() which replaces this call and can handle sensors with the same 'PID'   
    */
   float getValueForPid(long pid, boolean triggersDataRefresh);

   /**
    * Get a textual, long description regarding the PID, already translated (when translation is implemented)
    * @note If the PID returns multiple values(has multiple displays setup for the same PID), then this call will return the data for the first matching PID
    * @deprecated  See getPIDInformation(...), listAllPIDs(), getPIDValues(...) and listActivePIDs() which replaces this call and can handle sensors with the same 'PID'   
    */
   String getDescriptionForPid(long pid);
   
   /**
    * Get the shortname of the PID
    * @note If the PID returns multiple values, then this call will return the data for the first matching PID
    * @deprecated  See getPIDInformation(...), listAllPIDs(), getPIDValues(...) and listActivePIDs() which replaces this call and can handle sensors with the same 'PID'   
    */
   String getShortNameForPid(long pid);

   /**
    * Get the Si unit in string form for the PID, if no Si unit is available, a textual-description is returned instead.
    * @note If the PID returns multiple values(has multiple displays setup for the same PID), then this call will return the data for the first matching PID
    * @deprecated  See getPIDInformation(...), listAllPIDs(), getPIDValues(...) and listActivePIDs() which replaces this call and can handle sensors with the same 'PID'   
    */
   String getUnitForPid(long pid);
   
   /**
    * Get the minimum value expected for this PID
    * @note If the PID returns multiple values(has multiple displays setup for the same PID), then this call will return the data for the first matching PID
    * @deprecated  See getPIDInformation(...), listAllPIDs(), getPIDValues(...) and listActivePIDs() which replaces this call and can handle sensors with the same 'PID'   
    */
   float getMinValueForPid(long pid);
   
   /**
    * Get the maximum value expected for this PId
    * @note If the PID returns multiple values(has multiple displays setup for the same PID), then this call will return the data for the first matching PID
    * @deprecated  See getPIDInformation(...), listAllPIDs(), getPIDValues(...) and listActivePIDs() which replaces this call and can handle sensors with the same 'PID'   
    */
   float getMaxValueForPid(long pid);
   
   /**
    * Returns a list of currently 'active' PIDs. This list will change often. Try not to call this method too frequently.
    *
    * PIDs are stored as hex values, so '0x01, 0x0D' (vehicle speed) is the equivalent:  Integer.parseInt("010D",16);
    * @note If the PID returns multiple values(has multiple displays setup for the same PID), then this call will return the data for the first matching PID
    * @deprecated  See getPIDInformation(...), listAllPIDs(), getPIDValues(...) and listActivePIDs() which replaces this call and can handle sensors with the same 'PID'   
    */
   long[] getListOfActivePids();
   
   /**
    * Returns a list of PIDs that have been reported by the ECU as supported.
    *
    * PIDs are stored as hex values, so '0x01, 0x0D' (vehicle speed) is the equivalent:  Integer.parseInt("010D",16);
    * @note If the PID returns multiple values(has multiple displays setup for the same PID), then this call will return the data for the first matching PID
    * @deprecated  See getPIDInformation(...), listAllPIDs(), getPIDValues(...) and listActivePIDs() which replaces this call and can handle sensors with the same 'PID'   
    */
   long[] getListOfECUSupportedPids();
   
   /**
    * Returns a list of all the known available sensors, active or inactive.
    * 
    * Try not to call this method too frequently.
    *
    * PIDs are stored as hex values, so '0x01, 0x0D' (vehicle speed) is the equivalent:  Integer.parseInt("010D",16);
    * @note If the PID returns multiple values(has multiple displays setup for the same PID), then this call will return the data for the first matching PID
    * @deprecated  See getPIDInformation(...), getPIDValues(...)  and listAllPIDs() which replaces this call and can handle sensors with the same 'PID'
    */
   long[] getListOfAllPids();
   
   /**
    * True if the user has granted full permissions to the plugin (to send anything that it wants)
    */
   boolean hasFullPermissions();
   
   /**
    * Send a specific request over the OBD bus and return the response as a string
    *
    * This is currently limited by the 'Allow full permissions' option in the settings.
    */
   String[] sendCommandGetResponse(String header, String command);

  /**
   * Given this unit, get the users preferred units
   */
   String getPreferredUnit(String unit);
   
   /**
    * Add / Update a PID from your plugin to the main app, Your PID is keyed by name.
    *
    * @deprecated - (see below)superceded by setPIDInformation(String name, String shortName, String unit, float max, float min, float value, String stringValue);
    */
   boolean setPIDData(String name, String shortName, String unit, float max, float min, float value);
   
   /**
    * Get connection state to ECU
    * @return true if connected to the ECU, false if the app has not yet started retrieving data from the ECU 
    */
    boolean isConnectedToECU();

   /**
    * Turn on or off test mode. This is for debugging only and simulates readings to some of the sensors.
    */
   boolean setDebugTestMode(boolean activateTestMode);

   /**
    * Returns a string array containing the vehicle profile information:
    *
    *  Array:
    *     [0] Profile name
    *     [1] Engine Displacement (L)
    *     [2] Weight in kilogrammes
    *     [3] Fuel type (0 = Petrol, 1 = Diesel, 2 = E85 (Ethanol/Petrol)    *     [4] Boost adjustment
    *     [5] Max RPM setting
    *     [6] Volumetric efficiency (%)
    *     [7] Accumulated distance travelled
    */
   String[] getVehicleProfileInformation();

   /**
    * Store some information into the vehicle profile. 
    *
    * @param key  Prefix the 'key' with your apps classpath (to avoid conflicts). eg: "com.company.pluginname.SOME_KEY_NAME" is nice and clear  (Don't use any characters other than A-Za-z0-9 . and _)
    * @param The value to store.
    * @param saveToFile Set this to true (on your last 'set') to commit the information to disk.
    * @return 0 if successful.
    */
    int storeInProfile(String key, String value, boolean saveToFileNow);
    
    
   /**
    * Retrieve some information from the vehicle profile.
    *
    * @param Prefix the 'key' with your apps classpath (to avoid conflicts). 
    */
    String retrieveProfileData(String key);
    
    /**
     * Retrieve the number of errors that Torque has seen happen at the adapter
     *
     * Generally speaking, if this is above 0, then you have problems at the adapter side.
     */
    int getDataErrorCount();
    
    /**
     * Get max PID read speed in PIDs read per second
     *
     * This is reset each connection to the adpater.
     */
    double getPIDReadSpeed(); 
    

    /**
     * Gets the configured communications speed
     *
     *  1 == slowest (for problematic adapters)
     *  2 == standard (The app default)
     *  3 == fast mode (selectable in the OBD2 adapter settings)
     * 
     * Fast mode provides a significant speed increase on some vehicles for the read speed of sensor information
     */
    int getConfiguredSpeed();
    
    /**
     * returns true if the user is currently logging data to the file
     */
    boolean isFileLoggingEnabled();
    
    
    /**
     * returns true if the user is currently logging data to web
     */
    boolean isWebLoggingEnabled();
    
    /**
     * returns the number of items that are configured to be logged to file. The more items configured to log (and with logging enabled), the slower the refresh rate of individual PIDs.
     */
    int getNumberOfLoggedItems();

  /**
    * Get the time that the PID was last updated.
    * 
    * @note If the PID returns multiple values(has multiple displays setup for the same PID), then this call will return the data for the first matching PID    
    */
   long getUpdateTimeForPID(long pid);

   /**
    * Returns the scale of the requested PID
    * @note If the PID returns multiple values(has multiple displays setup for the same PID), then this call will return the data for the first matching PID      
    */
   float getScaleForPid(long pid);

   /**
    * Translate a string that *might* be in translation file in the main Torque app. Do not call this method repeatedly for the same text!
    */
    String translate(String originalText);

   /**
    * Method to send PID data in raw form. 
    *  Name, ShortName, ModeAndPID, Equation, Min, Max, Units, Header
    */ 
   boolean sendPIDData(String pluginName, in String[] name, in String[] shortName, in String[] modeAndPID, in String[] equation, in float[] minValue, in float[] maxValue, in String[] units, in String[] header);
   
   /**
    * Add / Update a PID from your plugin to the main app, Your PID is keyed by name.  This can be used to set a value on a PID in Torque.
    *
    * @param value       The value to be shown in the display 
    * @param stringValue A string value to be shown in the display - overrides 'value' when not null - note(try not to use numeric values here as they won't be unit converted for you).  Set to null to revert to using the 'float value'
    */
   boolean setPIDInformation(String name, String shortName, String unit, float max, float min, float value, String stringValue);
   
   
   /**
    * Get a list of all PIDs in torque, active or inactive. 
    *
    * The returned string is the ID of the PID to request over the aidl script.  To be helpful the first part of this string is the actual PID 'id'.
    * @note (don't call this too often as it is computationally expensive!)    
    */
    String[] listAllPIDs();
    
    
   /**
    * List all only the active PIDs
    *
    * The returned string is the ID of the PID to request over the aidl script.  To be helpful the first part of this string is the actual PID 'id'. 
    * @note (don't call this too often as it is computationally expensive!)  
    */
    String[] listActivePIDs();
    
   /**
    * List all only the active PIDs
    *
    * The returned string is the ID of the PID to request over the aidl script.  To be helpful the first part of this string is the actual PID 'id'. 
    * @note (don't call this too often as it is computationally expensive!)  
    */
    String[] listECUSupportedPIDs();
     
    
    /**
     * Return the current value only for the PID (or PIDs if you pass more than one)
     *
     * Use this method to frequently get the value of PID(s).  Be aware that the more PIDs you request, the slower the update speed (as the OBD2 adapter will require to update more PIDs and this is the choke-point)
     * This method is asynchronous updates via the adapter
     */
    float[] getPIDValues(in String[] pidsToRetrieve);
    
    
    
   /**
    * Return all the PID information in a single transaction. This is the new preferred method to get data from PIDs
    *
    * The unit returned is the raw unit (used for getPIDValues) - you can get the users preferred unit by using the relevant API call 
    *
    * Format of returned string array:
    *  String[] {
    *       String "pid information in csv format"
    *       String "pid information in csv format"
    *       ...(etc)
    *    }
    *  
    *  Example:
    *
    *   String[] {
    *      "<longName>,<shortName>,<unit>,<maxValue>,<minValue>,<scale>",
    *      "Intake Manifold Pressure,Intake,kPa,255,0,1",
    *      "Accelerator Pedal Position E,Accel(E),%,100,0,1"
    *   }
    */
   String[] getPIDInformation(in String[] pidIDs);
   
   
   /**
    * Get the time that the PID was last updated.
    *
    * @returns time when the PID value was retrieved via OBD/etc in milliseconds
    */
   long[] getPIDUpdateTime(in String[] pidIDs);
   
   
   
   
}