# NXP-APP INTERNAL Release Note V05-R02 [06/08/2024]

## Done

- Removed compilation options based upon MCU definition
- Variable speed functionality, through SPI messages towards bridge
- Removed shortest path, replaced by absolute positioning
- Zero detection and searching at start
- Replaced 0.1 precision with 0.125 deg precision positioning, according to new agreements

## To Be Tested

- MCU settings (1 or 2 motors) upon message received from bridge
- Speed variations without loosing steps

## To Be Implemented

- Offset Saving
- Dummy 8 bytes command
- MCU ID writing
- State writing
- SW ver and BL ver reading
- Accel - decel ramps
