CREATE DEFINER=`root`@`localhost` PROCEDURE `assessment_check`(in id INT(4))
BEGIN
	declare recruiter varchar(12);
    declare personality_grade decimal(3,2);
	declare education_grade int(1);
    declare experience_grade int(1);
	declare message varchar(100);
    declare finished integer default 0;
	declare assessment integer default 1;
    declare fail integer default 0;
	declare message_1 char(20);
	declare message_2 char(20);
	declare message_3 char(20);
    
	declare grade_cursor cursor for
    select applies.personality_grade, applies.experience_grade, applies.education_grade
    from applies
    inner join job on applies.job_id = job.id
    where job.id = id;
    
    declare continue handler 
	for not found set finished = 1;
    
    select job.recruiter
    into recruiter
    from job
    where job.id = id;
    
    open grade_cursor;
    
	check_grades: loop
		fetch grade_cursor into personality_grade, education_grade, experience_grade;
		if finished = 1 then 
			leave check_grades;
		end if;	
		if (personality_grade is null OR education_grade is null OR experience_grade is null) then
			set assessment = 0;
			leave check_grades;
		end if;
        if (personality_grade = 0 OR education_grade = 0 OR experience_grade = 0) then
			set fail = 1;
		end if;
	end loop check_grades;
	close grade_cursor;
    
    if assessment = 0 then
		set message = 'The assessment of this job has not been completed.';
		select message;
	else
		set message = 'The assessment of this job has been completed.';
		select message;
        
        SELECT cand_usrname as Candidate_Username, 
		(personality_grade + education_grade + experience_grade) as Total_Grade, 
		personality_grade as Personality_Grade, 
		education_grade as Education_Grade, 
		experience_grade as Experience_Grade,
		count(interview.candidate) as Number_of_Interviews
		from applies
		inner join candidate on applies.cand_usrname = candidate.username
		inner join interview on candidate.username = interview.candidate
		where applies.job_id = id  AND interview.job_id = id
		having personality_grade > 0 AND education_grade > 0 AND experience_grade > 0
		order by Total_Grade DESC;
        
        if fail = 1 then
			select Candidate_Username, Explanation
			from(
			select cand_usrname as Candidate_Username, CONCAT_WS(', ',@message_3,@message_2,@message_1) as Explanation,
			if (applies.personality_grade = 0, @message_1 := 'failed the interview', @message_1 := ''),
			if (applies.education_grade = 0, @message_2 := 'inadequate education', @message_2 :=''),
			if (applies.experience_grade = 0, @message_3 := 'no prior experience', @message_3 := '')
			from applies
			where applies.job_id = 2 AND (applies.personality_grade = 0 OR applies.education_grade = 0 OR applies.experience_grade = 0)) as source;
			end if;
	end if;
END