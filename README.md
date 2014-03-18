Lunch-Scheduler
===============

Obviously, the favicon.ico is the best part of this page.

## git-hook automation

Setup the appropriate folder on your remote server.

```bash
mkdir example.com.git
cd example.com.git
git init --bare
```

Add the following to example.com.git/hooks/post-receive and set it to executable:

```sh
#!/bin/sh
GIT_WORK_TREE=/path/to/DocumentRoot git checkout -f master
```

```bash
chmod +x example.com.git/hooks/post-receive
```

## MySQL Table

Here is the expected table format in MySQL. This is now created automatically if it doesn't exist.

```mysql
create table schedule(id int not null auto_increment, primary key(id), name varchar(50) not null, lunchslot varchar(30) not null, role varchar(30), date date not null, timestamp timestamp not null);
```
