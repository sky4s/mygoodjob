/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: /Users/ihawkins/Documents/workspace/torquescan/src/org/prowl/torque/remote/ITorqueService.aidl
 */
package org.prowl.torque.remote;
public interface ITorqueService extends android.os.IInterface
{
/** Local-side IPC implementation stub class. */
public static abstract class Stub extends android.os.Binder implements org.prowl.torque.remote.ITorqueService
{
private static final java.lang.String DESCRIPTOR = "org.prowl.torque.remote.ITorqueService";
/** Construct the stub at attach it to the interface. */
public Stub()
{
this.attachInterface(this, DESCRIPTOR);
}
/**
 * Cast an IBinder object into an org.prowl.torque.remote.ITorqueService interface,
 * generating a proxy if needed.
 */
public static org.prowl.torque.remote.ITorqueService asInterface(android.os.IBinder obj)
{
if ((obj==null)) {
return null;
}
android.os.IInterface iin = (android.os.IInterface)obj.queryLocalInterface(DESCRIPTOR);
if (((iin!=null)&&(iin instanceof org.prowl.torque.remote.ITorqueService))) {
return ((org.prowl.torque.remote.ITorqueService)iin);
}
return new org.prowl.torque.remote.ITorqueService.Stub.Proxy(obj);
}
public android.os.IBinder asBinder()
{
return this;
}
@Override public boolean onTransact(int code, android.os.Parcel data, android.os.Parcel reply, int flags) throws android.os.RemoteException
{
switch (code)
{
case INTERFACE_TRANSACTION:
{
reply.writeString(DESCRIPTOR);
return true;
}
case TRANSACTION_getVersion:
{
data.enforceInterface(DESCRIPTOR);
int _result = this.getVersion();
reply.writeNoException();
reply.writeInt(_result);
return true;
}
case TRANSACTION_getValueForPid:
{
data.enforceInterface(DESCRIPTOR);
long _arg0;
_arg0 = data.readLong();
boolean _arg1;
_arg1 = (0!=data.readInt());
float _result = this.getValueForPid(_arg0, _arg1);
reply.writeNoException();
reply.writeFloat(_result);
return true;
}
case TRANSACTION_getDescriptionForPid:
{
data.enforceInterface(DESCRIPTOR);
long _arg0;
_arg0 = data.readLong();
java.lang.String _result = this.getDescriptionForPid(_arg0);
reply.writeNoException();
reply.writeString(_result);
return true;
}
case TRANSACTION_getShortNameForPid:
{
data.enforceInterface(DESCRIPTOR);
long _arg0;
_arg0 = data.readLong();
java.lang.String _result = this.getShortNameForPid(_arg0);
reply.writeNoException();
reply.writeString(_result);
return true;
}
case TRANSACTION_getUnitForPid:
{
data.enforceInterface(DESCRIPTOR);
long _arg0;
_arg0 = data.readLong();
java.lang.String _result = this.getUnitForPid(_arg0);
reply.writeNoException();
reply.writeString(_result);
return true;
}
case TRANSACTION_getMinValueForPid:
{
data.enforceInterface(DESCRIPTOR);
long _arg0;
_arg0 = data.readLong();
float _result = this.getMinValueForPid(_arg0);
reply.writeNoException();
reply.writeFloat(_result);
return true;
}
case TRANSACTION_getMaxValueForPid:
{
data.enforceInterface(DESCRIPTOR);
long _arg0;
_arg0 = data.readLong();
float _result = this.getMaxValueForPid(_arg0);
reply.writeNoException();
reply.writeFloat(_result);
return true;
}
case TRANSACTION_getListOfActivePids:
{
data.enforceInterface(DESCRIPTOR);
long[] _result = this.getListOfActivePids();
reply.writeNoException();
reply.writeLongArray(_result);
return true;
}
}
return super.onTransact(code, data, reply, flags);
}
private static class Proxy implements org.prowl.torque.remote.ITorqueService
{
private android.os.IBinder mRemote;
Proxy(android.os.IBinder remote)
{
mRemote = remote;
}
public android.os.IBinder asBinder()
{
return mRemote;
}
public java.lang.String getInterfaceDescriptor()
{
return DESCRIPTOR;
}
/**
    * Get the API version (currently 1)
    */
public int getVersion() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
int _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_getVersion, _data, _reply, 0);
_reply.readException();
_result = _reply.readInt();
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
/**
    * Get the most recent value stored for the given PID.  This will return immediately whether or not data exists.
    * @param triggersDataRefresh Cause the data to be re-requested from the ECU
    */
public float getValueForPid(long pid, boolean triggersDataRefresh) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
float _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
_data.writeLong(pid);
_data.writeInt(((triggersDataRefresh)?(1):(0)));
mRemote.transact(Stub.TRANSACTION_getValueForPid, _data, _reply, 0);
_reply.readException();
_result = _reply.readFloat();
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
/**
    * Get a textual, long description regarding the PID, already translated (when translation is implemented)
    */
public java.lang.String getDescriptionForPid(long pid) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
java.lang.String _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
_data.writeLong(pid);
mRemote.transact(Stub.TRANSACTION_getDescriptionForPid, _data, _reply, 0);
_reply.readException();
_result = _reply.readString();
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
/**
    * Get the shortname of the PID
    */
public java.lang.String getShortNameForPid(long pid) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
java.lang.String _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
_data.writeLong(pid);
mRemote.transact(Stub.TRANSACTION_getShortNameForPid, _data, _reply, 0);
_reply.readException();
_result = _reply.readString();
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
/**
    * Get the Si unit in string form for the PID, if no Si unit is available, a textual-description is returned instead.
    */
public java.lang.String getUnitForPid(long pid) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
java.lang.String _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
_data.writeLong(pid);
mRemote.transact(Stub.TRANSACTION_getUnitForPid, _data, _reply, 0);
_reply.readException();
_result = _reply.readString();
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
/**
    * Get the minimum value expected for this PID
    */
public float getMinValueForPid(long pid) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
float _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
_data.writeLong(pid);
mRemote.transact(Stub.TRANSACTION_getMinValueForPid, _data, _reply, 0);
_reply.readException();
_result = _reply.readFloat();
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
/**
    * Get the maximum value expected for this PId
    */
public float getMaxValueForPid(long pid) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
float _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
_data.writeLong(pid);
mRemote.transact(Stub.TRANSACTION_getMaxValueForPid, _data, _reply, 0);
_reply.readException();
_result = _reply.readFloat();
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
/**
    * Returns a list of currently 'active' PIDs. This list will change often.
    *
    * PIDs are stored as hex values, so '0x01, 0x0D' (vehicle speed) is the equivalent:  Integer.parseInt("010D",16);
    */
public long[] getListOfActivePids() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
long[] _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_getListOfActivePids, _data, _reply, 0);
_reply.readException();
_result = _reply.createLongArray();
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
}
static final int TRANSACTION_getVersion = (android.os.IBinder.FIRST_CALL_TRANSACTION + 0);
static final int TRANSACTION_getValueForPid = (android.os.IBinder.FIRST_CALL_TRANSACTION + 1);
static final int TRANSACTION_getDescriptionForPid = (android.os.IBinder.FIRST_CALL_TRANSACTION + 2);
static final int TRANSACTION_getShortNameForPid = (android.os.IBinder.FIRST_CALL_TRANSACTION + 3);
static final int TRANSACTION_getUnitForPid = (android.os.IBinder.FIRST_CALL_TRANSACTION + 4);
static final int TRANSACTION_getMinValueForPid = (android.os.IBinder.FIRST_CALL_TRANSACTION + 5);
static final int TRANSACTION_getMaxValueForPid = (android.os.IBinder.FIRST_CALL_TRANSACTION + 6);
static final int TRANSACTION_getListOfActivePids = (android.os.IBinder.FIRST_CALL_TRANSACTION + 7);
}
/**
    * Get the API version (currently 1)
    */
