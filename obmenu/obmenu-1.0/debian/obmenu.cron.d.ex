#
# Regular cron jobs for the obmenu package
#
0 4	* * *	root	[ -x /usr/bin/obmenu_maintenance ] && /usr/bin/obmenu_maintenance
