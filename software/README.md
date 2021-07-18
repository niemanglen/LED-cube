# Hardware Considerations:

The pcb's have an ATMEGA328PB chip. Its datasheet can be found here.

The fuses need to be burned to use the internal oscillator at 8MHz. Additionally, preserving EEPROM after write is useful.

LFUSE: 0xe2

HFUSE: 0xd1

I have always used Arduino as ISP. The pcb programmer board is helpful if you are trying to avoid the wiring.
