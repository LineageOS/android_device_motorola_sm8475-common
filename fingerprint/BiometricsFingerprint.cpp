/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "android.hardware.biometrics.fingerprint@2.3-service.moto_sm8475_fod"

#include "BiometricsFingerprint.h"

#include <android-base/logging.h>
#include <display/drm/sde_drm.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <thread>

#define NOTIFY_FINGER_UP IMotFodEventType::FINGER_UP
#define NOTIFY_FINGER_DOWN IMotFodEventType::FINGER_DOWN

namespace android {
namespace hardware {
namespace biometrics {
namespace fingerprint {
namespace V2_3 {
namespace implementation {

void BiometricsFingerprint::setHighBrightFod(bool enable) {
    struct drm_msm_display_fod_hbm display_fod_hbm = {0};
    std::lock_guard<std::mutex> lock(mSetHbmFodMutex);
    int ret;

    if (hbmFodEnabled == enable)
        return;

    if (cardFd.get() < 0) {
        LOG(ERROR) << "Failed to open graphics card device " << 1;
        return;
    }

    display_fod_hbm.status = enable;

    ret = ioctl(cardFd.get(), DRM_IOCTL_MSM_DISPLAY_FOD_HBM, &display_fod_hbm);
    if (ret)
        LOG(ERROR) << "Failed to send FOD HBM ioctl " << 1;

    mMotoFingerprint->sendFodEvent(enable ? NOTIFY_FINGER_DOWN : NOTIFY_FINGER_UP, {},
                                   [](IMotFodEventResult, const hidl_vec<signed char> &) {});

    hbmFodEnabled = enable;
}

BiometricsFingerprint::BiometricsFingerprint() {
    biometrics_2_1_service = IBiometricsFingerprint_2_1::getService();
    mMotoFingerprint = IMotoFingerPrint::getService();

    hbmFodEnabled = false;
    cardFd = android::base::unique_fd(open("/dev/dri/card0", O_RDWR));
    if (cardFd.get() < 0) {
        LOG(ERROR) << "Failed to open graphics card device " << 1;
    }
}

Return<uint64_t> BiometricsFingerprint::setNotify(
    const sp<IBiometricsFingerprintClientCallback> &clientCallback) {
    return biometrics_2_1_service->setNotify(clientCallback);
}

Return<uint64_t> BiometricsFingerprint::preEnroll() {
    return biometrics_2_1_service->preEnroll();
}

Return<RequestStatus> BiometricsFingerprint::enroll(const hidl_array<uint8_t, 69> &hat,
                                                    uint32_t gid, uint32_t timeoutSec) {
    return biometrics_2_1_service->enroll(hat, gid, timeoutSec);
}

Return<RequestStatus> BiometricsFingerprint::postEnroll() {
    return biometrics_2_1_service->postEnroll();
}

Return<uint64_t> BiometricsFingerprint::getAuthenticatorId() {
    return biometrics_2_1_service->getAuthenticatorId();
}

Return<RequestStatus> BiometricsFingerprint::cancel() {
    auto ret = biometrics_2_1_service->cancel();
    BiometricsFingerprint::onFingerUp();
    return ret;
}

Return<RequestStatus> BiometricsFingerprint::enumerate() {
    return biometrics_2_1_service->enumerate();
}

Return<RequestStatus> BiometricsFingerprint::remove(uint32_t gid, uint32_t fid) {
    return biometrics_2_1_service->remove(gid, fid);
}

Return<RequestStatus> BiometricsFingerprint::setActiveGroup(uint32_t gid,
                                                            const hidl_string &storePath) {
    return biometrics_2_1_service->setActiveGroup(gid, storePath);
}

Return<RequestStatus> BiometricsFingerprint::authenticate(uint64_t operationId, uint32_t gid) {
    auto ret = biometrics_2_1_service->authenticate(operationId, gid);
    BiometricsFingerprint::onFingerUp();
    return ret;
}

Return<bool> BiometricsFingerprint::isUdfps(uint32_t) {
    return true;
}

Return<void> BiometricsFingerprint::onFingerDown(uint32_t, uint32_t, float, float) {
    BiometricsFingerprint::setHighBrightFod(true);

    std::thread([this]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        BiometricsFingerprint::onFingerUp();
    }).detach();

    return Void();
}

Return<void> BiometricsFingerprint::onFingerUp() {
    BiometricsFingerprint::setHighBrightFod(false);

    return Void();
}

}  // namespace implementation
}  // namespace V2_3
}  // namespace fingerprint
}  // namespace biometrics
}  // namespace hardware
}  // namespace android
