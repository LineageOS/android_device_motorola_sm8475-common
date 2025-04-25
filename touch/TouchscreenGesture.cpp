/*
 * Copyright (C) 2019 The LineageOS Project
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

#define LOG_TAG "TouchscreenGestureService"

#include <fstream>

#include <android-base/file.h>
#include <android-base/logging.h>

#include "TouchscreenGesture.h"

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

ndk::ScopedAStatus TouchscreenGesture::getSupportedGestures(std::vector<Gesture>* _aidl_return) {
    std::vector<Gesture> gestures;
    for (int32_t i = 0; i < std::size(kGestureNodes); ++i) {
        gestures.push_back({i, kGestureNodes[i].name, kGestureNodes[i].keycode});
    }

    *_aidl_return = gestures;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus TouchscreenGesture::setGestureEnabled(const Gesture& gesture, bool enable) {
    if (gesture.id >= std::size(kGestureNodes)) {
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    if (!android::base::WriteStringToFile(enable ? kGestureNodes[gesture.id].enable : kGestureNodes[gesture.id].disable,
                                          kGestureNodes[gesture.id].path)) {
        LOG(ERROR) << "Writing to file " << kGestureNodes[gesture.id].path << " failed";
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    return ndk::ScopedAStatus::ok();
}

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
