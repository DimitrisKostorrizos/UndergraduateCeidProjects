drop database erecruit;
create database erecruit;
use erecruit;

CREATE TABLE etaireia (
AFM char(9) NOT NULL, 
DOY varchar(15),
name varchar(35) NOT NULL default 'NO-NAME registered',
tel bigint(16),
street varchar(15),
num tinyint,
city varchar(15),
country varchar(15),
PRIMARY KEY (AFM)
)engine=InnoDB;

insert into etaireia (AFM, DOY, name, tel, street, num, city, country) values 
('023453344', 'C Patras', 'EXPENDITURE Ltd', 2610256321, 'Maizonos', 123, 'Patra', 'Greece'), 
('023451232', 'A Patras', 'Typology Ltd', 2610231452, 'Korinthou', 56, 'Patra', 'Greece'),
('123432211', 'A Geraka', 'SoftSol A.E.', 2103452133, 'Ahepa', 44, 'Athina', 'Greece'), 
('18765549', 'C Peiraia', 'Unigram', 2103452672, 'Karaiskaki', 10, 'Peiraias', 'Greece'),
('561234561', 'GS 35321 L', 'InCodeWeTrust', 1242345612, 'Oxford', 12, 'London', 'United Kingdom'), 
('23122345', 'SF 1234 BG', 'SocialSc', 3200123451, 'General Sklevi', 35, 'Sofia', 'Bulgaria');


CREATE TABLE antikeim (
title VARCHAR(36) NOT NULL,
descr TINYTEXT,
belongs_to varchar(36),
PRIMARY KEY (title),
CONSTRAINT ANTIKEIMENO FOREIGN KEY (belongs_to) REFERENCES antikeim(title) ON DELETE CASCADE ON UPDATE CASCADE
)engine=InnoDB;

insert into antikeim (title, descr, belongs_to) values 
('Computer Science', 'Root element, no more general antikeim', NULL),
('Databases', 'Level one element, child of Computer Science', 'Computer Science'),
('AI', 'Level one element, child of Computer Science', 'Computer Science'),
('Algorithms', 'Level one element, child of Computer Science', 'Computer Science'),
('Networking', 'Level one element, child of Computer Science', 'Computer Science'),
('Graphics', 'Level one element, child of Computer Science', 'Computer Science'),
('2D', 'Level two element, child of Graphics', 'Graphics'),
('3D', 'Level two element, child of Graphics', 'Graphics'),
('Animation', 'Level two element, child of Graphics', 'Graphics'),
('Programming', 'Level one element, child of Computer Science', 'Computer Science'),
('Web Programming', 'Level two element, child of Programming', 'Programming'),
('Mobile Apps', 'Level two element, child of Programming', 'Programming'),
('Relational DBs', 'Level two element, child of Databases', 'Databases'),
('Object-Oriented DBs', 'Level two element, child of Databases', 'Databases'),
('NoSQL DBs', 'Level two element, child of Databases', 'Databases'),
('Robotics', 'Level two element, child of AI', 'AI'),
('NLP', 'Level two element, child of AI', 'AI'),
('Information Retieval', 'Level three element, child of NLP', 'NLP'),
('Language analysis', ' Level three element, child of NLP', 'NLP'),
('Data structures', 'Level two element, child of Algorithms', 'Algorithms'),
('Complexity and Efficiency', 'Level two element, child of Algorithms', 'Algorithms'),
('Network setup and maintainance', 'Level two element, child of Networking', 'Networking'),
('Device connectivity', 'Level two element, child of Networking', 'Networking')
;


CREATE TABLE `user` (
username varchar(12) NOT NULL,
`password` varchar(10),
`name` varchar (25) NOT NULL,
surname varchar (35) NOT NULL,
reg_date DATETIME,
email varchar(30),
PRIMARY KEY (username)
)engine=InnoDB;

