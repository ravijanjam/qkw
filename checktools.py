import subprocess as sp
import datetime
import sys

#cmd = "abc 2>1 /dev/null"
#sp.run(cmd.split(' '))
#sys.exit(1)

cc = 0
logfile = open('log.txt','a')
ins = "\nChecks for dev libraries (fmt,sqlite3,yaml), and binaries (make,cmake,git,g++)\n"
print("\033[1m{}\033[0m".format(ins))
logfile.write(ins)

ok = False
def genTS(): return datetime.datetime.now().replace(tzinfo=datetime.timezone.utc)

print(genTS())

# (make,gcc,g++,git) check
# msg: <name> not found

# g++ checkheaders.cpp
# msg: check log file for the section 

# mkdir -p ./build

# download (fmt,sqlite3,pkg-config)
# check all versions, if exists or after exists

# once ready, ask the user to install, point to directory
# resume the script


# libraries ready
# make build
# make install
# make clean

# post installation reporting
# qkw ready
# show version


def exec_cmd(_cmd,cc):

	op = None
	try:
		logfile.write('\n----');
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



cc += 1
cmd = "rm -rf ./build"
print('Delete and recreate \'./build\' directory: [y/n]')
for line in sys.stdin:
	if 'y' == line.rstrip():
		ok = exec_cmd(cmd,cc)
		break;
	else: 
		print("  \'./build\' not deleted")
		break;


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


# Get the deps into build directory
cc += 1
url = "https://github.com/fmtlib/fmt.git"
dd = './build'
cmd = "git -C {} clone {}".format(dd,url)
exec_cmd(cmd,cc)

cc += 1
url = "https://github.com/jbeder/yaml-cpp"
cmd = "git -C {} clone {}".format(dd,url)
exec_cmd(cmd,cc)


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

cmd = "Please add the macros to \'bashrc\'in the directory :\n  |{} \nfor more functionality, refer to the docs: \n  |{}\n".format('github/bash','github.com/wiki')
logfile.write(cmd)
print(cmd)
