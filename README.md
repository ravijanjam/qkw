# QKW 
## Generalizing aliasing to simplify navigation, and executing complex multi-line terminal command sequences¶

The purpose of this application is to tag anything with a _label_ and, use it to retrieve the associated data for other applications. Some of qkw's use cases:

* Quickly test a set of commands with different options in different environments. 
* Rapidly create variations, and save them with a versioned tag. 
* Add a _help-string_ or _note_ with the associated data.
* Similar functionality, but different command base/ options can be tagged without having to remember them. 
* Store the data in a file rather than a executable script, and also search for the content. 
* Save/retrieve the script formatted as a string, as it is to/from a file. 
* Use this as a _clipboard_ to store the stdout/stderr for inspection or analysis. 
* Easily share the functional blocks of your _application like initialization, settings, etc_ by just sharing the database, where user is abstracted away from the details and focuses on using the functionality by mere execution of the tags.


For example:

> In different environments, say in linux flavors, one might be **repeating the same functionality, but with a different set of commands or their variations**. One of the first things a user would like to do in linux is to have their _bashrc_ configured with their personal set of commands. Using this tool it becomes easy, by saving under two C-tables, say one for _ubuntu_, and one for _opensuse_. It's enough if the end user just retrieves and executes(sources) the tag bashrc.


<br>


The basic tables used to store the data

*  _cmd_ :commands,scripts,etc with a note
*  _dir_ :directory paths


### CMD tables
![](https://github.com/ravijanjam/qkw/blob/master/docs/cmd_table.png)

### DIR tables
![](https://github.com/ravijanjam/qkw/blob/master/docs/dir_table.png)

**Manual**: Refer to the [[manual]](https://github.com/ravijanjam/qkw/blob/master/docs/qkw-manual.pdf) for all the available options, use cases and other information.  

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
* If necessary, modify the compile options `OPTS_SQLITE_3,OPTS_YAML-CPP,OPTS_FMT` in the Makefile, to point to the libs, and headers. There are subtle differences in libraries installed via _lib_ as a dev package or via compiled libraries. `pkg-config` provided options can work as well. 

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

Start the program and check the default tables `userdata.db` has two tables dir\_1, and cmd\_1

```bash

# get version info
qkw -v

# list all tables
qkw -T -lA 

# man pages
man qkw
```

<hr>

## Quick Start

There are about 75+ options to play with. Some of the most important ones demonstrated here. For all the available options, please read the section _Options_ in the [[manual]](https://github.com/ravijanjam/qkw/blob/master/docs/qkw-manual.pdf). 

The core option set 
* add
* delete
* modify
* search

<hr>

* Get help
```bash
qkw -h -T -cC
qkw -h -D -lA
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

* Content retrieval, gets data from the second column or V-column based on labels/tags

```bash
# only one label taken
qkw -gC <label> # C-tables
qkw -gD <label> # D-tables
```

* Visit a few directories and add labels
```bash
# current directory information 
qkw -addpath p1  # in dir /a/b/c
qkw -addpath p2  # in dir x/y
```

* Add content to the tables manually as _label:value_ strings
```bash
# directories, D tables
qkw -iD m:"/u/v/w/x"
qkw -iD n:"/q/r"

# commands, C tables
qkw -iC devpush:"git push origin dev"
qkw -iC open:"vi /path/to/my/todo/list.txt"
```

* Check the added content D:directories, C:commands
```bash
qkw -D -lA
qkw -C -lA
```


* _Bulk Changes_: adding/removing/modifying data via a file.
```bash
# template file with fields to populate information
# label,value,expl fields
qkw -gettemplate cmdinput.data 

# write to a file when labels are provided
qkw -C -if cmdoutput.data <L,L...,L> # L:labels

# write from file to the database
qkw -C -if cmdinput.data

# add modified data from file, should have existing label
# helps when you have changes to make or reuse with variations
qkw -C -mf cmdinput.data

# delete the modified data from file, label should exist
# rest of the fields are ignored
qkw -C -df cmdinput.data

# same operations work for dir tables, but with different format
# NOTE: -gettemplate option doesn't work for dir tables
# since the format is "label:value", one per line
qkw -D -if dirinput.data
qkw -D -mf dirinput.data
qkw -D -df dirinput.data
qkw -D -wf diroutput.data <L,L...,L>  # L:labels
```

* Check the added data
```bash
qkw -C -lA
```

* Add the macros `cd2:navigation`, and `runfast:command execution` in your bashrc or it's equivalent

```bash
# navigation
cd2(){
  cd `qkw -gD $1`
}

# command execution
runfast(){
  str=`qkw -gC $1`
  qkw -exec “${str}”
}
```

`source ~/.bashrc` and start using the tags

```bash
# takes you to directory /u/v/w/x
cd2 m 
```

```bash
# will run your the tagged lss commands
runfast lss 
```

To learn more, on how to set up `macros` and other advanced use cases on how to use `qkw`, please consult the [[manual]](https://github.com/ravijanjam/qkw/blob/master/docs/qkw-manual.pdf)
