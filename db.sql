create database ONEPOKER;
use ONEPOKER;

create table OP_CARD_LIST_TB(
	card_code int not null auto_increment primary key, 
	card_name varchar(4) not null unique,
);

create table OP_RATING_TB(
	rating_code int not null auto_increment primary key,
	rating_name varchar(10) not null unique,
	rating_condition int not null unique
);

create table OP_USER_TB(
	user_num int not null auto_increment primary key,
	id varchar(30) not null unique,
	pass varchar(30) not null,	
	email varchar(30) not null unique,
	email_cert ENUM('O', 'X') DEFAULT 'X',
	resent_access_date DATE DEFAULT "1970-01-01",
	money int DEFAULT 5000,
	win int DEFAULT 0,
	lose int DEFAULT 0,
	rating_code int not null,

	FOREIGN KEY(rating_code) REFERENCES OP_RATING_TB(rating_code) ON UPDATE CASCADE
);

create table OP_BLACK_IP_TB(
	ip varchar(16) not null primary key,
	add_date DATE not null,
	reason TEXT
);

create table OP_BLACK_USER_TB(
	user_num int not null, 
	add_date DATE not null,
	reason TEXT,

	FOREIGN KEY(user_num) REFERENCES OP_USER_TB(user_num) ON UPDATE CASCADE ON DELETE CASCADE

);
create table OP_ACCESS_LOG_TB(
	user_num int not null,
	ip varchar(16) not null,
	access_date DATE not null,

	FOREIGN KEY(user_num) REFERENCES OP_USER_TB(user_num) ON UPDATE CASCADE ON DELETE CASCADE
);
create table OP_MATCH_LOG_TB(
	match_num int not null auto_increment primary key,
	user_id1 varchar(30) not null,
	user_id2 varchar(30) not null,
	winner ENUM('1','2') not null,
	add_date DATE not null
);

INSERT INTO OP_CARD_LIST_TB(card_name, card_type, card_win) VALUES('2');
INSERT INTO OP_CARD_LIST_TB(card_name, card_type, card_win) VALUES('3');
INSERT INTO OP_CARD_LIST_TB(card_name, card_type, card_win) VALUES('4');
INSERT INTO OP_CARD_LIST_TB(card_name, card_type, card_win) VALUES('5');
INSERT INTO OP_CARD_LIST_TB(card_name, card_type, card_win) VALUES('6');
INSERT INTO OP_CARD_LIST_TB(card_name, card_type, card_win) VALUES('7');
INSERT INTO OP_CARD_LIST_TB(card_name, card_type, card_win) VALUES('8');
INSERT INTO OP_CARD_LIST_TB(card_name, card_type, card_win) VALUES('9');
INSERT INTO OP_CARD_LIST_TB(card_name, card_type, card_win) VALUES('10');
INSERT INTO OP_CARD_LIST_TB(card_name, card_type, card_win) VALUES('K');
INSERT INTO OP_CARD_LIST_TB(card_name, card_type, card_win) VALUES('Q');
INSERT INTO OP_CARD_LIST_TB(card_name, card_type, card_win) VALUES('J');
INSERT INTO OP_CARD_LIST_TB(card_name, card_type, card_win) VALUES('A');

INSERT INTO OP_RATING_TB(rating_name, rating_condition) VALUES("4", 0);
INSERT INTO OP_RATING_TB(rating_name, rating_condition) VALUES("3", 10000);
INSERT INTO OP_RATING_TB(rating_name, rating_condition) VALUES("2", 30000);
INSERT INTO OP_RATING_TB(rating_name, rating_condition) VALUES("1", 90000);

INSERT INTO OP_USER_TB(id, pass, email, rating_code) VALUES('hun5077', '123456', 'wqedwa@asd.com', 1);
INSERT INTO OP_USER_TB(id, pass, email, rating_code) VALUES('eqw456', '123456', 'wqedasdfsdaa@naefd.com', 1);

