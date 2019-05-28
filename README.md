

# CDMA Softwarestack

## Overview

When finished, this will be a softwarestack to send and receive data with CDMA encoding. CDMA allows for very robust data transfers over very large distances. An example for CDMA is GPS.

## Building

This Stack is written for the Apache Mynewt RT OS. 

1. Clone the repo

2. Download and install Apache Newt.

You will need to download the Apache Newt tool, as documented in the [Getting Started Guide](https://mynewt.apache.org/latest/get_started/index.html).

3. Download the Apache Mynewt Core package (executed from the root directory).

```no-highlight
    $ newt install
```

4. Create your targets for the sender/receiver apps based on your MCU and Board.

5. Build the the sender/receiver targets.

```no-highlight
    $ newt build <your-target>
```

Better instructions will follow as the project progesses.
