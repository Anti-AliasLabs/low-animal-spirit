Low Animal Spirit
=================

Scrolling LED matrix sign displaying Twitter feed from an Arduino Yun.


Setting up the Yun (upgraded to 1.5.1)
- Setup network connection (whether ethernet or wifi)
- SSH into Yun
- Update opkg, install easy_install, ssl, pip for Python

> opkg update
> opkg install distribute
> opkg install python-openssl

- Install twython and simplejson
> easy_install twython
> easy_install simplejson

- scp tweet-controller.py and credentials.py onto Yun
- Put token information in credentials.py