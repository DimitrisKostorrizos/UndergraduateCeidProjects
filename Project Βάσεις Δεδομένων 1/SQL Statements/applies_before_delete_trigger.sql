CREATE DEFINER=`root`@`localhost` TRIGGER `applies_BEFORE_DELETE` BEFORE DELETE ON `applies` FOR EACH ROW 
BEGIN
	declare job_date date;
	select job.submission_date
	into job_date
	from applies
	inner join job on applies.job_id = job.id
    where old.job_id = job.id;
	if datediff(job_date, current_date()) < 0 then
		SIGNAL SQLSTATE '45000'
		SET MESSAGE_TEXT = 'Cannot delete this row.';
	end if;
END