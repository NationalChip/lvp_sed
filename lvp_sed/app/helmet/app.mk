#
# Voice Signal Preprocess
# Copyright (C) 2001-2020 NationalChip Co., Ltd
# ALL RIGHTS RESERVED!
#
# Makefile: source list of this application
#
#=================================================================================#

ifeq ($(CONFIG_LVP_APP_HELMET), y)
app_objs += app/helmet/lvp_app_helmet.o
app_objs += $(patsubst %.c, %.o, $(wildcard app/helmet/resource/*.c))
endif

