#include "MicroBit.h"
    
    MicroBit uBit;
    
    void onConnected(MicroBitEvent)
    {
        uBit.display.print("C");
    }
    
    void onDisconnected(MicroBitEvent)
    {
        uBit.display.print("D");
    }
    
    int main()
    {
        // Initialise the micro:bit runtime.
        uBit.init();
    
        uBit.display.scroll("BLUE-NP");
    
        uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, onConnected);
        uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, onDisconnected);
    
        new MicroBitAccelerometerService(*uBit.ble, uBit.accelerometer);
        new MicroBitButtonService(*uBit.ble);
        new MicroBitIOPinService(*uBit.ble, uBit.io);
        new MicroBitLEDService(*uBit.ble, uBit.display);
        new MicroBitMagnetometerService(*uBit.ble, uBit.compass);
    
        // If main exits, there may still be other fibers running or registered event handlers etc.
        // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
        // sit in the idle task forever, in a power efficient sleep.
        release_fiber();
    }

