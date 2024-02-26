# Remote sensing environment sensor

```
          ┌──────────────┐         ┌─────────────────┐
          │              │  SPI    │  WeAct 1.54"    │
          │ RP-2040 Zero ├─────────┤  EPaper Display │
          │              │         └─────────────────┘
          └────────┬─────┘                            
                   │                                  
                   │                                  
                   │   UART     ┌───────┐             
                   └────────────┤ HC-12 │             
                                └───────┘             
           ┌────────────┐            /                 
           │            │            /                 
           │  Rpi PICO  │            /                 
           │            │            /                 
           └───┬────┬───┘            /                 
               │I2C │                /                 
               │    │                /                 
               │    │   UART    ┌───────┐             
┌─────────┐    │    └───────────┤ HC-12 │             
│ BMP-280 ├────┤                └───────┘             
└─────────┘    │                                      
               │                                      
 ┌────────┐    │                                      
 │ DS1307 ├────┘                                      
 └────────┘                                           
```