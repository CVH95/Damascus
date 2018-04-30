# Course Project - LEO2

### Secure Ad Hoc Networking with Raspberry Pi's.

Project of the course Linux for Embedded Objects (SDU Robotics).

### Branch Management

The project consisted on creating an ad-hoc network for communication bewteen multiple Raspberry Pi's. All RPi's have been equiped with Raspbian Lite (29-11-2017 version). Originally, 3 of this devices have been used. Additionaly, to test the security in the network, a laptop with Ubuntu 16.04 as OS will be used to eavesdrop. On each RPi, a new user will be created. City names have been used to identify the different nodes:

 - RPi 1: Naples (Italy).
 - RPi 2: Monterrey (Mexico).
 - RPi 3: Kinsasa (Democratic Republic of the Congo).
 - Laptop: Jerusalem (Israel).

The following is a quick guide on how to set up a new branch in the project git.

Create directory for the repo and navigate to it. Then start git:

```sh
$ mkdir ~/workspace/LEO2
$ cd ~/workspace/LEO2
$ git init
$ git add .
$ git commit -m "Starting new branch"
```

Then, create new branch by:

```sh
$ git checkout -b <new_branch_name>
```

Finally, add the branch to the remote repository by:

```sh
$ git remote add origin <url_of_repository>
$ git push -u origin <new_branch_name>
```

To see all branches created in a project, go to the directory in the local machine and type:

```sh
$ git branch
```


