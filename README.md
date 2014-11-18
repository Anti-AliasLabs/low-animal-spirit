Low Animal Spirit
=================

Scrolling LED matrix sign displaying Twitter feed from an Arduino Yun.


Setting up the Yun (upgraded to 1.5.1)
--------------------------------------
* Setup network connection (whether ethernet or wifi)
* SSH into Yun
* Update opkg, install easy_install, and ssl for Python

`> opkg update`

`> opkg install distribute`

`> opkg install python-openssl`

* Install twython and simplejson

`> easy_install twython`

`> easy_install simplejson`

* scp tweet-controller.py and credentials.py onto Yun
* Put token information in credentials.py

To start Python Twitter script
------------------------
* ssh to the Linino side of the Yun

`> ssh root@arduino.local`

* the password is arduino
* once logged in start the script

`> python tweet-controller.py &`

* once a new tweet is read, it should be printed to the screen along with the length of the tweet in characters (this is the data passed to the microcontroller side of the Yun)


Microcontroller
---------------
Uses Adafruit's HT1632 and GFX libraries. The HT1632 library uses the code in pull request https://github.com/adafruit/HT1632/pull/2/files