/* add CANDIDATES */
insert into `user` (username, `password`, `name`, surname, reg_date, email) values 
('cleogeo', 'upL34r', 'Cleomenis', 'Georgiadis', '2018-02-13 12:23:34', 'cleom17@gmail.com'),
('zazahir23', 'zoolhger', 'Ahmet', 'Mobasher-Hirs', '2017-05-11 14:08:23', 'ahmetTech@yahoo.com'),
('lionarF', 'erg2378', 'Freddy', 'Lionar', '2018-10-07 20:09:10', 'Lionarfre@ezra.co.uk'),
('liagourma', 'sionpass', 'Maria', 'Liagkoumi', '2018-05-22 17:03:01', 'mliagkr@gmail.com'),
('mnikol', 'm@n0lis', 'Manolis', 'Nikopoloulos', '2017-11-08 21:07:12', 'nikolp@gmail.com'),
('abrown', 'w1lcoxon', 'Andrew', 'McBrown', '2018-01-27 16:02:56', 'andrewbr@yahoo.com');

/* add RECRUITERS */
insert into `user` (username, `password`, `name`, surname, reg_date, email) values 
('msmith', 'we3wd', 'Mike', 'Smith', '2017-06-23 13:12:34', 'smithm@unigram.com'),
('varcon82', 'gotop@s$', 'Nick', 'Varcon', '2018-12-03 18:12:39', 'varcni@incode.com'),
('bettyg', 'jUn38@', 'Betty', 'Georgiou', '2017-04-12 12:23:10', 'georb@softsol.gr'),
('papad', 'pdfr45t', 'Kostas', 'Papadatos', '2018-11-17 23:10:08', 'georb@softsol.gr'),
('n_tri', 'grt12wX', 'Nikol', 'Triantou', '2018-03-08 20:10:20', 'triantou@typology.gr'),
('Giankost', 'jUn38@', 'Giannis', 'Kostoglou', '2018-02-23 11:08:15', 'kostog@typology.gr'),
('pavkie', 'julie79', 'Pavel', 'Skiev', '2017-03-25 11:23:45', 'pskiev@social-sc.bg')
;



CREATE TABLE recruiter (
username VARCHAR(12) NOT NULL,
exp_years TINYINT,
firm CHAR(9),
PRIMARY KEY (username),
CONSTRAINT RECR_USER FOREIGN KEY (username) REFERENCES `user`(username) ON DELETE CASCADE ON UPDATE CASCADE,
CONSTRAINT RECR_ETAIREIA FOREIGN KEY (firm) REFERENCES etaireia(AFM) ON DELETE CASCADE ON UPDATE CASCADE
)engine=InnoDB;

insert into recruiter (username, exp_years, firm) values 
('msmith', 4, '18765549'),
('varcon82', 2 , '561234561'),
('bettyg', 6, '123432211'),
('papad', 5, '123432211'),
('n_tri', 8, '023451232'),
('Giankost', 8, '023451232'),
('pavkie', 10, '23122345')
;

CREATE TABLE candidate(
username VARCHAR(12) NOT NULL,
bio TEXT NOT NULL,
sistatikes VARCHAR(35),
certificates VARCHAR(35),
PRIMARY KEY (username),
CONSTRAINT CAND_USER FOREIGN KEY (username) REFERENCES `user`(username) ON DELETE CASCADE ON UPDATE CASCADE
)engine=InnoDB;

insert into candidate(username, bio, sistatikes, certificates) values
('cleogeo', 'Cleomenis is a secodary education graduate who has long work experience in web programming technologies (has worked for than 25 years in the field). He has been also certified as a CISCO security expert (CCIE Security) and an IT project manager (PMI Project Management Professional and Project Management Professional).', 'RecLetters.pdf', 'certifALL.pdf'),
('zazahir23', 'Mr Mobasher is a highly skilled web programmer who also has experience in 2d and 3d graphics generation as well as animation rendering. Moreover he has long experience with design, development and administration of large scale DBs, mostly relational.', 'Mobasher_rec.pdf', 'Mobasher-certif.pdf'),
('lionarF', 'Freddy is an experienced web programmer but has also worked on mobile apps development the last 5 years. He is a freelancer and can work from a distance. He can also manage 2d graphics and has long experience with DB scripting (My SQL, MariaDB, MS SQL Server and Oracle.', 'LionFr_letters.pdf', 'LionFR_cert.pdf'),
('liagourma', 'Mrs Liagkoumi has a long experience in NLP and more specifically Information Retrieval and has also long research background on both areas. In addition she has worked on large coprus datasets and data visualization algorithms.', 'lettersLiagk.pdf', 'trainingLiagk.pdf'),
('mnikol', 'Mr Nikolopoulos holds a Computer Science diploma and an MSc and has long work experience in AI applications as well as Robotics. He has also managed large R&D projects in these domains and has teaching and research experience as well. Please refer to his referral letters for more details.','referralLetNikol.pdf','degreesAndCertNikol.pdf'),
('abrown', 'Andrew has a strong theoretical background in Algorithms and Data Stuctures and has worked for more than a decade in a software house that specializes in high performance data management. He is well skilled in high complexity schemes and heavy load memory management.', 'lettersscannedMcBr.pdf', 'degrees-cert.pdf')
;


