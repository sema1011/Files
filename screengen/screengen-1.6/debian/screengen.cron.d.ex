#
# Regular cron jobs for the screengen package
#
0 4	* * *	root	[ -x /usr/bin/screengen_maintenance ] && /usr/bin/screengen_maintenance
