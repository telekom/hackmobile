# Debug on Windows
To debug with the serial interface from the usb connection from the calliope board you just need to follow these steps:

* Install and download putty from [here](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html) or termite from [here](https://www.compuphase.com/software_termite.htm)
* Open your searchbar and search for ```Device Manager```
* Expand the Ports (COM & LPT) section 
![Device Manager](http://workshop.raspberrypiaustralia.com/assets/device-manager.png)  

> source: [raspberrypiaustralia.com](http://workshop.raspberrypiaustralia.com/usb/ttl/connecting/2014/08/31/01-connecting-to-raspberry-pi-via-usb/)
* Open Putty
* Select Serial as the connection type 
![Putty](http://workshop.raspberrypiaustralia.com/assets/putty-serial-connection-type.png)  

> source: [raspberrypiaustralia.com](http://workshop.raspberrypiaustralia.com/usb/ttl/connecting/2014/08/31/01-connecting-to-raspberry-pi-via-usb/)
* Enter the name of the COM port you’ve found
* Set the speed to 115200 
![Putty](http://workshop.raspberrypiaustralia.com/assets/putty-serial-settings.png)  

> source: [raspberrypiaustralia.com](http://workshop.raspberrypiaustralia.com/usb/ttl/connecting/2014/08/31/01-connecting-to-raspberry-pi-via-usb/)
* Click Open and you should see the terminal 
