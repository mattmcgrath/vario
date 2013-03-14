#!/bin/bash
cat /dev/cu.usbmodemfa131 9600 >> log.$(date +"%Y%m%d%H%M").txt
