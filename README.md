# QKW | Generalizing Aliasing
## Simplify navigation, alias CLI command sequence nuances, annotate, add help-strings, etc¶

The purpose of this application is to tag anything with a _label_ and, use it to retrieve the associated data for other applications. Data is stored as:

```
	<label> : 
		<data>

		<help-string,annotation,stdout,etc>

	(or)

	<label>:<data>
```

## Features

* **Directory navigation**: Use the bookmarked _keys_ to hop across directories
* Assign tags/labels to programmable/non-programmable structures. 
* Add a _help-string_ or _note_ with the associated data.
* Store, retrieve and search the data in a file rather than a executable script, formatted as a string.
* **Clipboard**: to store the stdout/stderr for inspection or analysis. 
* **Manage API distribution w/documentation**: Easily share the functional blocks of your _application like initialization, settings, etc_ by just sharing the database, where user is abstracted away from the details and focuses on using the functionality by mere execution of the tags.
* **DevOps automation** : 
	* Rapidly create variations, and save them with a versioned tag. 
	* Quickly test a set of commands with different options in different environments. 
	* Replace shell/bash aliasing using qkw's dynamic tagging.
	* Similar functionality, but different command base/ options can be tagged with identical tags and executed.


For example:

> In different linux flavors, one might be _**repeating identical functionality in different environments**_.  One of the first things a user would like to do is to have their _bashrc_ configured with their personal set of commands. 

> Sourcing the tags **opensuse.bashrc**, and **ubuntu.bashrc** would readily setup your environment. The data for OS specific environments are in the command tables.


<br>

## Getting Started

[**Manual**](https://github.com/ravijanjam/qkw/blob/master/docs/qkw-manual.pdf) contains information about use cases, and all the available options.

[**QuickStart**](https://github.com/ravijanjam/qkw/wiki/QuickStart) guide helps you get started with using the basic commands.


## Installation (Ubuntu/Debian)

* Clone the repo
```bash
git clone https://github.com/ravijanjam/qkw.git
cd qkw
```

* Install the dependencies
```bash

apt-get update
apt-get install -y git gcc g++ pkg-config cmake make
apt-get install -y libsqlite3-dev libyaml-cpp-dev
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


The basic tables used to store the data

*  _cmd_ :commands,scripts,etc with a note
*  _dir_ :directory paths


### CMD tables
![](https://github.com/ravijanjam/qkw/blob/master/docs/cmd_table.png)

### DIR tables
![](https://github.com/ravijanjam/qkw/blob/master/docs/dir_table.png)


<br>

_Category_ : CLI tools, productivity, bash utility, aliasing, labeling, sqlite, g++, commandline, documentation, docstring
