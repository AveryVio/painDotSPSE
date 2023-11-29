# Comunication
The motherboard uses I2C to comunicate with the other , peripheral boards to either get info or write onto the peripherals.

This approach was picked to make the software modular
and gives the motherboard freedom to have any still and
be able to use the paripherals.

> Note: While the motherboard uses the more powerfull `ATSAMD21G18` board, the controlers and display boards use the GPIO pin abundant `AVR128DB48` boards.
## format of comunication
all comuniction is consucted in this specicic format
```
action.parmeters
```

| display action | meaning | parameter options |
| -- | -- | -- |
| s | start | none |
| p | power save | none |
| r | rectangle | first - x axis, second - y axis |

| controler action | meaning | parameter options |
| -- | -- | -- |
| s | start | none |
| p | power save | none |
| g | get stats | *to be picked* |
## Motherboard to display
The display board has 2 diffetent modes. 
At first power on the motherboard gets some info from the display and then it comunicates only to write to the display.
### Starting phase
When the sysem is powered on the board gets the display info, then turns the backlight on and shows a deafult loading screen while everything gets setup.
### Main loop
In the main loop the motheboard writes onto the display only when a change happens. The display is allways backlit. 
> This is not the case when the system goes into power saving mode, during which the display shows a deafult sleep screen and the backlight is turned off.
#### Example message
creating a rectangle
```
r.0.0
```
## Motherboard to controlers
The controlers are used by the motherboard to control the on screen content with both the players having control of the monus but having separate control in game.

> Note: The controlers have an LED that indicates the players number, the LED shuts off whenever the system is in power saving mode
### Controler startup
At power on The controlers get assigned a number and that is shown on the controler LED and is shown in the coud logs
### Main loop usage.
In the main loop the controlers show report their states ehwnever they get an request from the motherboard, else they just wait for a request.
#### Example message
creating a rectangle
```
g.*something something idk*
```
# Supported by
![schoolLogo](https://www.spseplzen.cz/wp-content/uploads/2017/09/logo_1.png)