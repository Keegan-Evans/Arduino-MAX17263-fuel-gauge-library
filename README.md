See my website here:
https://www.avdweb.nl/arduino/hardware-interfacing/max17263-fuel-gauge
The library is not quite ready because I switched to another fuel gauge IC with high-side current sensing.

Most cheap fuel gauges that are for sale, only measure the voltage, but that is very inaccurate. It is also necessary to measure the battery current. With the measured voltage and current, complicated software is able to determine exactly the accurate state-of-charge (SOC). Manufactures have many ICs for this application. We use the MAX17263 here because it has one important advantage: it needs no time-consuming battery characterization.

The used algorithm of the MAX17263 is the so-called ModelGauge m5 algorithm, which uses among others self learning routines: as the cell ages, its change in capacity is monitored and updated.
