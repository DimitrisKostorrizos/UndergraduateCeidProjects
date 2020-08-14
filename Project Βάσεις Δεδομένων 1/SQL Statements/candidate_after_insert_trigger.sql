CREATE DEFINER=`root`@`localhost` TRIGGER `candidate_AFTER_INSERT` AFTER INSERT ON `candidate` FOR EACH ROW BEGIN
	declare username varchar(12);
	select user into username from login order by date desc limit 1;
	insert into record values (username, now(), 'Success', 'insert', 'candidate');
END