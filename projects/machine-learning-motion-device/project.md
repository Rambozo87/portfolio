---
title: Machine Learning Motion Device
description: A two-part motion-sensing system pairing Teensy Raw HID firmware with a C++ desktop data and model-training application.
tags:
  - C++
  - Teensy 4.0
  - HID
  - Machine learning
status: in-progress
featured: false
order: 1
---

## Overview

This project is based on the public [machine-learning-motion-device repository](https://github.com/Rambozo87/machine-learning-motion-device). It is presented as a source-based project record; this page does not claim benchmark accuracy, a finished hardware product, or a validated end-to-end deployment.

## Data path

The system is split across two applications. The Teensy 4.0 side initializes an MPU-class motion sensor over I2C, packs accelerometer, gyroscope, temperature, counter, and timestamp fields into a 64-byte buffer, and sends that buffer through the Raw HID interface. The desktop side opens the device with hidapi and collects those packets at the configured polling rate.

## Desktop pipeline

The desktop application exposes separate modes for live motion tracking, data collection, and training. Its CSV conversion path derives features such as axis means and deviations, acceleration and gyroscope magnitudes, jerk, orientation estimates, and a gravity-alignment measure. The training path loads CSV matrices with Armadillo and configures an mlpack random forest before writing a model artifact.

## Published boundary

The repository also contains an SDL3 window path and CMake configuration for the computer application, plus a PlatformIO configuration for the Teensy firmware. Generated build directories, clangd indexes, datasets, model binaries, and the large BMP input are intentionally not copied into this portfolio record. The [data-flow notes](docs/motion-data-flow.pdf) and [system diagram](images/motion-data-flow.png) summarize the published boundary.

The source browser includes selected C++ headers and implementation files from both sides of the system. They are displayed as read-only text and are not compiled, installed, or executed by the portfolio build.
