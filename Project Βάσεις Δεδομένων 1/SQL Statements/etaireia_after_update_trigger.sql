CREATE DEFINER=`root`@`localhost` TRIGGER `etaireia_AFTER_UPDATE` AFTER UPDATE ON `etaireia` FOR EACH ROW BEGIN
	declare username varchar(12);
	select user into username from login order by date desc limit 1;
	insert into record values (username, now(), 'Success', 'update', 'etaireia');
END