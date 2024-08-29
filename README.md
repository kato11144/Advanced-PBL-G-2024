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
```sql
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'enpit0000';
```

#### Exit MySQL
```sql
exit;
```

#### Run MySQL Secure Installation
```sh
mysql_secure_installation
```

#### During the prompts, enter the following responses
```sh
Enter password for user root : enpit0000

Would you like to setup VALIDATE PASSWORD component? (Press y|Y for Yes, any other key for No) : y

Please enter 0 = LOW, 1 = MEDIUM and 2 = STRONG : 0

Change the password for root? (Press y|Y for Yes, any other key for No) : n

Remove anonymous users? (Press y|Y for Yes, any other key for No) : y

Disallow root login remotely? (Press y|Y for Yes, any other key for No) : y

Remove test database and access to it? (Press y|Y for Yes, any other key for No) : y

Reload privilege tables now? (Press y|Y for Yes, any other key for No) : y
```

#### Log in to MySQL (password : enpit0000)
```sh
mysql -u root -p
```

#### Modify Password Settings
```sql
SET GLOBAL validate_password.length = 4;

SET GLOBAL validate_password.check_user_name = OFF;
```

#### Verify Password Settings
```sql
SHOW VARIABLES LIKE 'validate_password%';
```

#### Create Database and User
```sql
CREATE DATABASE RhoMethod;

CREATE USER 'attacker'@'localhost' IDENTIFIED BY '0000';

GRANT ALL ON RhoMethod.* TO 'attacker'@'localhost';

FLUSH PRIVILEGES;
```

#### Exit MySQL
```sql
exit;
```

---

### MySQL Commands
```sql
-- List all databases
SHOW DATABASES;

-- Switch to a specific database
USE <Database Name>;

-- List all tables in the database
SHOW TABLES;

-- Display records from a specific table
SELECT * FROM <Table Name>;
```
