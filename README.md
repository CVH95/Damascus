# Course Project - LEO2

### Secure Ad Hoc Networking with Raspberry Pi's.

Project of the course Linux for Embedded Objects (SDU Robotics).

The project consisted on creating an ad-hoc network for communication bewteen multiple Raspberry Pi's. All RPi's have been equiped with Raspbian Lite (29-11-2017 version). The following is a quick guide on how to set up a new branch in the project git.

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

### Implementation

All cryptographic functions were tested and work fine. However, the main functionality of the system inside an ad hoc network could not be tested yet, due to unavailability of hardware to broadcast an ad hoc network with Raspberry Pi's.

