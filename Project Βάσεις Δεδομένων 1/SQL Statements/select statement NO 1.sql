select job.recruiter as Recruiter_Name, etaireia.name as Company_Name, job.id as ID, job.salary as Salary, count(applies.job_id) as Number_of_Applications
from job 
inner join recruiter on job.recruiter = recruiter.username
inner join etaireia on recruiter.firm = etaireia.AFM
inner join applies on job.id = applies.job_id
where job.salary > 1900
group by job.id