CREATE TABLE languages(
candid VARCHAR(12) NOT NULL,
lang SET('EN', 'FR', 'SP', 'GR'),
PRIMARY KEY (candid, lang),
CONSTRAINT CAND_LANG FOREIGN KEY (candid) REFERENCES candidate(username) ON DELETE CASCADE ON UPDATE CASCADE
)engine=InnoDB;

insert into languages (candid, lang) values 
('cleogeo', 'EN,SP,GR'),
('zazahir23', 'GR,EN'),
('lionarF', 'EN,FR'),
('liagourma', 'GR,EN'),
('mnikol', 'GR,FR'),
('abrown', 'EN,FR,SP')
;

CREATE TABLE project(
candid varchar(12) NOT NULL,
num TINYINT,
descr TEXT,
url varchar(60),
PRIMARY KEY (candid, num),
CONSTRAINT PROJ_CAND FOREIGN KEY (candid) REFERENCES candidate(username) ON DELETE CASCADE ON UPDATE CASCADE
)engine=InnoDB;

insert into project (candid, num, descr, url) values 
('abrown', 1, 'Minimal examples of data structures and algorithms in Python', 'https://github.com/a_brown/algorithms'),
('abrown', 2, 'Interactive Online Platform that Visualizes Algorithms from Code', 'https://github.com/a_brown/algorithm-visualizer'),
('abrown', 3, 'Repository which contains links and resources on different topics of Computer Science', 'https://github.com/a_brown/AlgoWiki'),
('mnikol', 1, 'Essential Cheat Sheets for deep learning and machine learning researchers', 'https://github.com/nikolo0p/cheatsheets-ai'),
('mnikol', 2, 'Python sample codes for robotics algorithms.', 'https://github.com/nikolo0p/PythonRobotics'),
('zazahir23',1,'Go Graphics - 2D rendering in Go with a simple API.','https://github.com/mob@s/gg'),
('zazahir23',2,'Draco is a library for compressing and decompressing 3D geometric meshes and point clouds. It is intended to improve the storage and transmission of 3D graphics.','https://github.com/mob@s/draco'),
('zazahir23',3,'Data Discovery and Lineage for Big Data Ecosystem.','https://github.com/linkedin/WhereHows'),
('lionarF', 1, 'HTML5 Mobile App UI templates created using Intel App Framework.', 'https://github.com/lionarGF/appframework-templates'),
('lionarF', 2, 'Mobile Version of Travel sample App using Couchbase Lite 2.0.', 'https://github.com/lionarFG/mobile-travel-sample'),
('lionarF', 3, 'Appium Demo App with clearly defined Page Object Pattern for React Native Mobile App. Test Language - Javascript.','https://github.com/lionarFG/Appium-Page-Object-Model-Demo'),
('liagourma', 1, 'WebGL2 powered geospatial visualization layers. offers an extensive catalog of pre-packaged visualization "layers", including ScatterplotLayer, ArcLayer, TextLayer, GeoJsonLayer, etc. The input to a layer is usually an array of JSON objects. Each layer offers highly-flexible API to customize how the data should be rendered.', 'https://github.com/liagk0R/deck.gl'),
('liagourma', 2, 'Messy datasets? Missing values? missingno provides a small toolset of flexible and easy-to-use missing data visualizations and utilities that allows a quick visual summary of the completeness (or lack thereof) of the dataset.','https://github.com/liagk0R/missingno'),
('liagourma', 3,'Repository to track the progress in Natural Language Processing (NLP), including the datasets and the current state-of-the-art for the most common NLP tasks','https://github.com/liagk0R/NLP-progress'),
('liagourma', 4,'Supporting Rapid Prototyping with a Toolkit (incl. Datasets and Neural Network Layers)', 'https://github.com/liagk0R/PyTorch-NLP')
;

