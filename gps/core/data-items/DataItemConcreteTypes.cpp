/* Copyright (c) 2020-2021, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation, nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
Changes from Qualcomm Innovation Center are provided under the following license:

Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted (subject to the limitations in the
disclaimer below) provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.

    * Neither the name of Qualcomm Innovation Center, Inc. nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#define LOG_TAG "DataItemConcreteTypes"

#include "DataItemConcreteTypes.h"
#include <inttypes.h>
#include <log_util.h>

#define ENH_FIELD_ENABLED "IS_QUALCOMM_ENHANCED_PROVIDER_ENABLED"
#define GPSSTATE_FIELD_ENABLED "IS_GPS_PROVIDER_ENABLED"
#define WIFIHARDWARESTATE_FIELD_ENABLED "IS_WIFI_HARDWARE_ON"
#define POWERCONNECTSTATE_FIELD_ENABLED "IS_POWER_CONNECTED"
#define TIMEZONECHANGE_FIELD_ENABLED "IS_TIMEZONE_CHANGED"
#define TIMECHANGE_FIELD_ENABLED "IS_TIME_CHANGED"
#define TIMECHANGE_FIELD_CURRENT_TIME_MILLIS "CURR_TIME_MILLIS"
#define TIMECHANGE_FIELD_RAW_OFFSET_TZ "RAW_OFFSET_TZ"
#define TIMECHANGE_FIELD_DST_OFFSET_TZ "DST_OFFSET_TZ"

#define NETWORKINFO_CARD "ACTIVE_NETWORK_INFO"
#define NETWORKINFO_FIELD_TYPE "TYPE"
#define NETWORKINFO_FIELD_TYPENAME "TYPE_NAME"
#define NETWORKINFO_FIELD_SUBTYPENAME "SUB_TYPE_NAME"
#define NETWORKINFO_FIELD_AVAILABLE "IS_AVAILABLE"
#define NETWORKINFO_FIELD_CONNECTED "IS_CONNECTED"
#define NETWORKINFO_FIELD_ROAMING "IS_ROAMING"
#define NETWORKINFO_FIELD_NETWORKHANDLE_0 "NETWORK_HANDLE_0"
#define NETWORKINFO_FIELD_NETWORKHANDLE_1 "NETWORK_HANDLE_1"
#define NETWORKINFO_FIELD_NETWORKHANDLE_2 "NETWORK_HANDLE_2"
#define NETWORKINFO_FIELD_NETWORKHANDLE_3 "NETWORK_HANDLE_3"
#define NETWORKINFO_FIELD_NETWORKHANDLE_4 "NETWORK_HANDLE_4"
#define NETWORKINFO_FIELD_NETWORKHANDLE_5 "NETWORK_HANDLE_5"
#define NETWORKINFO_FIELD_NETWORKHANDLE_6 "NETWORK_HANDLE_6"
#define NETWORKINFO_FIELD_NETWORKHANDLE_7 "NETWORK_HANDLE_7"
#define NETWORKINFO_FIELD_NETWORKHANDLE_8 "NETWORK_HANDLE_8"
#define NETWORKINFO_FIELD_NETWORKHANDLE_9 "NETWORK_HANDLE_9"
#define NETWORKINFO_FIELD_APN_NAME "APN_NAME"

#define SERVICESTATUS_FIELD_STATE "CELL_NETWORK_STATUS"
#define MODEL_FIELD_NAME "MODEL"
#define MANUFACTURER_FIELD_NAME "MANUFACTURER"
#define OSSTATUS_CARD "ACTIVE_NETWORK_INFO"

#define RILSERVICEINFO_CARD "RIL-SERVICE-INFO"
#define RILSERVICEINFO_FIELD_ARIF_TYPE_MASK "SUPPORTED-AIRINTERFACE-TYPE-MASK"
#define RILSERVICEINFO_FIELD_CARRIER_ARIF_TYPE "CARRIER-AIRINTERFACE-TYPE"
#define RILSERVICEINFO_FIELD_CARRIER_MCC "MOBILE-COUNTRY-CODE"
#define RILSERVICEINFO_FIELD_CARRIER_MNC "MOBILE-NETWORK-CODE"
#define RILSERVICEINFO_FIELD_CARRIER_NAME "HOME-CARRIER-NAME"

#define RILCELLINFO_CARD "RIL-CELL-UPDATE"
#define RILCELLINFO_FIELD_NETWORK_STATUS "NETWORK-STATUS"
#define RILCELLINFO_FIELD_RIL_TECH_TYPE "RIL-TECH-TYPE"
#define RILLCELLINFO_FIELD_MCC "MOBILE-COUNTRY-CODE"
#define RILLCELLINFO_FIELD_MNC "MOBILE-NETWORK-CODE"
#define RILLCELLINFO_FIELD_LAC "LOCATION-AREA-CODE"
#define RILLCELLINFO_FIELD_CID "CELL-ID"
#define RILLCELLINFO_FIELD_SID "SYSTEM-ID"
#define RILLCELLINFO_FIELD_NID "NETWORK-ID"
#define RILLCELLINFO_FIELD_BSID "BASE-STATION-ID"
#define RILLCELLINFO_FIELD_BSLAT "BASE-STATION-LATITUDE"
#define RILLCELLINFO_FIELD_BSLON "BASE-STATION-LONGITUDE"
#define RILLCELLINFO_FIELD_UTC_TIME_OFFSET "TIME-ZONE-OFFSET"
#define RILLCELLINFO_FIELD_DAYLIGHT_TIMEZONE "IN-DAY-LIGHT-SAVING"
#define RILLCELLINFO_FIELD_TAC "TRACKING-AREA-CODE"
#define RILLCELLINFO_FIELD_PCI "PHYSICAL-CELL-ID"
#define RILLCELLINFO_FIELD_NB_MODE "NB-MODE"
#define RILLCELLINFO_FIELD_NB_EARFCN_OFFSET "NB-EARFCN-OFFSET"

#define WIFI_SUPPLICANT_FIELD_STATE "WIFI-SUPPLICANT-STATE"
#define MCCMNC_FIELD_NAME "MCCMNC"

#define OEM_GTP_UPLAOD_TRIGGER_READY_FIELD_NAME "OEM-GTP-UPLOAD-TRIGGER-READY"
#define BATTERYLEVEL_FIELD_BATTERY_PCT "BATTERY_PCT"

#define IN_EMERGENCY_CALL_FIELD_NAME "IS_EMERGENCY"
#define PRECISE_LOCATION_ENABLED_FIELD_NAME "PRECISE_LOCATION_ENABLED"
#define TRACKING_STARTED_FIELD_NAME "TRACKING_STARTED"
#define NTRIP_STARTED_FIELD_NAME "NTRIP_STARTED"
#define NLP_STARTED_FIELD_NAME "NLP_SESSION_STARTED"
#define LOC_FEATURE_STATUS_FIELD_NAME "LOC_FEATURE_STATUS"

#define QESDK_WWAN_FEATURE_STATUS_CARD "QESDK_WWAN_FEATURE_STATUS_CARD"
#define QESDK_WWAN_FEATURE_STATUS_FIELD_QESDK_FEATURE_ID "WWAN_FEATURE_ID"
#define QESDK_WWAN_FEATURE_STATUS_FIELD_APPHASH "WWAN_FEATURE_APP_HASH"

#define QESDK_WWAN_CS_CONSENT_SRC_CARD "QESDK_WWAN_CS_CONSENT_SRC_CARD"
#define QESDK_WWAN_CS_CONSENT_SRC_FIELD_QESDK_FEATURE_ID "QESDK_FEATURE_ID"
#define QESDK_WWAN_CS_CONSENT_SRC_FIELD_PID "PID"
#define QESDK_WWAN_CS_CONSENT_SRC_FIELD_UID "UID"
#define QESDK_WWAN_CS_CONSENT_SRC_FIELD_APPHASFINEPERMISSION "APPHASFINEPERMISSION"
#define QESDK_WWAN_CS_CONSENT_SRC_FIELD_APPHASBACKGROUNDPERMISSION "APPHASBACKGROUNDPERMISSION"
#define QESDK_WWAN_CS_CONSENT_SRC_FIELD_APPHASH "APPHASH"
#define QESDK_WWAN_CS_CONSENT_SRC_FIELD_APPPACKAGENAME "APPPACKAGENAME"
#define QESDK_WWAN_CS_CONSENT_SRC_FIELD_APPCOOKIE "APPCOOKIE"
#define QESDK_WWAN_CS_CONSENT_SRC_FIELD_APPQWESLICENSEID "APPQWESLICENSEID"

namespace loc_core
{
// stringify
void ENHDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(ENHDataItem, ENH_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr = ENH_FIELD_ENABLED;
        valueStr += ": ";
        valueStr += (d->isEnabled()) ? "true" : "false";
        valueStr += " IS_QUALCOMM_ENHANCED_PROVIDER_ENABLED_CONSENT: ";
        valueStr += (((1 << FIELD_CONSENT) & d->mEnhFields) != 0) ? "true" : "false";
        valueStr += " IS_QUALCOMM_ENHANCED_PROVIDER_ENABLED_REGION: ";
        valueStr += (((1 << FIELD_REGION) & d->mEnhFields) != 0) ? "true" : "false";
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}
void GPSStateDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(GPSStateDataItem, GPSSTATE_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr = GPSSTATE_FIELD_ENABLED;
        valueStr += ": ";
        valueStr += (d->mEnabled) ? ("true") : ("false");
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}
void WifiHardwareStateDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(WifiHardwareStateDataItem,
                WIFIHARDWARESTATE_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr = WIFIHARDWARESTATE_FIELD_ENABLED;
        valueStr += ": ";
        valueStr += (d->mEnabled) ? ("true") : ("false");
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}
void PowerConnectStateDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(PowerConnectStateDataItem,
                POWER_CONNECTED_STATE_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr = POWERCONNECTSTATE_FIELD_ENABLED;
        valueStr += ": ";
        valueStr += (d->mState) ? ("true") : ("false");
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}

void BatteryLevelDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(BatteryLevelDataItem, BATTERY_LEVEL_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr += BATTERYLEVEL_FIELD_BATTERY_PCT;
        valueStr += ": ";
        char state [12];
        snprintf (state, 12, "%d", d->mBatteryPct);
        valueStr += string (state);
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}

void TimeZoneChangeDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(TimeZoneChangeDataItem, TIMEZONE_CHANGE_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr = TIMEZONECHANGE_FIELD_ENABLED;
        valueStr += ": ";
        char time [30];
        snprintf (time, 30, "%" PRIi64, d->mCurrTimeMillis);
        valueStr += string (time);
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}
void TimeChangeDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(TimeChangeDataItem, TIME_CHANGE_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr = TIMECHANGE_FIELD_ENABLED;
        valueStr += ": ";
        char time [30];
        snprintf (time, 30, "%" PRIi64, d->mCurrTimeMillis);
        valueStr += string (time);
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}
void NetworkInfoDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(NetworkInfoDataItem, NETWORKINFO_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr = NETWORKINFO_CARD;
        valueStr += "::";
        valueStr += NETWORKINFO_FIELD_TYPE;
        valueStr += "s_MASK: ";
        char type [12];
        snprintf (type, 12, "%" PRIu64, mAllTypes);
        valueStr += string (type);
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_TYPENAME;
        valueStr += ": ";
        valueStr += d->mTypeName;
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_SUBTYPENAME;
        valueStr += ": ";
        valueStr += d->mSubTypeName;
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_AVAILABLE;
        valueStr += ": ";
        valueStr += (d->mAvailable) ? ("true") : ("false");
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_CONNECTED;
        valueStr += ": ";
        valueStr += (d->mConnected) ? ("true") : ("false");
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_ROAMING;
        valueStr += ": ";
        valueStr += (d->mRoaming) ? ("true") : ("false");
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_NETWORKHANDLE_0;
        valueStr += ": ";
        valueStr += d->mAllNetworkHandles[0].toString();
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_NETWORKHANDLE_1;
        valueStr += ": ";
        valueStr += d->mAllNetworkHandles[1].toString();
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_NETWORKHANDLE_2;
        valueStr += ": ";
        valueStr += d->mAllNetworkHandles[2].toString();
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_NETWORKHANDLE_3;
        valueStr += ": ";
        valueStr += d->mAllNetworkHandles[3].toString();
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_NETWORKHANDLE_4;
        valueStr += ": ";
        valueStr += d->mAllNetworkHandles[4].toString();
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_NETWORKHANDLE_5;
        valueStr += ": ";
        valueStr += d->mAllNetworkHandles[5].toString();
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_NETWORKHANDLE_6;
        valueStr += ": ";
        valueStr += d->mAllNetworkHandles[6].toString();
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_NETWORKHANDLE_7;
        valueStr += ": ";
        valueStr += d->mAllNetworkHandles[7].toString();
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_NETWORKHANDLE_8;
        valueStr += ": ";
        valueStr += d->mAllNetworkHandles[8].toString();
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_NETWORKHANDLE_9;
        valueStr += ": ";
        valueStr += d->mAllNetworkHandles[9].toString();
        valueStr += ", ";
        valueStr += NETWORKINFO_FIELD_APN_NAME;
        valueStr += ": ";
        valueStr += d->mApn;
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}
void ServiceStatusDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(ServiceStatusDataItem, SERVICESTATUS_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr += SERVICESTATUS_FIELD_STATE;
        valueStr += ": ";
        char state [12];
        snprintf (state, 12, "%d", d->mServiceState);
        valueStr += string (state);
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}
void ModelDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(ModelDataItem, MODEL_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr += MODEL_FIELD_NAME;
        valueStr += ": ";
        valueStr += d->mModel;
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}
void ManufacturerDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(ManufacturerDataItem, MANUFACTURER_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr += MANUFACTURER_FIELD_NAME;
        valueStr += ": ";
        valueStr += d->mManufacturer;
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}
void WifiSupplicantStatusDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(WifiSupplicantStatusDataItem,
                WIFI_SUPPLICANT_STATUS_DATA_ITEM_ID);
        valueStr += "Attach state: ";
        char t[50];
        memset (t, '\0', 50);
        snprintf (t, 50, "%d", d->mState);
        valueStr += t;

        valueStr += ", Mac address valid: ";
        valueStr += (d->mApMacAddressValid) ? ("true") : ("false");

        valueStr += ", AP MAC address: ";
        memset (t, '\0', 50);
        snprintf(t, 50, "[%02x:%02x:%02x:%02x:%02x:%02x]", d->mApMacAddress[0], d->mApMacAddress[1],
            d->mApMacAddress[2], d->mApMacAddress[3], d->mApMacAddress[4], d->mApMacAddress[5]);
        valueStr += t;

        valueStr += ", Wifi-Ap SSID Valid: ";
        valueStr += (d->mWifiApSsidValid) ? ("true") : ("false");

        valueStr += ", SSID: ";
        valueStr += d->mWifiApSsid;

    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}

void MccmncDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(MccmncDataItem, MCCMNC_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr += MCCMNC_FIELD_NAME;
        valueStr += ": ";
        valueStr += d->mValue;
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}

// copy
void InEmergencyCallDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(
                InEmergencyCallDataItem, IN_EMERGENCY_CALL_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr += IN_EMERGENCY_CALL_FIELD_NAME;
        valueStr += ": ";
        valueStr += (d->mIsEmergency) ? ("true") : ("false");
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}
int32_t ENHDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(ENHDataItem,  ENH_DATA_ITEM_ID);
        if (s->mEnhFields == d->mEnhFields) { result = true; break; }
        switch (d->mAction) {
            case SET:
                s->mEnhFields |= (1 << d->mFieldUpdate);
                break;
            case CLEAR:
                s->mEnhFields &= ~(1 << d->mFieldUpdate);
                break;
            default:
                break;
        }
        result = 0;
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
    return result;
}
int32_t GPSStateDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(GPSStateDataItem,  GPSSTATE_DATA_ITEM_ID);
        if (s->mEnabled == d->mEnabled) { result = 0; break; }
        s->mEnabled = d->mEnabled;
        result = 0;
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
    return result;
 }
int32_t WifiHardwareStateDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(WifiHardwareStateDataItem, WIFIHARDWARESTATE_DATA_ITEM_ID);
        if (s->mEnabled == d->mEnabled) { result = 0; break; }
        s->mEnabled = d->mEnabled;
        result = 0;
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
    return result;
}
int32_t PowerConnectStateDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(PowerConnectStateDataItem,
                POWER_CONNECTED_STATE_DATA_ITEM_ID);
        if (s->mState == d->mState) { result = 0; break; }
        s->mState = d->mState;
        result = 0;
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
    return result;
}
int32_t BatteryLevelDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(BatteryLevelDataItem, BATTERY_LEVEL_DATA_ITEM_ID);
        if (s->mBatteryPct == d->mBatteryPct) { result = 0; break; }
        s->mBatteryPct = d->mBatteryPct;
        result = 0;
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
    return result;
}
int32_t TimeZoneChangeDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(TimeZoneChangeDataItem, TIMEZONE_CHANGE_DATA_ITEM_ID);
        if (s->mCurrTimeMillis == d->mCurrTimeMillis &&
           s->mRawOffsetTZ == d->mRawOffsetTZ &&
           s->mDstOffsetTZ == d->mDstOffsetTZ) {
            result = 0;
            break;
        }
        s->mCurrTimeMillis = d->mCurrTimeMillis;
        s->mRawOffsetTZ = d->mRawOffsetTZ;
        s->mDstOffsetTZ = d->mDstOffsetTZ;
        result = 0;
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
    return result;
}
int32_t TimeChangeDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(TimeChangeDataItem, TIME_CHANGE_DATA_ITEM_ID);
        if (s->mCurrTimeMillis == d->mCurrTimeMillis &&
           s->mRawOffsetTZ == d->mRawOffsetTZ &&
           s->mDstOffsetTZ == d->mDstOffsetTZ) {
            result = 0;
            break;
        }
        s->mCurrTimeMillis = d->mCurrTimeMillis;
        s->mRawOffsetTZ = d->mRawOffsetTZ;
        s->mDstOffsetTZ = d->mDstOffsetTZ;
        result = 0;
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
    return result;
}
int32_t NetworkInfoDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(NetworkInfoDataItem, NETWORKINFO_DATA_ITEM_ID);
        NetworkType type = ((NetworkInfoDataItem*)d)->getType();
        if ((s->mAllTypes == d->mAllTypes) &&
            (s->getType() == type) && (0 == s->mTypeName.compare(d->mTypeName)) &&
            (0 == s->mSubTypeName.compare(d->mSubTypeName)) &&
            (s->mAvailable == d->mAvailable) &&
            (s->mConnected == d->mConnected) &&
            (s->mRoaming == d->mRoaming) &&
            (memcmp(s->mAllNetworkHandles, d->mAllNetworkHandles,
                    sizeof(s->mAllNetworkHandles)) == 0) &&
            (s->mNetworkHandle == d->mNetworkHandle) &&
            (s->mApn.compare(d->mApn))) {
            result = 0;
            break;
        }

        s->mAllTypes = (d->mAllTypes == 0) ? typeToAllTypes(type) : d->mAllTypes;
        if (s->getType() != type) { s->setType(type);}
        if (0 != s->mTypeName.compare(d->mTypeName)) { s->mTypeName = d->mTypeName;}
        if (0 != s->mSubTypeName.compare(d->mSubTypeName)) {s->mSubTypeName = d->mSubTypeName;}
        if (0 != s->mApn.compare(d->mApn)) {s->mApn = d->mApn;}
        if (s->mAvailable != d->mAvailable) {s->mAvailable = d->mAvailable;}
        if (s->mConnected != d->mConnected) {s->mConnected = d->mConnected;}
        if (s->mRoaming != d->mRoaming) {s->mRoaming = d->mRoaming;}
        if (memcmp(s->mAllNetworkHandles, d->mAllNetworkHandles,
                sizeof(s->mAllNetworkHandles)) != 0) {
            memcpy(static_cast<void*>(s->mAllNetworkHandles),
                    static_cast<void *>(d->mAllNetworkHandles), sizeof(s->mAllNetworkHandles));
        }
        if (s->mNetworkHandle != d->mNetworkHandle) {s->mNetworkHandle = d->mNetworkHandle;}

        result = 0;
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
    return result;
}
int32_t ServiceStatusDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(ServiceStatusDataItem, SERVICESTATUS_DATA_ITEM_ID);
        if (s->mServiceState == d->mServiceState) { result = 0; break; }
        s->mServiceState = d->mServiceState;
        result = 0;
    } while (0);
    EXIT_LOG("%d", result);
    return result;
}
int32_t ModelDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(ModelDataItem, MODEL_DATA_ITEM_ID);
        if (0 == s->mModel.compare(d->mModel)) { result = 0; break; }
        s->mModel = d->mModel;
        result = 0;
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
    return result;
}
int32_t ManufacturerDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(ManufacturerDataItem, MANUFACTURER_DATA_ITEM_ID);
        if (0 == s->mManufacturer.compare(d->mManufacturer)) { result = 0; break; }
        s->mManufacturer = d->mManufacturer;
        result = 0;
    } while (0);
    EXIT_LOG("%d", result);
    return result;
}
int32_t WifiSupplicantStatusDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(WifiSupplicantStatusDataItem,
                WIFI_SUPPLICANT_STATUS_DATA_ITEM_ID);
        if ( (s->mState == d->mState) &&
            (s->mApMacAddressValid == d->mApMacAddressValid) &&
            (s->mWifiApSsidValid == d->mWifiApSsidValid)) {

            // compare mac address
            if (memcmp(s->mApMacAddress, d->mApMacAddress, sizeof(s->mApMacAddress)) == 0) {

                // compare ssid
                if (s->mWifiApSsid.compare(d->mWifiApSsid) == 0) {
                    result = 0;
                    break;
                }
            }
        }

        if (s->mState != d->mState) { s->mState = d->mState;}
        if (s->mApMacAddressValid != d->mApMacAddressValid) {
            s->mApMacAddressValid = d->mApMacAddressValid;
        }
        if (s->mWifiApSsidValid != d->mWifiApSsidValid) {s->mWifiApSsidValid = d->mWifiApSsidValid;}
        if (memcmp(s->mApMacAddress, d->mApMacAddress, sizeof(s->mApMacAddress)) != 0) {
            memcpy(static_cast<void*>(s->mApMacAddress), static_cast<void *>(d->mApMacAddress),
                    sizeof(s->mApMacAddress));
        }
        if (s->mWifiApSsid.compare(d->mWifiApSsid) != 0) {
            s->mWifiApSsid = d->mWifiApSsid;
        }

        result = 0;
    } while (0);

    EXIT_LOG_WITH_ERROR("%d", result);
    return result;
}

int32_t MccmncDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(MccmncDataItem, MCCMNC_DATA_ITEM_ID);
        if (0 == s->mValue.compare(d->mValue)) { result = 0; break; }
        s->mValue= d->mValue;
        result = 0;
    } while (0);
    EXIT_LOG("%d", result);
    return result;
}
int32_t InEmergencyCallDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(
                InEmergencyCallDataItem, IN_EMERGENCY_CALL_DATA_ITEM_ID);
        s->mIsEmergency = d->mIsEmergency;
        result = 0;
    } while (0);
    EXIT_LOG("%d", result);
    return result;
}

void PreciseLocationEnabledDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(
                PreciseLocationEnabledDataItem, PRECISE_LOCATION_ENABLED_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr += PRECISE_LOCATION_ENABLED_FIELD_NAME;
        valueStr += ": ";
        valueStr += (d->mPreciseLocationEnabled) ? ("true") : ("false");
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}

int32_t PreciseLocationEnabledDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(
                PreciseLocationEnabledDataItem, PRECISE_LOCATION_ENABLED_DATA_ITEM_ID);
        s->mPreciseLocationEnabled = d->mPreciseLocationEnabled;
        result = 0;
    } while (0);
    EXIT_LOG("%d", result);
    return result;
}

void TrackingStartedDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(
                TrackingStartedDataItem, TRACKING_STARTED_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr += TRACKING_STARTED_FIELD_NAME;
        valueStr += ": ";
        valueStr += (d->mTrackingStarted) ? ("true") : ("false");
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}

int32_t TrackingStartedDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(
                TrackingStartedDataItem, TRACKING_STARTED_DATA_ITEM_ID);
        s->mTrackingStarted = d->mTrackingStarted;
        result = 0;
    } while (0);
    EXIT_LOG("%d", result);
    return result;
}

void NtripStartedDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(
                NtripStartedDataItem, NTRIP_STARTED_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr += NTRIP_STARTED_FIELD_NAME;
        valueStr += ": ";
        valueStr += (d->mNtripStarted) ? ("true") : ("false");
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}

int32_t NtripStartedDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(
                NtripStartedDataItem, NTRIP_STARTED_DATA_ITEM_ID);
        s->mNtripStarted = d->mNtripStarted;
        result = 0;
    } while (0);
    EXIT_LOG("%d", result);
    return result;
}

void LocFeatureStatusDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(
                LocFeatureStatusDataItem, LOC_FEATURE_STATUS_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr += LOC_FEATURE_STATUS_FIELD_NAME;
        valueStr += ": {";
        for (int item : d->mFids) {
            valueStr += std::to_string(item) + ", ";
        }
        valueStr += "}";
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}

int32_t LocFeatureStatusDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(
                LocFeatureStatusDataItem, LOC_FEATURE_STATUS_DATA_ITEM_ID);
        s->mFids = d->mFids;
        result = 0;
    } while (0);
    EXIT_LOG("%d", result);
    return result;
}

void NlpSessionStartedDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(
                NlpSessionStartedDataItem, NETWORK_POSITIONING_STARTED_DATA_ITEM_ID);
        valueStr.clear ();
        valueStr += NLP_STARTED_FIELD_NAME;
        valueStr += ": ";
        valueStr += (d->mNlpStarted) ? ("true") : ("false");
    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}

int32_t NlpSessionStartedDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(
                NlpSessionStartedDataItem, NETWORK_POSITIONING_STARTED_DATA_ITEM_ID);
        s->mNlpStarted = d->mNlpStarted;
        result = 0;
    } while (0);
    EXIT_LOG("%d", result);
    return result;
}

void QesdkWwanFeatureStatusDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(
            QesdkWwanFeatureStatusDataItem, QESDK_WWAN_FEATURE_STATUS_DATA_ITEM_ID);

        valueStr.clear ();

        valueStr = QESDK_WWAN_FEATURE_STATUS_CARD;
        valueStr += "::";

        valueStr += QESDK_WWAN_FEATURE_STATUS_FIELD_QESDK_FEATURE_ID;
        valueStr += ": ";
        char fid[12];
        snprintf(fid, 12, "%d", d->mQesdkFeatureId);
        valueStr += string(fid);
        valueStr += ", ";

        valueStr += QESDK_WWAN_FEATURE_STATUS_FIELD_APPHASH;
        valueStr += ": ";
        valueStr += d->mAppHash;
        valueStr += ", ";

    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}

int32_t QesdkWwanFeatureStatusDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(
                QesdkWwanFeatureStatusDataItem, QESDK_WWAN_FEATURE_STATUS_DATA_ITEM_ID);
        s->mQesdkFeatureId = d->mQesdkFeatureId;
        s->mAppHash = d->mAppHash;
        result = 0;
    } while (0);
    EXIT_LOG("%d", result);
    return result;
}

void QesdkWwanCsConsentSrcDataItem::stringify(string& valueStr) {
    int32_t result = 0;
    ENTRY_LOG();
    do {
        STRINGIFY_ERROR_CHECK_AND_DOWN_CAST(
            QesdkWwanCsConsentSrcDataItem, QESDK_WWAN_CS_CONSENT_SRC_DATA_ITEM_ID);

        valueStr.clear ();

        valueStr = QESDK_WWAN_CS_CONSENT_SRC_CARD;
        valueStr += "::";

        valueStr += QESDK_WWAN_CS_CONSENT_SRC_FIELD_QESDK_FEATURE_ID;
        valueStr += ": ";
        char fid[12];
        snprintf(fid, 12, "%d", d->mQesdkFeatureId);
        valueStr += string(fid);
        valueStr += ", ";

        valueStr += QESDK_WWAN_CS_CONSENT_SRC_FIELD_PID;
        valueStr += ": ";
        char pid[12];
        snprintf(pid, 12, "%d", d->mPid);
        valueStr += string(pid);
        valueStr += ", ";

        valueStr += QESDK_WWAN_CS_CONSENT_SRC_FIELD_UID;
        valueStr += ": ";
        char uid[12];
        snprintf(uid, 12, "%d", d->mUid);
        valueStr += string(uid);
        valueStr += ", ";

        valueStr += QESDK_WWAN_CS_CONSENT_SRC_FIELD_APPHASFINEPERMISSION;
        valueStr += ": ";
        valueStr += (d->mAppHasFinePermission) ? ("true") : ("false");
        valueStr += ", ";

        valueStr += QESDK_WWAN_CS_CONSENT_SRC_FIELD_APPHASBACKGROUNDPERMISSION;
        valueStr += ": ";
        valueStr += (d->mAppHasBackgroundPermission) ? ("true") : ("false");
        valueStr += ", ";

        valueStr += QESDK_WWAN_CS_CONSENT_SRC_FIELD_APPHASH;
        valueStr += ": ";
        valueStr += d->mAppHash;
        valueStr += ", ";

        valueStr += QESDK_WWAN_CS_CONSENT_SRC_FIELD_APPPACKAGENAME;
        valueStr += ": ";
        valueStr += d->mAppPackageName;
        valueStr += ", ";

        valueStr += QESDK_WWAN_CS_CONSENT_SRC_FIELD_APPCOOKIE;
        valueStr += ": ";
        valueStr += d->mAppCookie;
        valueStr += ", ";

        valueStr += QESDK_WWAN_CS_CONSENT_SRC_FIELD_APPQWESLICENSEID;
        valueStr += ": ";
        valueStr += d->mAppQwesLicenseId;

    } while (0);
    EXIT_LOG_WITH_ERROR("%d", result);
}

int32_t QesdkWwanCsConsentSrcDataItem::copyFrom(IDataItemCore* src) {
    int32_t result = -1;
    ENTRY_LOG();
    do {
        COPIER_ERROR_CHECK_AND_DOWN_CAST(
                QesdkWwanCsConsentSrcDataItem, QESDK_WWAN_CS_CONSENT_SRC_DATA_ITEM_ID);
        s->mQesdkFeatureId = d->mQesdkFeatureId;
        s->mPid = d->mPid;
        s->mUid = d->mUid;
        s->mAppHasFinePermission = d->mAppHasFinePermission;
        s->mAppHasBackgroundPermission = d->mAppHasBackgroundPermission;
        s->mAppHash = d->mAppHash;
        s->mAppPackageName = d->mAppPackageName;
        s->mAppCookie = d->mAppCookie;
        s->mAppQwesLicenseId = d->mAppQwesLicenseId;
        result = 0;
    } while (0);
    EXIT_LOG("%d", result);
    return result;
}

} //namespace loc_core
