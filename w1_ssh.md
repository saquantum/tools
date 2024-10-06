# SSH

​	`ssh` is the client, which you run on your machine to connect to another machine.

​	`	sshd` is the server, or *daemon* in UNIX-speak. It runs in the background on the machine you want to connect to, and needs to be installed by the system administrator. Note: SSH uses TCP port 22 by default.

#### Check your client

​	Type `ssh localhost` to test if the ssh client is working, and a ssh server is running on your current machine.

#### Connect to the lab

​	The bastion host `seis.bris.ac.uk`. This is reachable over SSH from the internet, and is on a university network that lets you connect further to the lab machines. You should not attempt to do any work on seis itself, as most of the software you would like to use (like compilers) is not installed there. However, you do have a home directory on seis for storing things like SSH keys.

​	The load balancer `rd-mvb-linuxlab.bristol.ac.uk`  connects you to a lab machine. 

​	Type `ssh USERNAME@seis.bris.ac.uk` . Command `uname -a` to print information about the system.  Try `whoami` and `uname -a` to check who you are logged in as, and where; also try `hostname` which just prints the machine name.

​	Jump:

```
ssh -J USERNAME@seis.bris.ac.uk USERNAME@rd-mvb-linuxlab.bristol.ac.uk
```

#### Setting up ssh keys

​	The keys that SSH uses implement digital signatures. Each key comes as a pair of files:

​	A private key (also known as secret key) in a file normally named `id_CIPHER` where CIPHER is the cipher in use. You need to keep this secure and only store it in places that only you have access to.

​	A public key in a file normally named `id_CIPHER.pub`. You can share this with the world, and you will need to store a copy of it on any machine or with any service that you want to log in to (for the lab, because the lab machines all share a file system, you only need to store it once - but seis has a separate file system so you need a separate copy there).

​	Generate keys: command `ssh-keygen -t ed25519` .

​	On your own machine: `ls -l ~/.ssh` 

```
-rw-r--r--.  config
-rw-------.  id_ed25519
-rw-r--r--.  id_ed25519.pub
-rw-r--r--.  known_hosts
```



~/.ssh/authorized_keys and ~/.ssh/id_ed25519.pub:

`ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIDxt6V4EEZ+7knCtSjsSYAtomEsH2WStEOQTE2JlwlHL saquantum@localhost.localdomain`
`ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIHQarE6bKBCgqhXXPyGPWRJaf8I8JZNhwHHfmNQQxFQz soyo@DESKTOP-PF2B1AC`