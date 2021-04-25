#######################################
# flash
#######################################
flash:
	-st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000

#######################################
# doxygen
#######################################
docs:
	-doxygen
	-make -C $(BUILD_DIR)/latex/ all
	-mv $(BUILD_DIR)/latex/refman.pdf $(BUILD_DIR)/manual.pdf