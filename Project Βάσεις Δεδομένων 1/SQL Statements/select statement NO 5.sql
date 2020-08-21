select recruiter.username as Recruiter_Username, count(job.id) as Number_of_Jobs, count(interview.candidate) as Number_of_Interviews, avg(job.salary) as Average_Salary
from recruiter
inner join job on recruiter.username = job.recruiter 
left join interview on recruiter.username = interview.recruiter
group by recruiter.username
having count(job.id) > 2
order by avg(job.salary) desc