/*
Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
SPDX-License-Identifier: BSD-3-Clause-Clear
*/
#include <aidl/android/hardware/gnss/visibility_control/BnGnssVisibilityControl.h>
#include "Gnss.h"
#include "GnssVisibilityControl.h"

namespace android {
namespace hardware {
namespace gnss {
namespace visibility_control {
namespace aidl {
namespace implementation {
static void convertGnssNfwNotification(const GnssNfwNotification& in,
    IGnssVisibilityControlCallback::NfwNotification& out);

void gnssVisibilityControlServiceDied(void* cookie) {
    LOC_LOGe("IGnssVisibilityControl AIDL service died");
    GnssVisibilityControl* iface = static_cast<GnssVisibilityControl*>(cookie);
    if (iface != nullptr) {
        iface->setCallback(nullptr);
        iface = nullptr;
    }
}

GnssVisibilityControl::GnssVisibilityControl(Gnss* gnss) : mGnss(gnss),
    mDeathRecipient(AIBinder_DeathRecipient_new(&gnssVisibilityControlServiceDied)) {
    LocationControlCallbacks locCtrlCbs;
    memset(&locCtrlCbs, 0, sizeof(locCtrlCbs));
    locCtrlCbs.size = sizeof(LocationControlCallbacks);

    locCtrlCbs.nfwStatusCb = [this](const GnssNfwNotification& notification) {
        statusCb(notification);
    };

    locCtrlCbs.isInEmergencyStatusCb = [this] () {
        return isE911Session();
    };

    if (mGnss->getLocationControlApi() != nullptr ) {
        mGnss->getLocationControlApi()->updateCallbacks(locCtrlCbs);
    }
}

ScopedAStatus GnssVisibilityControl::enableNfwLocationAccess(
        const std::vector<std::string>& proxyApps) {
    if (nullptr == mGnss || nullptr == mGnss->getLocationControlApi()) {
        LOC_LOGe("Null GNSS interface");
        return ScopedAStatus::fromExceptionCode(STATUS_INVALID_OPERATION);
    }

    std::vector<std::string> apps;
    for (auto i = 0; i < proxyApps.size(); i++) {
        apps.push_back((std::string)proxyApps[i]);
    }

    mGnss->getLocationControlApi()->enableNfwLocationAccess(apps);
        return ScopedAStatus::ok();
}
static void convertGnssNfwNotification(const GnssNfwNotification& in,
    IGnssVisibilityControlCallback::NfwNotification& out) {
    memset(&out, 0, sizeof(IGnssVisibilityControlCallback::NfwNotification));
    out.proxyAppPackageName = in.proxyAppPackageName;
    out.protocolStack = (IGnssVisibilityControlCallback::NfwProtocolStack)in.protocolStack;
    out.otherProtocolStackName = in.otherProtocolStackName;
    out.requestor = (IGnssVisibilityControlCallback::NfwRequestor)in.requestor;
    out.requestorId = in.requestorId;
    out.responseType = (IGnssVisibilityControlCallback::NfwResponseType)in.responseType;
    out.inEmergencyMode = in.inEmergencyMode;
    out.isCachedLocation = in.isCachedLocation;
}
void GnssVisibilityControl::statusCb(const GnssNfwNotification& notification) {
    std::unique_lock<std::mutex> lock(mMutex);
    auto gnssVisibilityControlCbIface(mGnssVisibilityControlCbIface);
    lock.unlock();
    if (gnssVisibilityControlCbIface != nullptr) {
        IGnssVisibilityControlCallback::NfwNotification nfwNotification;

        // Convert from one structure to another
        convertGnssNfwNotification(notification, nfwNotification);

        auto r = gnssVisibilityControlCbIface->nfwNotifyCb(nfwNotification);
        if (!r.isOk()) {
            LOC_LOGw("Error invoking NFW status cb");
        }
    } else {
        LOC_LOGw("setCallback has not been called yet");
    }
}

bool GnssVisibilityControl::isE911Session() {
    std::unique_lock<std::mutex> lock(mMutex);
    auto gnssVisibilityControlCbIface(mGnssVisibilityControlCbIface);
    lock.unlock();
    if (gnssVisibilityControlCbIface != nullptr) {
        bool res = false;
        auto r = gnssVisibilityControlCbIface->isInEmergencySession(&res);
        if (!r.isOk()) {
            LOC_LOGw("Error invoking NFW status cb");
            return false;
        } else {
            return (res);
        }
    } else {
        LOC_LOGw("setCallback has not been called yet");
        return false;
    }
}
/**
 * Registers the callback for HAL implementation to use.
 *
 * @param callback Handle to IGnssVisibilityControlCallback interface.
 */
ScopedAStatus GnssVisibilityControl::setCallback(
        const shared_ptr<IGnssVisibilityControlCallback>& callback) {
    if (nullptr == mGnss || nullptr == mGnss->getLocationControlApi()) {
        LOC_LOGe("Null GNSS interface");
        return ScopedAStatus::fromExceptionCode(STATUS_INVALID_OPERATION);
    }
    std::unique_lock<std::mutex> lock(mMutex);
    if (mGnssVisibilityControlCbIface != nullptr) {
        AIBinder_unlinkToDeath(mGnssVisibilityControlCbIface->asBinder().get(), mDeathRecipient,
                this);
    }
    mGnssVisibilityControlCbIface = callback;
    if (mGnssVisibilityControlCbIface != nullptr) {
        AIBinder_linkToDeath(mGnssVisibilityControlCbIface->asBinder().get(), mDeathRecipient,
                this);
    }

    return ScopedAStatus::ok();
}
}  // namespace implementation
}  // namespace aidl
}  // namespace visibility_control
}  // namespace gnss
}  // namespace hardware
}  // namespace android
