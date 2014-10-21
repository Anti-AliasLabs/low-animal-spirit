Low Animal Spirit
=================

Scrolling LED matrix sign displaying Twitter feed from an Arduino Yun.


Setting up the Yun (upgraded to 1.5.1)
--------------------------------------
* Setup network connection (whether ethernet or wifi)
* SSH into Yun
* Update opkg, install easy_install, ssl, pip for Python

`> opkg update`

`> opkg install distribute`

`> opkg install python-openssl`

* Install twython and simplejson

`> easy_install twython`
`> easy_install simplejson`

* scp tweet-controller.py and credentials.py onto Yun
* Put token information in credentials.py

Set up to launch at boot
------------------------
* The script `tweetinit` should be placed in `/etc/init.d/` 
* Then run `/etc/init.d/tweetinit enable` to generate a symlink to `/etc/rc.d/`.


`tweet-controller.py` is launched at boot via `/etc/init.d/tweetinit`. 

Due to still not understood reasons, the python script can only be launched manually via ssh or automatically via init.d. The script won't successfully authenticate to Twitter if launched via `rc.local`. It seems that the ethernet/Wifi interface won't be fully launched in time.

Additionally, some other interaction with the network needs to happen before launching the Python script. Here, Twitter is first pinged before starting Python.


