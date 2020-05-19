# ESPN RotoCalc
C++ Console Application for calculating Rotisserie-Style scoring for ESPN Fantasy Basketball Leagues.

## Features
ESPN RotoCalc implements a Rotisserie Scoring format for Categories and Points leagues. Rotisserie scoring is based on the description found [here.](https://en.wikipedia.org/wiki/Fantasy_basketball#Rotisserie_(ROTO))

The program includes the option to calculate Roto scoring from previous years, allowing users to better understand their league and roster structure.

The program gathers information from the [ESPN_V3_API](https://stmorse.github.io/journal/espn-fantasy-v3.html) with python and writes out the results to a csv file named after the configuration file name and the year of the results. The python script is abstracted away from the user and is called directly from the C++ program execution. 


## Dependencies
- Boost (Minimum 1.58.0)
- GCC 7.5.0 (This is the kit I used, but I assume it works with gcc-5 and gcc-6)
- Python3.6
- CMake (Minimum 3.17.0)

## Usage
First clone the program, then navigate the the root folder.
From there, build the program using CMake
```
cmake -S . -B build
```
Now, move the python script (fantasy.py) from the root into the build folder with
```
mv fantasy.py build
```
To get the stats from a private league, the request to the ESPN V3 API requires cookies to authenticate the user session, and the leagueId. These cookies are ***SWID and ESPN_S2***. These values can be found by looking through your browser settings. You can find your leagueId by navigating to your fantasy league's home page.

Create a configuration file with these values. the built program (roto)
scans your input configuration files for values in the following format:
```
swid = SWID
espn_s2 = espn_s2
id = leagueId
```

## Notes and Future Changes

Currently, the program runs the 'fantasy.py' script by invoking python3.6 from the command line with assorted parameters. Currently, the program will *only* work if your desktop as configured this way.
Future updates will have the correct python path specefied through the command line / config file.
