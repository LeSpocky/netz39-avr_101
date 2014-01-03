#!/bin/sh
avrdude -p t85 -P usb -c usbtiny -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
