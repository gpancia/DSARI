# DSARI
The Voltmeter folder contains the code for the Arduino Voltmeter,which just prints to serial its input on pin A1, with some extra math on top so that it has meaning (AKA interprets input as voltage).

In the Data Recorder folder there's the Java code I built using Processing, which reads from serial and writes to CSV files. I had to split them up because there's no append option in the library I was using, and since it was writing files throughout several hours I wanted to avoid the risk of a master file being lost (data was only readable after the output stream was closed). Saving every 30 minutes seemed like a good compromise, so that's what I did.

Lastly, the CSV Aggregator does exactly what its name implies, and is by far the largest program of the three. I will admit it is horribly bloated, however, as I didn't put that much effort into refining the code. As such there are a bunch of functions that don't do anything and a great many inefficiencies scattered all over the source code, but it does its job well. 

Data.csv is the output of CSV Aggregator.
