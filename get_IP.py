import subprocess

cmd = "hostname -I | cut -d\' \' -f1"
IP = subprocess.check_output(cmd, shell = True)
if IP and not IP.isspace():
	pass
else:
	IP = "No IP Address"
print( "%s\n" % (IP) )
