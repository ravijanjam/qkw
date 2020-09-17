# QKW 
## Generalizing aliasing to simplify navigation, and executing complex multi-line terminal command sequences¶

**Installation (Ubuntu/Debian)**

```bash

apt-get update
apt-get install -y git gcc g++ pkg-config cmake make
apt-get install -y libsqlite3-dev
```

* To keep building simple, a python script is set up which checks for requirements _(fmt,sqlite3,yaml)_, and a sanity check for required headers. Any errors will be in writen to the log file
```bash
python3 checktools.py
```

* Get into the `build` directory, and follow instructions for installing the dependencies [[fmt]](https://github.com/fmtlib/fmt), and [[yaml-cpp]](https://github.com/jbeder/yaml-cpp)

* Running `checktools.py` should download the github repos for `fmt`, and `yaml` into [[build]](github.com/ravijanjam/qkw/build) directory. Check the _log files_ in the same directory as the script executes or breaks


```bash
make build
make install
make clean
```

Setup the environment variable
```bash
export QKW_CONFIG=/etc/qkw-data/qkw-config.yaml
```

Start the program
```bash
qkw -v
```

<br>
## Quick Start
There are about 75+ options to play with. Some of the most important ones demonstrated here. For all the available options, please read the section _Options_ in the manual. 
* Get help
```bash
qkw -h -T -cC
```

* Create two tables
```bash
qkw -T -cC cmd_1
qkw -T -cD dir_1
```

* List the tables, and their types
```bash
qkw -T -lA
```

* Add the tables to config file. 
```bash
qkw -cfgfile
```

* Visit a few directories and add labels
```bash
qkw -addpath p1  # in dir /a/b/c
qkw -addpath p2  # in dir x/y
```

* Add directories manually
```bash
qkw -iD m:"/u/v/w/x"
qkw -iD n:"/q/r"
```

* Check the directories
```bash
qkw -D -lA
```

* Add commands manually
```bash
qkw -iC devpush:"git push origin dev"
qkw -iC open:"vi /path/to/my/todo/list.txt"
```

* Add commands via a file. Open the file and add some data in the file. For example, check `data/cmd-in.data`
```bash
qkw -gettemplate cmdinput.data
qkw -C -if cmdinput.data
```

* Check the added data
```bash
qkw -C -lA
```

* Add the macros `cd2:navigation`, and `runfast:command execution` in your bashrc or it's equivalent

```bash
cd2(){
  cd `qkw -gD $1`
}
```

```bash
runfast(){
  str=`qkw -gC $1`
  qkw -exec “${str}”
}
```

`source ~/.bashrc` for and start using the tags

```bash
# takes you to directory /u/v/w/x
cd2 m 
```

```bash
# will run your the tagged lss commands
runfast lss 
```

To learn more, on how to set up `macros` and other advanced use cases on how to use `qkw`, please consult the [[manual]]()

<hr>
The basic tables used to store the data
*  _cmd_ :commands,scripts,etc with a note
*  _dir_ :directory paths

### CMD tables
![](https://github.com/ravijanjam/qkw/blob/master/docs/cmd_table.png)

### DIR tables
![](https://github.com/ravijanjam/qkw/blob/master/docs/dir_table.png)
