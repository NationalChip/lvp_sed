#
# Voice Signal Preprocess
# Copyright (C) 2001-2020 NationalChip Co., Ltd
# ALL RIGHTS RESERVED!
#
# Makefile: source list of VSP other hook
#
#=================================================================================#

ifeq ($(CONFIG_LVP_APP_MP3_PLAYER), y)
app_objs += app/mp3_player/lvp_app_mp3_player.o
app_objs += $(patsubst %.c, %.o, $(wildcard app/mp3_player/resource/*.c))
endif

