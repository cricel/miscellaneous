# Drone_Tutorial (Ubuntu)

## offical document:
DroneKit: http://python.dronekit.io/guide/quick_start.html

Drone example code: http://python.dronekit.io/examples/running_examples.html

APM Planner: http://ardupilot.org/planner2/

Ardupilot simulator: http://ardupilot.org/dev/docs/setting-up-sitl-on-linux.html

`there are some new updated on the software, but the document is still old. please see Document for detail explanation and follow the following step to get everything set up`

## Example code:
check the offical document.
```
git clone http://github.com/dronekit/dronekit-python.git
cd dronekit-python/examples/
```

## Make it work:

### general package
```
sudo apt-get install python-pip python-dev python-numpy
sudo python -m pip install --upgrade dronekit
sudo python -m pip install --upgrade dronekit-sitl
sudo pip install MAVProxy
echo "export PATH=$PATH:$HOME/.local/bin" >> ~/.bashrc
```

### APM Planner
#### Installation:
go to http://firmware.ardupilot.org/Tools/APMPlanner/ and download `apm_planner_2.0.24_xenial64.deb`
```
# go to the directory where you download the package
sudo dpkg -i apm_planner_2.0.24_xenial64.deb
sudo apt-get -f install
sudo dpkg -i apm_planner_2.0.24_xenial64.deb
```

#### make it fly:
launch the apm planner
```
apmplanner2
```
open a new terminal,
```
cd dronekit-python/examples/simple_goto
python simple_goto.py
```
wait a few seconds, run 
make sure you put`5763`, not `5760`
```
mavproxy.py --master tcp:127.0.0.1:5763 --sitl 127.0.0.1:5501 --out 127.0.0.1:14550
```
`make sure you run those 3 command in the exact order, otherwise it may crash the system or throw errors.`

you will see a copter flying. 

### Ardupilot simulator
#### get the source code
```
git clone git://github.com/ArduPilot/ardupilot.git
cd ardupilot
git submodule update --init --recursive
```
#### install requied dependce and environment
`You will be asked for your Ubuntu root password. Respond with “Y” when anything pop up`
```
cd Tools/scripts
./install-prereqs-ubuntu.sh
```
#### getting started
go to the script folder
```
cd ardupilot/Tools/autotest
```

load the right default parameters for your vehicle. `-v` option give you the choice of different vehicle `ArduCopter|AntennaTracker|APMrover2|ArduSub|ArduPlane`
```
./sim_vehicle.py -v ArduCopter
```
After the default parameters are loaded you can start the simulator normally. First kill the sim_vehicle.py you are running using Ctrl-C. Then:
```
./sim_vehicle.py -v ArduCopter --console --map`
```
#### make it fly
Let’s also load a test mission. From within MAVProxy type:
```
wp load ../Tools/autotest/copter_mission.txt
```
Copter only supports takeoff in `guided` mode; if you want to fly a mission you first have to take off and then switch to `AUTO` mode. **Takeoff must start within 15 seconds of arming, or the motors will disarm!**
```
mode guided
arm throttle
takeoff 40
mode auto
```
Your virtual aircraft should now takeoff.



