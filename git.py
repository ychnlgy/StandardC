#!/usr/bin/python3

if __name__ == "__main__":

	import sys
	import os
	
	if len(sys.argv) == 1:
		print("(ERROR: no comment was provided.)")
		raise SystemExit(1)

	comment = " ".join(sys.argv[1:])

	os.system("git add .")
	os.system('git commit -m "%s"' % comment)
	os.system("git pull origin master")
	os.system("git push origin master")