public int getVersion() throws android.os.RemoteException;
/**
    * Get the most recent value stored for the given PID.  This will return immediately whether or not data exists.
    * @param triggersDataRefresh Cause the data to be re-requested from the ECU
    */
public float getValueForPid(long pid, boolean triggersDataRefresh) throws android.os.RemoteException;
/**
    * Get a textual, long description regarding the PID, already translated (when translation is implemented)
    */
public java.lang.String getDescriptionForPid(long pid) throws android.os.RemoteException;
/**
    * Get the shortname of the PID
    */
public java.lang.String getShortNameForPid(long pid) throws android.os.RemoteException;
/**
    * Get the Si unit in string form for the PID, if no Si unit is available, a textual-description is returned instead.
    */
public java.lang.String getUnitForPid(long pid) throws android.os.RemoteException;
/**
    * Get the minimum value expected for this PID
    */
public float getMinValueForPid(long pid) throws android.os.RemoteException;
/**
    * Get the maximum value expected for this PId
    */
public float getMaxValueForPid(long pid) throws android.os.RemoteException;
/**
    * Returns a list of currently 'active' PIDs. This list will change often.
    *
    * PIDs are stored as hex values, so '0x01, 0x0D' (vehicle speed) is the equivalent:  Integer.parseInt("010D",16);
    */
public long[] getListOfActivePids() throws android.os.RemoteException;
}
