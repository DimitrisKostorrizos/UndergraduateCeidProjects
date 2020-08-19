CREATE DEFINER=`root`@`localhost` TRIGGER `recruiter_AFTER_INSERT` AFTER INSERT ON `recruiter` FOR EACH ROW BEGIN
	declare username varchar(12);
	select user into username from login order by date desc limit 1;
	insert into record values (username, now(), 'Success', 'insert', 'recruiter');
END