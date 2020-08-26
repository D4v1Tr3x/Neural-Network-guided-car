ARDUINO_PACKAGE_DIR = $(HOME)/.arduino15/packages
ARCHITECTURE	= sam/1.6.12
ARDUINO_DIR 	= /usr/share/arduino
TARGET			= tests

BOARD_TAG 		= arduino_due_x_dbg
ARDUINO_PORT 	= /dev/ttyACM0

ARDUINO_LIB_PATH = $(HOME)/.arduino15/packages/arduino/$(ARCHITECTURE)/libraries/
ARDUINO_LIBS = Wire SPI
#AVRDUDE_CONF += -D

AVRDUDE_ARD_EXTRAOPTS += -D -v -v -W -Wall -pedantic -Werror


include $(ARDUINO_DIR)/Sam.mk

LDFLAGS += $(OPTIN)
