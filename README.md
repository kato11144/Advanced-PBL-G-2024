# PBL-G-Advanced-2024

This guide provides instructions for setting up the development environment using Docker

## Setup Instructions

### 1. Install Docker

#### macOS

**Option 1: Using the Installer**
1. Download Docker Desktop for Mac from the [official website](https://docs.docker.com/desktop/install/mac-install/)
2. Open the downloaded `.dmg` file
3. Drag Docker to the Applications folder
4. Launch Docker Desktop from the Applications folder

**Option 2: Using [Homebrew](https://brew.sh/)**
```sh
brew install --cask docker
```

#### Windows

**Option 1: Using the Installer**
1. Download Docker Desktop for Windows from the [official website](https://docs.docker.com/desktop/install/windows-install/)
2. Run the downloaded installer
3. Follow the setup instructions
4. Launch Docker Desktop from the Start menu

**Option 2: Using [Winget](https://github.com/microsoft/winget-cli)**
```sh
winget install Docker.DockerDesktop
```

### 2. Setup Docker Containers

Build and Start Container
```sh
docker compose up -d --build
```

Access the Container
```sh
docker compose exec ubuntu /bin/bash
```

### 3. Setup MySQL

#### Log in to MySQL (password : mysql)
```sh
mysql -u root -p
```

#### Change Authentication Method and Root Password
```sh
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'enpit0000';
```

#### Exit MySQL
```sh
exit;
```

---

#### Run MySQL Secure Installation
```sh
mysql_secure_installation
```

#### During the prompts, enter the following responses
```sh
Enter password for user root : enpit0000
VALIDATE PASSWORD COMPONENT can be used to test passwords and improve security. It checks the strength of password and allows the users to set only those passwords which are secure enough. Would you like to setup VALIDATE PASSWORD component? Press y|Y for Yes, any other key for No : y
Please enter 0 = LOW, 1 = MEDIUM and 2 = STRONG : 0
Change the password for root? (Press y|Y for Yes, any other key for No) : n
Remove anonymous users? (Press y|Y for Yes, any other key for No) : y
Disallow root login remotely? (Press y|Y for Yes, any other key for No) : y
Remove test database and access to it? (Press y|Y for Yes, any other key for No) : y
Reload privilege tables now? (Press y|Y for Yes, any other key for No) : y
```

---

#### Log in to MySQL (password : enpit0000)
```sh
mysql -u root -p
```

#### Modify Password Settings
```sh
set global validate_password.length=4;
set global validate_password.check_user_name=OFF;
```

#### Verify Password Settings
```sh
show variables like 'validate_password%';
```

#### Create Database and User
```sh
create database RhoMethod;
create user 'attacker'@'localhost' identified by '0000';
grant all on RhoMethod.* to 'attacker'@'localhost';
flush privileges;
```

#### Exit MySQL
```sh
exit;
```

---

#### Log in to MySQL (password : 0000)
```sh
mysql -u attacker -p
```

#### List available Databases
```sh
show databases;
```

#### Exit MySQL
```sh
exit;
```

---

### Docker Commands
```sh
# List All Containers
docker ps -a

# Stop the Container
docker stop <CONTAINER ID>

# Remove the Container
docker rm <CONTAINER ID>

# List All Images
docker images

# Remove the Image
docker rmi <IMAGE ID>
```
