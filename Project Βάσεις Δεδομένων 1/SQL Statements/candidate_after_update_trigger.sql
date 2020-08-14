CREATE DEFINER=`root`@`localhost` TRIGGER `candidate_AFTER_UPDATE` AFTER UPDATE ON `candidate` FOR EACH ROW BEGIN
	declare username varchar(12);
	select user into username from login order by date desc limit 1;
	insert into record values (username, now(), 'Success', 'update', 'candidate');
END