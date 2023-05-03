# vendor opensource packages
ifneq ($(BOARD_VENDOR_QCOM_GPS_LOC_API_HARDWARE),)

PRODUCT_PACKAGES += libgnsspps
PRODUCT_PACKAGES += libloc_socket

endif#BOARD_VENDOR_QCOM_GPS_LOC_API_HARDWARE
