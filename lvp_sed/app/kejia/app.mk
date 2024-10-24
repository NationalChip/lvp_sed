#
# Voice Signal Preprocess
# Copyright (C) 2001-2020 NationalChip Co., Ltd
# ALL RIGHTS RESERVED!
#
# Makefile: source list of this application
#
#=================================================================================#

ifeq ($(CONFIG_LVP_APP_KEJIA), y)
app_objs += app/kejia/lvp_app_kejia.o
app_objs += $(patsubst %.c, %.o, $(wildcard app/kejia/resource/*.c))
endif

