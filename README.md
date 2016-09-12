# HackTable
This is a firmware for a Photon Particle based, hacked Ikea Lack table

**Note:** This projects needs a Photon Particle device running and connected to the cloud. You may find all documentation about this device on http://particle.io

## This project consists of three components:
- A modified Ikea Lack table, instructions to build this can be found here: http://instructables.com/....
- This firmware project
- An installation of OpenHab (http://www.openhab.org), example configuration contained in "openhab_examples" folder

## Requirements to build the firmware:
To build the firmware you need the particle-cli tool which you may install with (nodejs required):

```
$ npm install -g particle-cli
```

The repository for particle-cli is here:

https://github.com/spark/particle-cli

This repository contains files from the FastLED project/library which you may find here:

https://github.com/FastLED/FastLED/

## How to compile:
On the Commandline type:

```
$ particle compile photon <path to directory with source files>
```

If it succeeds you end up with a file called "photon_firmware_\<timestamp\>.bin" in your current directory. To upload this to your Photon device, issue:

```
particle flash <devicename> <filename>
```
