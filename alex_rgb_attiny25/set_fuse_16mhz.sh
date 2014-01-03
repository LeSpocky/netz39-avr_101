#!/bin/sh
avrdude -p t85 -P usb -c usbtiny -U lfuse:w:0x61:m
