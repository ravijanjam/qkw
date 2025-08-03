import os
import subprocess as sp
import datetime
import sys

cc = 0
logfile = open('log.txt','a')
ins = "\nChecks for dev libraries (fmt,sqlite3,yaml), and binaries (make,cmake,git,g++)\n"
print("\033[1m{}\033[0m".format(ins))
logfile.write(ins)

ok = False
def genTS(): return datetime.datetime.now().replace(tzinfo=datetime.timezone.utc)

print(genTS())

def exec_cmd(_cmd,cc):

	op = None
	try:
		logfile.write('\n----')
		logfile.write('\n[{}]:{}'.format(cc,genTS()))
		logfile.write('\n\ncommand:\n {}'.format(_cmd))
		op = sp.Popen(_cmd.split(' '),stdout=sp.PIPE, stderr=sp.PIPE)
		logfile.write('\n\noutput:\n {}'.format(str(op.stdout.read(),'utf-8')))
		logfile.write('\n\n {}'.format(str(op.stderr.read(),'utf-8')))

	except:
		logfile.write('\n\nstatus:\n {}\n\n'.format('FAILED!'))
		print("FAILED AT:\n  [{}]:{}".format(cc,_cmd))
		print("====================================")
		print("ERROR: Please check the logfile....");
		print("====================================")
		sys.exit(1)

	return True


if os.path.exists(os.path.abspath("./build")):
	cc += 1
	cmd = "rm -rf ./build"
	print('Delete and recreate \'./build\' directory: [y/n]', end=" ", flush=True)
	for line in sys.stdin:
		if 'y' == line.rstrip():
			ok = exec_cmd(cmd,cc)
			break
		else: 
			print("  \'./build\' not deleted")
			break


cc+=1
cmd = "mkdir -p ./tests_bin/"
exec_cmd(cmd,cc)


# created if doesn't exist
cc+=1
cmd = "mkdir -p ./build"
exec_cmd(cmd,cc)

cc+=1
cmd = "g++ --version"
ok = exec_cmd(cmd,cc)

cc+=1
cmd = "git --version"
ok = exec_cmd(cmd,cc)

cc+=1
cmd = "make --version"
ok = exec_cmd(cmd,cc)

cmd = "cmake --version"
cc+=1
ok = exec_cmd(cmd,cc)

cc += 1
cmd = "pkg-config --version"
ok = exec_cmd(cmd,cc)

cc += 1
cmd = "unzip --version"
ok = exec_cmd(cmd, cc)


# Get the deps into build directory
cc += 1

url = "https://github.com/fmtlib/fmt/archive/refs/tags/11.2.0.zip"
dd = './build'
cmd = f"curl -L {url} -o {dd}/fmt.zip"
exec_cmd(cmd,cc)

cc += 1
url = "https://github.com/jbeder/yaml-cpp/archive/refs/tags/0.8.0.zip"
cmd = f"curl -L {url} -o {dd}/yaml-cpp.zip"
exec_cmd(cmd,cc)

cc += 1
cmd = f"unzip -q {dd}/fmt.zip -d {dd}"
exec_cmd(cmd,cc)
cmd = f"unzip -q {dd}/yaml-cpp.zip -d {dd}"
exec_cmd(cmd,cc)

cc += 1
cmd = f"rm {dd}/fmt.zip {dd}/yaml-cpp.zip"
exec_cmd(cmd,cc)


# we need to build yaml-cpp and fmtlib, once we get source files

# check for the headers by compiling
cc += 1
f='./tests/default_headers.cpp'
o='./tests_bin/default_headers_check'
cmd = "g++ -o {} -I./include {}".format(o,f)
exec_cmd(cmd,cc)

cc += 1
cmd = "./{}".format(o)
exec_cmd(cmd,cc)

cc += 1
cmd = "rm -rf {}".format(o)
exec_cmd(cmd,cc)

cc += 1
f='./tests/app_headers.cpp'
o='./tests_bin/app_header_check'
cmd = "make app"
exec_cmd(cmd,cc)

cc += 1
cmd = "./tests_bin/app_header_check"
exec_cmd(cmd,cc)

cc += 1
cmd = "rm -rf ./tests_bin/app_header_check"
exec_cmd(cmd,cc)

cc += 1
cmd = "pkg-config --list-all"
exec_cmd(cmd,cc)

cmd = "\nSUCCESS: All checks have passed and commands run..."
logfile.write(cmd)
print(cmd)

cmd = "\nPlease go to \'./build\' dir and build, the libraries"
logfile.write(cmd)
print(cmd)

print("\nCheck out the log file {} for what has been processed by this script".format('log.txt'))

cmd = "\nAfter building the libraries please run: \n \033[1m{}\033[0m\n".format('make install')
logfile.write(cmd)
print(cmd)

cmd = "Please add the macros to \'bashrc\'in the directory :\n  |{} \nfor more functionality, refer to the docs: \n  |{}\n".format('~/.bashrc','https://github.com/ravijanjam/qkw?tab=readme-ov-file#qkw--generalizing-aliasing')
logfile.write(cmd)
print(cmd)
