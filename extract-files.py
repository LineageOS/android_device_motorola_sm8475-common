#!/usr/bin/env -S PYTHONPATH=../../../tools/extract-utils python3
#
# SPDX-FileCopyrightText: The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#

from extract_utils.fixups_blob import (
    blob_fixup,
    blob_fixups_user_type,
)
from extract_utils.fixups_lib import (
    lib_fixups,
    lib_fixups_user_type,
)
from extract_utils.main import (
    ExtractUtils,
    ExtractUtilsModule,
)

namespace_imports = [
    'device/motorola/sm8475-common',
    'hardware/motorola',
    'hardware/qcom-caf/sm8450',
    'hardware/qcom-caf/wlan',
    'vendor/qcom/opensource/commonsys/display',
    'vendor/qcom/opensource/dataservices',
]


def lib_fixup_vendor_suffix(lib: str, partition: str, *args, **kwargs):
    return f'{lib}_{partition}' if partition == 'vendor' else None


lib_fixups: lib_fixups_user_type = {
    **lib_fixups,
    (
        'com.qualcomm.qti.dpm.api@1.0',
        'vendor.qti.diaghal@1.0',
        'vendor.qti.hardware.dpmservice@1.0',
        'vendor.qti.hardware.dpmservice@1.1',
        'vendor.qti.hardware.qccsyshal@1.0',
        'vendor.qti.hardware.qccsyshal@1.1',
        'vendor.qti.hardware.qccvndhal@1.0',
        'vendor.qti.imsrtpservice@3.0',
        'vendor.qti.qspmhal@1.0',
    ): lib_fixup_vendor_suffix,
}

blob_fixups: blob_fixups_user_type = {
    'system_ext/etc/permissions/moto-telephony.xml': blob_fixup().regex_replace(
        '/system/', '/system_ext/'
    ),
    'system_ext/lib64/vendor.qti.hardware.qccsyshal@1.2-halimpl.so': blob_fixup()
        .replace_needed('libprotobuf-cpp-full.so', 'libprotobuf-cpp-full-21.7.so'),
    (
        'vendor/lib64/libgarden.so',
        'vendor/lib64/libgarden_haltests_e2e.so'
    ): blob_fixup()
    .replace_needed(
        'android.hardware.gnss-V1-ndk_platform.so',
        'android.hardware.gnss-V1-ndk.so'
    )
    .replace_needed(
        'vendor.qti.gnss-V3-ndk_platform.so',
        'vendor.qti.gnss-V5-ndk_platform.so'
    ),
    (
        'vendor/bin/hw/android.hardware.security.keymint-service-qti',
        'vendor/lib64/libqtikeymint.so',
    ): blob_fixup()
    .replace_needed(
        'android.hardware.security.keymint-V1-ndk_platform.so',
        'android.hardware.security.keymint-V1-ndk.so',
    )
    .replace_needed(
        'android.hardware.security.secureclock-V1-ndk_platform.so',
        'android.hardware.security.secureclock-V1-ndk.so',
    )
    .replace_needed(
        'android.hardware.security.sharedsecret-V1-ndk_platform.so',
        'android.hardware.security.sharedsecret-V1-ndk.so',
    )
    .add_needed('android.hardware.security.rkp-V1-ndk.so'),
    'vendor/bin/init.kernel.post_boot.sh': blob_fixup()
        .regex_replace('ro.boot.using_zram_from_fstab', 'ro.vendor.zram.swapon'),
    'vendor/bin/qcc-trd': blob_fixup().replace_needed(
        'libgrpc++_unsecure.so', 'libgrpc++_unsecure_prebuilt.so'
    ),
    'vendor/lib64/libmotext_inf.so': blob_fixup().remove_needed('libril.so'),
    'system_ext/priv-app/ims/ims.apk': blob_fixup().apktool_patch(
        'ims-patches'
    ),
    'vendor/lib64/vendor.libdpmframework.so': blob_fixup().add_needed(
        'libhidlbase_shim.so'
    ),
    'vendor/lib64/libqcodec2_core.so': blob_fixup().add_needed(
        'libcodec2_shim.so'
    ),
    'vendor/lib64/sensors.moto.so': blob_fixup().add_needed('libbase_shim.so'),
    'vendor/etc/media_codecs_cape.xml': blob_fixup().regex_replace(
        '.*media_codecs_(google_audio|google_c2|google_telephony|google_video|vendor_audio|dolby_audio).*\n', ''
    ),
    (
        'vendor/bin/poweropt-service',
        'vendor/lib64/libapengine.so',
        'vendor/lib64/libdpps.so',
        'vendor/lib64/libgamepoweroptfeature.so',
        'vendor/lib64/liblearningmodule.so',
        'vendor/lib64/libpowercore.so',
        'vendor/lib64/libpsmoptfeature.so',
        'vendor/lib64/libsnapdragoncolor-manager.so',
        'vendor/lib64/libstandbyfeature.so',
        'vendor/lib64/libvendorscenariopoweroptfeature.so',
        'vendor/lib64/libvideooptfeature.so',
    ): blob_fixup()
    .replace_needed(
        'libtinyxml2.so',
        'libtinyxml2-v34.so',
    ),
    'vendor/etc/sensors/hals.conf': blob_fixup().add_line_if_missing(
        'sensors.moto_ext.so',
    ),
}  # fmt: skip

module = ExtractUtilsModule(
    'sm8475-common',
    'motorola',
    blob_fixups=blob_fixups,
    lib_fixups=lib_fixups,
    namespace_imports=namespace_imports,
)

if __name__ == '__main__':
    utils = ExtractUtils.device(module)
    utils.run()