CREATE TABLE degree (
titlos VARCHAR(50) NOT NULL,
idryma VARCHAR (40) NOT NULL,
bathmida ENUM ('LYKEIO', 'UNIV', 'MASTER', 'PHD'),
PRIMARY KEY (titlos, idryma)
)engine=InnoDB;

insert into degree (titlos, idryma, bathmida) values 
('Lysium certificate', '2nd Lysium of Aigaleo', 'LYKEIO'),
('Computer and Infromatics Eng.', ' Patras University', 'UNIV'),
('Electrical and Computer Eng.', 'Metsovio Polytexneio', 'UNIV'),
('Computer Science Dipl.', 'Lancster University', 'UNIV'),
('Computer Vision and Modelling', 'Princeton University', 'MASTER'),
('Artificial Intelligence', ' Cambrigde University', 'MASTER'),
('Big Data and Analytics', ' Imperial College London', 'MASTER'),
('Advanced Rendering Techniques', 'Delft University of Technology', 'MASTER'),
('Computer Science and Engineering', 'Delft University of Technology', 'UNIV'),
('Data Science Bachelor','Eindhoven University of Technology', 'UNIV'),
('PDEng Data Science', 'Eindhoven University of Technology', 'PHD'),
('NLP related high efficiency algorithms', 'Patras University', 'PHD'),
('Big Data Structures and Algorithms', 'Technical University of Denmark', 'MASTER')
;


CREATE TABLE has_degree (
degr_title VARCHAR(50) NOT NULL,
degr_idryma VARCHAR (40) NOT NULL,
cand_usrname VARCHAR(12) NOT NULL,
etos YEAR,
grade FLOAT(3,1),
PRIMARY KEY (degr_title, degr_idryma, cand_usrname),
CONSTRAINT HAS_DEGR FOREIGN KEY (degr_title, degr_idryma) REFERENCES degree(titlos, idryma) ON DELETE CASCADE ON UPDATE CASCADE,
CONSTRAINT HAS_CAND FOREIGN KEY (cand_usrname) REFERENCES candidate(username) ON DELETE CASCADE ON UPDATE CASCADE
)engine=InnoDB;
show tables;

insert into has_degree (cand_usrname, degr_title, degr_idryma, etos, grade) values 
('cleogeo','Lysium certificate', '2nd Lysium of Aigaleo', 1999, 19.2),
('zazahir23', 'Computer Science and Engineering', 'Delft University of Technology',2000, 8.2),
('zazahir23', 'PDEng Data Science', 'Eindhoven University of Technology',2006, 9),
('lionarF', 'Electrical and Computer Eng.', 'Metsovio Polytexneio', 1998, 7.6),
('lionarF', 'Computer Vision and Modelling', 'Princeton University', 2001, 8.5),
('liagourma', 'Computer and Infromatics Eng.', ' Patras University', 2003, 8.6),
('liagourma', 'Artificial Intelligence', ' Cambrigde University', 2008, 8),
('liagourma', 'NLP related high efficiency algorithms', 'Patras University', 2013, 9),
('mnikol', 'Computer Science Dipl.', 'Lancster University', 2001, 8.4),
('mnikol', 'Computer Vision and Modelling', 'Princeton University', 2006, 7.4),
('abrown','Data Science Bachelor','Eindhoven University of Technology',2004, 9.2),
('abrown','Big Data and Analytics', ' Imperial College London', 2006, 8),
('abrown','Big Data Structures and Algorithms', 'Technical University of Denmark', 2008, 8.2)
;



CREATE TABLE job(
id int(4) NOT NULL AUTO_INCREMENT,
start_date DATE NOT NULL,
salary FLOAT(6,1),
position VARCHAR(40),
edra VARCHAR(45),
recruiter VARCHAR(12) NOT NULL,
announce_date DATETIME DEFAULT NOW(),
submission_date DATE NOT NULL,
PRIMARY KEY (id),
CONSTRAINT JOB_RECR FOREIGN KEY (recruiter) REFERENCES recruiter(username) ON DELETE CASCADE ON UPDATE CASCADE
)engine=InnoDB;

