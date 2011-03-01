# Notification tool
# Run with the directory to watch
# currently hardcoded to use 
#
# (c) 2009-2010, Nikhil Marathe <nsm.nikhil@gmail.com>
# Licensed under the MIT License

import sys
import os
import subprocess
import re
from pyinotify import WatchManager, Notifier, ProcessEvent, IN_MODIFY

wm = WatchManager()

class Compile( ProcessEvent ):
    def process_IN_MODIFY( self, event ):
        print event.path, event.name, event.mask & IN_MODIFY

        if re.match( '[^\.].*.txt', event.name ):
            ex = subprocess.call( ['rst2s5', event.name, '%s'%(
                re.sub('\.txt$', '.html', event.name)), '--current-slide'] )
            subprocess.call( ['notify-send', "Conversion output", "%s" % ( ex == 0 and "Success" or "Error" )] )

c = Compile()
notifier = Notifier( wm, c )
wm.add_watch( sys.argv[1], IN_MODIFY, rec=True )

notifier.loop()
