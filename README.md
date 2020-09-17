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


The basic tables used to store the data
* **cmd**:commands,scripts,etc with a note,
* **dir**:directory paths
### CMD tables
![](https://github.com/ravijanjam/qkw/blob/master/docs/cmd_table.png)

### DIR tables
![](https://github.com/ravijanjam/qkw/blob/master/docs/dir_table.png)