insert into job (start_date, salary, position, edra, recruiter, announce_date, submission_date) values 
('2019-01-01', 1800, 'data analyst', 'Patra, Greece', 'n_tri', '2018-07-13', '2018-12-20'),
('2019-02-01', 1450, 'web programmer', 'Patra, Greece', 'n_tri', '2018-07-13', '2019-01-10'),
('2019-02-01', 2100, 'mobile app developer', 'Patra, Greece', 'n_tri', '2018-10-24', '2018-01-12'),
('2018-12-25', 2700, 'NLP expert', 'Peiraias, Greece', 'msmith', '2018-10-10', '2018-11-10'),
('2019-03-01', 2100, 'Graphics designer', 'Peiraias, Greece', 'msmith', '2018-10-10', '2019-02-01'),
('201-03-01', 2300, 'Visualization expert', 'Peiraias, Greece','Giankost', '2018-10-20', '2019-01-10'),
('2019-05-01', 1850, 'web and mobile app programmer', 'Athina, Greece','papad', '2018-11-20', '2019-04-12'),
('2019-05-01', 1600, 'graphics expert', 'Athina, Greece','bettyg', '2018-11-20', '2019-04-12'),
('2019-05-01', 1850, 'DB expert', 'Athina, Greece','papad', '2018-11-20', '2019-04-12'),
('2019-04-01', 2100, 'AI expert', 'Sofia, Bulgaria', 'pavkie', '2018-11-21', '2019-03-10'),
('2019-02-01', 2600, 'Algorithmic efficiency expert', 'Sofia, Bulgaria', 'pavkie', '2018-11-01', '2019-01-16'),
('2019-03-01', 2800, 'web and media programmer', 'Oxford, London', 'varcon82', '2018-11-01', '2019-01-03')
;


CREATE TABLE requires(
job_id int(4) NOT NULL,
antikeim_title VARCHAR(36) NOT NULL,
PRIMARY KEY(job_id, antikeim_title),
CONSTRAINT REQ_JOB FOREIGN KEY (job_id) REFERENCES job(id) ON DELETE CASCADE ON UPDATE CASCADE,
CONSTRAINT REQ_ANTIK FOREIGN KEY (antikeim_title) REFERENCES antikeim(title) ON DELETE CASCADE ON UPDATE CASCADE
)engine=InnoDB;

insert into requires (job_id, antikeim_title) values 
(1, 'Databases'),
(1,'Algorithms'),
(2,'Programming'),
(2,'Web Programming'),
(3, 'Mobile Apps'),
(3, 'Animation'),
(4, 'AI'),
(4, 'NLP'),
(5, 'Graphics'),
(6, 'Graphics'),
(6, 'Algorithms'),
(6, 'Programming'),
(7, 'Web Programming'),
(7, 'Mobile Apps'),
(8, '2D'),
(8, '3D'),
(9, 'Databases'),
(9, 'NoSQL DBs'),
(10, 'AI'),
(11, 'Complexity and Efficiency'),
(11, 'Algorithms'),
(12, 'Web Programming'),
(12, 'Mobile Apps'),
(12, 'Animation')
;

CREATE TABLE applies (
cand_usrname VARCHAR(12) NOT NULL,
job_id int(4) NOT NULL,
PRIMARY KEY (cand_usrname, job_id),
CONSTRAINT APPL_JOB FOREIGN KEY (job_id) REFERENCES job(id) ON DELETE CASCADE ON UPDATE CASCADE,
CONSTRAINT APPL_CAND FOREIGN KEY (cand_usrname) REFERENCES candidate(username) ON DELETE CASCADE ON UPDATE CASCADE
)engine=InnoDB;

insert into applies (cand_usrname, job_id) values 
('cleogeo', 2),
('cleogeo',7),
('zazahir23', 2),
('zazahir23',3),
('zazahir23',6),
('zazahir23',7),
('zazahir23',8),
('zazahir23',12),
('lionarF', 2),
('lionarF',3),
('lionarF',5),
('lionarF',6),
('lionarF',7),
('lionarF',9),
('lionarF',12),
('liagourma', 4),
('liagourma',6),
('liagourma',10),
('mnikol', 4), 
('mnikol',11),
('abrown', 1),
('abrown', 9),
('abrown', 11)
;
